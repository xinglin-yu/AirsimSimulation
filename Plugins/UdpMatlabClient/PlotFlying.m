clc
% clear

load('Data','Data')

%% 显示飞行路径 2D
fonts=15;
t=Data.t;
len=length(t);
figure 
hold on;grid on;

% title('The flying path of 2D');
%规划路线
load('Trajectory','trajectory')
xp=trajectory(:,1);   yp=trajectory(:,2);
plot(yp,xp,'b*-')
xlabel('y(m)'); ylabel('x(m)');  
%实际飞行路线
x=Data.Posi(:,1);   y=Data.Posi(:,2);   z=Data.Posi(:,3);
plot(y,x,'-r','linewidth',2)

%% 显示飞行路径 3D
figure
view(3)
xlabel('y(m)');ylabel('x(m)');zlabel('z(m)');
% title('The flying path of 3D');
hold on;grid on;
plot3(y,x,z,'-r')


%% 显示飞行高度 z
figure
plot(Data.t,z,'-g')
xlabel('t');ylabel('z(m)');
% title('The flying attitude');
hold on;grid on;


%% 显示飞行姿态 roll pitch
figure
subplot(211)
t=Data.t;
Aphi=Data.Atti(:,1);
Atheta=Data.Atti(:,2);
Apsi=Data.Atti(:,3);
xlabel('t');
hold on;grid on;
plot(t,Aphi,'-r',t,Atheta,'-g')
%设置属性
ylabel('Attitude (rad)','fontsize',10)
h=legend('\phi','\theta','Interpreter','latex')
set(h,'Fontsize',fonts,'Location','southeast','Orientation','horizontal');

%% 显示飞行偏航角 yaw
subplot(212)
plot(t,Apsi,'-b')
xlabel('t');
legend('yaw')
hold on;grid on;
%设置属性
ylabel('$\psi (rad)$','Interpreter','latex','fontsize',fonts)
h=legend('\psi','Interpreter','latex')
set(h,'Fontsize',fonts,'Location','southeast','Orientation','horizontal');

