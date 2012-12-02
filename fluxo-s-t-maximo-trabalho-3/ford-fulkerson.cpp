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
    pair<int,int> deletemax();
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

pair<int,int> Heap::deletemax() {
  pair<int,int> max = heap.front();
  swap(heap[0],heap[heap.size()-1]);
  heap.pop_back();
  heapifydown(0);
  return max;
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
  if (w > heap[index].second) {
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
  if (heap[parent(index)].second < heap[index].second) {
    swap(heap[parent(index)],heap[index]);
    heapifyup(parent(index));
  }
}

void Heap::heapifydown(int index) {
  int child_left = left(index);
  int child_right = right(index);
  if (child_left == -1 && child_right == -1) return;
  if (child_right == -1) { //one child at left
    if (heap[child_left].second > heap[index].second) swap(heap[child_left], heap[index]);
  } else if (child_left == -1) { //one child at right (its possible?!)
    if (heap[child_right].second > heap[index].second) swap(heap[child_right], heap[index]);
  } else if ((heap[index].second < heap[child_left].second) || (heap[index].second < heap[child_right].second)) { //two children
    if (heap[child_left].second > heap[child_right].second) {
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

int getmin(int a, int b) {
  if (a < b && a > 0) return a;
  else return b;
}

vector<int> find_path_dijkstra(int from, int to, Graph g) {
  
  //cout << "Calculating distance from " << from << " to " << to << endl;
  int previous[num_vertices(g)+1];
  for (int i = 0; i <= num_vertices(g); i++) previous[i] = 0;
  bool visited[num_vertices(g)+1];
  for (int i = 0; i <= num_vertices(g); i++) visited[i] = false;
  int distance[num_vertices(g)+1];
  for (int i = 0; i < num_vertices(g); i++) {
    distance[i] = -1;
  }

  distance[from] = 0;
  Heap* pQueue = new Heap();
  pQueue->insert(make_pair(from,0));
  pair<int,int> max = make_pair(from,0);
  bool achou = false;
  while (pQueue->size() > 0) {
    max = pQueue->deletemax();
    if (max.first == to) { 
      achou = true;
      break;
    }
    visited[max.first] = true;
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    IndexMap index = get(boost::vertex_index, g);
    typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
    std::pair<adjacency_iterator, adjacency_iterator> ngs = boost::adjacent_vertices(vertex(max.first,g), g);
    bool achou = false;
    for(; ngs.first != ngs.second; ++ngs.first) {
      int u = index[*ngs.first];
      Edge e = edge(max.first,u,g).first;
      if (!visited[u] && (g[e].weight > 0)) {
        achou = true;
        if (distance[u] < 0) {
          distance[u] = getmin(max.second, g[e].weight);
          pQueue->insert(make_pair(u,distance[u]));
          previous[u] = max.first;
        } else {
          if ( getmin(max.second, g[e].weight) > distance[u]) {
            distance[u] = getmin(max.second, g[e].weight);
            pQueue->update(u,distance[u]);
            previous[u] = max.first;
          }
        }
      }
    }
  }
  
  if (!achou) {
    vector<int> caminhovazio;
    return caminhovazio;
  }

  int prev = to;
  stack<int> pathtmp;
  while (prev != from) {
    pathtmp.push(prev);
    prev = previous[prev];
  }
  pathtmp.push(from);
  
  vector<int> path; 
  while (!pathtmp.empty()) {
    //cout << pathtmp.top() << "(" << distance[pathtmp.top()] << ")  ";
    path.push_back(pathtmp.top());
    pathtmp.pop();
  }
  //cout << endl;
  
  return path;
}

int bottleneck(vector<int> path, Graph g) {
  int min = maxweight;
  for (int i=0; i < path.size()-1; i++) {
    Edge e = edge(path[i],path[i+1],g).first;
    if (g[e].weight < min) min = g[e].weight;
  }
  return min;
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
  int result = 0;

  while (1) {
    int inc_flow = 0;
    vector<int> path = find_path_dijkstra(from, to, g);
    if (path.size() > 0) inc_flow = bottleneck(path, g);
    if (inc_flow == 0) break;
    for(int i = 0; i < path.size()-1; i++) {
      //incrementa fluxo
      Edge e = edge(path[i],path[i+1],g).first;
      g[e].weight -= inc_flow; //incrementa o fluxo
      //adiciona fluxo no grafo residual
      pair<Edge,bool> res_edge = edge(path[i+1], path[i], g);
      Edge re;
      if (!res_edge.second) {
        re = add_edge(path[+1], path[i], g).first;
        g[re].weight = inc_flow;
      } else {
        re = res_edge.first;
        g[re].weight += inc_flow;
      }      
    }
    cout << "+" << inc_flow << endl;
    result += inc_flow;
  }
   
  cout << result << endl;

}
