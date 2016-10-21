#include "priority_queue.hpp"
#include <fstream>
#include <sys/time.h>
#include <string>
#include <sstream>

using namespace std;

struct node {
    state_t state;
    int d;
    int hist;
};

bool limit = false;
long long nodes_generated = 0;
time_t begint,endt;

//Funcion heuristica GAP

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

void a_star_expand(node expand, PriorityQueue<node> &q) {
    int ruleID;
    ruleid_iterator_t iter;
    state_t child;
    init_fwd_iter(&iter, &expand.state);
    int f;

    while ((ruleID = next_ruleid(&iter)) >= 0){
        if (!fwd_rule_valid_for_history(expand.hist, ruleID)) continue;
        node child;
        child.hist = next_fwd_history(expand.hist, ruleID);
        apply_fwd_rule(ruleID, &expand.state, &child.state);
        child.d = expand.d + 1;
        nodes_generated++;
        f = child.d + gap(child.state);
        q.Add(f, f, child);
    }
}

int a_star(state_t state, int hist, int d) {
    PriorityQueue<node> q;
    int f = d + gap(state);
    node to_expand;
    state_t child;
    double secs;
    
    to_expand.state = state;
    to_expand.hist = hist;
    to_expand.d = d;

    q.Add(f, f, to_expand);

    while(!q.Empty()) {
        
        endt = time(NULL);
        secs = difftime(endt,begint);
        if(secs > 300) {    // 5 minutes
            limit = true;
            return 0;
        }

        to_expand = q.Top();
        q.Pop();

        if (is_goal(&to_expand.state)) return to_expand.d;
        a_star_expand(to_expand, q);
    }

    limit = true;
    return 0;

}


int main(int argc, char* argv[]) {
    
    state_t root;
    int aux;
    string state_string;
    char stateArray[256];
    int hist;
    clock_t begin, end;
    double elapsed_secs;
    double gen_per_sec;

    ifstream file (argv[1]);
    std::string path = argv[1];
    ofstream outfile (argv[2]);
    outfile << "grupo, algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec\n";


    if (file.is_open()) {

        while (getline(file, state_string)) {
            strncpy(stateArray, state_string.c_str(), sizeof(stateArray));
            stateArray[sizeof(stateArray) - 1] = 0;
            hist = init_history;
            read_state(stateArray, &root);
            nodes_generated++;

            begin = clock();
            begint = time(NULL);

            aux = a_star(root, hist, 0);

            end = clock();

            elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            gen_per_sec = double(nodes_generated)/elapsed_secs;

            if (!limit){
                outfile << "x, a_star, manhattan, ";
                outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
                outfile << "'" << stateArray << "', ";
                outfile << aux << ", ";
                outfile << gap(root) << ", ";
                outfile << nodes_generated << ", ";
                outfile << elapsed_secs << ", ";
                outfile << gen_per_sec << endl;
            }

            else {
                outfile << "x, a_star, manhattan, ";
                outfile << path.substr(path.find_last_of("\\/")+1,path.find_last_of(".")) << ", ";
                outfile << "'" << stateArray << "', ";
                outfile << "na, na, na, na, na "<< endl;
                limit = false; 
            }

            nodes_generated = 0;
        }

        file.close();
        outfile.close();
    }
}
