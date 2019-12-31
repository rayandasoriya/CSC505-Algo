#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

typedef struct int_tuple 
{
	int key;
	int value;
}int_tuple;


class MinHeap
{
	std::vector<int_tuple> heap;
	int branching_factor;
	int key_compares;
public:
	MinHeap(int branching_factor);

	int parent(int index){
		return (index>>branching_factor >= 0? index>>branching_factor : 0);
	}

	int leftmost_child(int index){
		return ((index<<branching_factor) + 1);
	}
	int rightmost_child(int index){
		return ((index+1)<<branching_factor);
	}
	int numCompares(){
		return key_compares;
	}
	void insert(int key, int value);

	void printheap();

	int_tuple removeMin();

	void MinHeapify(int index);
};


MinHeap::MinHeap(int bf){
	branching_factor = bf;
	key_compares =0;
}

void MinHeap::insert(int key,int value){
	/*
		This just creates a new tuple key value pair and adds it to the Vector 
	*/
	int_tuple temp;
	temp.key = key;
	temp.value = value;
	heap.push_back(temp);
}

void MinHeap::printheap(){
	int i;
	for (i=0; i<heap.size();i++){
		printf("%d = %d : %d\n",i,heap.at(i).key,heap.at(i).value );
	}
}

int_tuple MinHeap::removeMin(){
	MinHeap::MinHeapify();
	int last_index = heap.size()-1;
	std::swap(heap[0],heap[last_index]);
	int_tuple temp = heap[last_index];
	heap.pop_back();
	return temp;
}

void MinHeap::MinHeapify(){
	int num = (heap.size()-1) >> branching_factor;
	while(num>=0){
		MinHeap::MinHeapifyIndex(num);
		num--;
	}

}

void MinHeap::MinHeapifyIndex(int index){
	printf("%s %d\n","In minHeapify",index );
	int max_element = heap.size()-1;
	int leftmost_child = MinHeap::leftmost_child(index);
	if (leftmost_child>max_element){
		/*
			Element is a leaf node
		*/
		return;
	}
	int rightmost_child = MinHeap::rightmost_child(index);
	if (rightmost_child > max_element){
		rightmost_child = max_element;
	}
	int min_index = index;
	int i;
	for(i=leftmost_child;i<=rightmost_child;i++){
		key_compares++;
		printf("%s %d %d\n","comparing",i,min_index );
		if(heap.at(i).key < heap.at(min_index).key){
			min_index=i;
		}
	}
	if(min_index!=index){
		printf("%s %d %d \n","Swapping",min_index,index );
		std::swap(heap[index],heap[min_index]);
		MinHeap::MinHeapifyIndex(min_index);
	}
}

int poweroftwo(const char * c)
{
	if(int val = atoi(c)){
		if ( ceil(log2(val)) ==floor(log2(val)))
		{
			return 1;
		}
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	int heap_n;
	if (argc == 1)	heap_n = 1;
	else if(argc == 2){
		if (poweroftwo(argv[1]))
		{
			heap_n = log2(atoi(argv[1]));
		}
		else
		{
			printf("%s\n","Argument is not a power of two" );
			exit(1);
		}
	}
	else{
		printf("%s\n","Incorrect number of arguments" );
		exit(1);
	}

	MinHeap h(heap_n);
	int k,v;
	int_tuple temp;
	while(scanf("%d",&k)==1){
		if(k == -1){
			printf("Remove : %d\n",k);
			temp = h.removeMin();
			printf("%d %d\n",temp.key,temp.value );
		}
		else{
			scanf("%d",&v);
			printf("Insert %d %d\n",k,v );
			h.insert(k,v);
		}
		h.printheap();
	}
	printf("%s %d\n","key comparisions : ",h.numCompares() );


	return 0;
}