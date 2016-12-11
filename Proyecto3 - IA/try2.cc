//Proyecto 3
//Reticulas


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, const char **argv) {
  int n, m;
  string line, aux;
  for (int filename = 1; filename < 63; filename++) {
    ifstream infile(to_string(filename) + ".txt");
    getline(infile, line);
    istringstream iss(line);
    iss >> aux;
    iss >> n;
    iss >> m;
    ofstream outfile(to_string(filename) + "final.txt");
    for (int i = 2; i < line.length(); i++) {
      outfile << line[i];
    }
    outfile << '\n';
    infile.close();
    ifstream infile2(to_string(filename) + "out.txt");
    getline(infile2, line);
    outfile << n << ' ' << m << ' ';
    if (line == "SAT") {
      getline(infile2, line);
      istringstream iss(line);
      for (int i = 0; i < n*2+1; i++) {
        for (int j = 0; j < m+i%2; j++) {
          iss >> aux;
          (aux[0] == '-') ? outfile << '0': outfile << '1';
        }
        outfile << ' ';
      }
    }
    if (line == "UNSAT") outfile << "UNSAT";
    infile2.close();
    outfile.close();
  }
}