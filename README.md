# Slambook2 for Windows
code of 14 lectures on visual SLAM 2nd built on Windows 10

## Environment
IDE : `Visual Studio 2017`

### Package
|Name|Version|
|-|-|
|eigen3:x64-windows|`3.3.9`|
|g2o:x64-windows|`2020-02-07#1`|
|pcl:x64-windows|`1.11.1#2`|
|pangolin:x64-windows|`0.5#15`|
|boost:x64-windows|`1.67.0`|
|ceres:x64-windows|`2.0.0#4`|

### Package install

using `vcpkg`, detail [Link](https://github.com/Microsoft/vcpkg)
```shell
git clone https://github.com/microsoft/vcpkg  // only first use
.\vcpkg\bootstrap-vcpkg.bat                   // only first use
cd "vcpkg root directory"
.\vcpkg\vcpkg install [packages to install]
```

### Integrate for Visual Studio
```shell
.\vcpkg\vcpkg integrate install
```

## Solution for some error
### 'M_PI' or 'M_2_SQRTPI': undeclared identifier
add this definition n top of the code or right click the project and then click `Properties -> C/C++ -> Preprocessor -> Preprocessor definitions`
```c++
#define _USE_MATH_DEFINES
```
### Error: 'usleep' was not declared
usleep is declared in `unistd.h`, but windows doesn't provide this library.

So, replace by
```c++
#include<chrono>
#include<thread>
...
std::this_thread::sleep_for(std::chrono::microseconds(usec));  // usec is time for sleeping in microsecond
```

### How to read command line argument with visual studio
1. build the project to generate the exe file, then use cmd to execute the file
```shell
cd ...                               // cd directory of the exe file 
example.exe argv[1] argv[2] ...      // execute the file with command line argument
```
2. Right click the project and then click `Properties -> Debugging -> Command Arguments`, and then input parameters 

### Compiling `g2oCurveFitting.cpp` will occur Error: ... must return a value
Errors like
```shell
Error	C4716	'CurveFittingVertex::read': must return a value
Error	C4716	'CurveFittingEdge::write': must return a value
```
Sol : Add `return true;` in those functions

### Error: 'CV_LOAD_IMAGE_COLOR' was not declared in this scope
Replace `CV_LOAD_IMAGE_COLOR` by `cv::IMREAD_COLOR`

### Error: conversion from 'size_t' to 'int' requires a narrowing conversion
```c++
...
for (int i1 = 0; i1 < desc1.size(); ++i1)  // Replace `size_t i1` by `int i1`
...
```

### CV_FM_8POINT was not declared in this scope
Replace `CV_FM_8POINT` by `FM_8POINT`

## Reference
* github : https://github.com/gaoxiang12/slambook2
* SLAM視覺十四講：雙倍內容強化版 (`ISBN：9789865501044`)

![Reference](https://github.com/Offliners/SLAM/blob/main/reference.png)
