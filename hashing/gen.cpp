#include<iostream>
#include<cassert>
#include<list>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  assert(argc == 3);
  int m = atoi(argv[2]);
  int n = atoi(argv[1]);
  
  cout << n << " " << m << endl;

  list<int> numbers;
  srand(time(NULL));
  for (int i=0; i < n; i++) {
    int num = (rand() % 9999999)+1;
    numbers.push_back(num);
    cout << num << endl;    
  }
    
  bool print = false;
  int count_lookup = 0;  
  list<int>::iterator i;  
  for (i=numbers.begin(); i != numbers.end() && count_lookup < m; ++i) {
    if (print) {
      cout << *i << endl;
      count_lookup++;
      print = !print;
    } else {
      print = !print;
      cout << ((rand() % 32767)+1) << endl;
      count_lookup++;
    }   
  }
  
  return 0;
}
