#!/usr/bin/env bash


python setup.py build
#    running build
#    running build_ext
#    building 'cxpy' extension
#    creating build
#    creating build/temp.linux-x86_64-3.7
#    import cxpy
#    gcc -pthread -B /opt/fff/anaconda3/compiler_compat -Wl,--sysroot=/ -Wsign-compare -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes -fPIC -I/opt/fff/anaconda3/include/python3.7m -c cxpy_module.cpp -o build/temp.linux-x86_64-3.7/cxpy_module.o
#    cc1plus: warning: command line option ‘-Wstrict-prototypes’ is valid for C/ObjC but not for C++
#    gcc -pthread -B /opt/fff/anaconda3/compiler_compat -Wl,--sysroot=/ -Wsign-compare -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes -fPIC -I/opt/fff/anaconda3/include/python3.7m -c cxpy_noddy2.cpp -o build/temp.linux-x86_64-3.7/cxpy_noddy2.o
#    cc1plus: warning: command line option ‘-Wstrict-prototypes’ is valid for C/ObjC but not for C++
#    cxpy_noddy2.cpp: In function ‘int Noddy_init(Noddy*, PyObject*, PyObject*)’:
#    cxpy_noddy2.cpp:54:61: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
#         static char *kwlist[] = {"first", "last", "number", NULL};
#                                                                 ^
#    cxpy_noddy2.cpp:54:61: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
#    cxpy_noddy2.cpp:54:61: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
#    creating build/lib.linux-x86_64-3.7
#    g++ -pthread -shared -B /opt/fff/anaconda3/compiler_compat -L/opt/fff/anaconda3/lib -Wl,-rpath=/opt/fff/anaconda3/lib -Wl,--no-as-needed -Wl,--sysroot=/ build/temp.linux-x86_64-3.7/cxpy_module.o build/temp.linux-x86_64-3.7/cxpy_noddy2.o -o build/lib.linux-x86_64-3.7/cxpy.cpython-37m-x86_64-linux-gnu.so

python setup.py install
#    running install
#    running build
#    running build_ext
#    running install_lib
#    copying build/lib.linux-x86_64-3.7/cxpy.cpython-37m-x86_64-linux-gnu.so -> /opt/fff/anaconda3/lib/python3.7/site-packages
#    running install_egg_info
#    Writing /opt/fff/anaconda3/lib/python3.7/site-packages/cxpy-1.0-py3.7.egg-info
cd /opt/fff/anaconda3/lib/python3.7/site-packages && ll
#    -rw-r--r--   1 root root     176 Mar  3 22:29 cxpy-1.0-py3.7.egg-info
#    -rwxr-xr-x   1 root root   68144 Mar  3 22:27 cxpy.cpython-37m-x86_64-linux-gnu.so*
vim cxpy-1.0-py3.7.egg-info
#    Metadata-Version: 1.0
#    Name: cxpy
#    Version: 1.0
#    Summary: UNKNOWN
#    Home-page: UNKNOWN
#    Author: UNKNOWN
#    Author-email: UNKNOWN
#    License: UNKNOWN
#    Description: UNKNOWN
#    Platform: UNKNOWN
python test.py
#    <class 'str'>
#    <class 'str'>
#    11