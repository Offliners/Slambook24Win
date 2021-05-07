# Slambook2 for Windows
code of 14 lectures on visual SLAM 2nd

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

### Solution for some error
#### 'M_PI': undeclared identifier
add this definition n top of the code or project `Properties -> C/C++ -> Preprocessor -> Preprocessor definitions`
```
#define _USE_MATH_DEFINES
```

## Reference
* SLAM視覺十四講：雙倍內容強化版 (`ISBN：9789865501044`)

![Reference](https://github.com/Offliners/SLAM/blob/main/reference.png)
