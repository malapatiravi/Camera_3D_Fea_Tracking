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

# Student Notes
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
I have tested every combination of detector and descriptor using the #define PERF_TESTING
1. I observed that maximum diff of time between Camera TTC and Lidar TTC is with ORB and SIFT so they dont work together. the diff in time is 486.222s
2. The best i have seen is with SHITOMASI detector and ORB descriptor is ORB. The diff is 0.010265s
3. SHITOMASI det and BRISK desc seems to work well. But this comoibation may take more time. So this is not recommended. 
4. FAST dete Type and ORB Desc Type works well with respect to time and also the maximum time diff is not more than 4 sec. 
5. The following table provides more information on which combination performs better. 

```
Det Type|Des Type|TTC Lidar|TTC Camera|Diff|abs diff|
|:-----------:|:------------:|:--------:|:--------:|:-------:|:--------|
SHITOMASI|BRISK|12.5156|13.9019|1.38632|1.38632|
SHITOMASI|BRISK|12.6142|12.9876|0.373362|0.373362|
SHITOMASI|BRISK|14.091|13.2474|-0.843567|0.843567|
SHITOMASI|BRISK|16.6894|12.8675|-3.82185|3.82185|
SHITOMASI|BRISK|15.9082|13.4476|-2.46065|2.46065|
SHITOMASI|BRISK|12.6787|13.5266|0.847853|0.847853|
SHITOMASI|BRISK|11.9844|12.7172|0.732857|0.732857|
SHITOMASI|BRISK|13.1241|13.712|0.587852|0.587852|
SHITOMASI|BRISK|13.0241|11.5126|-1.5115|1.5115|
SHITOMASI|BRISK|11.1746|13.456|2.28139|2.28139|
SHITOMASI|BRISK|12.8086|11.9816|-0.827026|0.827026|
SHITOMASI|BRISK|8.95978|11.8135|2.85372|2.85372|
SHITOMASI|BRISK|9.96439|12.0367|2.0723|2.0723|
SHITOMASI|BRISK|9.59863|11.342|1.74338|1.74338|
SHITOMASI|BRISK|8.57352|9.0531|0.479579|0.479579|
SHITOMASI|BRISK|9.51617|10.4612|0.945076|0.945076|
SHITOMASI|BRISK|9.54658|11.6823|2.13575|2.13575|
SHITOMASI|BRISK|8.3988|9.73863|1.33983|1.33983|
SHITOMASI|BRIEF|12.5156|14.0747|1.55912|1.55912|
SHITOMASI|BRIEF|12.6142|13.8102|1.19596|1.19596|
SHITOMASI|BRIEF|14.091|11.712|-2.379|2.379|
SHITOMASI|BRIEF|16.6894|13.6007|-3.08865|3.08865|
SHITOMASI|BRIEF|15.9082|12.3|-3.60823|3.60823|
SHITOMASI|BRIEF|12.6787|13.2703|0.591609|0.591609|
SHITOMASI|BRIEF|11.9844|21.3301|9.34575|9.34575|
SHITOMASI|BRIEF|13.1241|12.5199|-0.604197|0.604197|
SHITOMASI|BRIEF|13.0241|11.6077|-1.41639|1.41639|
SHITOMASI|BRIEF|11.1746|13.6717|2.49701|2.49701|
SHITOMASI|BRIEF|12.8086|11.7805|-1.02808|1.02808|
SHITOMASI|BRIEF|8.95978|11.7604|2.80058|2.80058|
SHITOMASI|BRIEF|9.96439|11.7506|1.78625|1.78625|
SHITOMASI|BRIEF|9.59863|11.6524|2.0538|2.0538|
SHITOMASI|BRIEF|8.57352|11.2953|2.72181|2.72181|
SHITOMASI|BRIEF|9.51617|11.5174|2.00119|2.00119|
SHITOMASI|BRIEF|9.54658|11.1869|1.64029|1.64029|
SHITOMASI|BRIEF|8.3988|7.96101|-0.437791|0.437791|
SHITOMASI|ORB|12.5156|13.5031|0.987549|0.987549|
SHITOMASI|ORB|12.6142|12.6706|0.0563915|0.0563915|
SHITOMASI|ORB|14.091|11.99|-2.101|2.101|
SHITOMASI|ORB|16.6894|12.5425|-4.1469|4.1469|
SHITOMASI|ORB|15.9082|12.1886|-3.71964|3.71964|
SHITOMASI|ORB|12.6787|13.7364|1.05769|1.05769|
SHITOMASI|ORB|11.9844|11.9741|-0.010265|0.010265|
SHITOMASI|ORB|13.1241|12.5072|-0.616947|0.616947|
SHITOMASI|ORB|13.0241|11.3432|-1.68095|1.68095|
SHITOMASI|ORB|11.1746|13.3149|2.14027|2.14027|
SHITOMASI|ORB|12.8086|11.3246|-1.48398|1.48398|
SHITOMASI|ORB|8.95978|11.5372|2.57745|2.57745|
SHITOMASI|ORB|9.96439|12.3068|2.34242|2.34242|
SHITOMASI|ORB|9.59863|11.342|1.74338|1.74338|
SHITOMASI|ORB|8.57352|10.4584|1.8849|1.8849|
SHITOMASI|ORB|9.51617|10.8713|1.35511|1.35511|
SHITOMASI|ORB|9.54658|10.7263|1.1797|1.1797|
SHITOMASI|ORB|8.3988|8.06211|-0.336698|0.336698|
SHITOMASI|SIFT|12.5156|14.2804|1.76482|1.76482|
SHITOMASI|SIFT|12.6142|12.9001|0.285861|0.285861|
SHITOMASI|SIFT|14.091|11.6087|-2.48236|2.48236|
SHITOMASI|SIFT|16.6894|12.9209|-3.76847|3.76847|
SHITOMASI|SIFT|15.9082|12.1886|-3.71964|3.71964|
SHITOMASI|SIFT|12.6787|13.0553|0.376627|0.376627|
SHITOMASI|SIFT|11.9844|12.6612|0.676806|0.676806|
SHITOMASI|SIFT|13.1241|12.1376|-0.986508|0.986508|
SHITOMASI|SIFT|13.0241|11.9899|-1.03424|1.03424|
SHITOMASI|SIFT|11.1746|13.5009|2.32624|2.32624|
SHITOMASI|SIFT|12.8086|12.1033|-0.705309|0.705309|
SHITOMASI|SIFT|8.95978|11.8967|2.93693|2.93693|
SHITOMASI|SIFT|9.96439|11.6227|1.65834|1.65834|
SHITOMASI|SIFT|9.59863|10.9335|1.33491|1.33491|
SHITOMASI|SIFT|8.57352|12.5287|3.95516|3.95516|
SHITOMASI|SIFT|9.51617|10.68|1.16387|1.16387|
SHITOMASI|SIFT|9.54658|10.7642|1.21763|1.21763|
SHITOMASI|SIFT|8.3988|9.52513|1.12633|1.12633|
HARRIS|BRISK|12.5156|10.9082|-1.60738|1.60738|
HARRIS|BRISK|12.6142|10.195|-2.41922|2.41922|
HARRIS|BRISK|14.091|-80.8525|-94.9435|94.9435|
HARRIS|BRISK|16.6894|11.3951|-5.29424|5.29424|
HARRIS|BRISK|15.9082|222|222|222|
HARRIS|BRISK|12.6787|12.9945|0.315773|0.315773|
HARRIS|BRISK|11.9844|12.2|0.215649|0.215649|
HARRIS|BRISK|13.1241|25.116|11.9919|11.9919|
HARRIS|BRISK|13.0241|14.2079|1.18381|1.18381|
HARRIS|BRISK|11.1746|222|222|222|
HARRIS|BRISK|12.8086|11.6702|-1.13837|1.13837|
HARRIS|BRISK|8.95978|11.6948|2.73503|2.73503|
HARRIS|BRISK|9.96439|284.161|274.197|274.197|
HARRIS|BRISK|9.59863|11.2961|1.69748|1.69748|
HARRIS|BRISK|8.57352|-14.7808|-23.3543|23.3543|
HARRIS|BRISK|9.51617|6.65726|-2.85891|2.85891|
HARRIS|BRISK|9.54658|12.5848|3.03826|3.03826|
HARRIS|BRISK|8.3988|222|222|222|
HARRIS|BRIEF|12.5156|10.9082|-1.60738|1.60738|
HARRIS|BRIEF|12.6142|11.0081|-1.6061|1.6061|
HARRIS|BRIEF|14.091|-11.4731|-25.5642|25.5642|
HARRIS|BRIEF|16.6894|11.3951|-5.29424|5.29424|
HARRIS|BRIEF|15.9082|35.3833|19.475|19.475|
HARRIS|BRIEF|12.6787|15.2483|2.56955|2.56955|
HARRIS|BRIEF|11.9844|14.2744|2.29005|2.29005|
HARRIS|BRIEF|13.1241|13.5704|0.446298|0.446298|
HARRIS|BRIEF|13.0241|3.90277|-9.12135|9.12135|
HARRIS|BRIEF|11.1746|222|222|222|
HARRIS|BRIEF|12.8086|11.6702|-1.13837|1.13837|
HARRIS|BRIEF|8.95978|11.6948|2.73503|2.73503|
HARRIS|BRIEF|9.96439|14.1613|4.19696|4.19696|
HARRIS|BRIEF|9.59863|5.66097|-3.93766|3.93766|
HARRIS|BRIEF|8.57352|222|222|222|
HARRIS|BRIEF|9.51617|6.7641|-2.75207|2.75207|
HARRIS|BRIEF|9.54658|12.5848|3.03826|3.03826|
HARRIS|BRIEF|8.3988|222|222|222|
HARRIS|ORB|12.5156|10.9082|-1.60738|1.60738|
HARRIS|ORB|12.6142|11.0081|-1.6061|1.6061|
HARRIS|ORB|14.091|-11.4731|-25.5642|25.5642|
HARRIS|ORB|16.6894|11.3951|-5.29424|5.29424|
HARRIS|ORB|15.9082|34.1473|18.239|18.239|
HARRIS|ORB|12.6787|13.6217|0.942989|0.942989|
HARRIS|ORB|11.9844|13.497|1.51263|1.51263|
HARRIS|ORB|13.1241|13.5704|0.446298|0.446298|
HARRIS|ORB|13.0241|14.2079|1.18381|1.18381|
HARRIS|ORB|11.1746|10.6219|-0.552736|0.552736|
HARRIS|ORB|12.8086|11.6702|-1.13837|1.13837|
HARRIS|ORB|8.95978|11.6948|2.73503|2.73503|
HARRIS|ORB|9.96439|13.9608|3.99644|3.99644|
HARRIS|ORB|9.59863|6.06984|-3.52879|3.52879|
HARRIS|ORB|8.57352|222|222|222|
HARRIS|ORB|9.51617|6.71705|-2.79912|2.79912|
HARRIS|ORB|9.54658|12.5848|3.03826|3.03826|
HARRIS|ORB|8.3988|222|222|222|
HARRIS|FREAK|12.5156|8.81335|-3.70225|3.70225|
HARRIS|FREAK|12.6142|10.195|-2.41922|2.41922|
HARRIS|FREAK|14.091|-10.295|-24.386|24.386|
HARRIS|FREAK|16.6894|11.7693|-4.92006|4.92006|
HARRIS|FREAK|15.9082|44.9166|29.0084|29.0084|
HARRIS|FREAK|12.6787|13.5599|0.881141|0.881141|
HARRIS|FREAK|11.9844|13.497|1.51263|1.51263|
HARRIS|FREAK|13.1241|12.9162|-0.207908|0.207908|
HARRIS|FREAK|13.0241|15.4179|2.39381|2.39381|
HARRIS|FREAK|11.1746|10.6219|-0.552736|0.552736|
HARRIS|FREAK|12.8086|11.6702|-1.13837|1.13837|
HARRIS|FREAK|8.95978|11.6948|2.73503|2.73503|
HARRIS|FREAK|9.96439|13.9608|3.99644|3.99644|
HARRIS|FREAK|9.59863|12.1403|2.54162|2.54162|
HARRIS|FREAK|8.57352|222|222|222|
HARRIS|FREAK|9.51617|6.6376|-2.87857|2.87857|
HARRIS|FREAK|9.54658|nan|222|222|
HARRIS|FREAK|8.3988|nan|222|222|
HARRIS|SIFT|12.5156|10.9082|-1.60738|1.60738|
HARRIS|SIFT|12.6142|52.7952|40.1809|40.1809|
HARRIS|SIFT|14.091|-80.8525|-94.9435|94.9435|
HARRIS|SIFT|16.6894|11.3951|-5.29424|5.29424|
HARRIS|SIFT|15.9082|13.6432|-2.26503|2.26503|
HARRIS|SIFT|12.6787|27.8744|15.1957|15.1957|
HARRIS|SIFT|11.9844|13.497|1.51263|1.51263|
HARRIS|SIFT|13.1241|13.5704|0.446298|0.446298|
HARRIS|SIFT|13.0241|12.9165|-0.107644|0.107644|
HARRIS|SIFT|11.1746|222|222|222|
HARRIS|SIFT|12.8086|11.2142|-1.59438|1.59438|
HARRIS|SIFT|8.95978|11.6948|2.73503|2.73503|
HARRIS|SIFT|9.96439|13.9608|3.99644|3.99644|
HARRIS|SIFT|9.59863|8.87966|-0.71897|0.71897|
HARRIS|SIFT|8.57352|222|222|222|
HARRIS|SIFT|9.51617|7.29175|-2.22442|2.22442|
HARRIS|SIFT|9.54658|12.5848|3.03826|3.03826|
HARRIS|SIFT|8.3988|222|222|222|
FAST|BRISK|12.5156|12.6908|0.175229|0.175229|
FAST|BRISK|12.6142|12.3534|-0.260875|0.260875|
FAST|BRISK|14.091|12.3379|-1.75315|1.75315|
FAST|BRISK|16.6894|12.7|-3.98938|3.98938|
FAST|BRISK|15.9082|13.8295|-2.07872|2.07872|
FAST|BRISK|12.6787|12.1823|-0.49641|0.49641|
FAST|BRISK|11.9844|12.9291|0.944752|0.944752|
FAST|BRISK|13.1241|12.3971|-0.726994|0.726994|
FAST|BRISK|13.0241|12.4101|-0.614025|0.614025|
FAST|BRISK|11.1746|13.8255|2.65082|2.65082|
FAST|BRISK|12.8086|12.0998|-0.708807|0.708807|
FAST|BRISK|8.95978|12.5921|3.63229|3.63229|
FAST|BRISK|9.96439|11.6909|1.72648|1.72648|
FAST|BRISK|9.59863|11.5009|1.90224|1.90224|
FAST|BRISK|8.57352|11.1439|2.57042|2.57042|
FAST|BRISK|9.51617|11.1636|1.64743|1.64743|
FAST|BRISK|9.54658|10.5164|0.969849|0.969849|
FAST|BRISK|8.3988|11.7623|3.36349|3.36349|
FAST|BRIEF|12.5156|11.7503|-0.765342|0.765342|
FAST|BRIEF|12.6142|11.7583|-0.855914|0.855914|
FAST|BRIEF|14.091|13.955|-0.13597|0.13597|
FAST|BRIEF|16.6894|13.1309|-3.55846|3.55846|
FAST|BRIEF|15.9082|14.8298|-1.07848|1.07848|
FAST|BRIEF|12.6787|13.5942|0.915441|0.915441|
FAST|BRIEF|11.9844|13.2774|1.29309|1.29309|
FAST|BRIEF|13.1241|12.7749|-0.349179|0.349179|
FAST|BRIEF|13.0241|12.8008|-0.22334|0.22334|
FAST|BRIEF|11.1746|13.0092|1.83461|1.83461|
FAST|BRIEF|12.8086|11.8702|-0.938388|0.938388|
FAST|BRIEF|8.95978|11.5256|2.56577|2.56577|
FAST|BRIEF|9.96439|11.7066|1.74217|1.74217|
FAST|BRIEF|9.59863|10.6452|1.04653|1.04653|
FAST|BRIEF|8.57352|11.5312|2.95764|2.95764|
FAST|BRIEF|9.51617|10.323|0.806865|0.806865|
FAST|BRIEF|9.54658|9.89452|0.347944|0.347944|
FAST|BRIEF|8.3988|11.5081|3.10927|3.10927|
FAST|ORB|12.5156|11.3326|-1.18304|1.18304|
FAST|ORB|12.6142|12.3289|-0.285391|0.285391|
FAST|ORB|14.091|12.318|-1.773|1.773|
FAST|ORB|16.6894|12.6028|-4.08654|4.08654|
FAST|ORB|15.9082|13.2618|-2.6464|2.6464|
FAST|ORB|12.6787|12.4061|-0.272632|0.272632|
FAST|ORB|11.9844|13.6643|1.67992|1.67992|
FAST|ORB|13.1241|12.7764|-0.34775|0.34775|
FAST|ORB|13.0241|12.4617|-0.562433|0.562433|
FAST|ORB|11.1746|12.8653|1.69064|1.69064|
FAST|ORB|12.8086|11.947|-0.861619|0.861619|
FAST|ORB|8.95978|11.2036|2.24384|2.24384|
FAST|ORB|9.96439|11.7216|1.75726|1.75726|
FAST|ORB|9.59863|10.7766|1.17798|1.17798|
FAST|ORB|8.57352|10.4391|1.86561|1.86561|
FAST|ORB|9.51617|10.1523|0.636149|0.636149|
FAST|ORB|9.54658|9.25534|-0.291242|0.291242|
FAST|ORB|8.3988|11.3881|2.9893|2.9893|
FAST|FREAK|12.5156|12.0538|-0.461774|0.461774|
FAST|FREAK|12.6142|12.6011|-0.0131201|0.0131201|
FAST|FREAK|14.091|13.2302|-0.860809|0.860809|
FAST|FREAK|16.6894|13.7727|-2.91666|2.91666|
FAST|FREAK|15.9082|13.0459|-2.86235|2.86235|
FAST|FREAK|12.6787|12.1987|-0.480041|0.480041|
FAST|FREAK|11.9844|12.9963|1.01196|1.01196|
FAST|FREAK|13.1241|12.5528|-0.571325|0.571325|
FAST|FREAK|13.0241|12.8937|-0.130429|0.130429|
FAST|FREAK|11.1746|12.8249|1.65026|1.65026|
FAST|FREAK|12.8086|12.2504|-0.558236|0.558236|
FAST|FREAK|8.95978|12.1867|3.22694|3.22694|
FAST|FREAK|9.96439|11.5554|1.59102|1.59102|
FAST|FREAK|9.59863|11.0837|1.48506|1.48506|
FAST|FREAK|8.57352|11.1409|2.56733|2.56733|
FAST|FREAK|9.51617|11.2241|1.70791|1.70791|
FAST|FREAK|9.54658|10.3661|0.819519|0.819519|
FAST|FREAK|8.3988|11.5605|3.16173|3.16173|
FAST|SIFT|12.5156|12.2747|-0.240918|0.240918|
FAST|SIFT|12.6142|11.3986|-1.21566|1.21566|
FAST|SIFT|14.091|14.0617|-0.029332|0.029332|
FAST|SIFT|16.6894|13.1232|-3.56622|3.56622|
FAST|SIFT|15.9082|14.3505|-1.55771|1.55771|
FAST|SIFT|12.6787|12.828|0.1493|0.1493|
FAST|SIFT|11.9844|12.409|0.424632|0.424632|
FAST|SIFT|13.1241|12.6899|-0.434183|0.434183|
FAST|SIFT|13.0241|12.5506|-0.473529|0.473529|
FAST|SIFT|11.1746|12.6708|1.49619|1.49619|
FAST|SIFT|12.8086|11.8062|-1.00239|1.00239|
FAST|SIFT|8.95978|11.1726|2.21287|2.21287|
FAST|SIFT|9.96439|11.5632|1.59876|1.59876|
FAST|SIFT|9.59863|11.3432|1.74454|1.74454|
FAST|SIFT|8.57352|10.8743|2.30076|2.30076|
FAST|SIFT|9.51617|10.1671|0.650893|0.650893|
FAST|SIFT|9.54658|9.44427|-0.102313|0.102313|
FAST|SIFT|8.3988|10.6624|2.26362|2.26362|
BRISK|BRISK|12.5156|13.4086|0.893008|0.893008|
BRISK|BRISK|12.6142|21.5276|8.9134|8.9134|
BRISK|BRISK|14.091|12.625|-1.46601|1.46601|
BRISK|BRISK|16.6894|15.2037|-1.48564|1.48564|
BRISK|BRISK|15.9082|27.6679|11.7597|11.7597|
BRISK|BRISK|12.6787|18.3114|5.63273|5.63273|
BRISK|BRISK|11.9844|17.1427|5.15834|5.15834|
BRISK|BRISK|13.1241|16.0991|2.97495|2.97495|
BRISK|BRISK|13.0241|14.801|1.77691|1.77691|
BRISK|BRISK|11.1746|13.9297|2.75505|2.75505|
BRISK|BRISK|12.8086|13.1359|0.327275|0.327275|
BRISK|BRISK|8.95978|11.3409|2.38113|2.38113|
BRISK|BRISK|9.96439|11.8565|1.89211|1.89211|
BRISK|BRISK|9.59863|12.3978|2.79915|2.79915|
BRISK|BRISK|8.57352|12.7089|4.13539|4.13539|
BRISK|BRISK|9.51617|11.503|1.98687|1.98687|
BRISK|BRISK|9.54658|9.29379|-0.252789|0.252789|
BRISK|BRISK|8.3988|10.7753|2.37649|2.37649|
BRISK|BRIEF|12.5156|12.8448|0.329151|0.329151|
BRISK|BRIEF|12.6142|16.8618|4.2476|4.2476|
BRISK|BRIEF|14.091|11.6672|-2.42379|2.42379|
BRISK|BRIEF|16.6894|20.5725|3.88311|3.88311|
BRISK|BRIEF|15.9082|19.7052|3.79695|3.79695|
BRISK|BRIEF|12.6787|17.5642|4.88549|4.88549|
BRISK|BRIEF|11.9844|15.5809|3.5965|3.5965|
BRISK|BRIEF|13.1241|18.7451|5.62094|5.62094|
BRISK|BRIEF|13.0241|15.4585|2.43438|2.43438|
BRISK|BRIEF|11.1746|11.4809|0.306308|0.306308|
BRISK|BRIEF|12.8086|13.3636|0.555024|0.555024|
BRISK|BRIEF|8.95978|14.3071|5.34729|5.34729|
BRISK|BRIEF|9.96439|12.3266|2.36225|2.36225|
BRISK|BRIEF|9.59863|10.9457|1.34706|1.34706|
BRISK|BRIEF|8.57352|11.6289|3.05541|3.05541|
BRISK|BRIEF|9.51617|12.1739|2.65772|2.65772|
BRISK|BRIEF|9.54658|11.3792|1.83263|1.83263|
BRISK|BRIEF|8.3988|10.7022|2.30337|2.30337|
BRISK|ORB|12.5156|14.6831|2.16748|2.16748|
BRISK|ORB|12.6142|20.3646|7.75031|7.75031|
BRISK|ORB|14.091|13.2508|-0.840188|0.840188|
BRISK|ORB|16.6894|16.3706|-0.318751|0.318751|
BRISK|ORB|15.9082|20.2973|4.38905|4.38905|
BRISK|ORB|12.6787|21.3674|8.68864|8.68864|
BRISK|ORB|11.9844|16.4615|4.47715|4.47715|
BRISK|ORB|13.1241|16.1576|3.0335|3.0335|
BRISK|ORB|13.0241|14.9216|1.89751|1.89751|
BRISK|ORB|11.1746|11.5139|0.339228|0.339228|
BRISK|ORB|12.8086|13.7091|0.900508|0.900508|
BRISK|ORB|8.95978|11.024|2.0642|2.0642|
BRISK|ORB|9.96439|11.7553|1.79095|1.79095|
BRISK|ORB|9.59863|12.4047|2.80611|2.80611|
BRISK|ORB|8.57352|11.4092|2.83565|2.83565|
BRISK|ORB|9.51617|11.2864|1.77021|1.77021|
BRISK|ORB|9.54658|9.94177|0.39519|0.39519|
BRISK|ORB|8.3988|11.4769|3.07809|3.07809|
BRISK|FREAK|12.5156|12.7574|0.241844|0.241844|
BRISK|FREAK|12.6142|24.137|11.5228|11.5228|
BRISK|FREAK|14.091|13.9605|-0.130522|0.130522|
BRISK|FREAK|16.6894|13.9445|-2.74486|2.74486|
BRISK|FREAK|15.9082|23.0655|7.15728|7.15728|
BRISK|FREAK|12.6787|16.8726|4.19391|4.19391|
BRISK|FREAK|11.9844|15.5199|3.53557|3.53557|
BRISK|FREAK|13.1241|18.7996|5.67552|5.67552|
BRISK|FREAK|13.0241|14.9704|1.94626|1.94626|
BRISK|FREAK|11.1746|13.7428|2.56811|2.56811|
BRISK|FREAK|12.8086|12.8798|0.0712148|0.0712148|
BRISK|FREAK|8.95978|11.4488|2.48906|2.48906|
BRISK|FREAK|9.96439|11.4362|1.4718|1.4718|
BRISK|FREAK|9.59863|11.2969|1.69826|1.69826|
BRISK|FREAK|8.57352|13.3364|4.76292|4.76292|
BRISK|FREAK|9.51617|10.3718|0.855642|0.855642|
BRISK|FREAK|9.54658|9.33041|-0.216168|0.216168|
BRISK|FREAK|8.3988|10.9372|2.53843|2.53843|
BRISK|SIFT|12.5156|12.9834|0.467761|0.467761|
BRISK|SIFT|12.6142|16.0654|3.45117|3.45117|
BRISK|SIFT|14.091|16.6949|2.60387|2.60387|
BRISK|SIFT|16.6894|12.5648|-4.12457|4.12457|
BRISK|SIFT|15.9082|26.3307|10.4225|10.4225|
BRISK|SIFT|12.6787|14.504|1.82532|1.82532|
BRISK|SIFT|11.9844|13.9956|2.01125|2.01125|
BRISK|SIFT|13.1241|17.0214|3.89726|3.89726|
BRISK|SIFT|13.0241|17.8988|4.87469|4.87469|
BRISK|SIFT|11.1746|14.6452|3.47054|3.47054|
BRISK|SIFT|12.8086|15.9755|3.16693|3.16693|
BRISK|SIFT|8.95978|11.7122|2.7524|2.7524|
BRISK|SIFT|9.96439|13.3127|3.34831|3.34831|
BRISK|SIFT|9.59863|10.5612|0.962616|0.962616|
BRISK|SIFT|8.57352|14.2108|5.63726|5.63726|
BRISK|SIFT|9.51617|11.0325|1.51631|1.51631|
BRISK|SIFT|9.54658|10.1474|0.600803|0.600803|
BRISK|SIFT|8.3988|12.3189|3.92008|3.92008|
ORB|BRISK|12.5156|15.0326|2.51697|2.51697|
ORB|BRISK|12.6142|13.0953|0.481077|0.481077|
ORB|BRISK|14.091|12.4165|-1.67448|1.67448|
ORB|BRISK|16.6894|29.9201|13.2307|13.2307|
ORB|BRISK|15.9082|156.224|140.315|140.315|
ORB|BRISK|12.6787|11.1136|-1.56507|1.56507|
ORB|BRISK|11.9844|13.6966|1.71222|1.71222|
ORB|BRISK|13.1241|10.9433|-2.18086|2.18086|
ORB|BRISK|13.0241|13.0852|0.061127|0.061127|
ORB|BRISK|11.1746|19.472|8.29735|8.29735|
ORB|BRISK|12.8086|8.34928|-4.45932|4.45932|
ORB|BRISK|8.95978|222|222|222|
ORB|BRISK|9.96439|7.97816|-1.98623|1.98623|
ORB|BRISK|9.59863|9.47411|-0.124516|0.124516|
ORB|BRISK|8.57352|8.69652|0.122998|0.122998|
ORB|BRISK|9.51617|13.2755|3.7593|3.7593|
ORB|BRISK|9.54658|12.372|2.82544|2.82544|
ORB|BRISK|8.3988|25.9992|17.6004|17.6004|
ORB|BRIEF|12.5156|20.6602|8.14459|8.14459|
ORB|BRIEF|12.6142|47.92|35.3057|35.3057|
ORB|BRIEF|14.091|103.665|89.574|89.574|
ORB|BRIEF|16.6894|14.0679|-2.62154|2.62154|
ORB|BRIEF|15.9082|22.8925|6.9843|6.9843|
ORB|BRIEF|12.6787|15.1309|2.4522|2.4522|
ORB|BRIEF|11.9844|55.1976|43.2132|43.2132|
ORB|BRIEF|13.1241|76.7595|63.6354|63.6354|
ORB|BRIEF|13.0241|70.7145|57.6904|57.6904|
ORB|BRIEF|11.1746|16.2625|5.08786|5.08786|
ORB|BRIEF|12.8086|17.4453|4.63666|4.63666|
ORB|BRIEF|8.95978|14.1185|5.15872|5.15872|
ORB|BRIEF|9.96439|13.301|3.33665|3.33665|
ORB|BRIEF|9.59863|9.71308|0.114449|0.114449|
ORB|BRIEF|8.57352|8.816|0.242472|0.242472|
ORB|BRIEF|9.51617|10.9804|1.46419|1.46419|
ORB|BRIEF|9.54658|13.442|3.89542|3.89542|
ORB|BRIEF|8.3988|18.4392|10.0404|10.0404|
ORB|ORB|12.5156|100.873|88.357|88.357|
ORB|ORB|12.6142|10.7511|-1.86311|1.86311|
ORB|ORB|14.091|16.6755|2.58448|2.58448|
ORB|ORB|16.6894|30.3839|13.6945|13.6945|
ORB|ORB|15.9082|32.5463|16.6381|16.6381|
ORB|ORB|12.6787|152.439|139.76|139.76|
ORB|ORB|11.9844|216.716|204.731|204.731|
ORB|ORB|13.1241|9.38588|-3.73824|3.73824|
ORB|ORB|13.0241|21.4942|8.47011|8.47011|
ORB|ORB|11.1746|16.9407|5.76607|5.76607|
ORB|ORB|12.8086|8.28796|-4.52064|4.52064|
ORB|ORB|8.95978|35.6408|26.6811|26.6811|
ORB|ORB|9.96439|9.77565|-0.188739|0.188739|
ORB|ORB|9.59863|9.56052|-0.0381144|0.0381144|
ORB|ORB|8.57352|12.849|4.27544|4.27544|
ORB|ORB|9.51617|11.3484|1.83219|1.83219|
ORB|ORB|9.54658|12.7284|3.1818|3.1818|
ORB|ORB|8.3988|29.89|21.4912|21.4912|
ORB|FREAK|12.5156|12.1791|-0.336508|0.336508|
ORB|FREAK|12.6142|20.1206|7.50634|7.50634|
ORB|FREAK|14.091|17.4865|3.39551|3.39551|
ORB|FREAK|16.6894|10.8706|-5.81877|5.81877|
ORB|FREAK|15.9082|222|222|222|
ORB|FREAK|12.6787|11.5438|-1.13495|1.13495|
ORB|FREAK|11.9844|222|222|222|
ORB|FREAK|13.1241|9.02151|-4.10261|4.10261|
ORB|FREAK|13.0241|13.3112|0.287043|0.287043|
ORB|FREAK|11.1746|222|222|222|
ORB|FREAK|12.8086|7.95795|-4.85065|4.85065|
ORB|FREAK|8.95978|35.8486|26.8888|26.8888|
ORB|FREAK|9.96439|6.5346|-3.42979|3.42979|
ORB|FREAK|9.59863|57.3947|47.7961|47.7961|
ORB|FREAK|8.57352|8.60003|0.0265098|0.0265098|
ORB|FREAK|9.51617|9.3402|-0.175971|0.175971|
ORB|FREAK|9.54658|11.3219|1.77534|1.77534|
ORB|FREAK|8.3988|16.8655|8.4667|8.4667|
ORB|SIFT|12.5156|12.8362|0.320623|0.320623|
ORB|SIFT|12.6142|10.5162|-2.09802|2.09802|
ORB|SIFT|14.091|11.669|-2.42196|2.42196|
ORB|SIFT|16.6894|209.183|192.494|192.494|
ORB|SIFT|15.9082|502.13|486.222|486.222|
ORB|SIFT|12.6787|21.0101|8.33139|8.33139|
ORB|SIFT|11.9844|222|222|222|
ORB|SIFT|13.1241|10.4477|-2.67643|2.67643|
ORB|SIFT|13.0241|15.1132|2.08908|2.08908|
ORB|SIFT|11.1746|11.1389|-0.035773|0.035773|
ORB|SIFT|12.8086|10.1214|-2.68723|2.68723|
ORB|SIFT|8.95978|222|222|222|
ORB|SIFT|9.96439|7.94456|-2.01983|2.01983|
ORB|SIFT|9.59863|18.6477|9.04904|9.04904|
ORB|SIFT|8.57352|13.6989|5.12541|5.12541|
ORB|SIFT|9.51617|9.56045|0.0442762|0.0442762|
ORB|SIFT|9.54658|18.3228|8.77619|8.77619|
ORB|SIFT|8.3988|10.7852|2.38636|2.38636|
AKAZE|BRISK|12.5156|11.9017|-0.613866|0.613866|
AKAZE|BRISK|12.6142|15.6249|3.01063|3.01063|
AKAZE|BRISK|14.091|13.4652|-0.625802|0.625802|
AKAZE|BRISK|16.6894|14.4196|-2.26981|2.26981|
AKAZE|BRISK|15.9082|14.7461|-1.16217|1.16217|
AKAZE|BRISK|12.6787|14.8422|2.16349|2.16349|
AKAZE|BRISK|11.9844|16.1855|4.20118|4.20118|
AKAZE|BRISK|13.1241|13.9909|0.866806|0.866806|
AKAZE|BRISK|13.0241|13.8949|0.870824|0.870824|
AKAZE|BRISK|11.1746|11.878|0.703354|0.703354|
AKAZE|BRISK|12.8086|12.5054|-0.303211|0.303211|
AKAZE|BRISK|8.95978|10.3735|1.41376|1.41376|
AKAZE|BRISK|9.96439|10.1489|0.184487|0.184487|
AKAZE|BRISK|9.59863|10.0378|0.439219|0.439219|
AKAZE|BRISK|8.57352|10.1702|1.59668|1.59668|
AKAZE|BRISK|9.51617|10.3767|0.860511|0.860511|
AKAZE|BRISK|9.54658|9.63699|0.0904045|0.0904045|
AKAZE|BRISK|8.3988|8.95291|0.554106|0.554106|
AKAZE|BRIEF|12.5156|13.2804|0.764805|0.764805|
AKAZE|BRIEF|12.6142|15.381|2.76673|2.76673|
AKAZE|BRIEF|14.091|13.6728|-0.418231|0.418231|
AKAZE|BRIEF|16.6894|13.9793|-2.7101|2.7101|
AKAZE|BRIEF|15.9082|15.1106|-0.797615|0.797615|
AKAZE|BRIEF|12.6787|13.9098|1.23112|1.23112|
AKAZE|BRIEF|11.9844|15.9355|3.95113|3.95113|
AKAZE|BRIEF|13.1241|14.4514|1.32732|1.32732|
AKAZE|BRIEF|13.0241|13.5101|0.486025|0.486025|
AKAZE|BRIEF|11.1746|11.6672|0.492545|0.492545|
AKAZE|BRIEF|12.8086|12.3566|-0.452022|0.452022|
AKAZE|BRIEF|8.95978|11.6794|2.71963|2.71963|
AKAZE|BRIEF|9.96439|10.1188|0.154437|0.154437|
AKAZE|BRIEF|9.59863|9.85941|0.260785|0.260785|
AKAZE|BRIEF|8.57352|9.48744|0.913911|0.913911|
AKAZE|BRIEF|9.51617|9.69853|0.182356|0.182356|
AKAZE|BRIEF|9.54658|9.50336|-0.0432247|0.0432247|
AKAZE|BRIEF|8.3988|9.12903|0.730224|0.730224|
AKAZE|ORB|12.5156|12.4033|-0.11234|0.11234|
AKAZE|ORB|12.6142|15.0918|2.47756|2.47756|
AKAZE|ORB|14.091|13.2795|-0.81156|0.81156|
AKAZE|ORB|16.6894|14.3594|-2.33|2.33|
AKAZE|ORB|15.9082|15.8935|-0.0147262|0.0147262|
AKAZE|ORB|12.6787|13.8327|1.15394|1.15394|
AKAZE|ORB|11.9844|15.414|3.42965|3.42965|
AKAZE|ORB|13.1241|13.9668|0.842716|0.842716|
AKAZE|ORB|13.0241|13.4456|0.421482|0.421482|
AKAZE|ORB|11.1746|11.6151|0.440477|0.440477|
AKAZE|ORB|12.8086|12.1404|-0.668161|0.668161|
AKAZE|ORB|8.95978|11.6512|2.69138|2.69138|
AKAZE|ORB|9.96439|10.0845|0.120154|0.120154|
AKAZE|ORB|9.59863|10.3482|0.749609|0.749609|
AKAZE|ORB|8.57352|10.2772|1.70364|1.70364|
AKAZE|ORB|9.51617|9.68854|0.172373|0.172373|
AKAZE|ORB|9.54658|9.06825|-0.478332|0.478332|
AKAZE|ORB|8.3988|9.07751|0.678705|0.678705|
AKAZE|FREAK|12.5156|12.1239|-0.391749|0.391749|
AKAZE|FREAK|12.6142|14.0613|1.44702|1.44702|
AKAZE|FREAK|14.091|13.9585|-0.132487|0.132487|
AKAZE|FREAK|16.6894|14.2454|-2.44402|2.44402|
AKAZE|FREAK|15.9082|16.1433|0.235045|0.235045|
AKAZE|FREAK|12.6787|14.5111|1.83241|1.83241|
AKAZE|FREAK|11.9844|15.4457|3.46132|3.46132|
AKAZE|FREAK|13.1241|13.6867|0.562615|0.562615|
AKAZE|FREAK|13.0241|13.0989|0.0747708|0.0747708|
AKAZE|FREAK|11.1746|12.0412|0.866605|0.866605|
AKAZE|FREAK|12.8086|12.2112|-0.597386|0.597386|
AKAZE|FREAK|8.95978|10.9925|2.03274|2.03274|
AKAZE|FREAK|9.96439|10.9715|1.00708|1.00708|
AKAZE|FREAK|9.59863|9.99992|0.401286|0.401286|
AKAZE|FREAK|8.57352|9.87014|1.29662|1.29662|
AKAZE|FREAK|9.51617|10.3531|0.836913|0.836913|
AKAZE|FREAK|9.54658|9.10004|-0.446538|0.446538|
AKAZE|FREAK|8.3988|8.65041|0.251604|0.251604|
AKAZE|AKAZE|12.5156|12.3444|-0.171208|0.171208|
AKAZE|AKAZE|12.6142|14.0983|1.48408|1.48408|
AKAZE|AKAZE|14.091|12.8828|-1.20818|1.20818|
AKAZE|AKAZE|16.6894|14.4781|-2.21132|2.21132|
AKAZE|AKAZE|15.9082|16.7468|0.838524|0.838524|
AKAZE|AKAZE|12.6787|13.8675|1.18879|1.18879|
AKAZE|AKAZE|11.9844|15.3438|3.35943|3.35943|
AKAZE|AKAZE|13.1241|14.1378|1.01365|1.01365|
AKAZE|AKAZE|13.0241|13.8398|0.815652|0.815652|
AKAZE|AKAZE|11.1746|11.5483|0.373644|0.373644|
AKAZE|AKAZE|12.8086|12.1341|-0.674506|0.674506|
AKAZE|AKAZE|8.95978|11.0554|2.09557|2.09557|
AKAZE|AKAZE|9.96439|11.2852|1.32083|1.32083|
AKAZE|AKAZE|9.59863|10.5845|0.985867|0.985867|
AKAZE|AKAZE|8.57352|10.1989|1.62535|1.62535|
AKAZE|AKAZE|9.51617|9.81256|0.296389|0.296389|
AKAZE|AKAZE|9.54658|9.06452|-0.482057|0.482057|
AKAZE|AKAZE|8.3988|8.97386|0.575053|0.575053|
AKAZE|SIFT|12.5156|12.4103|-0.105316|0.105316|
AKAZE|SIFT|12.6142|14.6432|2.02891|2.02891|
AKAZE|SIFT|14.091|13.2294|-0.861586|0.861586|
AKAZE|SIFT|16.6894|14.1141|-2.57533|2.57533|
AKAZE|SIFT|15.9082|16.5952|0.686989|0.686989|
AKAZE|SIFT|12.6787|13.9616|1.28288|1.28288|
AKAZE|SIFT|11.9844|15.7668|3.78248|3.78248|
AKAZE|SIFT|13.1241|13.7661|0.641965|0.641965|
AKAZE|SIFT|13.0241|14.0783|1.05418|1.05418|
AKAZE|SIFT|11.1746|11.7502|0.575607|0.575607|
AKAZE|SIFT|12.8086|12.2176|-0.590988|0.590988|
AKAZE|SIFT|8.95978|11.1693|2.20956|2.20956|
AKAZE|SIFT|9.96439|10.861|0.896636|0.896636|
AKAZE|SIFT|9.59863|10.4743|0.875651|0.875651|
AKAZE|SIFT|8.57352|9.94151|1.36798|1.36798|
AKAZE|SIFT|9.51617|10.1277|0.611565|0.611565|
AKAZE|SIFT|9.54658|9.02048|-0.5261|0.5261|
AKAZE|SIFT|8.3988|8.9967|0.597894|0.597894|
SIFT|BRISK|12.5156|11.6767|-0.838944|0.838944|
SIFT|BRISK|12.6142|13.3294|0.715132|0.715132|
SIFT|BRISK|14.091|14.4774|0.386362|0.386362|
SIFT|BRISK|16.6894|18.9447|2.25535|2.25535|
SIFT|BRISK|15.9082|14.9068|-1.00145|1.00145|
SIFT|BRISK|12.6787|11.5508|-1.12791|1.12791|
SIFT|BRISK|11.9844|14.3811|2.39678|2.39678|
SIFT|BRISK|13.1241|15.5638|2.43967|2.43967|
SIFT|BRISK|13.0241|13.0599|0.0357605|0.0357605|
SIFT|BRISK|11.1746|10.843|-0.33168|0.33168|
SIFT|BRISK|12.8086|13.2357|0.427138|0.427138|
SIFT|BRISK|8.95978|10.296|1.33618|1.33618|
SIFT|BRISK|9.96439|9.99995|0.0355639|0.0355639|
SIFT|BRISK|9.59863|9.55221|-0.0464218|0.0464218|
SIFT|BRISK|8.57352|9.46445|0.890921|0.890921|
SIFT|BRISK|9.51617|8.76753|-0.748636|0.748636|
SIFT|BRISK|9.54658|9.52376|-0.022822|0.022822|
SIFT|BRISK|8.3988|9.32687|0.928062|0.928062|
SIFT|BRIEF|12.5156|12.0813|-0.434327|0.434327|
SIFT|BRIEF|12.6142|14.236|1.62178|1.62178|
SIFT|BRIEF|14.091|15.0724|0.981378|0.981378|
SIFT|BRIEF|16.6894|21.3092|4.61976|4.61976|
SIFT|BRIEF|15.9082|13.5967|-2.31155|2.31155|
SIFT|BRIEF|12.6787|12.5453|-0.13343|0.13343|
SIFT|BRIEF|11.9844|14.5816|2.59722|2.59722|
SIFT|BRIEF|13.1241|15.2572|2.13309|2.13309|
SIFT|BRIEF|13.0241|13.0451|0.0209508|0.0209508|
SIFT|BRIEF|11.1746|10.3097|-0.8649|0.8649|
SIFT|BRIEF|12.8086|13.0457|0.237117|0.237117|
SIFT|BRIEF|8.95978|9.86388|0.904102|0.904102|
SIFT|BRIEF|9.96439|10.1399|0.175533|0.175533|
SIFT|BRIEF|9.59863|9.2679|-0.330733|0.330733|
SIFT|BRIEF|8.57352|9.99457|1.42105|1.42105|
SIFT|BRIEF|9.51617|9.06923|-0.446942|0.446942|
SIFT|BRIEF|9.54658|8.94618|-0.6004|0.6004|
SIFT|BRIEF|8.3988|9.23257|0.833763|0.833763|
SIFT|FREAK|12.5156|11.3065|-1.20915|1.20915|
SIFT|FREAK|12.6142|13.8342|1.21997|1.21997|
SIFT|FREAK|14.091|13.6135|-0.477498|0.477498|
SIFT|FREAK|16.6894|21.1519|4.46254|4.46254|
SIFT|FREAK|15.9082|13.5635|-2.34476|2.34476|
SIFT|FREAK|12.6787|12.2446|-0.434075|0.434075|
SIFT|FREAK|11.9844|14.8159|2.83157|2.83157|
SIFT|FREAK|13.1241|15.2357|2.11153|2.11153|
SIFT|FREAK|13.0241|14.389|1.36486|1.36486|
SIFT|FREAK|11.1746|11.572|0.397381|0.397381|
SIFT|FREAK|12.8086|12.0594|-0.749154|0.749154|
SIFT|FREAK|8.95978|10.0929|1.13313|1.13313|
SIFT|FREAK|9.96439|10.312|0.347602|0.347602|
SIFT|FREAK|9.59863|9.89671|0.298076|0.298076|
SIFT|FREAK|8.57352|9.19678|0.62326|0.62326|
SIFT|FREAK|9.51617|9.49736|-0.0188071|0.0188071|
SIFT|FREAK|9.54658|9.18097|-0.365609|0.365609|
SIFT|FREAK|8.3988|9.93226|1.53345|1.53345|
SIFT|SIFT|12.5156|11.9769|-0.538691|0.538691|
SIFT|SIFT|12.6142|12.5597|-0.0545167|0.0545167|
SIFT|SIFT|14.091|13.1739|-0.917066|0.917066|
SIFT|SIFT|16.6894|19.6445|2.95508|2.95508|
SIFT|SIFT|15.9082|15.2698|-0.638447|0.638447|
SIFT|SIFT|12.6787|11.1131|-1.56558|1.56558|
SIFT|SIFT|11.9844|13.9096|1.92525|1.92525|
SIFT|SIFT|13.1241|15.6277|2.50361|2.50361|
SIFT|SIFT|13.0241|15.0391|2.01497|2.01497|
SIFT|SIFT|11.1746|10.5588|-0.615835|0.615835|
SIFT|SIFT|12.8086|11.7091|-1.09948|1.09948|
SIFT|SIFT|8.95978|11.6299|2.67014|2.67014|
SIFT|SIFT|9.96439|9.24828|-0.716115|0.716115|
SIFT|SIFT|9.59863|10.644|1.04537|1.04537|
SIFT|SIFT|8.57352|10.4388|1.86531|1.86531|
SIFT|SIFT|9.51617|9.57995|0.0637835|0.0637835|
SIFT|SIFT|9.54658|8.88504|-0.661537|0.661537|
SIFT|SIFT|8.3988|9.01264|0.613839|0.613839|
```
