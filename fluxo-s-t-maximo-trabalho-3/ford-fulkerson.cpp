#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stack>
#include <iterator>
#include <sstream>
#include <bitset>
#include <limits>
#include <boost/dynamic_bitset.hpp>
#include <math.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

using namespace std;
using namespace boost;

// information stored in vertices
struct VertexInformation {
  unsigned component;
};
    
// information stored in edges
struct EdgeInformation {
  unsigned weight;
};
      
const unsigned maxweight = 9999999;
        
// graph is an adjacency list represented by vectors
typedef adjacency_list<vecS, vecS, directedS,VertexInformation,EdgeInformation> Graph;
typedef graph_traits<Graph>::vertex_descriptor Node;
typedef graph_traits <Graph>::edge_descriptor Edge;

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

void Heap::update(int _vertex, int w) {
  int vertex, index;
  for (int i = 0; i < heap.size(); i++) {
    if (heap[i].first == _vertex) {
      vertex = heap[i].first;
      index = i;
      break;
    }
  }
  if (w < heap[index].second) {
    heap[index] = make_pair(vertex,w);
    heapifyup(index);
  } else {
    heap[index] = make_pair(vertex,w);
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
  int i = 2 * parent + 1;
  return ( i < heap.size() ) ? i : -1;
}

int Heap::right(int parent) {
  int i = 2 * parent + 2;
  return ( i < heap.size() ) ? i : -1;
}

int Heap::parent(int child) {
  if (child != 0) {
    return (child - 1) / 2;
  }
  return -1;
}

void find_path(int *flow) {
  *flow = 0;  
}

int main (int argc, char *argv[]) {
  assert(argc == 3);
  int from = atoi(argv[1]);
  int to = atoi(argv[2]);
  
  //cout << "Importing graph..." << endl;
  string line;
  Graph g;
  while (cin) {
    getline(cin, line);
    vector<string> tokens;
    istringstream iss(line);
    copy(istream_iterator<string>(iss),
      istream_iterator<string>(),
      back_inserter<vector<string> >(tokens));
    if (tokens.size() && tokens[0] == "a") {
      Edge e = add_edge( atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), g).first;
      g[e].weight = atoi(tokens[3].c_str());
    } 
  };
  //cout << "Finished importing" <<  endl;
  
  /*** Ford-Fulkerson ***/ 
  int total_edges = num_edges(g);
  int flow[total_edges+1];
  for (int i=0; i < num_edges(g); i++) flow[i] = 0;

  int result = 0;

  while (1) {
    int flow = 0;
    int path[total_edges];
    find_path(&flow);
    int size=sizeof path/sizeof(int);
    if (flow == 0) break;
    for(int i = 0; i < size-1; i++) {
      Edge e = edge(path[i],path[i+1],g).first;
      g[e].weight += flow; //incrementa o fluxo
    }  
  }
  
  cout << result;

  /*** Dijkstra
  //cout << "Calculating distance from " << from << " to " << to << endl;
  int previous[num_vertices(g)+1];
  for (int i = 0; i <= num_vertices(g); i++) previous[i] = 0;
  bool visited[num_vertices(g)+1];
  for (int i = 0; i <= num_vertices(g); i++) visited[i] = false;
  clock_t start, finish;
  start = clock();
  int distance[num_vertices(g)+1];
  for (int i = 0; i < num_vertices(g); i++) {
    distance[i] = maxweight*2;
  }
  distance[from] = 0;
  Heap* pQueue = new Heap();
  pQueue->insert(make_pair(from,0));
  count_insert++;
  pair<int,int> min = make_pair(from,0);
  while (pQueue->size() > 0) {
    int prev = min.first;
    min = pQueue->deletemin();
    count_deletemin++;
    if (min.first == to) break;
    visited[min.first] = true;
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    IndexMap index = get(boost::vertex_index, g);
    typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
    std::pair<adjacency_iterator, adjacency_iterator> ngs = boost::adjacent_vertices(vertex(min.first,g), g);
    for(; ngs.first != ngs.second; ++ngs.first) {
      int u = index[*ngs.first];
      if (!visited[u]) {
        if (distance[u] > maxweight) {
          Edge e = edge(min.first,u,g).first;
          distance[u] = (min.second + g[e].weight);
          pQueue->insert(make_pair(u,distance[u]));
          count_insert++;
          previous[u] = min.first;
        } else {
          Edge e = edge(min.first,u,g).first;
          if ( (min.second + g[e].weight) < distance[u]) {
            distance[u] = (min.second + g[e].weight);
            pQueue->update(u,distance[u]);
            count_update++;
            previous[u] = min.first;
          }
        }
      }
    }
  }
  finish = clock();
  long elapsed_time = ((double)(finish - start))*1000/CLOCKS_PER_SEC;
  if (distance[to] == maxweight*2)
    cout << "inf" << endl;
  else
    cout << distance[to] << endl;
  cerr << num_vertices(g) << "\t" << elapsed_time << "\t" 
        << num_edges(g) << "\t" << count_deletemin << "\t" << count_insert << "\t" << count_update << endl; 
  */

  /* Return the path
  int prev = to;
  stack<int> path;
  int dist_sum = 0;
  while (prev != from) {
    dist_sum += g[edge(previous[prev],prev,g).first].weight;
    path.push(prev);
    prev = previous[prev];
  }
  path.push(from);
  cout << "Path: ";
  while (!path.empty()) {
    cout << path.top() << " ";
    path.pop();
  }
  cout << endl << " -> Total distance: " << dist_sum << endl;
  */
}
