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

const unsigned M = 7919;
int table1[M];
int table2[M];

double A = (sqrt(5)-1)/2;
double B = (sqrt(10)-1)/3.14159265;

int hash1(int x) {
  return (int) 7744 * fmod(A*x,1);
}

int hash2(int x) {
  return (int) 7744 * fmod(B*x,1);
}

int lookup(int x) {
  if (table1[hash1(x)] == x || table2[hash2(x)] == x) return 1;//x;
  return NUL;
}

bool insert(int x) {
  if (lookup(x) != NUL) return false;
  int p = hash1(x);
  bool h1 = true;
  int count_down = 2*M;
  while (count_down-- > 0) {
    bool brk = false;
    if (h1) {
      if (table1[p] == NUL) {
        table1[p] = x;
        brk = true;
        break;
      }
      if (brk) cout << "fudeu!" << endl;
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

  clock_t start, finish;
  start = clock();
  //int fail = 0;
  for (int i=0; i < ninserts; i++) {
    //if (!insert(inserts[i])) fail++; 
    insert(inserts[i]);
  } 

  finish = clock();
  long elapsed_time_insert = ((double)(finish - start))*1000/CLOCKS_PER_SEC;

  start = clock();
  for (int i=0; i < nlookups; i++) {
    cout << lookup(lookups[i]) << endl;
  }
  finish = clock();
  long elapsed_time_lookup = ((double)(finish - start))*1000/CLOCKS_PER_SEC;

  cerr << ninserts << " " << nlookups << " " << M << " " <<  elapsed_time_insert << " " << elapsed_time_lookup << endl;
  //print();
  //cout << "Fails: " << fail << endl;
}
