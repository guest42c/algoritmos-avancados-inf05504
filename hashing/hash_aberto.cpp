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

//int n,q;
const unsigned M = 100000;
int table[M];

int hash(int x) {
  return x % M;
}

int lookup(int x) {
  int i = hash(x);
  while (table[i] != NUL) {
    if (table[i] != DEL && table[i] == x) return table[i];
    i = (i == M-1) ? 0 : i + 1; // increment i (mod table.length)
  }
  return NUL;
}

bool insert(int x) {
  if (lookup(x) != NUL) return false;
  //if (2*(q+1) > table.length) resize(); //50% occupancy
  int i = hash(x);
  while (table[i] != NUL && table[i] != DEL) {
    i = (i == M-1) ? 0 : i+1;
  }
  //if (table[i] == NUL) q++;
  //n++;
  table[i] = x;
  return true;
}

int remove(int x) {
  int i = hash(x);
  while (table[i] != NUL) {
    int y = table[i];
    if (y != DEL && x == y) {
      table[i] = DEL;
      //n--;
      //if (8*n < M) resize(); //min 12.5% occupancy
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

  for (int i=0; i < ninserts; i++) {
    insert(inserts[i]);
  } 

  for (int i=0; i < nlookups; i++) {
    cout << lookup(lookups[i]) << endl;
  }

  /*  
  list<int> numbers;
  srand(time(NULL));
  for (int i=1; i <= 12; i++) {
    int num = (rand() % 32767)+1;
    numbers.push_back(num);
    insert(num);
  }
  
  print();
  
  bool rem = false;  
  list<int>::iterator i;  
  for (i=numbers.begin(); i != numbers.end(); ++i) {
    if (rem) {
      remove(*i);
      rem = !rem;
    } else {
      cout << lookup(*i) << " ";
      rem = !rem;
    }
  }
  cout << endl;

  print();
  
  for (int i=1; i <= 12; i++) {
    int num = (rand() % 32767)+1;
    insert(num);
  }
  
  print();
  */
}
