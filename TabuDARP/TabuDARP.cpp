// TabuDARP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//CopyRight

#include "pch.h"
#include "Data.h"
#include "solution.h"
#include "construct.h"
#include "localsearch.h"
#include "record_move.h"
#include <iostream>
#include <queue>
#include <vector>
#define NONE_PARALLEL
Point poi[maxn];
double depart[maxn];
double arrive[maxn];
int count_request_route[maxn];

int main(int argc,char* argv[])
{
	/*initialization parameter*/
	std::ios::sync_with_stdio(false);
	const char *path = "E:/dataset/R8a.txt";
	Data d(path);
	Parameter p(1,1,1,1,0.5,10,7.5*log(d.get_vertex_number()/2),15);
	solution s;
	Record_move rm;
	int search_function = VNS;
	Answer_Record ansrec_imp,ansrec_nonimp;
	/*initialization*/
	if (search_function == Tabu) 
	{		
		s = construct_Tabu(d,rm); 
		
	}
	else if (search_function == VNS) 
	{ 
		//d.pruning();
		//d.printTimeWindow();
		s = construct_VNS(d);
		s.update(p, d);
		//s.output("123");
	} 
	else 
	{ 
		s = construct_Para(d); 
	}
	/*Tabu Search components*/
	if(search_function==Tabu) TabuSearch(s, p, d,rm,1);
	else if (search_function == VNS) 
	{ 
		printf("improved Search\n");
		printf("s cost : %.4lf\n", s.get_cost(p,d));
		VariableNeighborSearch(s, p, d, 1,ansrec_imp);
		printf("Record : \n first to find : %d\nbest Cost %.4lf\n", ansrec_imp.first_to_discover_improve, ansrec_imp.BestFind_Improve);
		printf("non improved search\n");
		p.set(1, 1, 1, 1, 0.5, 10, 7.5*log(d.get_vertex_number() / 2), 15);
		printf("s cost : %.4lf\n", s.get_cost(p,d));
		VariableNeighborSearch(s, p, d, 0, ansrec_nonimp);
		printf("Record : \n first to find : %d\nbest Cost %.4lf\n", ansrec_nonimp.first_to_discover_noimprove, ansrec_nonimp.BestFind_Improve);
	}
	else paraNeighborSearch(s, p);
	puts("Result");
	printf("improve : first discover feasible : %d\nbest cost : %.4lf\n",ansrec_imp.first_to_discover_improve,ansrec_imp.BestFind_Improve);
	printf("nonimprove : first discover feasible : %d\nbest cost : %.4lf\n", ansrec_nonimp.first_to_discover_noimprove, ansrec_nonimp.BestFind_Improve);
	system("pause");
	return 0;
}
