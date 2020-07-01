#include "seaborn.h"
#include<iostream>
#include<map>
#include<python2.7/Python.h>
using namespace std;
void relplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/test1.csv");
	
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
	s.saveGraph("Outputs/relplot");
}

void catplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/exercise.csv");
	
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
	s.saveGraph("Outputs/catplot");
}

void lmplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/test1.csv");
	
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
	s.saveGraph("Outputs/lmplot");
}

void regplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/test1.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
		
	store.setDouble(0.2);
	args["x_jitter"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.regplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("Outputs/regplot");
}

void residplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/anscombe.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.residplot("x", "y", args);
		
	//Save Graph
	s.saveGraph("Outputs/residplot");
}

void distplotExample(Seaborn &s, Storage &store)
{
	double a[100] = { -0.29385136, 0.28196709, 0.92542057, 0.8208778, 0.21837386, -0.88259887,
						-0.88595316, 0.48483897, -1.17235545, -0.68126546, 0.51600199, -0.33735844,
						1.06707407, 0.25734881, -0.90703331, 0.60856498, 2.87439584, 0.50700039,
						0.01418172, 0.17660051, 0.77373668, -0.0734634, -0.13348907, -0.19562405,
						0.44535002, 0.51461805, 0.96354967, 1.26410625, -1.09070097, -0.20217336,
						-0.21456817, 0.5232655, -1.11752028, -1.10361684, -0.80743155, 1.50310648,
						0.16699, 0.51775273, -1.2762417,  1.49814803, -1.00618166, 1.82314498,
						-0.32672569, 2.79690646, -1.85608818, -0.84808529, -0.98065428, 0.39521234,
						-0.23937032, 0.63696037, -0.12242001, 0.65924443, -0.9287651, -1.38085266,
						-0.58196925, -0.48117534, -0.80324574, -0.1079184, -1.32690859, 1.38280845,
						1.96118507, -1.29409899, -1.33165691, -0.02934378, 1.0515531, -1.15023811,
						0.15361587, 0.04867364, -0.14832351, -0.08449501, 0.01969361, 0.51500492,
						1.04933527, 1.3153045, -1.4654021, -1.10688957, 0.72920653, -1.69699198,
						-0.90225131, -2.05667412, -0.59581024, -1.16733476, 0.8123405, -1.51777801,
						0.61392725, 0.80048959, -0.54114263, 0.36487752, 0.06444122, -1.93596928,
						1.35741195, 0.4776197, -0.59896581, -0.23869392, 0.2926181, -1.69157301,
						0.36470062, -1.68651989, -0.9639898, 1.08390747 };
	
	//Distplot example
	Storage ar;
	ar.setDoubleArray(a, sizeof(a)/sizeof(double));
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setBool(true);
	args["rug"] = store;
	
	//rug_kws
	Storage kws;
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
	
	//Call function relplot with 'a' and arguments (args is optional)
	bool dist = s.distplot(ar, args);
		
	//Save Graph
	s.saveGraph("Outputs/distplot");
}

void pairplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/iris.csv");
	
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
	s.saveGraph("Outputs/pairplot");
}

void jointplotExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/test1.csv");
	
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("hex");
	args["kind"] = store;
	
	//Call function relplot with x, y and arguments (args is optional)
	bool rel = s.jointplot("total_bill", "tip", args);
		
	//Save Graph
	s.saveGraph("Outputs/jointplot");
}

void heatmapExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/flights.csv");
	
	//Heatmap example
	//The arguments are completely optional
	map<string, Storage> args;
	store.setString("YlGnBu");
	args["cmap"] = store;
		
	store.setDouble(0.5);
	args["linewidths"] = store;
		
	//Call function catplot with x, y and arguments (args is optional)
	bool cat = s.heatmap("month", "year", "passengers", args);
		
	//Save Graph
	s.saveGraph("Outputs/heatmap");
}

void clustermapExample(Seaborn &s, Storage &store)
{
	//Pass CSV dataset path
	bool ret = s.loadData("Datasets/iris_modified.csv");
	
	//Clustermap example
	//The arguments are completely optional
	map<string, Storage> args;
	store.setBool(false);
	args["row_cluster"] = store;
	
	double dendRatio[2] = { 0.1, 0.2 };
	store.setDoubleArray(dendRatio, 2, false);
	args["dendrogram_ratio"] = store;
	
	double cbarPos[4] = { 0, 0.2, 0.03, 0.4 };
	store.setDoubleArray(cbarPos, 4, false);
	args["cbar_pos"] = store;
		
	//Call function clustermap with x, y and arguments (args is optional)
	bool cat = s.clustermap(args);
		
	//Save Graph
	s.saveGraph("Outputs/clustermap");
}
int main()
{
	//Initialise Seaborn
	Seaborn s;
	Storage store;
	
	relplotExample(s, store);
	
	catplotExample(s, store);
	
	lmplotExample(s, store);

	regplotExample(s, store);

	residplotExample(s, store);

	distplotExample(s, store);
	
	pairplotExample(s, store);
		
	jointplotExample(s, store);

	heatmapExample(s, store);
	return 0;
}
