%% extract position velocity and time
num_exp = 6;
for EXP = 1:num_exp
    load(sprintf('Pole_rawData_%d.mat',EXP))
    position = out.polePosition.data;
    velocity = out.poleVelocity.data;
    time = out.tout;
    clear('out')
    save(sprintf('Data_exp_%d',EXP))
end

%% Load and Visualize data
% clear;
initial_pos = 1.5703; %PI/2
interval = 15200; % timestep(2 min 30 sec) 
experiments_position = [];
experiments_velocity = [];
f1 = figure('Name','Angular displacement');
hold on
f2 = figure('Name','Angular velocity');
hold on
use_time = (0:0.01:152)';
for i = 1:6
    load(sprintf('Data_exp_%d.mat',i))
    t_i = find(position >= initial_pos, 1, 'last') - 1; %finding initial time
    t_f = t_i + interval; %finding final time
    use_position = position(t_i:t_f);
    experiments_position = cat(2,experiments_position,use_position);
    use_velocity = reshape(velocity(t_i:t_f),interval+1,[]);
    experiments_velocity = cat(2,experiments_velocity,use_velocity);
    figure(f1);
    plot(use_time,use_position,'DisplayName',sprintf('Exp %d',i));
    figure(f2);
    plot(use_time,use_velocity,'DisplayName',sprintf('Exp %d',i));
    clear('use_position','use_velocity','t_i','t_f','position','velocity')
end
figure(f1)
grid on
xlabel('Time [sec]')
ylabel('Angular displacement [rad]')
lgd = legend;
lgd.NumColumns = 2;

figure(f2)
grid on
xlabel('Time [sec]')
ylabel('Angular velocity [rad/s]')
lgd = legend;
lgd.NumColumns = 2;

position_exp1 = experiments_position(:,1);
position_exp2 = experiments_position(:,2);
position_exp3 = experiments_position(:,3);
position_exp4 = experiments_position(:,4);
position_exp5 = experiments_position(:,5);
position_exp6 = experiments_position(:,6);

velocity_exp1 = experiments_velocity(:,1);
velocity_exp2 = experiments_velocity(:,2);
velocity_exp3 = experiments_velocity(:,3);
velocity_exp4 = experiments_velocity(:,4);
velocity_exp5 = experiments_velocity(:,5);
velocity_exp6 = experiments_velocity(:,6);
% min: Exp3 max: Exp6  => Op1
% min: Exp4 max: Exp1  => Op2

%% finding peak from experiment
exp_num_peak = zeros(6,1);
exp_peak_vaule = [];

exp_data = position_exp6;
[exp_peaks,exp_locs] = findpeaks(exp_data);
exp_num_peak(i) = numel(exp_peaks);
max_peak = max(exp_num_peak);
exp_num_cycles = numel(exp_peaks)-1;
exp_total_time = (exp_locs(end) - exp_locs(1))*0.01;    %secound
exp_avg_period = exp_total_time/exp_num_cycles;
plot((1:numel(exp_peaks))',exp_peaks)
peak_angle = cat(2,(1:numel(exp_peaks))',exp_peaks);
peak_angle = cat(2,peak_angle,exp_peaks.*180/pi);
peak_angle_exp6 = peak_angle;
% % select interested peak between 70-4 degree
% interested_peak = find(peak_angle(:,3)<=70,1,"first")
% figure("Name","exp_peaks");
% findpeaks(exp_data)
% title('experiment peaks')

%% finding peak from model 
model_data = SDOSimTest_Log.simulationData1.Data;
[model_peaks,model_locs] = findpeaks(model_data);
model_num_cycles = numel(model_peaks)-1;
model_total_time = (model_locs(end) - model_locs(1))*0.01;    %secound
model_avg_period = model_total_time/model_num_cycles;
figure("Name","model_peaks");
findpeaks(model_data)
title('model peaks')
%% Validation
position_sim = SDOSimTest_Log.position_sim.Data;
velocity_sim = SDOSimTest_Log.velocity_sim.Data;
f3 = figure('Name','Angular displacement: validation');
hold on
f4 = figure('Name','Angular velocity: validation');
hold on
for n=1:6
    figure(f3);
    plot(use_time,experiments_position(:,n),'DisplayName',sprintf('Exp %d',n));
    figure(f4);
    plot(use_time,experiments_velocity(:,n),'DisplayName',sprintf('Exp %d',n));
end

figure(f3);
plot(use_time,position_sim,'DisplayName',sprintf('simulation'));
grid on
xlabel('Time [sec]')
ylabel('Angular displacement [rad]')
lgd = legend;
lgd.NumColumns = 2;

figure(f4);
plot(use_time,velocity_sim,'DisplayName',sprintf('simulation'));
grid on
xlabel('Time [sec]')
ylabel('Angular velocity [rad/s]')
lgd = legend;
lgd.NumColumns = 2;
error1_t = rmse(position_sim, position_exp3);
error1 = rmse(position_sim(1:10000), position_exp3(1:10000));
%% Validation2
position_test = out.polePosition.data;
velocity_test = out.poleVelocity.data;
velocity_test = reshape(velocity_test(:,:,:),numel(velocity_test),[]);
start = 934;
stop = 14434;
use_position_test = position_test(start:stop);
use_velocity_test = velocity_test(start:stop);

position_sim = SDOSimTest_Log.position_sim.Data;
velocity_sim = SDOSimTest_Log.velocity_sim.Data;

f5 = figure('Name','Angular displacement: validation2');
f6 = figure('Name','Angular velocity: validation2');
use_time = (0:0.01:135)';
figure(f5);
hold on
plot(use_time,position_sim,'DisplayName',sprintf('simulation'));
plot(use_time,use_position_test,'DisplayName',sprintf('Exp'));
grid on
xlabel('Time [sec]')
ylabel('Angular displacement [rad]')
lgd = legend;
lgd.NumColumns = 2;

figure(f6);
hold on
plot(use_time,velocity_sim,'DisplayName',sprintf('simulation'));
plot(use_time,use_velocity_test,'DisplayName',sprintf('Exp'));
grid on
xlabel('Time [sec]')
ylabel('Angular velocity [rad/s]')
lgd = legend;
lgd.NumColumns = 2;

error2 = rmse(position_sim, use_position_test);