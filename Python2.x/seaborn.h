#include <python2.7/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
//#include <conio.h>
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
	bool *bl;
	map<string, Storage> m;
	
	string val;
	bool type;
		
	public:
		
		void setDouble(double i)
		{
			this->i = i;
			val = "int";
			
			s = "";
			b = false;
			li = new double[1];
			sa = new string[1];
			bl = new bool[1];
		}
			
		void setString(string s)
		{
			this->s = s;
			val = "str";
			
			i = 0;
			b = false;
			li = new double[1];
			sa = new string[1];
			bl = new bool[1];
		}
		
		void setBool(bool b)
		{
			this->b = b;
			val = "bool";
			
			i = 0;
			s = "";
			li = new double[1];
			sa = new string[1];
			bl = new bool[1];
		}
		
		void setDoubleArray(double *li, int n, bool t = true)
		{
			this->li = new double[n];
			copy(li, li + n, this->li);
			val = "intarr";
			type = t;
			this->n = n;
			
			i = 0;
			s = "";
			b = false;
			sa = new string[1];
			bl = new bool[1];
		}
		
		void setStringArray(string *sa, int n, bool t = true)
		{
			this->sa = new string[n];
			copy(sa, sa + n, this->sa);
			val = "strarr";
			type = t;
			this->n = n;
			
			i = 0;
			s = "";
			b = false;
			li = new double[1];
			bl = new bool[1];
		}
		
		void setBoolArray(bool *bl, int n, bool t = true)
		{
			this->bl = new bool[n];
			copy(bl, bl + n, this->bl);
			val = "boolarr";
			type = t;
			this->n = n;
			
			i = 0;
			s = "";
			b = false;
			sa = new string[1];
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
			bl = new bool[1];
		}
		
		void setDict(map<string, Storage> m)
		{
			this->m = m;
			val = "kwargs";
			
			i = 0;
			s = "";
			b = false;
			li = new double[1];
			sa = new string[1];
			bl = new bool[1];
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
		
		bool* getBoolArray() const
		{
			return bl;
		}
		
		map<string, Storage> getDict() const
		{
			return m;
		}
		
		string getVal() const
		{
			return val;
		}
		
		bool getType() const
		{
			return type;
		}
};
class Seaborn
{
	PyObject* seabornLib;
	PyObject* dataset;
	PyObject* savefig;
	PyObject* pandas;
	PyObject* readCsv;
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
			if(store.getType())
			{
				tmp = PyList_New(n);
				for(int i=0; i<n; i++)
	       	    {
		        	PyList_SetItem(tmp, i, PyFloat_FromDouble(t[i]));
		    	}
			}
			else
			{
				tmp = PyTuple_New(n);
				for(int i=0; i<n; i++)
				{
			        PyTuple_SetItem(tmp, i, PyFloat_FromDouble(t[i]));
		        }
	    	}
		}
		else if(store.getVal().compare("strarr") == 0)
		{
			int n = store.getN();
			string* t = store.getStringArray();
			if(store.getType())
			{
				tmp = PyList_New(n);
				for(int i=0; i<n; i++)
	       	    {
		        	PyList_SetItem(tmp, i, PyUnicode_FromString(t[i].c_str()));
		    	}
		    }
		    else
		    {
		    	tmp = PyTuple_New(n);
				for(int i=0; i<n; i++)
				{
			        PyTuple_SetItem(tmp, i, PyUnicode_FromString(t[i].c_str()));
		        }
			}
		}
		else if(store.getVal().compare("boolarr") == 0)
		{
			int n = store.getN();
			bool* t = store.getBoolArray();
			if(store.getType())
			{
				tmp = PyList_New(n);
				for(int i=0; i<n; i++)
	       	    {
	       	    	if(t[i])
		        		PyList_SetItem(tmp, i, Py_True);
		        	else
		        		PyList_SetItem(tmp, i, Py_False);
		    	}
		    }
		    else
		    {
		    	tmp = PyTuple_New(n);
				for(int i=0; i<n; i++)
	       	    {
	       	    	if(t[i])
		        		PyTuple_SetItem(tmp, i, Py_True);
		        	else
		        		PyTuple_SetItem(tmp, i, Py_False);
		    	}
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
			map<string, Storage> val = store.getDict();
			for(map<string, Storage>::const_iterator i = val.begin(); i != val.end(); ++i)
	        {
	    		PyObject* tmp = getArgData(i->second);
	        	PyDict_SetItemString(tmp, i->first.c_str(), tmp);
	        }
		}
		
		return tmp;
	}

