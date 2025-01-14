#pragma once
#include "Tour.h"
#include "parameter.h"
class solution
{
private:
	Tour tourlist[200];
	int length;
	double cost;
	bool feasibility;
public:
	solution() {  feasibility = false; cost = 0; length = 0; }
	solution(const solution & s);
	Tour get_Tour(int index);
	int get_length();
	double get_cost(Parameter &p,Data &d);
	bool get_feasibility();
	void update(Parameter &p,Data &d);
	void output(const char* direction);
	void set_length(int len) { length = len; }
	void set_tourlist(Tour t, int index) { tourlist[index] = t; }
	bool operator == (solution &s);
	bool operator < (const solution &s) const;
	double hard_cost();
	void checkFeasibility(Data &d);
};
struct Answer_Record
{
	int first_to_discover_improve;
	double BestFind_Improve;
	int first_to_discover_noimprove;
	double BestFine_nonimprove;
};