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

/* Distancias de Manhattan para 15-puzzle
int mdistance[16][16] = 
{
 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4, 4, 3, 4, 5},
 {2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3, 5, 4, 3, 4},
 {3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2, 6, 5, 4, 3},
 {1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5},
 {2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4},
 {3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3},
 {4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2},
 {2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4},
 {3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3},
 {4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2},
 {5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1},
 {3, 4, 5, 6, 2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3},
 {4, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2},
 {5, 4, 3, 4, 4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1},
 {6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0}
};

// Recibe un objeto de tipo state_t y lo convierte en un arreglo de enteros
int* toArray(state_t state){
	int k = 0;
	char auxArray[32];
	int* distance = new int[16];
	char* ptr = NULL;

	sprint_state(auxArray,32,&state);
	ptr = strtok(auxArray," ");

	while(ptr!=NULL){
		if(strcmp(ptr,"B")==0){
			distance[k] = 0;
		} else {
			distance[k] = atoi(ptr);
		}
		k = k + 1;
		ptr = strtok(NULL," ");		
	}
	return distance;
}

// Calcula la distancia Manhattan a un tile en el 15-puzzle
int Manhattan(state_t state){
	int distance = 0;
	int* puzzle;
	puzzle = toArray(state);
	for(int i = 0; i < 16; i++){
		distance = distance + mdistance[puzzle[i]][i];
	}
	delete[] puzzle;
	return distance;
	
}
*/
