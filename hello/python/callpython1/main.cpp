#include "Python.h"

int main()
{
    Py_Initialize();

    PyRun_SimpleString("print('hello');");

    Py_Finalize();
}
