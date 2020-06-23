#include "seaborn.h"
#include<iostream>
#include<map>
using namespace std;
int main()
{
	//Initialize seaborn object
	seaborn s;
	
	//Loads dataset
	s.loadDataSet("test1.csv");

	//defines relplot parameters
	map<string, string> args;
	args["hue"] = "day";

	//saves graph in the same folders
	bool x = s.relplot("total_bill", "tip", args);
	s.saveGraph("relpolt");
	return 0;

}
