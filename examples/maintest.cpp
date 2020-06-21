#include "seaborn.h"
#include<iostream>
using namespace std;
int main()
{
	seaborn s;
	s.loadDataSet("test1.csv");
	s.relplot("total_bill","tip");
	cout<<"done1";
	return 0;

}
