#include "../Seaborn.h"
#include <iostream>
#include <conio.h>
#include <map>

using namespace std;

int main()
{
	//Initialise Seaborn
	Seaborn s;
	Storage store;
	
	//Pass CSV dataset path
	bool ret = s.loadData("test1.csv");	
	
	//Replot example
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
	
	getch();
	return 0;
}
