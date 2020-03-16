#include "Python.h"

#include <iostream>

using namespace std;

int main()
{
    // 初始化
    Py_Initialize();

    // 将Python工作路径切换到待调用模块所在目录，一定要保证路径名的正确性
    string path = "~/test";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char *cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    // 加载模块
    PyObject * moduleName = PyUnicode_FromString("test"); //模块名，不是文件名
    PyObject * pModule = PyImport_Import(moduleName);
    if (!pModule) // 加载模块失败
    {
        cout << "[ERROR] Python get module failed." << endl;
        return 0;
    }
    cout << "[INFO] Python get module succeed." << endl;

    // 加载函数
    PyObject * pv = PyObject_GetAttrString(pModule, "test_add");
    if (!pv || !PyCallable_Check(pv))  // 验证是否加载成功
    {
        cout << "[ERROR] Can't find funftion (test_add)" << endl;
        return 0;
    }
    cout << "[INFO] Get function (test_add) succeed." << endl;

    // 设置参数
    PyObject * args = PyTuple_New(2);   // 2个参数
    PyObject * arg1 = PyLong_FromLong(4);    // 参数一设为4
    PyObject * arg2 = PyLong_FromLong(3);    // 参数二设为3
    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);

    // 调用函数
    PyObject * pRet = PyObject_CallObject(pv, args);

    // 获取参数
    if (pRet)  // 验证是否调用成功
    {
        long result = PyLong_AsLong(pRet);
        cout << "result:" << result;
    }

    // 释放资源
    Py_Finalize();

    return 0;
}
