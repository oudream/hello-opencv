#!/usr/bin/env bash

open https://docs.python.org/zh-cn/3/extending/building.html

#
open https://zhuanlan.zhihu.com/p/24311879


cmake -D gs_3rd_enable_gtest=ON  gs_debug_type=Release -S "./cmake1" -B"./cmake1/build-"
cmake -D gs_3rd_enable_gtest=ON -D gs_debug_type=Release -P "./cmake1/a.cmake"
cmake -P "./cmake1/a.cmake"


cmake . --build "/opt/ddd/ccpp/ccxx/build/cmake" -B"/opt/ddd/ccpp/ccxx/build/cmake-gcc"
cmake . -DCMAKE_BUILD_TYPE=Debug --build "/opt/ddd/ccpp/gcl3/build/cmake" -B"/opt/ddd/ccpp/gcl3/build/cmake-gcc"
cmake . -DCMAKE_BUILD_TYPE=Debug --build . -B"./cmake-gcc"
