/*
C++ Program that uses Binary minheap as a priority queue for implementing Johnsons's Algorithm 
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
	int * SSSP;
    int V;    
    Graph(int v);
    void add_edge(int vert1,int vert2,int weight);
	void SSSP_djik(int vert1);
	bool Johnson();
};


Graph::Graph(int v){
    V = v;
    adj = new vector<node_t>[V+1];
	SSSP = new int [V*V];
	std::fill(SSSP, SSSP + V*V, INT32_MAX);
}

void Graph::add_edge(int vert1,int vert2,int weight){
    node_t temp1;
    temp1.key = weight;
    temp1.value = vert2;
    adj[vert1].push_back(temp1);
}

void Graph::SSSP_djik(int vert1){
	MinHeap h(1);
	h.itemLookupCreate(V);
	int i;
    int *key = new int[V];
	int *parent = new int[V];
	for(i=0;i<V;i++){
		key[i] = INT32_MAX;
		parent[i] = -1;
	}
	h.decreaseKey(vert1,0);
	key[vert1] =0;
	vector<node_t>::iterator it;
	node_t temp_node;
	while(!h.empty()){
		temp_node = h.removeMin();
		int u = temp_node.value; // u becomes the next node to be 
		for(it = adj[u].begin();it!=adj[u].end();it++){
			int v = (*it).value;
			int weight = (*it).key + key[u];
			if(key[v]>weight){
				key[v]= weight;
				h.decreaseKey(v,weight);
				parent[v] = u;
			}
		}
	}
	for(i=0;i<V;i++){
		SSSP[V*vert1+ i] = key[i];
	}
	
}

bool Graph::Johnson(){
	
	int * dist = new int[V+1];
	std::fill(dist, dist+V,INT32_MAX);
	dist[V] = 0;
	int i,j,w;
	// Add Dummy Edge
	for(i=0;i<V;i++){
		Graph::add_edge(V,i,0);
	}
	// Bellman Ford Starts
	vector<node_t>::iterator it;
	int out;
	for(out=0;out<V;out++){
		for(i=0;i<=V;i++){
			for( it =adj[i].begin();it!=adj[i].end();it++){
				j = (*it).value;
				w = (*it).key;
				if(dist[i]!=INT32_MAX && dist[i]+w < dist[j]){
					dist[j] = dist[i]+w;
				} 
			}
		}
	}
	// Bellman Ford Ends
	// Check Path Dists
	for(i=0;i<V;i++){
		for( it =adj[i].begin();it!=adj[i].end();it++){
			j = (*it).value;
			w = (*it).key;
			if((w + dist[i] - dist[j])<0){
				return false;
			}
		}
	}
	//Calculate SSSP for each using Djikstra
	for(i=0;i<V;i++){
		Graph::SSSP_djik(i);
	}


	return true;
}


int main(int argc, char const *argv[])
{
    int  e,v;
	scanf("%d",&v);
	scanf("%d",&e);
    Graph g(v);
    int i,vert1,vert2,weight;
	for(i=0;i<e;i++){
		scanf("%d",&vert1);
        scanf("%d",&vert2);
        scanf("%d",&weight);
        g.add_edge(vert1,vert2,weight);
	}
	if(g.Johnson()){
		int p,val;
		scanf("%d",&p);
		for(i=0;i<p;i++){
			scanf("%d",&vert1);
			scanf("%d",&vert2);
			val = g.SSSP[v*(vert1)+vert2];
			if(val!=INT32_MAX){
				printf("\n%d -> %d = %d",vert1,vert2,val);
			}
			else
			{
				printf("\n%d -> %d = X",vert1,vert2);
			}
		}
	}
	else{
		printf("Negative Weight Cycle");
	}
	printf("\n");
    return 0;
}

