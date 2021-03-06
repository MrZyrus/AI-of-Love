// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 1/11/16
// Modified by: 
//  - Jose Cipagauta (05-38040)
//  - Ricardo Lira (08-10616)
//  - Daniela Ortiz (10-10517)

#include <iostream>
#include <climits>
#include "othello_cut.h" // won't work correctly until .h is fixed!
#include "utils.h"
#include <sys/time.h>
#include <cassert>
#include <unordered_map>

using namespace std;

unsigned expanded = 0;
unsigned generated = 0;
double secs;
int tt_threshold = 32; // threshold to save entries in TT
time_t begint,endt;

// Transposition table
struct stored_info_t {
    int value_;
    int type_;
    enum { EXACT, LOWER, UPPER };
    stored_info_t(int value = -100, int type = LOWER) : value_(value), type_(type) { }
};

struct hash_function_t {
    size_t operator()(const state_t &state) const {
        return state.hash();
    }
};

class hash_table_t : public unordered_map<state_t, stored_info_t, hash_function_t> {
};

hash_table_t TTable[2];

int maxmin(state_t state, int depth, bool use_tt);
int minmax(state_t state, int depth, bool use_tt = false);
int maxmin(state_t state, int depth, bool use_tt = false);
int negamax(state_t state, int depth, int color, bool use_tt = false);
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);
bool TEST(state_t state, int depth, int score, int condition, int color);
int scout(state_t state, int depth, int color, bool use_tt = false);
int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false);

int main(int argc, const char **argv) {
    state_t pv[128];
    int npv = 0;
    for( int i = 0; PV[i] != -1; ++i ) ++npv;

    int algorithm = 0;
    if( argc > 1 ) algorithm = atoi(argv[1]);
    bool use_tt = argc > 2;

    // Extract principal variation of the game
    state_t state;
    cout << "Extracting principal variation (PV) with " << npv << " plays ... " << flush;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        pv[npv - i] = state;
        state = state.move(player, pos);
    }
    pv[0] = state;
    cout << "done!" << endl;

#if 0
    // print principal variation
    for( int i = 0; i <= npv; ++i )
        cout << pv[npv - i];
#endif

    // Print name of algorithm
    cout << "Algorithm: ";
    if( algorithm == 0 ) {
        cout << "Minmax-Maxmin";
    } else if( algorithm == 1 ) {
        cout << "Negamax (minmax version)";
    } else if( algorithm == 2 ) {
        cout << "Negamax (alpha-beta version)";
    } else if( algorithm == 3 ) {
        cout << "Scout";
    } else if( algorithm == 4 ) {
        cout << "Negascout";
    }
    cout << (use_tt ? " w/ transposition table" : "") << endl;

    // Run algorithm along PV (backwards)
    cout << "Moving along PV:" << endl;
    begint = time(NULL);
    for( int i = 0; i <= npv; ++i ) {
        //cout << pv[i];
        int value = 0;
        TTable[0].clear();
        TTable[1].clear();
        float start_time = Utils::read_time_in_seconds();
        expanded = 0;
        generated = 0;
        int color = i % 2 == 1 ? 1 : -1;

        try {
            if( algorithm == 0 ) {
                value = color * (color == 1 ? maxmin(pv[i], 100, use_tt) : minmax(pv[i], 100, use_tt));
            } else if( algorithm == 1 ) {
                value = negamax(pv[i], 100, color, use_tt);
            } else if( algorithm == 2 ) {
                value = negamax(pv[i], 0, -200, 200, color, use_tt);
            } else if( algorithm == 3 ) {
                value = scout(pv[i], 0, color, use_tt);
            } else if( algorithm == 4 ) {
                value = negascout(pv[i], 0, -200, 200, color, use_tt);
            }
        } catch( const bad_alloc &e ) {
            cout << "size TT[0]: size=" << TTable[0].size() << ", #buckets=" << TTable[0].bucket_count() << endl;
            cout << "size TT[1]: size=" << TTable[1].size() << ", #buckets=" << TTable[1].bucket_count() << endl;
            use_tt = false;
        }

        float elapsed_time = Utils::read_time_in_seconds() - start_time;

        cout << npv + 1 - i << ". " << (color == 1 ? "Black" : "White") << " moves: "
             << "value=" << (algorithm == 3 ? value : color * value)
             << ", #expanded=" << expanded
             << ", #generated=" << generated
             << ", seconds=" << elapsed_time
             << ", #generated/second=" << generated/elapsed_time
             << endl;
	
		
    }

    return 0;
}

int minmax(state_t state, int depth, bool use_tt){
    endt = time(NULL);
    secs = difftime(endt,begint);
    assert(secs <= 600);
    if (depth == 0 || state.terminal()) return state.value();
    ++expanded;
    int score = INT_MAX;
    state_t child;

    // Iterate over all valid moves
    for (int i = 0; i < DIM; ++i){
        // Generate childs and expand
        if (state.is_white_move(i)){
            child = state.white_move(i);
            ++generated;
            score = min(score,maxmin(child,depth-1,use_tt));         
        }
    }
    if (score == INT_MAX) {
        ++generated;
	    return maxmin(state,depth-1,use_tt);
    }
    return score;
}

