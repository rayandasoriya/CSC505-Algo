/*
C++ Program that uses 2^d-ary minheap as a priority queue for implementing Prim-Jarnik's Minumum Spanning Tree Detection Algorithm
Authors:
Kushagr Gupta (kgupta7)
Rayan Dasoriya (rdasori)

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

typedef struct node_t
{
	int key;
	int value;
}node_t;


class MinHeap
{
	std::vector<node_t> heap;
	int branching_factor;
	int *item_lookup;
	// int key_compares;
public:

	MinHeap(int branching_factor);

	int parent(int index) {
		return (index >> branching_factor >= 0 ? (index - 1) >> branching_factor : 0);
	}

	int leftmost_child(int index) {
		return ((index << branching_factor) + 1);
	}
	int rightmost_child(int index) {
		return ((index + 1) << branching_factor);
	}
	// int numCompares() {
	// 	return key_compares;
	// }
    bool empty(){
        return(heap.size() ==0);
    }
	void insertValue(int key, int value);

	node_t removeMin();

	void MinHeapify(int index);

	void HeapSwap(int to, int from);

	void decreaseKey(int item,int new_key);

	void itemLookupCreate(int V);

};


MinHeap::MinHeap(int bf) {
	branching_factor = bf;
}

void MinHeap::itemLookupCreate(int V){
	MinHeap::item_lookup = new int[V];
	for(int i=0;i<V;i++){
		item_lookup[i] = -1;
	}
}

void MinHeap::insertValue(int key, int value) {
	/*
	This just creates a new tuple key value pair and adds it to the Vector
	*/
	node_t temp;
	temp.key = key;
	temp.value = value;
	heap.push_back(temp);
	int item_index = heap.size() - 1;
	item_lookup[value] = item_index;
	while (item_index != 0) {
		if (heap.at(MinHeap::parent(item_index)).key > (heap.at(item_index)).key) {
			MinHeap::HeapSwap(item_index,MinHeap::parent(item_index));
			item_index = MinHeap::parent(item_index);
		}
		else
		{
			break;
		}
	}
}

node_t MinHeap::removeMin() {
	int last_index = heap.size() - 1;
	MinHeap::HeapSwap(0,last_index);
	node_t temp = heap[last_index];
	heap.pop_back();
	item_lookup[temp.value]=-1;
	MinHeapify(0);
	return temp;
}

void MinHeap::MinHeapify(int index) {
	int leftmost_child = MinHeap::leftmost_child(index);
	int min_index = index;
	for (int j = 0; j < pow(2, branching_factor); j++)
	{
		if ((leftmost_child + j < (int)heap.size()) && (heap.at(leftmost_child + j).key < heap.at(min_index).key)) {
			min_index = leftmost_child + j;
		}
	}

	if (min_index != index) {
		MinHeap::HeapSwap(index,min_index);
		MinHeap::MinHeapify(min_index);
	}
}

void MinHeap::HeapSwap(int to, int from){
	item_lookup[heap[to].value] = from;
	item_lookup[heap[from].value] = to;
	std::swap(heap[to],heap[from]);
}

void MinHeap::decreaseKey(int item, int new_key){
	int pos = item_lookup[item];
	if(pos == -1){
		MinHeap::insertValue(new_key,item);
	}
	else{
		heap[pos].key = new_key;
		int item_index = pos;
		while (item_index != 0) {
		if (heap.at(MinHeap::parent(item_index)).key > (heap.at(item_index)).key) {
			MinHeap::HeapSwap(item_index,MinHeap::parent(item_index));
			item_index = MinHeap::parent(item_index);
		}
		else
		{
			break;
		}
	}
	}
}


class Graph{
public:
    vector<node_t> *adj;
    int V;    
    Graph(int v);
    void add_edge(int vert1,int vert2,int weight);
    void primMST(int bf);
	void print_adj();
};

void Graph::print_adj(){
	int i;
	printf("\nAdj List");
	vector<node_t>::iterator it;
	for(i=0;i<V;i++){
		for(it=adj[i].begin();it!=adj[i].end();it++){
			printf("\n\t%d -> %d | %d",i,(*it).value,(*it).key);
		}
	}
}

Graph::Graph(int v){
    V = v;
    adj = new vector<node_t>[V];
}

void Graph::add_edge(int vert1,int vert2,int weight){
    node_t temp1,temp2;
    temp1.key = weight;
    temp1.value = vert2;
    adj[vert1].push_back(temp1);
    temp2.key = weight;
    temp2.value = vert1;
    adj[vert2].push_back(temp2);
}

void Graph::primMST(int bf){
    MinHeap h(bf);
	h.itemLookupCreate(V);
	int i;
    int *key = new int[V];
	for(i=0;i<V;i++){
		key[i] = INT32_MAX;
	}
	int *parent = new int[V];
	for(i=0;i<V;i++){
		parent[i] = -1;
	}
	bool *inMST = new bool[V];
	for(i=0;i<V;i++){
		inMST[i] = false;
	}
	vector<node_t>::iterator it;
	int tree_count =0;
	int total_weight = 0;
	node_t temp_node;
	for(i=0;i<V;i++){
		if(inMST[i]==false)
		{
			h.insertValue(0,i);
			key[i] = 0;
			while(!h.empty()){
				temp_node = h.removeMin();
				int u = temp_node.value; // u becomes the next node to be 
				inMST[u] = true;
				for(it = adj[u].begin();it!=adj[u].end();it++){
					int v = (*it).value;
					int weight = (*it).key;
					if(inMST[v]==false && key[v]>weight){
						key[v]= weight;
						h.decreaseKey(v,weight);
						parent[v] = u;
					}
				}

			}
			
		}
	}
	for(i=0;i<V;i++){
		total_weight+=key[i];
	}
	for(i=0;i<V;i++){
		if(parent[i]==-1){
			tree_count++;
		}
	}
	printf("\n%d %d %d",(int)pow(2,bf),tree_count,total_weight);
	}

int main(int argc, char const *argv[])
{
    int heap_bf, e,v;
	scanf("%d",&v);
	scanf("%d",&e);
	heap_bf = (int) log2((float)(e/v))+1;
    Graph g(v);
    int vert1,vert2,weight;
    while(scanf("%d",&vert1)==1){
        scanf("%d",&vert2);
        scanf("%d",&weight);
        g.add_edge(vert1,vert2,weight);
    }
    g.primMST(heap_bf);
}

