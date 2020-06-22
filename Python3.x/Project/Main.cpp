#include "D:\Programs\seaborn-cpp-master\seaborn-cpp-master\seaborn.h"
#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	seaborn s;
	s.loadDataSet("test1.csv");
	s.relplot("total_bill","tip");
	cout<<"\ndone\n";
	getch();
	return 0;
}
