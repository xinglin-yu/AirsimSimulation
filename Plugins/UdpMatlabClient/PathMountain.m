clc;
%山脉路线
lineLoop=[
   -12600,9400;
   -12600,14950;
   -5350,14950;
   -5350,9400;
   -2500,6850;
   -2500,4650;
   2200,3450;
   3300,550;
   3050,-3000;
   1250,-4400;
   -2100,-1700;
   -8200,-3200;
   -10850,2200;
   -9550,4700;
   -11100,6850; 
   -12550,9400;
];

% %矩形路线
% lineLoop=[
%    -12600,9400;
%    -12600,14950;
%    -5350,14950;
%    -5350,9400;
%    -9150,9400;
%    -12600,9400;
% ];

trajectory=(lineLoop-lineLoop(1,:))/100
figure
%中线
xp=trajectory(:,1);   yp=trajectory(:,2);
plot(yp,xp,'b-*')
grid on; hold on
xlabel('y'); ylabel('x');
legend('Desired Trajectory')
    
save('Trajectory','trajectory')
