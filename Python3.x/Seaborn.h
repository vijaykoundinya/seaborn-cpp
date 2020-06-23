#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <conio.h>
#include <map>

using namespace std;

class Seaborn
{
	PyObject* seabornLib;
	PyObject* dataset;
	PyObject* savefig;
	
	PyObject* safe_import(PyObject* lib, const string fn)
	{
		PyObject* fname = PyObject_GetAttrString(lib, fn.c_str());
		if(!fname)
			throw std::runtime_error(fn);
		if(!PyFunction_Check(fname))
			throw std::runtime_error(fn);
		return fname;	
	}
	
	public:
		
	Seaborn()
	{
		Py_Initialize();
		PyObject* seabornName = PyUnicode_FromString("seaborn");
		seabornLib = PyImport_Import(seabornName);
		if(!seabornLib)
		{
			PyErr_Print();
		}
		
		PyObject* matplotlibName = PyUnicode_FromString("matplotlib.pyplot");
		PyObject* matplotlibLib = PyImport_Import(matplotlibName);
		if(!matplotlibLib)
		{
			PyErr_Print();
		}
		
		savefig = safe_import(matplotlibLib,"savefig");
	}
	
	~Seaborn()
	{	
		Py_Finalize();
	}
	
	bool loadData(string s)
	{
		PyObject* pandasName = PyUnicode_FromString("pandas");
		PyObject* pandas = PyImport_Import(pandasName);
		if(!pandas)
		{
			PyErr_Print();
		}
		
		PyObject* pystring = PyTuple_New(1);
		PyTuple_SetItem(pystring,0,PyUnicode_FromString(s.c_str()));
		PyObject* readCsv = safe_import(pandas,"read_csv");
		dataset = PyObject_CallObject(readCsv,pystring);
		if(!dataset)
		{
			PyErr_Print();
			return false;
		}
		
		PyObject* o = PyObject_Repr(dataset);
		const char* check = PyBytes_AsString(PyUnicode_AsUTF8String(o));
		
		cout<<"\n";
		cout<<check;
		cout<<"\n";
		
		return dataset;
	}
	
	bool saveGraph(string s)
	{
		PyObject* pystring = PyTuple_New(1);
		PyTuple_SetItem(pystring, 0, PyUnicode_FromString(s.c_str()));
		PyObject* res = PyObject_CallObject(savefig,pystring);
		if(!res)
		{
			PyErr_Print();
		}
		
		return res;
	}
	
	bool relplot(const string x, const string y, const map<string, string>& keywords)
	{
		PyObject* pyrelplot = safe_import(seabornLib,"relplot");
		
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyUnicode_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyUnicode_FromString(y.c_str()));
		
		PyObject* kwargs = PyDict_New();
		for(map<string, string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
	    {
	        PyDict_SetItemString(kwargs, it->first.c_str(), PyUnicode_FromString(it->second.c_str()));
	    }
	    
	    PyDict_SetItemString(kwargs, "data", dataset);
		
		PyObject* res = PyObject_Call(pyrelplot, args, kwargs);
		if(!res)
		{
			PyErr_Print();
		}
		
		Py_DECREF(args);
    	Py_DECREF(kwargs);
    	if(res)
			Py_DECREF(res);
    	
    	return res;
	}
};

