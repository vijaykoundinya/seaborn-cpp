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
	
	//Pass CSV dataset path
	ret = s.loadData("test1.csv");	
	
	//Replot example
	//The arguments are completely optional
	map<string, Storage> argsrel;
	store.setString("time");
	argsrel["hue"] = store;
	
	store.setString("day");
	
	argsrel["row"] = store;
	
	//store.setDouble(2);
	//args["col_wrap"] = store;
		
	store.setDouble(0.7);
	argsrel["aspect"] = store;
	
	string rowOrder[4] = { "Fri", "Sun", "Thur", "Sat" };
	store.setStringArray(rowOrder, 4);
	argsrel["row_order"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	rel = s.relplot("total_bill", "tip", argsrel);
		
	//Save Graph
	s.saveGraph("relplot");
	
	//getch();
	return 0;
}
