#include<iostream>
#include<vector>
#include<list>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

using namespace std;

int n;
const unsigned M = 13;
list<int> table[M];

int hash(int x) {
  //cout << "hash(" << x << "): " << x % M << endl;
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
  /*
  string line;
  getline(cin, line);
  while (cin) {
    getline(cin, line);
  }  
  */
  list<int> numbers;
  srand(time(NULL));
  for (int i=1; i <= 10000; i++) {
    int num = (rand() % 32767)+1;
    numbers.push_back(num);
    insert(num);
  }
  /*
  list<int>::iterator i;  
  for (i=numbers.begin(); i != numbers.end(); ++i) {
    cout << lookup(*i) << " - ";    
  }
  cout << endl;
  */
  print();

  cout << endl;
}
