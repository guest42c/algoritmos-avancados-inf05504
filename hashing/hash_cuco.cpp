#include<iostream>
#include<vector>
#include<list>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iterator>
#include<sstream>
#include<math.h>

using namespace std;

const int NUL = 0;

//int n,q;
const unsigned M = 37; //7919;
int table1[M];
int table2[M];

int hash1(int x) {
  return x % M;
}

int hash2(int x) {
  return ((int)floor(x/11)) % M;
}

int lookup(int x) {
  if (table1[hash1(x)] == x || table2[hash2(x)] == x) return x;
  return NUL;
}

bool insert(int x) {
  if (lookup(x) != NUL) return false;
  int p = hash1(x);
  bool h1 = true;
  int count_down = floor(M/2);
  while (count_down > 0) {
    count_down--;
    if (h1) {
      if (table1[p] == NUL) {
        table1[p] = x;
        break;
      }
      swap(x,table1[p]);
      p = hash2(x);
      h1 = !h1;      
    } else {
      if (table2[p] == NUL) {
        table2[p] = x;
        break;
      }
      swap(x,table2[p]);
      p = hash1(x);
      h1 = !h1;      
    }
  }
  if (count_down < 1) return false; //rehash
  return true;
}

void remove(int x) {
  if (table1[hash1(x)] == x) table1[hash1(x)] = NUL;
  if (table2[hash2(x)] == x) table2[hash2(x)] = NUL;
}

void print() {
  cout << "Tabela 1" << endl;
  for (int i=0; i < M; i++) {
    cout << table1[i] << " ";
  }
  cout << endl << "Tabela 2" << endl;
  for (int i=0; i < M; i++) {
    cout << table2[i] << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  string line;
  getline(cin, line);
  vector<string> tokens;
  istringstream iss(line);
  copy(istream_iterator<string>(iss),
    istream_iterator<string>(),
    back_inserter<vector<string> >(tokens));
  int ninserts = atoi(tokens[0].c_str());
  int nlookups = atoi(tokens[1].c_str());
  int insert_count = 0;
  int lookups_count = 0;
  int inserts[ninserts];
  int lookups[nlookups];
  while (cin) {
    getline(cin, line);
    if (insert_count < ninserts) {
      inserts[insert_count] = atoi(line.c_str());
      insert_count++;
    } else {
      lookups[lookups_count] = atoi(line.c_str());
      lookups_count++;
    }
  }  

  for (int i=0; i < ninserts; i++) {
    insert(inserts[i]);
  } 

  print();

  cout << "Lookups" << endl;
  for (int i=0; i < nlookups; i++) {
    cout << "Find " << lookups[i] << " ==> " << lookup(lookups[i]) << " " << endl;
  }
  //cout << endl;
}
