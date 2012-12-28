#include<iostream>
#include<vector>
#include<list>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iterator>
#include<sstream>

using namespace std;

const int DEL = -1;
const int NUL = 0;

const unsigned M = 7919; //100000;
int table[M];

int hash(int x) {
  return x % M;
}

int lookup(int x) {
  int i = hash(x);
  int limit = M;
  while (table[i] != NUL && limit-- > 0) {
    if (table[i] != DEL && table[i] == x) return table[i];
    i = (i == M-1) ? 0 : i + 1; // increment i (mod table.length)
  }
  return NUL;
}

bool insert(int x) {
  if (lookup(x) != NUL) return false;
  int i = hash(x);
  int limit = M;
  while (table[i] != NUL && table[i] != DEL && limit-- > 0) {
    i = (i == M-1) ? 0 : i+1;
  }
  table[i] = x;
  return true;
}

int remove(int x) {
  int i = hash(x);
  while (table[i] != NUL) {
    int y = table[i];
    if (y != DEL && x == y) {
      table[i] = DEL;
      return y;
    }
    i = (i == M-1) ? 0 : i+1;
  }
  return NUL;
}

void print() {
  for (int i=0; i < M; i++) {
    cout << table[i] << " ";
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
  for (int i=0; i < ninserts; i++) {
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

}
