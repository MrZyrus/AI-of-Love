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
double weight = 1.5;
time_t begint,endt;


int idaVisit(state_t,int,int,int);


// Funcion heuristica gap

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


int main(int argc, char* argv[]) {


	cout << "Introduzca peso:";
	cin >> weight;	
	ulimit(UL_SETFSIZE,2048000);
	state_t root;
	int aux;
	unsigned d = 0;
	int hist;
	string state_string;
	char stateArray[256];
	clock_t begin,end;
    
	ifstream file (argv[1]);
	std::string path = argv[1];
	ofstream outfile (argv[2]);
	outfile << "grupo, algorithm, heuristic, weight, domain, instance, cost, h0, generated, time, gen_per_sec\n";
	
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
			int h0 = gap(root)*weight;
			
			
			if (!limit){
				outfile << "x, wida, gap, ";
				outfile << weight << ", ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateArray << "', ";
				outfile << aux << ", ";
				outfile << h0 << ", ";
				outfile << nodes_generated << ", ";
				outfile << elapsed_secs << ", ";
				outfile << gen_per_sec << endl;
			}
			else {
				outfile << "x, wida, gap, ";
				outfile << weight << ", ";
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


/* Funcion de recorrido usando el algoritmo WIDA* con una profundidad de "maxBound"
   Retorna un numero positivo si encontro un goal, el numero representa el costo al goal
   Retorna un numero negativo si no encontro el goal, el valor absoluto del numero representa el nuevo maxBound*/

int idaVisit(state_t state, int bound, int maxBound,int hist){
	
	int ruleID, nextHist, aux;
	ruleid_iterator_t iter;
	state_t child;
	
	endt = time(NULL);
	secs = difftime(endt,begint);
	if(secs > 300 || limit){	// 5 minutes
		limit = true;
		return 0;
	}
	int f = bound + gap(state)*weight; 
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
