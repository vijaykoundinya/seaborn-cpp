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
	
	//Relational Plot Argument Variables
	PyObject* col_wrap;
	PyObject* row_order;
	PyObject* col_order;
	PyObject* palette;
	PyObject* hue_order;
	PyObject* hue_norm;
	PyObject* sizes;
	PyObject* size_order;
	PyObject* size_norm;
	PyObject* legend;
	PyObject* height;
	PyObject* aspect;
	PyObject* facet_kws;
	
	//This function is used to import subfunctions of a header
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
	
	//Constructor to initialize Seaborn and Matplotlib
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
	
	//Destructor
	~Seaborn()
	{	
		Py_Finalize();
	}
	
	/*
		This function is used to load the dataset
		
		Parameters:
		:s: string - Path to the dataset (must be a CSV)
		
    	:return: bool - Result of operation (Success or Failure)
	*/
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
	
	/*
		This function is used to save the plot as PNG
		
		Parameters:
		:s: string - Name of file to be saved
		
    	:return: bool - Result of operation (Success or Failure)
	*/
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
	
	//=================================================================================================================
	//RELATIONAL PLOTS
	//https://seaborn.pydata.org/generated/seaborn.relplot.html#seaborn.relplot
	
	/*
		This function is used to set value col_wrap in Relational Plots
		
		Parameters:
		:colwrap: long int - Width to wrap wrap the column
		
		NOTE: The variable 'col' needs to be set for col_wrap to work 
	*/
	void setColWrap(const long int colwrap)
	{
		col_wrap = PyLong_FromLong(colwrap);
	}
	
	/*
		This function is used to set value height in Relational Plots
		
		Parameters:
		:h: double - Height (in inches) of each facet
	*/
	void setHeight(const double h)
	{
		height = PyFloat_FromDouble(h);
	}
	
	/*
		This function is used to set value aspect in Relational Plots
		
		Parameters:
		:a: double - Aspect ratio of each facet, so that aspect * height gives the width of each facet in inches
	*/
	void setAspect(const double a)
	{
		aspect = PyFloat_FromDouble(a);
	}
	
	/*
		This function is used to draw relational plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, string>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, string> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
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
	    
	    if(!dataset)
	    {
	    	cout<<"\nDataset not loaded\n";
	    	return false;
		}
		
	    PyDict_SetItemString(kwargs, "data", dataset);
	    
	    if(col_wrap)
	    {
	    	PyDict_SetItemString(kwargs, "col_wrap", col_wrap);
		}
		
		if(height)
	    {
	    	PyDict_SetItemString(kwargs, "height", height);
		}
		
		if(aspect)
	    {
	    	PyDict_SetItemString(kwargs, "aspect", aspect);
		}
		
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
	
	//=================================================================================================================
};

