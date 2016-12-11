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
    outfile.close();
  }
  infile.close();
}