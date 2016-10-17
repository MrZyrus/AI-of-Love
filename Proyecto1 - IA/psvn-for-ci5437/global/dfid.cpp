#include <iostream>
#include <fstream> 
#include <sys/time.h>

using namespace std;

long long nodes_generated = 0;
bool limit = false;
double secs;
time_t begint,endt;

int dfidVisit(state_t,int,int,int);
//int dfid (state_t);

int main(int argc, char* argv[]) {

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
	outfile << "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n";
	
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
				aux = dfidVisit(root,0,d,hist);
				if (aux != -1) break; 
				d++;
				
			}
			end = clock();

			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			double gen_per_sec = double(nodes_generated)/elapsed_secs;
			
			if (!limit){
				outfile << "x, dfid, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateArray << "', ";
				outfile << aux << ", ";
				outfile << nodes_generated << ", ";
				outfile << elapsed_secs << ", ";
				outfile << gen_per_sec << endl;
			}
			else {
				outfile << "x, dfid, ";
				outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
				outfile << "'" << stateArray << "', ";
				outfile << "na, na, na, na "<< endl;
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

/*
int dfid(state_t root){
	
	if (is_goal(&root)) return 0;
	int aux;
	int bound = 0;
	int hist = init_history;
	while(true){
		aux = dfidVisit(root,0,bound,hist); 
		if (aux != -1){
			return aux;
		}
		bound++;
	}
}
*/

int dfidVisit(state_t state, int bound, int maxBound, int hist){
	
	int ruleID, nextHist, aux;
	ruleid_iterator_t iter;
	state_t child;

	endt = time(NULL);
	secs = difftime(endt,begint);
	
	if(secs > 600 || limit){	// 10 minutes
		limit = true;
		return -2;
	}
	
	if ( bound + 1 >= maxBound){ 
		return -1;
	}
	if (is_goal(&state)){
		return bound;  
	}

	init_fwd_iter(&iter,&state);

	while ((ruleID = next_ruleid(&iter)) >= 0){
		if (!fwd_rule_valid_for_history(hist,ruleID)) continue;

		nextHist = next_fwd_history(hist,ruleID);
		apply_fwd_rule(ruleID, &state, &child);
		nodes_generated++; 

		aux = dfidVisit(child,bound+1,maxBound,nextHist);
		if (aux != -1) return aux; 
	}

	return -1;
}



