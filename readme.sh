#!/usr/bin/env bash

cmake . -DCMAKE_BUILD_TYPE=Debug --build "$PWD" -B"$PWD/build-cmake"

cmake . -DCMAKE_BUILD_TYPE=Debug --build . -B"./build-cmake"


cmake . -G "Visual Studio 12 2013" --build "C:\ddd\ccpp\googletest\googletest-master" -B"C:\ddd\ccpp\googletest\googletest-master\cmake-vs2013"

cmake . -G "Visual Studio 14 2015" --build "C:\ddd\ccpp\googletest\googletest-master" -B"C:\ddd\ccpp\googletest\googletest-master\build\cmake-vs2015" -Dgtest_build_tests=ON -Dgtest_build_samples=ON -Dgmock_build_tests=ON

-DCMAKE_BUILD_TYPE=Debug -Dgtest_build_tests=ON -Dgtest_build_samples=ON -Dgmock_build_tests=ON

-DCMAKE_BUILD_TYPE=Release -Dgtest_build_tests=ON -Dgtest_build_samples=ON -Dgmock_build_tests=ON
