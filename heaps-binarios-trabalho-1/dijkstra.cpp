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
#include <bitset>
#include <limits>
#include <boost/dynamic_bitset.hpp>
#include <math.h>

using namespace std;
using namespace boost;

map<int, set<int> > sparseMatrix;
map<pair<int,int>, int> weights; 

class Heap {
  public:
    Heap();
    ~Heap();
    void insert(pair<int,int> element);
    pair<int,int> deletemin();
    void print();
    int size() { return heap.size(); }
  private:
    int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);
  private:
    vector<pair<int,int> > heap;
};

Heap::Heap() {}

Heap::~Heap() {}

void Heap::insert(pair<int,int> element) {
  heap.push_back(element);
  heapifyup(heap.size() - 1);
  print();
}

pair<int,int> Heap::deletemin() {
  pair<int,int> min = heap.front();
  swap(heap[0],heap[heap.size() - 1]);
  heap.pop_back();
  heapifydown(0);
  return min;
}

void Heap::print() {
  vector<pair<int,int> >::iterator pos = heap.begin();
  cout << "Heap" << endl;;
  while ( pos != heap.end() ) {
    cout << pos->first << " - " << pos->second << endl;
    ++pos;
  }
  cout << "END" << endl;
}

void Heap::heapifyup(int index) {
  if (index == 0) return;
  if (heap[parent(index)].second > heap[index].second) {
    swap(heap[parent(index)],heap[index]);
    heapifyup(parent(index));
  }
}

void Heap::heapifydown(int index) {
  int child_left = left(index);
  int child_right = right(index);
  if (child_left == -1) return;
  if (child_right == -1) { //one child
    if (heap[child_left].second < heap[index].second) swap(heap[child_left].second, heap[index].second);
  } else if ((heap[index].second > heap[child_left].second) || (heap[index].second > heap[child_right].second)) { //two children
    if (heap[child_left].second < heap[child_right].second) {
      swap(heap[index].second, heap[child_left].second);
      heapifydown(child_left);
    } else {
      swap(heap[index].second, heap[child_right].second);
      heapifydown(child_right);
    }
  }
}


int Heap::left(int parent) {
  int i = (2*parent)+1;
  return ( i < heap.size() ) ? i : -1;
}

int Heap::right(int parent) {
  int i = (2*parent) + 2;
  return ( i < heap.size() ) ? i : -1;
}

int Heap::parent(int child) {
  if (child != 0) {
    int i = int(floor((child - 1) / 2.0));
    return i;
  }
  return -1;
}

int main (int argc, char *argv[]) {
  assert(argc == 3);
  int from = atoi(argv[1]);
  int to = atoi(argv[2]);
  Heap* pQueue = new Heap();
  int total_nodes;
  int total_arcs;
  cout << "Importing graph...";
  string line;
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
      pair<int,int> arc = make_pair(atoi(tokens[1].c_str()),atoi(tokens[2].c_str()));
      weights.insert(make_pair(arc,atoi(tokens[3].c_str())));
    } else if (tokens.size() && tokens[0] == "p") {
      total_nodes = atoi(tokens[2].c_str());
      total_arcs = atoi(tokens[3].c_str());
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
  /*
  for (set<int>::const_iterator i = sparseMatrix[from].begin(); i != sparseMatrix[from].end(); i++) {
    cout << "Vertice " << from << " para vertice " << *i << " com peso " << weights[make_pair(from,*i)] << endl;
  }
  */
  
  cout << " - Finished" <<  endl;
  /*** Dijkstra ***/
  dynamic_bitset<> visited(total_arcs); //zero by default
  int distance[total_nodes];
  distance[from] = 0;
  for (int i = 0; i < total_nodes; i++) {
    if (i != from) distance[i] = numeric_limits< int >::max();
  }

  pQueue->insert(make_pair(from,49)); 
  pQueue->insert(make_pair(to,50)); 
  pQueue->insert(make_pair(19,901)); 
  pQueue->insert(make_pair(39,31)); 
  pQueue->insert(make_pair(49,729)); 
  pQueue->insert(make_pair(69,379)); 
  pQueue->insert(make_pair(79,149)); 
  pQueue->insert(make_pair(89,597)); 
  pQueue->insert(make_pair(99,190)); 
  //pQueue->print();
  
  pair<int,int> min = pQueue->deletemin();
  cout << " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout <<  " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout <<  " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout << " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout <<  " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout <<  " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout <<  " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout <<  " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
  min = pQueue->deletemin();
  cout <<  " * " <<  min.first << " - " << min.second << endl;
  //pQueue->print();
}
