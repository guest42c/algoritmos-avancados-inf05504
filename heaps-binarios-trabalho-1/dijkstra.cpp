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
map<string, int> weights; 


class Heap {
  public:
    Heap();
    ~Heap();
    void insert(pair<int,int> element);
    void update(int w, int index);
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
}

pair<int,int> Heap::deletemin() {
  pair<int,int> min = heap.front();
  swap(heap[0],heap[heap.size()-1]);
  heap.pop_back();
  heapifydown(0);
  return min;
}

void Heap::update(int w, int index) {
  if (w < heap[index].second) {
    heap[index] = make_pair(heap[index].first,w);
    heapifyup(index);
  } else {
    heap[index] = make_pair(heap[index].first,w);
    heapifydown(index);
  }
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
  if (child_left == -1 && child_right == -1) return;
  if (child_right == -1) { //one child at left
    if (heap[child_left].second < heap[index].second) swap(heap[child_left], heap[index]);
  } else if (child_left == -1) { //one child at right
    if (heap[child_right].second < heap[index].second) swap(heap[child_right], heap[index]);
  } else if ((heap[index].second > heap[child_left].second) || (heap[index].second > heap[child_right].second)) { //two children
    if (heap[child_left].second < heap[child_right].second) {
      swap(heap[index], heap[child_left]);
      heapifydown(child_left);
    } else {
      swap(heap[index], heap[child_right]);
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
  int total_nodes;
  int total_arcs;
  int answer;
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
      stringstream ss;
      ss << tokens[1] << "to" << tokens[2];
      string key = ss.str();
      weights[key] = atoi(tokens[3].c_str()); 
    } else if (tokens.size() && tokens[0] == "p") {
      total_nodes = atoi(tokens[2].c_str());
      total_arcs = atoi(tokens[3].c_str());
    } else if (tokens.size() && (tokens[0] == "c") && (tokens[1] == "answer")) {
      cout << tokens[1] << " from " << tokens[3] << " to " << tokens[4] << ": " << tokens[2] << endl;;
      answer = atoi(tokens[2].c_str());
      from = atoi(tokens[3].c_str());
      to = atoi(tokens[4].c_str());
    }    
  };
  cout << " - Finished" <<  endl;
  /*** Dijkstra ***/
  dynamic_bitset<> visited(total_nodes+1); //zero by default
  int distance[total_nodes];
  for (int i = 0; i < total_nodes; i++) {
    distance[i] = -1;
  }
  distance[from-1] = 0;
  Heap* pQueue = new Heap();
  pQueue->insert(make_pair(from,0));
  bool found = false;
  while (pQueue->size() > 0) {
    pair<int, int> min = pQueue->deletemin();
    visited.set(min.first);
    set<int> neighbors = sparseMatrix[min.first];
    for (set<int>::iterator i = neighbors.begin(); i != neighbors.end(); i++) {
      if (!visited.test(*i)) {
        if (distance[*i-1] == -1) {
          stringstream ss;
          ss << min.first << "to" << *i;
          string key = ss.str();
          distance[*i-1] = min.second + weights[key];
          pQueue->insert(make_pair(*i,distance[*i-1]));
        } else {
          stringstream ss;
          ss << min.first << "to" << *i;
          string key = ss.str();
          if ( (min.second + weights[key]) < distance[*i-1]) { 
            distance[*i-1] = min.second + weights[key];
            pQueue->update(*i-1,distance[*i-1]);
          }
        }
      }   
    }
  } 
  cout << distance[to-1] << endl;
  //cout << answer << " == " << distance[to-1] << endl;
}