public:
	Seaborn()
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
		PyObject* pandasName = PyString_FromString("pandas");
		pandas = PyImport_Import(pandasName);
		if(!pandas)
		{
			PyErr_Print();
		}
		readCsv = safe_import(pandas,"read_csv");

	}
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
		PyTuple_SetItem(pystring,0,PyString_FromString(s.c_str()));
		dataset = PyObject_CallObject(readCsv,pystring);
		if(!dataset)
		{
			PyErr_Print();
			return false;
		}
		PyObject* o = PyObject_Repr(dataset);
		const char* check = PyString_AsString(o);
		cout<<check;
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
		String arguments can be passed through the map<string, string>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/	
	bool relplot(const string x,const string y,const map<string, Storage>& keywords)
	{
		PyObject* pyrelplot = safe_import(seabornLib,"relplot");
		
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyString_FromString(y.c_str()));
		
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
	//CATEGORICAL PLOTS
	//https://seaborn.pydata.org/generated/seaborn.catplot.html#seaborn.catplot
	
	
	/*
		This function is used to draw categorical plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, Storage>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool catplot(const string x,const string y,const map<string, Storage>& keywords)
	{

		PyObject* pycatplot= safe_import(seabornLib,"catplot");
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyString_FromString(y.c_str()));

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
		else
				
		Py_DECREF(args);
	    	Py_DECREF(kwargs);
	    	if(res)
			Py_DECREF(res);
	    	return res;	
		
	}
	//=================================================================================================================


	//=================================================================================================================
	//REGRESSION PLOTS
	//https://seaborn.pydata.org/tutorial/regression.html
	
	
	/*
		This function is used to draw regression plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, Storage>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool lmplot(const string x,const string y,const map<string, Storage>& keywords)
	{

		PyObject* pylmplot= safe_import(seabornLib,"lmplot");
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyString_FromString(y.c_str()));

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
			
		PyObject* res = PyObject_Call(pylmplot, args, kwargs);
		if(!res)
			PyErr_Print();
		else
				
		Py_DECREF(args);
	    	Py_DECREF(kwargs);
	    	if(res)
			Py_DECREF(res);
	    	return res;	
		
	}


	/*
		This function is used to draw regression plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, Storage>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool regplot(const string x,const string y,const map<string, Storage>& keywords)
	{

		PyObject* pyregplot= safe_import(seabornLib,"regplot");
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyString_FromString(y.c_str()));

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
			
		PyObject* res = PyObject_Call(pyregplot, args, kwargs);
		if(!res)
			PyErr_Print();
		else
				
		Py_DECREF(args);
	    	Py_DECREF(kwargs);
	    	if(res)
			Py_DECREF(res);
	    	return res;	
		
	}
	/*
		This function is used to draw regression plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, Storage>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool residplot(const string x,const string y,const map<string, Storage>& keywords)
	{

		PyObject* pyresidplot= safe_import(seabornLib,"residplot");
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyString_FromString(y.c_str()));

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
			
		PyObject* res = PyObject_Call(pyresidplot, args, kwargs);
		if(!res)
			PyErr_Print();
		else
				
		Py_DECREF(args);
	    	Py_DECREF(kwargs);
	    	if(res)
			Py_DECREF(res);
	    	return res;	
		
	}



	//=================================================================================================================
	/*
		This function is used to flexibly plot a univariate distribution of observations.
		
		Parameters:
		:a: Storage Class - Observed data
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    		:return: bool - Result of operation (Success or Failure)
	*/
	bool distplot(const Storage a, const map<string, Storage>& keywords = map<string, Storage>())
	{
		PyObject* pydistplot = safe_import(seabornLib, "distplot");
		
		PyObject* args = getArgData(a);
		
		PyObject* kwargs = PyDict_New();
		for(map<string, Storage>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
	    	{
	    		PyObject* data = getArgData(it->second);	
			PyDict_SetItemString(kwargs, it->first.c_str(), data);
	    	}
	    		
		PyObject* res;
		//if(PyLong_AsLong(PyLong_FromSsize_t(PyDict_Size(kwargs))) == 0)
		//	res = PyObject_Call(pydistplot, args, Py_None);
		//else
		res = PyObject_Call(pydistplot, args, kwargs);
		
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
/*
		This function is used to draw bivariate plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, Storage>
		All arguments have to be set manually through setter functions
		
		Parameters:
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    		:return: bool - Result of operation (Success or Failure)
	*/
	bool pairplot(const map<string, Storage>& keywords = map<string, Storage>())
	{

		PyObject* pypairplot= safe_import(seabornLib,"pairplot");
		if(!dataset)
	    	{
	    		cout<<"\nDataset not loaded\n";
	    		return false;
		}
		PyObject* args = PyTuple_New(1);
		PyTuple_SetItem(args, 0, dataset);

		PyObject* kwargs = PyDict_New();
		for(map<string, Storage>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
		{
	    		PyObject* data = getArgData(it->second);	
			PyDict_SetItemString(kwargs, it->first.c_str(), data);
		}   
			
		PyObject* res = PyObject_Call(pypairplot, args, kwargs);
		if(!res)
			PyErr_Print();
		else
				
		Py_DECREF(args);
	    	Py_DECREF(kwargs);
	    	if(res)
			Py_DECREF(res);
	    	return res;	
		
	}
	//=================================================================================================================

	/*
		This function is used to draw bivariate plots
		The dataset should be loaded through the loadData() function
		String arguments can be passed through the map<string, Storage>
		Other arguments have to be set manually through setter functions
		
		Parameters:
		:x: string - Column Name in dataset - Must be numeric
		:y: string - Column Name in dataset - Must be numeric
		:keywords: map<string, Storage> - Key-Value Pairs of additional arguments of type string
		
    	:return: bool - Result of operation (Success or Failure)
	*/
	bool jointplot(const string x,const string y,const map<string, Storage>& keywords)
	{

		PyObject* pyjointplot= safe_import(seabornLib,"jointplot");
		PyObject* args = PyTuple_New(2);
		PyTuple_SetItem(args, 0, PyString_FromString(x.c_str()));
		PyTuple_SetItem(args, 1, PyString_FromString(y.c_str()));

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
			
		PyObject* res = PyObject_Call(pyjointplot, args, kwargs);
		if(!res)
			PyErr_Print();
		else
				
		Py_DECREF(args);
	    	Py_DECREF(kwargs);
	    	if(res)
			Py_DECREF(res);
	    	return res;	
		
	}



	//=================================================================================================================
	
};

