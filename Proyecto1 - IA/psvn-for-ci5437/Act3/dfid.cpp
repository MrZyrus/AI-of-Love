#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

unsigned long long nodes_generated = 0;

int dfidVisit(state_t,int,int,int);
int dfid (state_t);

int main(){
	state_t root;
	string state_string;
	int r;
	cout << "Enter State: " << endl;

	getline(cin,state_string);

	if (read_state(state_string.c_str(),&root) == -1){

		cout << "Incorrect State." << endl;
		int goal;
		first_goal_state(&root,&goal);

		cout << "The goal is: " << endl;
		print_state(stdout,&root);
		cout << endl;
		return 0;
	}

	nodes_generated = 0;

	clock_t begin = clock();

	r = dfid(&root);

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	double gen_per_sec = double(nodes_generated)/elapsed_secs;

	cout << " algorithm, domain, instance, cost, generated, time, gen_per_sec " << endl;

	cout << " dfid ," << state_string << ", " << r;
	cout << ", " << nodes_generated << ", " << elapsed_secs << ", ";
	cout << gen_per_sec << endl;

}


void dfid(state_t root){
	int aux;
	int bound = 0;
	int hist = init_history;
	while(true){
		aux = dfidVisit(&root,0,bound,hist); 
		if (aux < 0){
			return aux;
		}
		bound++;
	}
}

int dfidVisit(state_t state, int bound, int actCost, int hist){
	
	int ruleID, nextHist, aux;
	ruleid_iterator_t iter;
	state_t child;
	
	if ( bound + 1 >= actCost){ 
		return -1;
	}

	if (is_goal(&state)){
		return bound+1;
	}

	init_fwd_iter(&iter,&state);

	while ((ruleID = next_ruleid(&iter)) >= 0){
		if (!fwd_rule_valid_for_history(hist,ruleID)) continue;

		nextHist = next_fwd_history(hist,ruleID);
		apply_fwd_rule(ruleID, &state, &child);
		nodes_generated++; 
		aux = dfidVisit(child,bound+1,actCost,nextHist);
		if (aux != -1) return aux; 
	}

	return -1;
}
