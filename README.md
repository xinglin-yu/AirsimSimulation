# AirsimSimulation


The simulation enviroument based on [Airsim](https://github.com/Microsoft/AirSim) 
is developed to verify the dynamic model and the designed control algorithm for quadrotor.
The quadrotor' motion is restrained in a narrow corridor, which represents a much more challenging workspace because any oscillation with the walls may cause the crash of the quadrotor vehicle.
The successive desired waypoints are specified on the critical corners of the maze map.

<div style="float:center;border:solid 1px 000;margin:2px;">
<img src="./Plugins/UdpMatlabClient/Result/MazeMapQuadrotor.bmp"  width = "171" height = "151" />
<img src="./Plugins/UdpMatlabClient/Result/PathMaze.bmp" width = "202" height = "160" />
</div>




<div style="float:center;border:solid 1px 000;margin:2px;">
<img src="./Plugins/UdpMatlabClient/Result/MazeMapQuadrotor.bmp"  width = "171" height = "151"></div>
<div style="float:center;border:solid 1px 000;margin:2px;">
<img src="./Plugins/UdpMatlabClient/Result/PathMaze.bmp" width = "202" height = "160" ></div>


## Video
[![Watch the video](./Plugins/UdpMatlabClient/Result/MazeMap.bmp)](https://www.youtube.com/embed/9PYSBlhq-9o "Play")
[![IMAGE ALT TEXT](http://img.youtube.com/vi/lu3YBzcjbMQ/0.jpg)](https://www.youtube.com/embed/lu3YBzcjbMQ "Play")

* Youtube site: https://youtu.be/9PYSBlhq-9o


[![asciicast](https://asciinema.org/a/42383.png)](https://asciinema.org/a/42383)



## Environment

* Windows 10
* Visual Studio 2015 Professional
* MATLAB 2016
* [Airsim V1.1.8](https://github.com/Microsoft/AirSim) 
* Unreal Engine 4.16
