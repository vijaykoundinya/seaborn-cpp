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
	double a[15] = { -0.29385136, 0.28196709, 0.92542057, 0.8208778, 0.21837386, -0.88259887,
						-0.88595316, 0.48483897, -1.17235545, -0.68126546, 0.51600199, -0.33735844,
						1.06707407, 0.25734881, -0.90703331};
	
	//Distplot example
	Storage ar;
	ar.setDoubleArray(a, 15);
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setBool(true);
	args["rug"] = store;
	
	//rug_kws
	/*Storage kws;
	map<string, Storage> kw_args;
	kws.setString("g");
	kw_args["color"] = kws;
	
	kws.setDict(kw_args);
	args["rug_kws"] = kws;
	kw_args.clear();
	
	//kde_kws
	kws.setString("r");
	kw_args["color"] = kws;
	
	kws.setDouble(3);
	kw_args["lw"] = kws;
	
	kws.setString("KDE");
	kw_args["label"] = kws;
	
	kws.setDict(kw_args);
	args["kde_kws"] = kws;
	kw_args.clear();
	
	//hist_kws
	kws.setString("step");
	kw_args["histtype"] = kws;
	
	kws.setDouble(3);
	kw_args["linewidth"] = kws;
	
	kws.setDouble(1);
	kw_args["alpha"] = kws;
	
	kws.setString("b");
	kw_args["color"] = kws;
	
	kws.setDict(kw_args);
	args["hist_kws"] = kws;
	kw_args.clear();
	*/
	//Call function relplot with 'a' and arguments (args is optional)
	bool dist = s.distplot(ar, args);
		
	//Save Graph
	s.saveGraph("distplot");
}

void pairplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("iris.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("species");
	args["hue"] = store;
	
	string markers[3] = { "o", "s","D"};
	store.setStringArray(markers, 3);
	args["markers"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.pairplot(args);
		
	//Save Graph
	s.saveGraph("pairplot");
}

void jointplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("test1.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("hex");
	args["kind"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.jointplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("jointplot");
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

	//distplotExample(s, store);
	
	//pairplotExample(s, store);
		
	jointplotExample(s, store);
	return 0;
}
