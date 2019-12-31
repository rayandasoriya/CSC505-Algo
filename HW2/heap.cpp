/*
A C++ program for min-heap sort with varibale number of children as a power of two and using bit shifting operations instead of the arithmetic operations.

Authors:
Kushagr Gupta (kgupta7)
Rayan Dasoriya (rdasori)

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

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

	int parent(int index) {
		return (index >> branching_factor >= 0 ? (index - 1) >> branching_factor : 0);
	}

	int leftmost_child(int index) {
		return ((index << branching_factor) + 1);
	}
	int rightmost_child(int index) {
		return ((index + 1) << branching_factor);
	}
	int numCompares() {
		return key_compares;
	}
	void insertValue(int key, int value);

	int_tuple removeMin();

	void MinHeapify(int index);

};


MinHeap::MinHeap(int bf) {
	branching_factor = bf;
	key_compares = 0;
}

void MinHeap::insertValue(int key, int value) {
	/*
	This just creates a new tuple key value pair and adds it to the Vector
	*/
	int_tuple temp;
	temp.key = key;
	temp.value = value;
	heap.push_back(temp);
	int item_index = heap.size() - 1;
	while (item_index != 0) {
		key_compares++;
		if (heap.at(MinHeap::parent(item_index)).key > (heap.at(item_index)).key) {
			std::swap(heap[item_index], heap[MinHeap::parent(item_index)]);
			item_index = MinHeap::parent(item_index);
		}
		else
		{
			break;
		}
	}
}

int_tuple MinHeap::removeMin() {
	int last_index = heap.size() - 1;
	std::swap(heap[0], heap[last_index]);
	int_tuple temp = heap[last_index];
	heap.pop_back();
	MinHeapify(0);
	return temp;
}

void MinHeap::MinHeapify(int index) {
	int leftmost_child = MinHeap::leftmost_child(index);
	int min_index = index;
	for (int j = 0; j < pow(2, branching_factor); j++)
	{
		if (leftmost_child + j < (int)heap.size()) {
			key_compares++;
		}
		if ((leftmost_child + j < (int)heap.size()) && (heap.at(leftmost_child + j).key < heap.at(min_index).key)) {
			min_index = leftmost_child + j;
		}
	}

	if (min_index != index) {
		std::swap(heap[index], heap[min_index]);
		MinHeap::MinHeapify(min_index);
	}
}

int poweroftwo(const char * c)
{
	if (int val = atoi(c)) {
		if (ceil(log2(val)) == floor(log2(val)))
		{
			return log2(val);
		}
	}
	return -1;
}


int main(int argc, char const *argv[])
{
	int heap_n;
	if (argc == 1)	heap_n = 1;
	else if (argc == 2) {
		heap_n = poweroftwo(argv[1]);
		if (heap_n < 1)
		{
			printf("%s\n", "Argument is not a power of two");
			exit(1);
		}
	}
	else {
		printf("%s\n", "Incorrect number of arguments");
		exit(1);
	}

	MinHeap h(heap_n);
	int k, v;
	int_tuple temp;
	while (scanf("%d", &k) == 1) {
		if (k == -1) {
			temp = h.removeMin();
			printf("%d %d\n", temp.key, temp.value);
		}
		else {
			scanf("%d", &v);
			h.insertValue(k, v);
		}

	}
	printf("%s %d\n", "key comparisions : ", h.numCompares());

	return 0;
}