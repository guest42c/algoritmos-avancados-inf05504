#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

map<int, set<int> > sparseMatrix;
map<pair<int,int>, int> weights; 

int main (int argc, char *argv[]) {
  assert(argc == 3);
  unsigned from = atoi(argv[1]);
  unsigned to = atoi(argv[2]);  
  cout << "From:" << from << endl << "To:" << to << endl;
  string line;
  //getline(cin, line); //Ignore first line
  while (cin) {
    getline(cin, line);
    vector<string> tokens;
    istringstream iss(line);
    copy(istream_iterator<string>(iss),
      istream_iterator<string>(),
      back_inserter<vector<string> >(tokens));
    if (tokens.size() && tokens[0] == "a") {
      sparseMatrix[atoi(tokens[1].c_str())]
        .insert(atoi(tokens[2].c_str()));
      //cout << tokens[1] << " " << tokens[2] << " " << tokens[3] << endl;
      pair<int,int> aresta = make_pair(atoi(tokens[1].c_str()),atoi(tokens[2].c_str()));
      weights.insert(make_pair(aresta,atoi(tokens[3].c_str())));
    }
  };
  /*** Iterating over sparseMatrix ***/
  /*
  for(map<int, set<int> >::const_iterator i = sparseMatrix.begin();
      i != sparseMatrix.end(); ++i) {
    for(set<int>::const_iterator j = i->second.begin();
        j != i->second.end(); ++j) {
      cout << "An edge exists from " << i->first << " to " << *j << ", with wieght of " << weights[make_pair(i->first,*j)]  << endl;
    }
  }
  */

  /*** Adjacent edges ***/
  for (set<int>::const_iterator i = sparseMatrix[from].begin(); i != sparseMatrix[from].end(); i++) {
    cout << "Vertice " << from << " para vertice " << *i << " com peso " << weights[make_pair(from,*i)] << endl;
  }
}
