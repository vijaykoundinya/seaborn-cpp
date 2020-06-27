#include "seaborn.h"
#include<iostream>
#include<map>
using namespace std;
int main()
{
	//Initialise Seaborn
	seaborn s;
	Storage store;
	
	//Pass CSV dataset path
	bool ret = s.loadData("exercise.csv");	
	
	//Replot example
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("kind");
	args["hue"] = store;
	
	//store.setDouble(2);
	//args["col_wrap"] = store;
		
	store.setDouble(0.7);
	args["aspect"] = store;
	
	store.setString("violin");
	args["kind"] = store;

	store.setFunctionName("numpy.mean");
	args["estimator"] = store;
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.catplot("time", "pulse", args);
		
	//Save Graph
	s.saveGraph("catplot3s");
	
	//getch();
	return 0;
}
