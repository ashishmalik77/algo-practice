// Assumtions:
// Valid values : [1,MAX_VAL]
// maximum count : MAX
// Unique numbers 


#include <iostream> 
#define MAX 1000
#define MAX_VAL 1000
#define MINUS_INF 0

class minheap{
	public:
		minheap();
		~minheap();
		void removeMin();
		void remove(int val);
		int getMin();
		void insert(int val);

    private:
	    void swap(int aId, int bId);
		void reset();
    private:
		int *valToNodeId;
		int *heap; // 0th is unused, one extra space for MINUS_INF
		int cnt;
};

minheap::minheap() {
	valToNodeId = new int[MAX_VAL+1];
	heap = new int[MAX + 2]; // 0th is unused, one extra space for MINUS_INF
	reset();	
}
minheap::~minheap() {
	delete []valToNodeId;
	delete []heap;
}

void minheap::reset() {
	cnt=0;
	for (int i=0; i<=MAX_VAL; i++) {
		valToNodeId[i] = -1;
	}	
}
void minheap::swap(int aId, int bId) {
	int t = heap[aId];
	heap[aId] = heap[bId];
	heap[bId] = t;
	valToNodeId[heap[aId]] = aId;
	valToNodeId[heap[bId]] = bId;
}

void minheap::insert(int a) {
	cnt++;
	heap[cnt] = a;
	valToNodeId[a] = cnt;
	int p = cnt / 2;
	int ch = cnt;
	while (p && heap[p] > heap[ch]) {
		swap(p, ch);
		ch = p;
		p = ch / 2;
	}
}

int minheap::getMin() {
	if (cnt == 0)
		return -1;

	return heap[1];
}

void minheap::removeMin() {
	swap(1, cnt);
	valToNodeId[heap[cnt]] = -1;
	cnt--;

	int p = 1;

	while (1) {
		int ch1 = 2 * p;
		int ch2 = 2 * p + 1;
		int smallerChild;

		if (ch1 > cnt) {
			break;
		}

		if (ch2 > cnt) {
			smallerChild = ch1;
		}
		else {
			smallerChild = ((heap[ch1] < heap[ch2]) ? ch1 : ch2);
		}
		if (heap[p] < heap[smallerChild])
			break;

		swap(p, smallerChild);
		p = smallerChild;
	}
}


void minheap::remove(int val) {
	int id = valToNodeId[val];
	valToNodeId[val] = -1;

	heap[id] = MINUS_INF;

	valToNodeId[MINUS_INF] = id;
	int p = id/2;
	while(p && heap[p] > heap[id]) {
		swap(p, id);
		id = p;
		p = id/2;
	}
	removeMin();
}


// test 

#include <cstdlib>
#include <iostream>

using namespace std;
int nums[MAX + 1];

void basicTestGetMin() {
	// Varify if insertion and getMin are working
	srand(MAX);

	int end = MAX;
	// Fill input array
	for (int i = 1; i<=end; i++) {
		nums[i] = i;
	}

    // Randomize the array
	for (int i = 1; i <= end; i++) {
		int a = rand() % end + 1;
		int b = rand() % end + 1;
		int t = nums[a];
		nums[a] = nums[b];
		nums[b] = t;
	}
	minheap mh;
	for (int i = 1; i <= end; i++) {
		mh.insert(nums[i]);
	}
	int lastMin = -1;
	int min;
	while ((min = mh.getMin()) != -1) {	
		if (min < lastMin) {
			cout << "Error!!!!!!!!!!!" << endl;
			break;
		}
		cout << min << "\t";
		mh.removeMin();
		lastMin = min;
	}
	cout << "done" << endl;
	char ch;
	cin >> ch;

	return;
}
int main() {
	basicTestGetMin();

	return 0;
}
