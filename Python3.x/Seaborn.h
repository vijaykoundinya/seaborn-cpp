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

class Storage
{
	int n;
	double i;
	string s;
	bool b;
	double *li;
	string *sa;
	
	string val;
		
	public:
		
		void setDouble(double i)
		{
			this->i = i;
			val = "int";
			
			s = "";
			b = false;
			li = new double[1];
			sa = new string[1];
		}
			
		void setString(string s)
		{
			this->s = s;
			val = "str";
			
			i = 0;
			b = false;
			li = new double[1];
			sa = new string[1];
		}
		
		void setBool(bool b)
		{
			this->b = b;
			val = "bool";
			
			i = 0;
			s = "";
			li = new double[1];
			sa = new string[1];
		}
		
		void setDoubleArray(double *li, int n)
		{
			this->li = new double[n];
			copy(li, li + n, this->li);
			val = "intarr";
			this->n = n;
			
			i = 0;
			s = "";
			b = false;
			sa = new string[1];
		}
		
		void setStringArray(string *sa, int n)
		{
			this->sa = new string[n];
			copy(sa, sa + n, this->sa);
			val = "strarr";
			this->n = n;
			
			i = 0;
			s = "";
			b = false;
			li = new double[1];
		}
		
		int getN() const
		{
			return n;
		}
		
		double getDouble() const
		{
			return i;
		}
		
		string getString() const
		{
			return s;
		}
		
		bool getBool() const
		{
			return b;
		}
		
		double* getDoubleArray() const
		{
			return li;
		}
		
		string* getStringArray() const
		{
			return sa;
		}
		
		string getVal() const
		{
			return val;
		}
};

class Seaborn
{
	PyObject* seabornLib;
	PyObject* dataset;
	PyObject* savefig;
	
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
		This function is used to draw relational plots
		The dataset should be loaded through the loadData() function
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, string> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool relplot(const string x, const string y, const map<string, Storage>& keywords)
	{
		PyObject* pyrelplot = safe_import(seabornLib,"relplot");
		
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyUnicode_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyUnicode_FromString(y.c_str()));
		
		PyObject* kwargs = PyDict_New();
		for(map<string, Storage>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
	    {
	    	PyObject* tmp;
	    	if(it->second.getVal().compare("str") == 0)
	    	{
	    		tmp = PyUnicode_FromString(it->second.getString().c_str());
			}
			else if(it->second.getVal().compare("int") == 0)
	    	{
	    		tmp = PyFloat_FromDouble(it->second.getDouble());
			}
			else if(it->second.getVal().compare("bool") == 0)
	    	{
	    		if(!it->second.getBool())
	    			tmp = Py_False;
	    		else
	    			tmp = Py_True;
			}
			else if(it->second.getVal().compare("intarr") == 0)
	    	{
	    		int n = it->second.getN();
	    		double* t = it->second.getDoubleArray();
	    		tmp = PyTuple_New(n);
				for(int i=0; i<n; i++)
			    {
			        PyTuple_SetItem(tmp, i, PyFloat_FromDouble(t[i]));
			    }
			}
			else if(it->second.getVal().compare("strarr") == 0)
	    	{
	    		int n = it->second.getN();
	    		string* t = it->second.getStringArray();
	    		tmp = PyList_New(n);
				for(int i=0; i<n; i++)
			    {
			        PyList_SetItem(tmp, i, PyUnicode_FromString(t[i].c_str()));
			    }
			}
	        PyDict_SetItemString(kwargs, it->first.c_str(), tmp);
	    }
	    
	    if(!dataset)
	    {
	    	cout<<"\nDataset not loaded\n";
	    	return false;
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
	
	//=================================================================================================================
};

