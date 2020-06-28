#include "seaborn.h"
#include<iostream>
#include<map>
#include<python2.7/Python.h>
using namespace std;
void relplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("test1.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("time");
	args["hue"] = store;
	
	store.setString("day");
	
	args["row"] = store;
	
	//store.setDouble(2);
	//args["col_wrap"] = store;
		
	store.setDouble(0.7);
	args["aspect"] = store;
	
	string rowOrder[4] = { "Fri", "Sun", "Thur", "Sat" };
	store.setStringArray(rowOrder, 4);
	args["row_order"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.relplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("relplot");
}

void catplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("exercise.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("kind");
	args["hue"] = store;
	
	//store.setDouble(2);
	//args["col_wrap"] = store;
		
	store.setDouble(2);
	args["aspect"] = store;
	
	store.setString("box");
	args["kind"] = store;
	
	store.setFunctionName("numpy.mean");
	args["estimator"] = store;

	//Call function catplot with x, y and arguments (args is optional)
	bool rel = s.catplot("time", "pulse", args);
		
	//Save Graph
	s.saveGraph("catplot");
}

void lmplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("test1.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("smoker");
	args["hue"] = store;
		
	store.setDouble(0.7);
	args["aspect"] = store;
	
	store.setDouble(0.2);
	args["x_jitter"] = store;

	string markers[2] = { "o", "x"};
	store.setStringArray(markers, 2);
	args["markers"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.lmplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("lmplot");
}

void regplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("test1.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
		
	store.setDouble(0.2);
	args["x_jitter"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.regplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("regplot");
}

void residplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("anscombe.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.residplot("x", "y", args);
		
	//Save Graph
	s.saveGraph("residplot");
}

void distplotExample(Seaborn &s, Storage &store)
{
	//Pass dataset as a list object
	PyObject* list =PyList_New(5);
	for(int i=0; i<5; i++)
	{
	        PyTuple_SetItem(list, i, PyFloat_FromDouble(i));
	}
	map<string, Storage> args;
	store.setString("y");
	args["color"] = store;

	bool rel = s.distplot(list,args);
	//Save Graph
	s.saveGraph("distplot");
}
int main()
{
	//Initialise Seaborn
	Seaborn s;
	Storage store;
	
	//relplotExample(s, store);
	
	//catplotExample(s, store);
	
	//lmplotExample(s, store);

	//regplotExample(s, store);

	//residplotExample(s, store);

	distplotExample(s, store);
	
	return 0;
}
