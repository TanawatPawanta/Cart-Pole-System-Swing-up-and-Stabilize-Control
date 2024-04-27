/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Motor.h"
#include "Encoder.h"
#include "Proximity.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//Motor
Motor Cart_motor;
MotorDir dir = CW;
float gain = 0.5;
//Encoders
Encoder Pole_encoder;
Encoder Cart_encoder;
//Proximity
Proximity Prox;
//UART Communication
uint8_t TxBuffer[11];
uint8_t RxBuffer[5];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void ToSimulink(uint8_t header, Encoder* pole_encoder, Encoder* cart_encoder);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  //Star UART in DMA mode
  HAL_UART_Receive_DMA(&huart2, RxBuffer, 4);
  //Start Timer
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);						//Start PWM
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1|TIM_CHANNEL_2);	//Start QEI
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1|TIM_CHANNEL_2);	//Start QEI
  //Initiate Function
  Motor_init(&Cart_motor, &htim3);
  Encoder_init(&Pole_encoder, &htim1, 100);
  Encoder_init(&Cart_encoder, &htim2, 100);
  Proximity_init(&Prox);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  static uint32_t timestamp = 0;


	  if(HAL_GetTick()>=timestamp)
	  {
			timestamp = HAL_GetTick() + 10; // 100 hz
			Motor_run(&Cart_motor);

			Pole_pulse2degree(&Pole_encoder);
			Encoder_getFeedback(&Pole_encoder);
			Encoder_getFeedback(&Cart_encoder);

			ToSimulink(61, &Pole_encoder, &Cart_encoder);

	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void ToSimulink(uint8_t header, Encoder* pole_encoder, Encoder* cart_encoder)
{
	//Transmit low level data to simulink by UART

	/* create data frame START*/
	TxBuffer[0] = header; // header
	//pole position
	TxBuffer[1] = pole_encoder->QEI_read & 0xff;
	TxBuffer[2] = (pole_encoder->QEI_read & 0xff00) >> 8;
	//pole difference position
	TxBuffer[3] = pole_encoder->diff_deg & 0xff;
	TxBuffer[4] = (pole_encoder->diff_deg & 0xff00) >> 8;
	//cart position
	TxBuffer[5] = cart_encoder->QEI_read & 0xff;
	TxBuffer[6] = (cart_encoder->QEI_read & 0xff00) >> 8;
	//cart difference position
	TxBuffer[7] = cart_encoder->diff_QEI & 0xff;
	TxBuffer[8] = (cart_encoder->diff_QEI & 0xff00) >> 8;

	TxBuffer[9] = 10; // /n
	/* create data frame END*/

	//transmit data
	HAL_UART_Transmit_DMA(&huart2,TxBuffer, 10);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//Recieve data from simulink
	if(huart == &huart2)
	{
		if(RxBuffer[0] == 62)
		{
			Motor_setPWM(&Cart_motor, (RxBuffer[1]<<8)|RxBuffer[2]);
			if(RxBuffer[3]==1)
			{
				Motor_setDir(&Cart_motor, CCW);
			}
			else if(RxBuffer[3]==2)
			{
				Motor_setDir(&Cart_motor, CW);
			}
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* proximity interrupt START*/
	if (GPIO_Pin == GPIO_PIN_11)// proximity B
	{
		Prox.Prox_B = ~Prox.Prox_B;
	}
	if (GPIO_Pin == GPIO_PIN_12)// proximity A
	{
		Prox.Prox_A = ~Prox.Prox_A;
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
