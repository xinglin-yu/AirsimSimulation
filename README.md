# AirsimSimulation


The simulation enviroument based on [Airsim](https://github.com/Microsoft/AirSim) 
is developed to verify the dynamic model and the designed control algorithm for quadrotor.
The quadrotor' motion is restrained in a narrow corridor, which represents a much more challenging workspace because any oscillation with the walls may cause the crash of the quadrotor vehicle.
The successive desired waypoints are specified on the critical corners of the maze map.

<div style="float:center;border:solid 1px 000;margin:2px;">
<img src="./Plugins/UdpMatlabClient/Result/MazeMap.bmp"  width = "171" height = "151" />
<img src="./Plugins/UdpMatlabClient/Result/MazeMapQuadrotor.bmp"  width = "171" height = "151" />
<img src="./Plugins/UdpMatlabClient/Result/PathMaze.bmp" width = "202" height = "160" />
</div>



## Video
[![Watch the video](./Plugins/UdpMatlabClient/Result/Video.bmp)](https://www.youtube.com/embed/9PYSBlhq-9o "Play")


* Youtube site: https://youtu.be/9PYSBlhq-9o



## Environment

* Windows 10
* Visual Studio 2015 Professional
* MATLAB 2016
* [Airsim V1.1.8](https://github.com/Microsoft/AirSim) 
* Unreal Engine 4.16
