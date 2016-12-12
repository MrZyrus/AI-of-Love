//Proyecto 3
//Reticulas


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, const char **argv) {
  int n, m, filename, typeIclauses, i, j;
  string line;
  ifstream infile(argv[1]);
  filename = 1;
  
  while (getline(infile, line)) {
    istringstream iss(line);
    typeIclauses = 0;
    string aux;
    iss >> n;
    iss >> m;

    ofstream outfile(to_string(filename++) + ".txt");

    while (iss >> aux) {
      for (int k = 0; k < aux.length(); k++) {
        if (aux[k] == '0') typeIclauses = typeIclauses + 4;
        if (aux[k] == '1') typeIclauses = typeIclauses + 7;
        if (aux[k] == '2') typeIclauses = typeIclauses + 8;
        if (aux[k] == '3') typeIclauses = typeIclauses + 7;
        if (aux[k] == '4') typeIclauses = typeIclauses + 4;
      }
    }
    
    outfile << "c " << line << '\n';
    outfile << "p cnf " << (n+1)*m+n*(m+1) << ' ' << typeIclauses + 24 + ((n-2)*2+(m-2)*2)*4 + ((n-1)*2+(m-1)*2)*6 + ((n-2)*(m-1)+(n-1)*(m-2))*8 << '\n';
    istringstream ss(line);
    ss >> aux;
    ss >> aux;

    i = 1;
    while (ss >> aux) {
      for (j = 1; j < m+1; j++) {
        if (aux[j-1] == '0') {
          outfile << -((i-1)*(2*m+1)+j) << " 0\n";
          outfile << -(i*(2*m+1)+j) << " 0\n";
          outfile << -((i-1)*(2*m+1)+j+m) << " 0\n";
          outfile << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
        }
        if (aux[j-1] == '1') {
          outfile << (i-1)*(2*m+1)+j << ' ' << i*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m << ' ' << (i-1)*(2*m+1)+j+m+1 << " 0\n";
          outfile << -((i-1)*(2*m+1)+j) << ' ' << -(i*(2*m+1)+j) << " 0\n";
          outfile << -((i-1)*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m) << " 0\n";
          outfile << -((i-1)*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
          outfile << -(i*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m) << " 0\n";
          outfile << -(i*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
          outfile << -((i-1)*(2*m+1)+j+m) << ' ' << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
        }
        if (aux[j-1] == '2') {
          outfile << (i-1)*(2*m+1)+j << ' ' << i*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m << " 0\n";
          outfile << (i-1)*(2*m+1)+j << ' ' << i*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m+1 << " 0\n";
          outfile << (i-1)*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m << ' ' << (i-1)*(2*m+1)+j+m+1 << " 0\n";
          outfile << i*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m << ' ' << (i-1)*(2*m+1)+j+m+1 << " 0\n";
          outfile << -((i-1)*(2*m+1)+j) << ' ' << -(i*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m) << " 0\n";
          outfile << -((i-1)*(2*m+1)+j) << ' ' << -(i*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
          outfile << -((i-1)*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m) << ' ' << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
          outfile << -(i*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m) << ' ' << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
        }
        if (aux[j-1] == '3') {
          outfile << (i-1)*(2*m+1)+j << ' ' << i*(2*m+1)+j << " 0\n";
          outfile << (i-1)*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m << " 0\n";
          outfile << (i-1)*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m+1 << " 0\n";
          outfile << i*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m << " 0\n";
          outfile << i*(2*m+1)+j << ' ' << (i-1)*(2*m+1)+j+m+1 << " 0\n";
          outfile << (i-1)*(2*m+1)+j+m << ' ' << (i-1)*(2*m+1)+j+m+1 << " 0\n";
          outfile << -((i-1)*(2*m+1)+j) << ' ' << -(i*(2*m+1)+j) << ' ' << -((i-1)*(2*m+1)+j+m) << ' ' << -((i-1)*(2*m+1)+j+m+1) << " 0\n";
        }
        if (aux[j-1] == '4') {
          outfile << (i-1)*(2*m+1)+j << " 0\n";
          outfile << i*(2*m+1)+j << " 0\n";
          outfile << (i-1)*(2*m+1)+j+m << " 0\n";
          outfile << (i-1)*(2*m+1)+j+m+1 << " 0\n";
        }
      }
      i++;
    }

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
      outfile << "-" << i << " " << i+1+n << " " << i+1+2*n << " 0\n";
      outfile << "-" << i << " -" << i+1+n << " -" << i+1+2*n << " 0\n";
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

    outfile.close();
  }
  infile.close();
}
