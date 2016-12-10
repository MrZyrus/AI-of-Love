// Proyecto 3
// Juego de Reticula


#include <iostream>
#include <sys/time.h>
#include <ostream>
#include <fstream> 
#include <sstream>
#include <ios>

using namespace std;

int main(int argc, const char **argv) {

	ifstream file (argv[1]);
	ofstream outfile (argv[2]);
	int n =5;
	int m= 5;
	outfile << "p cnf " << (n+1)*m + n*(m+1) << " " << 24+4*(2*(n-2)+2*(m-2))+6*(2*(n-1)+2*(m-1))+8*((n-2)*(m-1)+(m-2)*(n-1)) <<"\n";

	// Imprimir clausulas de los segmentos esquinas para camino cerrado

	outfile << "-1 " << n+1 << " 0\n";
	outfile << "-1 2 " << n+2 << " 0\n";
	outfile << "-1 -2 -" <<n+2<< " 0\n";
	outfile << "-"<<n<<" "<<2*n+1<<" 0\n";
	outfile << "-"<<n<<" "<<n-1<<" "<<2*n<<" 0\n";
	outfile << "-"<<n<<" -"<<n-1<<" -"<<2*n<<" 0\n";
	outfile << "-"<<n+1<<" "<<"1 0\n";
	outfile << "-"<<n+1<<" "<<2*n+2<<" "<<3*n+2<<" 0\n";
	outfile << "-"<<n+1<<" -"<<2*n+2<<" -"<<3*n+2<<" 0\n";
	outfile << "-"<<2*n+1<<" "<<n<<" 0\n";
	outfile << "-"<<2*n+1<<" "<<3*n+1<<" "<<4*n+2<<" 0\n";
	outfile << "-"<<2*n+1<<" -"<<3*n+1<<" -"<<4*n+2<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+1<<" "<<(m-1)*(n+1)+n*m+2+n<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+1<<" "<< (m-1)*(n+1)+n*m-2*n<<" "<< (m-1)*(n+1)+n*m+1-n<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+1<<" -"<< (m-1)*(n+1)+n*m-2*n<<" -"<< (m-1)*(n+1)+n*m+1-n<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+2+n<<" "<< (m-1)*(n+1)+n*m+1 <<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+2+n<<" "<< (m-1)*(n+1)+n*m+2<<" "<<(m-1)*(n+1)+n*m+3+n<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+2+n<<" -"<< (m-1)*(n+1)+n*m+2<<" -"<<(m-1)*(n+1)+n*m+3+n<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+1+n<<" "<< n*(m+1)+m*(n+1)<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+1+n<<" "<< (m-1)*(n+1)+n*m-n <<" "<<(m-1)*(n+1)+n*m<<" 0\n";
	outfile << "-"<<(m-1)*(n+1)+n*m+1+n<<" -"<< (m-1)*(n+1)+n*m-n <<" -"<<(m-1)*(n+1)+n*m<<" 0\n";
	outfile << "-"<<n*(m+1)+m*(n+1)<<" "<<(m-1)*(n+1)+n*m+1+n<<" 0\n";
	outfile << "-"<<n*(m+1)+m*(n+1)<<" "<< (m-1)*(n+1)+n*m+n <<" "<<n*(m+1)+m*(n+1)-1<<" 0\n";
	outfile << "-"<<n*(m+1)+m*(n+1)<<" -"<< (m-1)*(n+1)+n*m+n <<" -"<<n*(m+1)+m*(n+1)-1<<" 0\n";

	// Imprimir clausulas de los segmentos bordes para camino cerrado

	int i = 2;
	while(i<n){
		outfile << "-" << i << " " << i+n << " " << i-1 << " 0\n";
		outfile << "-" << i << " -" << i+n << " -" << i-1 << " 0\n";
		outfile << "-" << i << " " << i+n+1 << " " << i+1 << " 0\n";
		outfile << "-" << i << " -" << i+n+1 << " -" << i+1 << " 0\n";

		outfile << "-" << i+n << " " << i << " " << i-1 << " 0\n";
		outfile << "-" << i+n << " -" << i << " -" << i-1 << " 0\n";
		outfile << "-" << i+n << " " << i+2*n << " " << i+1+2*n << " " << i+1+3*n << " 0\n";
		outfile << "-" << i+n << " -" << i+2*n << " -" << i+1+2*n << " 0\n";
		outfile << "-" << i+n << " -" << i+2*n << " -" << i+1+3*n << " 0\n";
		outfile << "-" << i+n << " -" << i+1+3*n << " -" << i+1+2*n << " 0\n";
		i++;
	}
	outfile << "-" << i+n << " " << i << " " << i-1 << " 0\n";
	outfile << "-" << i+n << " -" << i << " -" << i-1 << " 0\n";
	outfile << "-" << i+n << " " << i+2*n << " " << i+1+2*n << " " << i+1+3*n << " 0\n";
	outfile << "-" << i+n << " -" << i+2*n << " -" << i+1+2*n << " 0\n";
	outfile << "-" << i+n << " -" << i+2*n << " -" << i+1+3*n << " 0\n";
	outfile << "-" << i+n << " -" << i+1+3*n << " -" << i+1+2*n << " 0\n";
	i=3*n+2;
	while(i<(m-1)*(n+1)+n*m-2*n+1){
		outfile << "-" << i << " " << i-1-2*n << " " << i-n << " 0\n";
		outfile << "-" << i << " -" << i-1-2*n << " -" << i-n << " 0\n";
		outfile << "-" << i << " " << i+1-n << " " << i+1+2*n << " 0\n";
		outfile << "-" << i << " -" << i+1-n << " -" << i+1+2*n << " 0\n";

		outfile << "-" << i-n << " " << i-1-2*n << " " << i << " 0\n";
		outfile << "-" << i-n << " -" << i-1-2*n << " -" << i << " 0\n";
		outfile << "-" << i-n << " " << i-2*n << " " << i+1 << " " << i-n+1 << " 0\n";
		outfile << "-" << i-n << " -" << i-2*n << " -" << i+1 << " 0\n";
		outfile << "-" << i-n << " -" << i-2*n << " -" << i-n+1 << " 0\n";
		outfile << "-" << i-n << " -" << i+1 << " -" << i-n+1 << " 0\n";
		i = i+2*n+1;
	}
	outfile << "-" << i-n << " " << i-1-2*n << " " << i << " 0\n";
	outfile << "-" << i-n << " -" << i-1-2*n << " -" << i << " 0\n";
	outfile << "-" << i-n << " " << i-2*n << " " << i+1 << " " << i-n+1 << " 0\n";
	outfile << "-" << i-n << " -" << i-2*n << " -" << i+1 << " 0\n";
	outfile << "-" << i-n << " -" << i-2*n << " -" << i-n+1 << " 0\n";
	outfile << "-" << i-n << " -" << i+1 << " -" << i-n+1 << " 0\n";
	i = 4*n+2;
	while(i<(m-1)*(n+1)+n*m-n+1){
		outfile << "-" << i << " " << i-1-2*n << " " << i-1-n << " 0\n";
		outfile << "-" << i << " -" << i-1-2*n << " -" << i-1-n << " 0\n";
		outfile << "-" << i << " " << i+n << " " << i+1+2*n << " 0\n";
		outfile << "-" << i << " -" << i+n << " -" << i+1+2*n << " 0\n";

		outfile << "-" << i-n-1 << " " << i-1-2*n << " " << i << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-1-2*n << " -" << i << " 0\n";
		outfile << "-" << i-n-1 << " " << i-2-2*n << " " << i-1 << " " << i-n-2 << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-1 << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-n-2 << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-1 << " -" << i-n-2 << " 0\n";
		i = i+2*n+1;
	}
	outfile << "-" << i-n-1 << " " << i-1-2*n << " " << i << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-1-2*n << " -" << i << " 0\n";
	outfile << "-" << i-n-1 << " " << i-2-2*n << " " << i-1 << " " << i-n-2 << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-1 << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-n-2 << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-1 << " -" << i-n-2 << " 0\n";
	i = (m-1)*(n+1)+n*m+2+n+1;
	while(i<n*(m+1)+m*(n+1)){
		outfile << "-" << i << " " << i-n << " " << i+1 << " 0\n";
		outfile << "-" << i << " -" << i-n << " -" << i+1 << " 0\n";
		outfile << "-" << i << " " << i-n-1 << " " << i-1 << " 0\n";
		outfile << "-" << i << " -" << i-n-1 << " -" << i-1 << " 0\n";

		outfile << "-" << i-n-1 << " " << i-1 << " " << i << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-1 << " -" << i << " 0\n";
		outfile << "-" << i-n-1 << " " << i-2-2*n << " " << i-1-2*n << " " << i-2-3*n << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-1-2*n << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-3*n-2 << " 0\n";
		outfile << "-" << i-n-1 << " -" << i-1-2*n << " -" << i-2-3*n << " 0\n";
		i++;
	}
	outfile << "-" << i-n-1 << " " << i-1 << " " << i << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-1 << " -" << i << " 0\n";
	outfile << "-" << i-n-1 << " " << i-2-2*n << " " << i-1-2*n << " " << i-2-3*n << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-1-2*n << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-2-2*n << " -" << i-3*n-2 << " 0\n";
	outfile << "-" << i-n-1 << " -" << i-1-2*n << " -" << i-2-3*n << " 0\n";

	// Imprimir clausulas de los segmentos interiores para camino cerrado

	i = 2*n+3;
	int j = 0;
	while(i<(m-1)*(n+1)+n*m){
		while(j<n-2){
			outfile << "-" << i+j << " " << i+j-1-n << " " << i+j-1 << " " << i+j+n << " 0\n";
			outfile << "-" << i+j << " -" << i+j-1-n << " -" << i+j-1 << " 0\n";
			outfile << "-" << i+j << " -" << i+j-1-n << " -" << i+j+n << " 0\n";
			outfile << "-" << i+j << " -" << i+j-1 << " -" << i+j+n << " 0\n";
			outfile << "-" << i+j << " " << i+j+1+n << " " << i+j+1 << " " << i+j-n << " 0\n";
			outfile << "-" << i+j << " -" << i+j+1+n << " -" << i+j+1 << " 0\n";
			outfile << "-" << i+j << " -" << i+j+1+n << " -" << i+j-n << " 0\n";
			outfile << "-" << i+j << " -" << i+j+1 << " -" << i+j-n << " 0\n";
			j++;
		}
		i = i+1+2*n;
		j=0;
	}
	i = 3*n+3;
	j = 0;
	while(i<(m-1)*(n+1)+n*m-n){
		while(j<n-1){
			outfile << "-" << i+j << " " << i+j-n-1 << " " << i+j-1-2*n << " " << i+j-n << " 0\n";
			outfile << "-" << i+j << " -" << i+j-n-1 << " -" << i+j-1-2*n << " 0\n";
			outfile << "-" << i+j << " -" << i+j-n-1 << " -" << i+j-n << " 0\n";
			outfile << "-" << i+j << " -" << i+j-1-2*n << " -" << i+j-n << " 0\n";
			outfile << "-" << i+j << " " << i+j+n+1 << " " << i+j+1+2*n << " " << i+j+n << " 0\n";
			outfile << "-" << i+j << " -" << i+j+n+1 << " -" << i+j+1+2*n << " 0\n";
			outfile << "-" << i+j << " -" << i+j+n+1 << " -" << i+j+n << " 0\n";
			outfile << "-" << i+j << " -" << i+j+1+2*n << " -" << i+j+n << " 0\n";
			j++;
		}
		i = i+1+2*n;
		j=0;
	}







}


