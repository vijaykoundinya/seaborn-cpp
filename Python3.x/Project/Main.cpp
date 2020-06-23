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
	
	//Replot
	//https://seaborn.pydata.org/generated/seaborn.relplot.html#seaborn.relplot
	//Create map to set fields
	map<string, string> args;
	args["hue"] = "day";
	
	bool rel = s.relplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("relplot");
	
	getch();
	return 0;
}
