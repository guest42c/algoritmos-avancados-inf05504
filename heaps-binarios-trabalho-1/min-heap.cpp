#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Heap {
public:
    Heap();
    ~Heap();
    void insert(int element);
    int deletemin();
    void print();
    int size() { return heap.size(); }
private:
    int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);
private:
    vector<int> heap;
};

Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::insert(int element)
{
    heap.push_back(element);
    heapifyup(heap.size() - 1);
}

int Heap::deletemin()
{
    int min = heap.front();
    heap[0] = heap.at(heap.size() - 1);
    heap.pop_back();
    heapifydown(0);
    return min;
}

void Heap::print()
{
    vector<int>::iterator pos = heap.begin();
    cout << "Heap = ";
    while ( pos != heap.end() ) {
        cout << *pos << " ";
        ++pos;
    }
    cout << endl;
}

void Heap::heapifyup(int index)
{    
    while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
          ( heap[parent(index)] > heap[index] ) )
    {
      int tmp = heap[parent(index)];
      heap[parent(index)] = heap[index];
      heap[index] = tmp;
      index = parent(index);
    }
}

void Heap::heapifydown(int index)
{
  int child = left(index);
  if ( ( child > 0 ) && ( right(index) > 0 ) &&
     ( heap[child] > heap[right(index)] ) )
  {
    child = right(index);
  }
  if ( child > 0 )
  {
    int tmp = heap[index];
    heap[index] = heap[child];
    heap[child] = tmp;
    heapifydown(child);
  }
}


int Heap::left(int parent)
{
    int i = ( parent << 1 ) + 1; // 2 * parent + 1
    return ( i < heap.size() ) ? i : -1;
}

int Heap::right(int parent)
{
    int i = ( parent << 1 ) + 2; // 2 * parent + 2
    return ( i < heap.size() ) ? i : -1;
}

int Heap::parent(int child)
{
    if (child != 0)
    {
        int i = (child - 1) >> 1;
        return i;
    }
    return -1;
}

int main()
{
  Heap* myheap = new Heap();
  myheap->insert(700);
  myheap->print();
  myheap->insert(500);
  myheap->print();
  myheap->insert(100);
  myheap->print();
  myheap->insert(800);
  myheap->print();
  myheap->insert(200);
  myheap->print();
  myheap->insert(400);
  myheap->print();
  myheap->insert(900);
  myheap->print();
  myheap->insert(1000);
  myheap->print();
  myheap->insert(300);
  myheap->print();
  myheap->insert(600);
  myheap->print();

  int heapSize = myheap->size();
  for ( int i = 0; i < heapSize; i++ )
      cout << "Get min element = " << myheap->deletemin() << endl;

  delete myheap;
}
