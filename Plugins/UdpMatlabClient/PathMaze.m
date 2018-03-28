clc;
%山脉路线
lineLoop=[
   -2500,-1500;
   4500,-1500;
   4500,500;
   6500,500;
   6500,2500;
   4500,2500;
   4500,4500;
   500,4500;
   500,2500;   
   -1500,2500;
   -1500,6500;
   6500,6500;
   6500,7500;
];

trajectory=(lineLoop-lineLoop(1,:))/100
figure
%中线
xp=trajectory(:,1);   yp=trajectory(:,2);
plot(yp,xp,'b-*','linewidth',2)
grid on; hold on
% xlabel('x'); ylabel('y');
legend('Desired Trajectory')
set(gca,'XTickLabel','','YTickLabel','');

save('Trajectory','trajectory')
