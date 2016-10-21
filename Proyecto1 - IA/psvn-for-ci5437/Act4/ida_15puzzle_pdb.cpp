#include <iostream>
#include <fstream> 
#include <sys/time.h>
#include <sstream>
#include <string>
#include <ulimit.h>

using namespace std;

long long nodes_generated = 0;
bool limit = false;
double secs;
time_t begint,endt;


int idaVisit(state_t,int,int,int);
int pdb(state_t);

state_map_t *pdb1;
state_map_t *pdb2;       
state_map_t *pdb3;
abstraction_t *abs1;
abstraction_t *abs2;
abstraction_t *abs3;


int main(int argc, char* argv[]) {

	
ulimit(UL_SETFSIZE,2000000);
	state_t root;
	int aux;
	unsigned d = 0;
	int hist;
	string state_string;
	char stateArray[256];
	clock_t begin,end;

	abs1 = read_abstraction_from_file("./PDB/pdb1.abst");
    abs2 = read_abstraction_from_file("./PDB/pdb2.abst");
    abs3 = read_abstraction_from_file("./PDB/pdb3.abst");

    FILE *f = fopen ("./PDB/pdb1.pdb" , "r"); 
    pdb1 = read_state_map(f);
    fclose (f);
    FILE *f2 = fopen ("./PDB/pdb2.pdb" , "r"); 
    pdb2 = read_state_map(f2);
    fclose (f2);

    FILE *f3 = fopen ("./PDB/pdb3.pdb" , "r"); 
    pdb3 = read_state_map(f3);
    fclose (f3);
    
	ifstream file (argv[1]);
	std::string path = argv[1];
	ofstream outfile (argv[2]);
	outfile << "grupo, algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec\n";
	
	if (file.is_open()){

		while ( getline (file,state_string) ){
		  	
			strncpy(stateArray, state_string.c_str(), sizeof(stateArray));
			stateArray[sizeof(stateArray) - 1] = 0;
			hist = init_history;
			read_state(stateArray,&root);
			nodes_generated++;

			begin = clock();
			begint = time(NULL);

			while(true){
				aux = idaVisit(root,0,d,hist);
				if (aux > -1) break; 
				d = -aux;
			}
			end = clock();

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			double gen_per_sec = double(nodes_generated)/elapsed_secs;
			
			if (!limit){
				outfile << "x, ida, pdb555, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateArray << "', ";
				outfile << aux << ", ";
				outfile << pdb(root) << ", ";
				outfile << nodes_generated << ", ";
				outfile << elapsed_secs << ", ";
				outfile << gen_per_sec << endl;
			}
			else {
				outfile << "x, ida, pdb555, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateArray << "', ";
				outfile << "na, na, na, na, na "<< endl;
				limit = false; 
			}
			
			nodes_generated = 0;
			aux = 0;
			d = 0;
		}

		file.close();
		outfile.close();
	}

}

int pdb(state_t state){

	state_t abstrac1;
	state_t abstrac2;
	state_t abstrac3;
	abstract_state(abs1,&state,&abstrac1);
	abstract_state(abs2,&state,&abstrac2);
	abstract_state(abs3,&state,&abstrac3);

    // Calculo del costo de cada pdb
	const int *value1 = state_map_get(pdb1,&abstrac1); 
	const int *value2 = state_map_get(pdb2,&abstrac2);
	const int *value3 = state_map_get(pdb3,&abstrac3);  

	return *value1+*value2+*value3;
}

/* Funcion de recorrido usando el algoritmo IDA* con una profundidad de "maxBound"
   Retorna un numero positivo si encontro un goal, el numero representa el costo al goal
   Retorna un numero negativo si no encontro el goal, el valor absoluto del numero representa el nuevo maxBound*/

int idaVisit(state_t state, int bound, int maxBound,int hist){
	
	int ruleID, nextHist, aux;
	ruleid_iterator_t iter;
	state_t child;
	
	endt = time(NULL);
	secs = difftime(endt,begint);
	if(secs > 300 || limit){	// 10 minutes
		limit = true;
		return 2;
	}
	int f = bound + pdb(state); 
	if ( f > maxBound){
		return -f;
	}
	if (is_goal(&state)){
		return bound;  
	}

	init_fwd_iter(&iter,&state);
	int t = 300000;
	while ((ruleID = next_ruleid(&iter)) >= 0){
		if (!fwd_rule_valid_for_history(hist,ruleID)) continue;

		nextHist = next_fwd_history(hist,ruleID);
		apply_fwd_rule(ruleID, &state, &child);
		nodes_generated++; 

		aux = idaVisit(child,bound+1,maxBound,nextHist);
		if (aux > -1) return aux; 
		t = min(t,-aux);
	}
	return -t;
}

