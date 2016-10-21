#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

// Funcion heuristica Manhattan

int manhatan(state_t state){
	char stateArr[100];
	sprint_state(stateArr,100,&state);
	string vals(stateArr);
	std :: istringstream iss(vals);
        string curr;
	iss >> curr;
	int first;
	int i =0;
	int sum = 0;
	
	while(i<16){
		if (curr == "B"){
			if(i == 15)
				break;
			iss >> curr;
			i++;
			continue;
		}
		first = atoi(curr.c_str());
		int row = first/4;
		int col = first % 4;
		int row2 = i/4;
		int col2 = i % 4;
		sum += abs(row - row2) + abs(col - col2);			
		iss >> curr;
		i++;
		
	}
	return sum;
}
