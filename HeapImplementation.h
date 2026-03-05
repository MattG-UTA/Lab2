#ifndef HEAPIMPLEMENTATIONS_H
#define HEAPIMPLEMENTATIONS_H
extern int N,
	    *pq,
	    *qp,
	    maxQueued;
 extern	double *a;

	int parent(int i);
	int left(int i);
	int right(int i);

	void exch(int i, int j);
	void minHeapInit(double *items, int n, int m);
	int minHeapEmpty();
	int minHeapFull();
	int less(int i, int j);
	void fixUp(int *pq, int k);
	void minHeapify(int *pq, int k, int N);
	void minHeapInsert(int k);
	int heapExtractMin();
	void minHeapChange(int k);

#endif
