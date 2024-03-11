m = 0.093;  %Kg
l = 0.52;   %m
b = 0.01;
innertia = 0.00209; %Kg*m^2
g = 9.81;   %m/s^2

% Pole_pos15 = out.polePosition.data;
% Pole_velo15 = out.poleVelocity.data;
% Pole_velo15 = Pole_velo15(:); 
% 
% start = 1662;
% stop = 2401;
% Pole_pos15_use = Pole_pos15(start:stop);
% Pole_velo15_use = Pole_velo15(start:stop);
% time = (0:0.01:(stop-start)*0.01)';
% save("PoleData15")
%% 
% plot phase space
plot(Pole_pos90_use,Pole_velo90_use);
xlabel("theta")
ylabel("thetadot")
