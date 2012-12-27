#include<iostream>
#include<vector>
#include<list>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iterator>
#include<sstream>

using namespace std;

int n;
const unsigned M = 13;
list<int> table[M];

int hash(int x) {
  return x % M;
}

int lookup(int x) {
  int j = hash(x);
  list<int>::iterator i;
  for (i=table[j].begin(); i != table[j].end(); ++i) {
    if (x == *i) {
      return *i;
    }
  }
  return 0;
}

bool insert(int x) {
  if (lookup(x) != 0) return false;
  //if ((n+1) > table.length) resize();
  table[hash(x)].push_back(x);
  n++;
  return true;
}

int remove(int x) {
  int j = hash(x);
  list<int>::iterator i;
  for (i=table[j].begin(); i != table[j].end(); ++i) {
    int y = *i;
    if (x == y) {
      table[j].remove(*i);
      n--;
      return y;
    }
  }
  return 0;
}

void print() {
  for (int i=0; i < M; i++) {
    int count = 0;
    list<int>::iterator j;  
    for (j=table[i].begin(); j != table[i].end(); ++j) {
      count++;
      //cout << *j << " ";
    }
    cout << count << endl;
  }
}

int main(int argc, char *argv[]) {
  //Hash with lists
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
  for (int i=0; i < nlookups; i++) {
    cout << lookup(lookups[i]) << endl;
  }
  
  print();
}