int maxmin(state_t state, int depth, bool use_tt){
    endt = time(NULL);
    secs = difftime(endt,begint);
    assert(secs <= 600);
    if (depth == 0 || state.terminal()) return state.value();
    ++expanded;
    int score = INT_MIN;
    state_t child;

    // Iterate over all valid moves
    for (int i = 0; i < DIM; ++i){
        // Generate childs and expand
        if (state.is_black_move(i)){
            child = state.black_move(i);
            ++generated;
            score = max(score,minmax(child,depth-1,use_tt)); 
            
        }
    }
    if (score == INT_MIN){
        ++generated;
	    return minmax(state,depth-1,use_tt);
    }
    return score;
}

int negamax(state_t state, int depth, int color, bool use_tt){
    endt = time(NULL);
    secs = difftime(endt,begint);
    assert(secs <= 600);
    if (depth == 0 || state.terminal()) return color*state.value();
    ++expanded;
    int alpha = INT_MIN;
    state_t child;
    bool bow = false; // black(false) or white(true)
    bow = color > 0;

    // Iterate over all valid moves
    for (int i = 0; i < DIM; ++i){
        // Generate childs and expand
        if (state.outflank(bow,i)){
            child = state.move(bow,i);
            ++generated;
            alpha = max(alpha,-negamax(child,depth-1,-color,use_tt));      
        }
    }
    if (alpha == INT_MIN){
        ++generated;
	   return max(alpha,-negamax(state,depth-1,-color,use_tt));
    }
    return alpha;
}


int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt){
    endt = time(NULL);
    secs = difftime(endt,begint);
    assert(secs <= 600);
    if (/*depth == 0 ||*/ state.terminal()) return color*state.value();
    ++expanded;
    int score = INT_MIN;
    int val;
    state_t child;
    bool bow = false; // black(false) or white(true)
    bow = color > 0;

    // Iterate over all valid moves
    for (int i = 0; i < DIM; ++i){
        // Generate childs 
        if (state.outflank(bow,i)){
            child = state.move(bow,i);
            ++generated;
            val = -negamax(child,depth-1,-beta,-alpha,-color,use_tt);
            score = max(score,val);
            alpha = max(alpha,val);
            if (alpha >= beta) break;
        }
    }
    if (score == INT_MIN) { 
        ++generated;
        val = -negamax(state,depth-1,-beta,-alpha,-color,use_tt);
        score = max(score,val);
        
    }
    return score;
}

int scout(state_t state, int depth, int color, bool use_tt){
    endt = time(NULL);
    secs = difftime(endt,begint);
    assert(secs <= 600);
    if (state.terminal()) return state.value();
    ++expanded;
    int score = INT_MIN; 
    bool is_first_child = true;
    state_t child;
    bool bow = false; // black(false) or white(true)
    bow = color > 0;

    // Iterate over all valid moves
    for (int i = 0; i < DIM; ++i){
        // Generate childs 
        if (state.outflank(bow,i)){
            child = state.move(bow,i);
            ++generated;
            if (is_first_child){
                score = scout(child,depth-1,-color,use_tt);
                is_first_child = false;
            }
            else{
                if (color == 1 && TEST(child,score,depth-1,-color,0)){
                    score = scout(child,depth-1,-color,use_tt);   
                }
                if (color == -1 && !TEST(child,score,depth-1,-color,1)){
                    score = scout(child,depth-1,-color,use_tt); 
                }

            }
            
        }
    }
    if (score == INT_MIN) {
        ++generated;
        return scout(state,depth-1,-color,use_tt);  
    }  
    return score;
}

bool TEST(state_t state, int score, int depth, int color, int condition){
    if (state.terminal()) return (condition == 1) ? state.value() >= score : state.value() > score;
    state_t child;
    bool bow = false; // black(false) or white(true)
    bow = color > 0;
    bool pass = true;
    ++expanded;
    // Iterate over all valid moves
    for (int i = 0; i < DIM; ++i){
        // Generate childs 
        if (state.outflank(bow,i)){
            child = state.move(bow,i);
            pass = false;
            ++generated;
            if (color == 1 && TEST(child,score,depth-1,-color,condition) ) return true;
            else if (color == -1 && !TEST(child,score,depth-1,-color,condition) ) return false;
        }
    }
    if (pass) {
        ++generated;
        return TEST(state,score,depth-1,-color,condition);
    }
    return (color == 1) ? false : true;

}

int negascout(state_t state, int depth, int alpha, int beta, int color, bool use_tt){
    endt = time(NULL);
    secs = difftime(endt,begint);
    assert(secs <= 600);
    if (state.terminal()) return color*state.value();
    ++expanded;
    int score = INT_MIN; 
    bool is_first_child = true;
    state_t child;
    bool bow = false; // black(false) or white(true)
    bow = color > 0;

    // Iterate over all valid moves
    for (int i = 0; i < DIM; ++i){
        // Generate childs 
        if (state.outflank(bow,i)){
            child = state.move(bow,i);
            ++generated;
            if (is_first_child){
                is_first_child = false;
                score = -negascout(child,depth-1,-beta,-alpha,-color,use_tt);
            }
            else{
                score = -negascout(child,depth-1,-alpha-1,-alpha,-color,use_tt);    
                if (alpha < score && score < beta){
                    score = -negascout(child,depth-1,-beta,-score,-color,use_tt);
                }
            }
            alpha = max(alpha,score);
            if (alpha >= beta) break;
            
        }
    }
    if (score == INT_MIN){
        ++generated;
        alpha = -negascout(state, depth-1, -beta, -alpha, -color, use_tt);
    }
    return alpha;
}
