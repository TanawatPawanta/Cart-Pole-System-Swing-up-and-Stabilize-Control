m = 0.093;  %Kg
l = 0.52;   %m
b = 0.01;
inertia = 0.027; %Kg*m^2
g = 9.81;   %m/s^2

Pole_pos150 = out.polePosition.data;
Pole_velo150 = out.poleVelocity.data;
Pole_velo150 = Pole_velo150(:); 

start = 2779;
stop = 7191;
Pole_pos150_use = Pole_pos150(start:stop);
Pole_velo150_use = Pole_velo150(start:stop);
time = (0:0.01:(stop-start)*0.01)';
save("PoleData150")
%% 
% plot phase space
% plot(Pole_pos90_use,Pole_velo90_use);
% xlabel("theta")
% ylabel("thetadot")
