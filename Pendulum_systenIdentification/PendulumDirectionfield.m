[x,y] = meshgrid(-9.2:0.25:9.2,-9:0.25:9);
g = 9.81;
l = 0.493;
u = y;
v = -g*sin(x)/l;
L = sqrt(u.^2 + v.^2);
f1 = figure(Name='Pendulum phase protrit');
hold on

q = quiver(x,y,u./L,v./L,0.4);
hold on

q.Color = 'black';
q.AutoScale = 'on';
q.MaxHeadSize = 0.2;
axis([-3.2 3.2 -2 2]);

f = @pend;
% xic = [-6.0 -6.0 -6.0 -6.0 -2.98 -1 -1.5 6 6 6 -6 -2];
% yic = [2.5 1.5 1.98 -2.5 0 0 0 -1.5 -1.98 -2.5 -1.5 0];
xic = [-1.0 -2.0 -2.98 2.98 -0.6 -4.2 4.2 6.12 -6.12 -7.28 7.28 7 -7];
yic = [2.5 1.5 0 0 1 1 -1 2.5 2.5 3 3 -8.3 8.3];
for ic = [xic;yic]
    [t,z] = ode45(f,[0,20],[ic]);
    plot(z(:,1),z(:,2),'b:');
    hold on
end
plot(-2*pi,0,'c*','LineWidth',3.5)
plot(-pi,0,'m*','LineWidth',3.5)
plot(0,0,'c*','LineWidth',3.5)
plot(pi,0,'m*','LineWidth',3.5)
plot(2*pi,0,'c*','LineWidth',3.5)

plot(out.theta.data, out.theta_dot.data,'r','LineWidth',1.5)
title("Pendulum Trajectory",'FontSize', 20)
xlabel('\theta','FontSize', 20)
ylabel('$\dot{\theta}$', 'Interpreter','latex','FontSize', 20)


function dxdt = pend(t,z)
g = 9.81;
l = 0.493;
x1 = z(1);
x2 = z(2);
dxdt = [x2;(- g*sin(x1)/l)];
end