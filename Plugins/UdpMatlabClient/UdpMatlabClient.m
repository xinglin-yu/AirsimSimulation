clc
% clear

ip='192.168.1.102'; 
port=8085;


%% 窗口初始化
% figure('toolbar','none','menubar','none','Name','Flying','NumberTitle','off');
figure('menubar','none','Name','Flying','NumberTitle','off');
%set(gcf,'Position',[1000 0 920 1080]); %右边
set(gcf,'Position',[0 10 920 1040]); %左下角

%显示飞行路径 2D
fonts=15;
subplot(3,2,1) 
hold on;grid on;
xlabel('y');
ylabel('x');
title('The flying path of 2D');
%显示飞行路径 3D
subplot(3,2,2) 
view(3)
xlabel('y(m)');ylabel('x(m)');zlabel('z(m)');
title('The flying path of 3D');
hold on;grid on;
%显示飞行姿态 roll
subplot(3,2,[3,4]) 
xlabel('t(s)');ylabel('rad');
title('The flying attitude');
hold on;grid on;
%显示yaw
subplot(3,2,[5,6]) 
xlabel('t(s)');ylabel('yaw(rad)');
title('The flying attitude of yaw');
hold on;grid on;
%需要暂停一下才能绘图
pause(0.001);

%% 接收数据 初始化
% Data 用于存储所有的数据
Data.AngV=[];% x y z
Data.LinV=[];
Data.Atti=[];
Data.Posi=[];
Data.Acce=[];
Data.AccN=[];
Data.t=[];
Data.times=0; %接收次数


%% UDP接收并处理
data_all=[];%用于存储所有的数据
u = udp(ip, port, 'Timeout', 100,'InputBufferSize',10240);%连接这个ip和这个端口的UDP服务器，60秒超时，缓冲大小1024
fopen(u);
fwrite(u,-15.6,'float');    %发送一段数据给udp服务器。服务器好知道matlab的ip和端口

t=1;
recLen=1;
tc=0.5; %时间变换系数
while(1)
    %接收
    receive = fread(u,recLen,'float');
    receive=receive';
    %whos receive  
 
    %数据解析
    data.Point=receive(1); %启动点
    data.AngV=receive(2:4);       Data.AngV=[Data.AngV;data.AngV];  %角速度 
    data.LinV=receive(5:7);       Data.LinV=[Data.LinV;data.LinV];  %线速度
    data.Atti=receive(8:10);      Data.Atti=[Data.Atti;data.Atti];  %角度
    data.Posi=receive(11:13);     Data.Posi=[Data.Posi;data.Posi];  %位置
    data.Acce=receive(14:16);     Data.Acce=[Data.Acce;data.Acce];  %加速度
    data.AccN=receive(17:19);     Data.AccN=[Data.AccN;data.AccN];  %加速度 噪声值  
   %跟新时间
    Data.t=[Data.t;Data.times*tc];
    Data.times=(Data.times+1);  %接收次数
   
 
    %显示飞行路径 2D
    subplot(3,2,1)
    %路线
    load('Trajectory','trajectory')
    xp=trajectory(:,1);   yp=trajectory(:,2);
    plot(yp,xp,'b-*')
    grid on; hold on
    xlabel('y'); ylabel('x');  
    %路径
    x=Data.Posi(:,1);   y=Data.Posi(:,2);   z=Data.Posi(:,3);
    plot(y,x,'-r','linewidth',2)
    legend('trajectory','real path')
    
    %显示飞行路径 3D
    subplot(3,2,2) 
    plot3(y,x,z,'-r')
    %显示飞行姿态
    subplot(3,2,[3,4]) 
    plot(Data.t,Data.Atti(:,1),'-r',Data.t,Data.Atti(:,2),'-g')
    %设置属性
    ylabel('Attitude (rad)')
    h=legend('\phi','\theta','Interpreter','latex')
    set(h,'Location','northwest','Orientation','vertical');

    legend('roll','pitch')
    %显示飞行偏航角
    subplot(3,2,[5,6])
    plot(Data.t,Data.Atti(:,3),'-b')
    %设置属性
    ylabel('$\psi (rad)$','Interpreter','latex')
    h=legend('yaw')
    set(h,'Location','northwest','Orientation','horizontal');

    %暂停一下显示
    pause(0.001); 
    %发送
    fwrite(u,-1,'float');
    t=t+1
    save('Data','Data')
end

fclose(u);
delete(u);
