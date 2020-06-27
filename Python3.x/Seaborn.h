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
	map<string, Storage> m;
	
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
		
		void setFunctionName(string s)
		{
			this->s = s;
			val = "func";
			
			i = 0;
			b = false;
			li = new double[1];
			sa = new string[1];
		}
		
		void setkwargs(string str, map<string, Storage> m)
		{
			this->m = m;
			val = "kwargs";
			
			i = 0;
			s = "";
			b = false;
			li = new double[1];
			sa = new string[1];
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
		
		map<string, Storage> getkwargs() const
		{
			return m;
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
	PyObject* pandas;
	PyObject* savefig;
	PyObject* readCsv;
	
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
	
	PyObject* getArgData(Storage store)
	{
		PyObject* tmp;
		if(store.getVal().compare("str") == 0)
		{	
			tmp = PyUnicode_FromString(store.getString().c_str());
		}
		else if(store.getVal().compare("int") == 0)
		{
			tmp = PyFloat_FromDouble(store.getDouble());
		}
		else if(store.getVal().compare("bool") == 0)
		{
			if(!store.getBool())
				tmp = Py_False;
			else
				tmp = Py_True;
		}
		else if(store.getVal().compare("intarr") == 0)
		{
			int n = store.getN();
			double* t = store.getDoubleArray();
			tmp = PyTuple_New(n);
			for(int i=0; i<n; i++)
			{
		        PyTuple_SetItem(tmp, i, PyFloat_FromDouble(t[i]));
	        }
		}
		else if(store.getVal().compare("strarr") == 0)
		{
			int n = store.getN();
			string* t = store.getStringArray();
			tmp = PyList_New(n);
			for(int i=0; i<n; i++)
       	    {
	        	PyList_SetItem(tmp, i, PyUnicode_FromString(t[i].c_str()));
	    	}
		}
		else if(store.getVal().compare("func") == 0)
		{
			string s = store.getString();
			int pos = s.find_last_of(".");
			string module = s.substr(0,pos);
			string funcName = s.substr(pos+1,s.length()-1);
    		PyObject* functionName = PyUnicode_FromString(module.c_str());
			PyObject* tmp1 = PyImport_Import(functionName);
			if(!tmp1)
			{
				PyErr_Print();
			}
			tmp = safe_import(tmp1,funcName);
		}
		else if(store.getVal().compare("kwargs") == 0)
		{
			tmp = PyDict_New();
			map<string, Storage> val = store.getkwargs();
			for(map<string, Storage>::const_iterator i = val.begin(); i != val.end(); ++i)
	        {
	    		PyObject* tmp = getArgData(i->second);
	        	PyDict_SetItemString(tmp, i->first.c_str(), tmp);
	        }
		}
		
		return tmp;
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
		
		PyObject* pandasName = PyUnicode_FromString("pandas");
		pandas = PyImport_Import(pandasName);
		if(!pandas)
		{
			PyErr_Print();
		}
		
		savefig = safe_import(matplotlibLib, "savefig");
		
		readCsv = safe_import(pandas, "read_csv");
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
		PyObject* pystring = PyTuple_New(1);
		PyTuple_SetItem(pystring, 0, PyUnicode_FromString(s.c_str()));

		dataset = PyObject_CallObject(readCsv, pystring);
		
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
		PyObject* res = PyObject_CallObject(savefig, pystring);
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
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool relplot(const string x, const string y, const map<string, Storage>& keywords = map<string, Storage>())
	{
		PyObject* pyrelplot = safe_import(seabornLib,"relplot");
		
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyUnicode_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyUnicode_FromString(y.c_str()));
		
		PyObject* kwargs = PyDict_New();
		for(map<string, Storage>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
    	{
    		PyObject* data = getArgData(it->second);	
        	PyDict_SetItemString(kwargs, it->first.c_str(), data);
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
	//=================================================================================================================

	//=================================================================================================================
	//CATEGORICAL PLOTS
	//https://seaborn.pydata.org/generated/seaborn.relplot.html#seaborn.catplot
	
	/*
		This function is used to draw categorical plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, string>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool catplot(const string x,const string y,const map<string, Storage>& keywords = map<string, Storage>())
	{
		PyObject* pycatplot= safe_import(seabornLib, "catplot");
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyUnicode_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyUnicode_FromString(y.c_str()));

		PyObject* kwargs = PyDict_New();
		for(map<string, Storage>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
		{
	    	PyObject* data = getArgData(it->second);	
			PyDict_SetItemString(kwargs, it->first.c_str(), data);
		}
		
		PyDict_SetItemString(kwargs, "data", dataset);
				
		if(!dataset)
	    {
    		cout<<"\nDataset not loaded\n";
    		return false;
		}
			
		PyObject* res = PyObject_Call(pycatplot, args, kwargs);
		
		if(!res)
			PyErr_Print();
				
		Py_DECREF(args);
    	Py_DECREF(kwargs);
    	if(res)
			Py_DECREF(res);
		
    	return res;
		
	}
	
	//=================================================================================================================

};
