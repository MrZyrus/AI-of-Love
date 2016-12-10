//Proyecto 3
//Reticulas


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char **argv) {
  int n, m, i, typeIclauses;
  string line;
  ifstream infile(argv[1]);
  i = 1;
  
  while (getline(infile, line)) {
    n = line[0] - '0';
    m = line[2] - '0';
    typeIclauses = 0;
    ofstream outfile(to_string(i++) + ".txt");
    for (int j = 4; j < line.length(); j++) {
      if (line[j] == '0') typeIclauses = typeIclauses + 4;
      if (line[j] == '1') typeIclauses = typeIclauses + 7;
      if (line[j] == '2') typeIclauses = typeIclauses + 8;
      if (line[j] == '3') typeIclauses = typeIclauses + 7;
      if (line[j] == '4') typeIclauses = typeIclauses + 4;
    }
    outfile << "p cnf " << m * n * 4 << ' ' << ((m-1) * n + (n-1) * m) * 2 + typeIclauses;
    outfile.close();
  }
  infile.close();
}