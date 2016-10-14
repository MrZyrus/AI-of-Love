#include <string>
#include <iostream>

using namespace std;

state_map_t* pdb1;
state_map_t* pdb2;       
state_map_t* pdb3;
abstraction_t* abs1;
abstraction_t* abs2;
abstraction_t* abs3;

int PDB15-puzzle(state_t state){

	state_t abstrac1;
	state_t abstrac2;
	state_t abstrac3;
	abstract_state(abs1,&state,&abstrac1);
	abstract_state(abs2,&state,&abstrac2);
	abstract_state(abs3,&state,&abstrac3);

	// Calculo del costo de cada pdb
	int value1 = *state_map_get(pdb1,&abstrac1); 
	int value2 = *state_map_get(pdb2,&abstrac2);  
	int value3 = *state_map_get(pdb3,&abstrac3);  

	return value1+value2+value3;
}