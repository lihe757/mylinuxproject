#include <stdio.h>
#include "/usr/include/python2.6/Python.h"
int main(void)
{
	Py_Initialize();
	if(!Py_IsInitialized())
	{
		printf("init error");
		return -1;
	}
	
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;
	PyObject *pName = NULL;

	pName = PyString_FromString("pytest");
	pModule = PyImport_ImportModule("pytest");
	if (!pModule)
	{
		printf("load module error \n");
	}
	pFunc = PyObject_GetAttrString(pModule,"hello");
	PyEval_CallObject(pFunc,NULL);
	Py_Finalize();
	return 0;
}
