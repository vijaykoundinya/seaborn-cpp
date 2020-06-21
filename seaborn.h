#include <stdio.h>
#include <python2.7/Python.h>
#include<numeric>
#include<vector>
#include<string>
#include<stdexcept>
#include<iostream>
using namespace std;
class seaborn
{
PyObject* seabornLib;
PyObject* dataset;
PyObject* savefig;
PyObject* safe_import(PyObject* lib,const string fn)
{
	PyObject* fname = PyObject_GetAttrString(lib,fn.c_str());
	if(!fname)
		throw std::runtime_error(fn);
	if(!PyFunction_Check(fname))
		throw std::runtime_error(fn);
	return fname;	
}
public:
seaborn()
{
	Py_Initialize();
	PyObject* seabornName = PyString_FromString("seaborn");
	seabornLib = PyImport_Import(seabornName);
	if(!seabornLib)
	{
		PyErr_Print();
	}
	PyObject* matplotlibName = PyString_FromString("matplotlib.pyplot");
	PyObject* matplotlibLib = PyImport_Import(matplotlibName);
	if(!matplotlibLib)
	{
		PyErr_Print();
	}
	savefig = safe_import(matplotlibLib,"savefig");
}
~seaborn()
{	
	Py_Finalize();
}
void loadDataSet(string s)
{
	PyObject* pandasName = PyString_FromString("pandas");
	PyObject* pandas = PyImport_Import(pandasName);
	if(!pandas)
	{
		PyErr_Print();
	}
	PyObject* pystring = PyTuple_New(1);
	PyTuple_SetItem(pystring,0,PyString_FromString(s.c_str()));
	PyObject* readCsv = safe_import(pandas,"read_csv");
	dataset = PyObject_CallObject(readCsv,pystring);
	PyObject* o = PyObject_Repr(dataset);
	const char* check = PyString_AsString(o);
	cout<<check;
}
void saveGraph(string s)
{
	PyObject* pystring = PyTuple_New(1);
	PyTuple_SetItem(pystring,0,PyString_FromString(s.c_str()));
	PyObject* res = PyObject_CallObject(savefig,pystring);	
}
void relplot(const string x,const string y)
{
	PyObject* pyrelplot = safe_import(seabornLib,"relplot");
	PyObject* args = PyTuple_New(3);
	PyTuple_SetItem(args,1,PyString_FromString(x.c_str()));
	PyTuple_SetItem(args,0,PyString_FromString(y.c_str()));
	PyTuple_SetItem(args,2,dataset);
	PyObject* res = PyObject_CallObject(pyrelplot,args);
	saveGraph("test");
}
};

