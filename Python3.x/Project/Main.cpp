#include "../Seaborn.h"
#include <iostream>
#include <conio.h>
#include <map>

using namespace std;

int main()
{
	//Initialise Seaborn
	Seaborn s;
	
	//Pass CSV dataset path
	bool ret = s.loadData("test1.csv");	
	
	//Replot example
	//The arguments are completely optional
	map<string, string> args;
	args["hue"] = "time";
	args["row"] = "day";
	
	//s.setColWrap(2);
	
	//s.setHeight(5);
	
	//s.setAspect(0.7);
	
	string rowOrder[4] = { "Fri", "Sun", "Thur", "Sat" };
	s.setRowOrder(rowOrder, 4);
	
	bool rel = s.relplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("relplot");
	
	getch();
	return 0;
}
