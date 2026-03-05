#include <stdio.h>
#include <stdlib.h>
#include "HeapImplementation.h"

int N = 0;
int *pq = NULL;
int *qp = NULL;
int maxQueued = 0;
double *a = NULL;

int parent(int i)
{
  return i/2;
}

int left(int i)
{
  return 2*i;
}

int right(int i)
{
  return 2*i+1;
}

void exch(int i, int j)
{
// Swaps parent with child
int t;

t = pq[i];
pq[i] = pq[j];
pq[j] = t;
qp[pq[i]] = i;
qp[pq[j]] = j;
}

void minHeapInit(double *items,int n,int m)
{
int i;

a = items;    // Save reference to index table
maxQueued=m;
N = 0;
pq=(int*) malloc((maxQueued+1)*sizeof(int)); // Contains subscripts to a[]
qp=(int*) malloc(n*sizeof(int));   // Inverse of pq, allows changing priorities
if (!pq || !qp)
{
  printf("malloc failed %d\n",__LINE__);
  exit(0);
}
// Set all handles to unused
for (i=0;i<n;i++)
  qp[i]=(-1);
}

int minHeapEmpty()
{
return !N;
}

int minHeapFull()
{
return N == maxQueued;
}

int less(int i, int j)
{
// Notice how heap entries reference a[]
return a[pq[i]] < a[pq[j]];
}

void fixUp(int *pq,int k) // AKA swim
{
while (k>1 && less(k,parent(k)))
{
  exch(k, parent(k));
  k = parent(k);
}
}

void minHeapify(int *pq,int k, int N) // AKA sink
{
int j;

while (left(k) <= N)
{
  j = left(k);
  if (j < N && less(j+1, j))
    j=right(k);
  if (!less(j, k))
    break;
  exch(k, j);
  k = j;
}
}

void minHeapInsert(int k)
{
qp[k] = ++N;
pq[N] = k;
fixUp(pq, N);
}

int heapExtractMin()
{
exch(1, N);
minHeapify(pq, 1, --N);
qp[pq[N+1]]=(-1);  // Set to unused
return pq[N+1];
}

void minHeapChange(int k)
{
fixUp(pq, qp[k]);
minHeapify(pq, qp[k], N);
}
