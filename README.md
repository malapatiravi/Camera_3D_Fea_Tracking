# SFND 3D Object Tracking

Welcome to the final project of the camera course. By completing all the lessons, you now have a solid understanding of keypoint detectors, descriptors, and methods to match them between successive images. Also, you know how to detect objects in an image using the YOLO deep-learning framework. And finally, you know how to associate regions in a camera image with Lidar points in 3D space. Let's take a look at our program schematic to see what we already have accomplished and what's still missing.

<img src="images/course_code_structure.png" width="779" height="414" />

In this final project, you will implement the missing parts in the schematic. To do this, you will complete four major tasks: 
1. First, you will develop a way to match 3D objects over time by using keypoint correspondences. 
2. Second, you will compute the TTC based on Lidar measurements. 
3. You will then proceed to do the same using the camera, which requires to first associate keypoint matches to regions of interest and then to compute the TTC based on those matches. 
4. And lastly, you will conduct various tests with the framework. Your goal is to identify the most suitable detector/descriptor combination for TTC estimation and also to search for problems that can lead to faulty measurements by the camera or Lidar sensor. In the last course of this Nanodegree, you will learn about the Kalman filter, which is a great way to combine the two independent TTC measurements into an improved version which is much more reliable than a single sensor alone can be. But before we think about such things, let us focus on your final project in the camera course. 

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * This must be compiled from source using the `-D OPENCV_ENABLE_NONFREE=ON` cmake flag for testing the SIFT and SURF detectors.
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level project directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./3D_object_tracking`.

#Student Notes
Custom settings
1. #define CUSTOM_RING_BUFFER // Enable this to have custom Ring buffer in the code
2. #define PERF_TESTING //Emable this to have every combination os Detector and Descriptor to run and log results.
Follow the following steps to run the code


## FP.1 Match 3D Objects
Location: Lines 212 to 265 in camFusion_student.cpp
The code calclates the Match betwen previous frame and current frame. 
## FP.2 Compute Lidar-based TTC
Location: Lines 200 to 210 in  camFusion_student.cpp
The code sorts the lidar points first using the sorting comprator.
Once sorted the median  Lidar points details are used to claculate TTC, This avoids using the closest or farway Lidar points and calculating the TTC. 
TTC using lidar is calculated using the formula as follows
TTC = d1*(1.0/frameRate/(d0-d1)
## FP.3 Associate Keypoint Correspondences with Bounding Boxes
Location: Lines 133 to 150 in camFusion_student.cpp
## FP.4 Compute Camera-based TTC
Location: Lines 156 to 190 camFusion_student.cpp
## FP.5 Performance Evaluation 1
TTC using Lidar maximum value is 16.689. This was the heighest but for the same frame the value for camera is 14.47 sec. The difference between TTC Camera and TTC Lidar is resonable. 
The maximum difference between TTC Lidar and TTC Camera is 3.4 seconds at max. The exact TTC Lidar value is 11.96 and TTC Camera values is 15.34. I think this is not resonable given the difference of 3.4 seconds difference for the same image. 
But when we look over all the images this does not show huge impact in TTC value at the end. 
## FP.6 Performance Evaluation 2
