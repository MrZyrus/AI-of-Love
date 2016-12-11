//Proyecto 3
//Reticulas


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, const char **argv) {
  int n, m, i, typeIclauses;
  string line;
  ifstream infile(argv[1]);
  i = 1;
  
  while (getline(infile, line)) {
    istringstream iss(line);
    typeIclauses = 0;
    string aux;
    iss >> n;
    iss >> m;

    ofstream outfile(to_string(i++) + ".txt");

    while (iss >> aux) {
      for (int j = 0; j < aux.length(); j++) {
        if (aux[j] == '0') typeIclauses = typeIclauses + 4;
        if (aux[j] == '1') typeIclauses = typeIclauses + 7;
        if (aux[j] == '2') typeIclauses = typeIclauses + 8;
        if (aux[j] == '3') typeIclauses = typeIclauses + 7;
        if (aux[j] == '4') typeIclauses = typeIclauses + 4;
      }
    }
    
    outfile << "p cnf " << m * n * 4 << ' ' << ((m-1) * n + (n-1) * m) * 2 + typeIclauses;
    outfile.close();
  }
  infile.close();
}