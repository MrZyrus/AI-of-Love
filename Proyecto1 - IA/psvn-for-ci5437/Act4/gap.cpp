#include <iostream>
#include <fstream> 
#include <sys/time.h>
#include <sstream>
#include <string>

using namespace std;

// Funcion heuristica de gap

int gap(state_t state){
	char stateArr[100];
	sprint_state(stateArr,100,&state);
	string vals(stateArr);
	std :: istringstream iss(vals);
        string curr;
	iss >> curr;
	int first, second;
	int i =0;
	int sum = 0;
	first = atoi(curr.c_str());
	iss >> curr;
	second = atoi(curr.c_str());
	while(i<27){
		if(abs(first-second) > 1)
			sum++;
		first = second;
		iss >> curr;
		second = atoi(curr.c_str());
		i++;
		
	}
	return sum;
}
