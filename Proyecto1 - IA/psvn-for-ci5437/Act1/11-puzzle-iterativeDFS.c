/* This program reads a state from stdin and prints out its successors.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

#define  MAX_LINE_LENGTH 999 

int vals[21];

void dfs(state_t state, int d){

    if(d > 20)
   	  return;
    vals[d]++;

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
   

    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    int childCount;
    int hist;
    hist = init_history;
    childCount = 0;
    init_fwd_iter(&iter, &state);  // initialize the child iterator 
    while( (ruleid = next_ruleid(&iter)) >= 0 ) {
	       if (!fwd_rule_valid_for_history(hist,ruleid)){	    
	            continue;
	       }
         apply_fwd_rule(ruleid, &state, &child);
         ++childCount;
	       dfs(child,d+1);       
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
    int childCount;

    // READ A LINE OF INPUT FROM stdin
    printf("Please enter a state followed by ENTER: ");
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }

    // CONVERT THE STRING TO A STATE
    nchars = read_state(str, &state);
    if( nchars <= 0 ) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");

    // LOOP THOUGH THE CHILDREN ONE BY ONE
 
    dfs(state,0);
    int i= 0;
    while(i<21){
       printf(" %d estados a profundidad %d\n",vals[i],i);
       i++;
   }
    
    return 0;
}
