// Proyecto 3
// Juego de Reticula


#include <iostream>
#include <sys/time.h>
#include <cassert>

int main(int argc, const char **argv) {

	ifstream file (argv[1]);
	ofstream outfile (argv[2]);
	outfile << "p cnf 60 x\n";
	// Imprimir clausulas de los segmentos esquinas para camino simple y cerrado
	outfile << "-1 6 0\n";
	outfile << "-1 2 7 0\n";
	outfile << "-1 -2 -7 0\n";
	outfile << "-5 11 0\n";
	outfile << "-5 4 10 0\n";
	outfile << "-5 -4 -10 0\n";
	outfile << "-6 1 0\n";
	outfile << "-6 12 17 0\n";
	outfile << "-6 -12 -17 0\n";
	outfile << "-11 5 0\n";
	outfile << "-11 16 22 0\n";
	outfile << "-11 -16 -22 0\n";
	outfile << "-50 56 0\n";
	outfile << "-50 39 45 0\n";
	outfile << "-50 -39 -45 0\n";
	outfile << "-56 50 0\n";
	outfile << "-56 51 57 0\n";
	outfile << "-56 -51 -57 0\n";
	outfile << "-55 60 0\n";
	outfile << "-55 44 49 0\n";
	outfile << "-55 -44 -49 0\n";
	outfile << "-60 55 0\n";
	outfile << "-60 54 59 0\n";
	outfile << "-60 -54 -59 0\n";
	// Imprimir clausulas de los segmentos bordes para camino simple y cerrado
	int i = 2;
	while(i<5){
		outfile << "-" << i << " " << i+5 << " " << i-1 << " 0\n";
		outfile << "-" << i << " -" << i+5 << " -" << i-1 << " 0\n";
		outfile << "-" << i << " " << i+6 << " " << i+1 << " 0\n";
		outfile << "-" << i << " -" << i+6 << " -" << i+1 << " 0\n";
		i++;
	}
	i=17;
	while(i<40){
		outfile << "-" << i << " " << i-11 << " " << i-5 << " 0\n";
		outfile << "-" << i << " -" << i-11 << " -" << i-5 << " 0\n";
		outfile << "-" << i << " " << i+6 << " " << i+11 << " 0\n";
		outfile << "-" << i << " -" << i+6 << " -" << i+11 << " 0\n";
		i = i+11;
	}
	i = 22;
	while(i<45){
		outfile << "-" << i << " " << i-11 << " " << i-6 << " 0\n";
		outfile << "-" << i << " -" << i-11 << " -" << i-6 << " 0\n";
		outfile << "-" << i << " " << i+5 << " " << i+11 << " 0\n";
		outfile << "-" << i << " -" << i+5 << " -" << i+11 << " 0\n";
		i = i+11;
	}
	i = 57;
	while(i<61){
		outfile << "-" << i << " " << i-5 << " " << i+1 << " 0\n";
		outfile << "-" << i << " -" << i-5 << " -" << i+1 << " 0\n";
		outfile << "-" << i << " " << i-6 << " " << i-1 << " 0\n";
		outfile << "-" << i << " -" << i-6 << " -" << i-1 << " 0\n";
		i++;
	}
	// Imprimir clausulas de los segmentos interiores para camino simple y cerrado
}
