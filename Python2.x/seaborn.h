#include <stdio.h>
#include <python2.7/Python.h>
#include<numeric>
#include<vector>
#include<string>
#include<stdexcept>
#include<iostream>
#include<map>
using namespace std;
class seaborn
{
	PyObject* seabornLib;
	PyObject* dataset;
	PyObject* savefig;
	PyObject* safe_import(PyObject* lib,const string fn)
	{
	//Imports Function Object
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
	//loads dataset(.csv files only)
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
		if(!dataset)
		{
			PyErr_Print();
			return;
		}
		PyObject* o = PyObject_Repr(dataset);
		const char* check = PyString_AsString(o);
		cout<<check;
	}
	void saveGraph(string s)
	{
	//Saves any graph previously generated
	//Call after every plot fuction
		PyObject* pystring = PyTuple_New(1);
		PyTuple_SetItem(pystring,0,PyString_FromString(s.c_str()));
		PyObject* res = PyObject_CallObject(savefig,pystring);	
	}
	bool relplot(const string x,const string y,const map<string, string>& keywords)
	{
		//mimics the relplot function of seaborn.
		PyObject* pyrelplot = safe_import(seabornLib,"relplot");
			
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyString_FromString(y.c_str()));

		PyObject* kwargs = PyDict_New();
		for(map<string, string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
		{
		    PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
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
		return true;
	}
};

