#!/usr/bin/env bash

# https://github.com/opencv/opencv/wiki
# https://docs.opencv.org/4.1.2/d9/df8/tutorial_root.html
# https://www.tutorialspoint.com/opencv/opencv_quick_guide.htm


# examples c++
# https://github.com/spmallick/learnopencv
# https://github.com/oreillymedia/Learning-OpenCV-3_examples


# mat
# https://docs.opencv.org/4.1.2/d3/d63/classcv_1_1Mat.html



### install's cmd
git clone https://github.com/opencv/opencv.git --recursive
git clone https://github.com/opencv/opencv_contrib.git --recursive

cd opencv

export CONDA_HOME=/opt/fff/anaconda3 
export SRC_OPENCV_CONTRIB_PATH=/opt/limi/opencv_contrib 
export SRC_OPENCV_PATH=/opt/limi/opencv 
export CPLUS_INCLUDE_PATH=${CONDA_HOME}/bin/python3

cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=${SRC_OPENCV_CONTRIB_PATH}/modules \
    -D PYTHON3_LIBRARY=${CONDA_HOME}/lib/libpython3.7m.dylib \
    -D PYTHON3_INCLUDE_DIR=${CONDA_HOME}/include/python3.7m \
    -D PYTHON3_EXECUTABLE=${CONDA_HOME}/bin/python \
    -D PYTHON3_PACKAGES_PATH=${CONDA_HOME}/lib/python3.7/site-packages \
    -D BUILD_opencv_python2=OFF \
    -D BUILD_opencv_python3=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D INSTALL_C_EXAMPLES=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D BUILD_EXAMPLES=ON \
    -G "CodeBlocks - Unix Makefiles" \
    -S . ${SRC_OPENCV_PATH} \
    -B${SRC_OPENCV_PATH}\bb

cd ${SRC_OPENCV_PATH}\bb

make -j 4

sudo make install


### clion define
-D CMAKE_BUILD_TYPE=RELEASE
-D CMAKE_INSTALL_PREFIX=/usr/local
-D OPENCV_EXTRA_MODULES_PATH=/opt/limi/opencv_contrib/modules
-D PYTHON3_LIBRARY=/opt/fff/anaconda3/lib/libpython3.7m.dylib
-D PYTHON3_INCLUDE_DIR=/opt/fff/anaconda3/include/python3.7m
-D PYTHON3_EXECUTABLE=/opt/fff/anaconda3/bin/python
-D PYTHON3_PACKAGES_PATH=/opt/fff/anaconda3/lib/python3.7/site-packages
-D BUILD_opencv_python2=OFF
-D BUILD_opencv_python3=ON
-D INSTALL_PYTHON_EXAMPLES=ON
-D INSTALL_C_EXAMPLES=ON
-D OPENCV_ENABLE_NONFREE=ON
-D BUILD_EXAMPLES=ON



conda clean --all