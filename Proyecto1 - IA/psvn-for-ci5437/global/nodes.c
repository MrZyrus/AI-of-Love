#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

#define  MAX_LINE_LENGTH 999 

int vals[20]; //Global variable to store number of nodes at the index depth, considering max depth 20

void dfs(state_t state, int d, int chist, int n){

    if(d > n)
        return;
    vals[d]++;

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    int hist, child_hist;
    hist = chist;
    init_fwd_iter(&iter, &state);  // initialize the child iterator 
    while( (ruleid = next_ruleid(&iter)) >= 0 ) {
        if (!fwd_rule_valid_for_history(hist,ruleid)){	    
           continue;
        }
        child_hist = next_fwd_history(hist,ruleid);
        apply_fwd_rule(ruleid, &state, &child);	
        dfs(child,d+1,child_hist,n);       
    }
}

int main(int argc, char **argv ) {
    // VARIABLES FOR INPUT
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;

    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    int depth_to_explore;

    printf("Please enter the depth to count nodes to: ");
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return -1; 
    }

    depth_to_explore = atoi(str);

    // READ A LINE OF INPUT FROM stdin
    printf("Please enter a state followed by ENTER: ");
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return -1; 
    }

    // CONVERT THE STRING TO A STATE
    nchars = read_state(str, &state);
    if( nchars <= 0 ) {
        printf("Error: invalid state entered.\n");
        return -1; 
    }

    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");
    printf("Please wait while the nodes are counted, this may take several minutes.\n");

    // LOOP THOUGH THE CHILDREN ONE BY ONE
    dfs(state,0,init_history,depth_to_explore);
    int i = 0;
    while(i<depth_to_explore+1){ //Finally printing the nodes found at each depth
        printf(" %d states found at depth %d\n", vals[i], i);
        i++;
    }
    
    return 0;
}
