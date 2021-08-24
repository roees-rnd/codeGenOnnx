# This part showcases incorporation of deployed model in ROS cpp

Make sure that the source files are up to date and correctly imported from 02_CMake stage.

To use this as a ROS package link `rl_explore` to your desired catkin_ws/src directory:
```bash
cd <path to catkin_ws/src>
ln -s <path to repo>/fromOnnx/03_ROS/rl_explore rl_explore
```

TODO: create shell script for importing source code from previous stage (02_CMake). Nore: some files were modified to release dependency from omp (such as in FullyConnectedActivation.cpp line 1502)