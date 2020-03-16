

set(Python_ADDITIONAL_VERSIONS 3.8 3.7 3.6 3.5 3.4)
find_package(PythonLibsNew REQUIRED)

# Cache variables so pybind11_add_module can be used in parent projects
set(PYBIND11_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include" CACHE INTERNAL "")
set(PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS} CACHE INTERNAL "")
set(PYTHON_LIBRARIES ${PYTHON_LIBRARIES} CACHE INTERNAL "")
set(PYTHON_MODULE_PREFIX ${PYTHON_MODULE_PREFIX} CACHE INTERNAL "")
set(PYTHON_MODULE_EXTENSION ${PYTHON_MODULE_EXTENSION} CACHE INTERNAL "")
set(PYTHON_VERSION_MAJOR ${PYTHON_VERSION_MAJOR} CACHE INTERNAL "")
set(PYTHON_VERSION_MINOR ${PYTHON_VERSION_MINOR} CACHE INTERNAL "")

#find_package (PythonInterp REQUIRED)
#find_package (PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

message(-----------PYTHON_INCLUDE_DIRS:${PYTHON_INCLUDE_DIRS})
message(-----------PYTHON_LIBRARIES:${PYTHON_LIBRARIES})
message(-----------PYTHON_DEBUG_LIBRARIES:${PYTHON_DEBUG_LIBRARIES})

add_subdirectory(noddy)

add_subdirectory(shoddy)

add_subdirectory(pythoncall2)

add_subdirectory(callpython1)

add_subdirectory(callpython2)

add_subdirectory(callpython3)

add_subdirectory(callpython-getattr1)

if (PYTHONINTERP_FOUND)
    message("------PYTHON_INCLUDE_DIRS = " ${PYTHON_INCLUDE_DIRS})
    message("------PYTHON_LIBRARIES = " ${PYTHON_LIBRARIES})
else()
    message("Python not found")
endif()

# old style
# SET(Python_ADDITIONAL_VERSIONS 3 3.6 3.5 3.4 3.3 3.2 3.1 3.0)
# FIND_PACKAGE(PythonInterp 3.6)
#
#
#    https://cmake.org/cmake/help/latest/module/FindPython3.html
#    find_package (Python3 COMPONENTS Interpreter Development)
#    /usr/lib/x86_64-linux-gnu/libpython3.6m.a
#    /usr/lib/x86_64-linux-gnu/libpython3.6m.so
#    /usr/include/python3.6
#    -DPYTHON_LIBRARY='/softwarepath/Python/Python2.7/lib/libpython2.7.so'
#    -DPYTHON_INCLUDE='/softwarepath/Python/Python2.7/include'
#
#    apt purge python2.x-minimal
#    apt purge python2.7-minimal
#
#    apt install python3
#    apt install python3-pip
#
#    update-alternatives: --install needs <link> <name> <path> <priority>
#    update-alternatives --install /usr/bin/python python /usr/bin/python3 1
#    update-alternatives --install /usr/bin/pip python /usr/bin/pip3 1
#
#    /opt/tmp/pybind11/tools/FindPythonLibsNew.cmake