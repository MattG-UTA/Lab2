//Matthew Gutierrez
//1002333697
//Lab 2
//gcc lab2.c HeapImplementation.c -o lab2
#include <stdio.h>
#include <stdlib.h>
#include "HeapImplementation.h"

// main implements Huffman code.
// Index is just a table of priorities whose
// subscripts are used in the PQ.

int main (int argc, char*argv[])
{
	int n,m,op,i,j,val;
	double *priority,probSum,expected=0.0;
	int *left,*right;  // Links for Huffman code tree, root is subscript m-1
	int *parent;  // For printing the codes
	int *length;
	char *outString;

	printf("Enter alphabet size\n");
	scanf("%d",&n);
	m=(3*n-1)/2;  // Number of nodes in tree
	priority=(double*) malloc(m*sizeof(double));
	left=(int*) malloc(m*sizeof(int));
	right=(int*) malloc(m*sizeof(int));
	parent=(int*) malloc(m*sizeof(int));
	outString=(char*) malloc((n+1)*sizeof(char));
	length=(int*) malloc(m*sizeof(int));
	if (!priority || !left || !right || !parent || !outString || !length)
	{
  		printf("malloc problem %d\n",__LINE__);
  		exit(0);
	}

	minHeapInit(priority,m,n);

	for (i=0;i<n;i++) priority[i]=(-1);

	// Read and load alphabet symbols' probabilities into priority queue.
	probSum=0.0;
	for (i=0;i<n;i++)
	{
  		scanf("%lf",priority+i);
  		probSum+=priority[i];
  		minHeapInsert(i);
  		left[i]=right[i]=(-1);
	}

	printf("Probabilities sum to %f\n",probSum);

	// Huffman code tree construction
	for (i=n;i<m;i++)
	{
  		left[i]=heapExtractMin();
  		right[i]=heapExtractMin();
  		parent[left[i]]=parent[right[i]]=i;
  		priority[i]=priority[left[i]]+priority[right[i]];
  		minHeapInsert(i);
	}

	i=heapExtractMin();

	if (i!=m-1)
	{
  		printf("The root isn't the root\n");
  		exit(0);
	}

	parent[m-1]=(-1);

	// Goes breadth-first from root to compute length of prefix bit codes.
	length[m-1]=0;

	for (i=m-1;i>=n;i--) length[left[i]]=length[right[i]]=length[i]+1;

	// Print the leaves, i.e. for the alphabet symbols
	printf("   i  prob  parent  bits product  code\n");

	for (i=0;i<n;i++)
	{
  		// Crawl up the tree to get prefix code
  		outString[length[i]]='\0';

  		for (j=i;j!=m-1;j=parent[j]) outString[length[j]-1]=(left[parent[j]]==j) ? '0' : '1';

  		printf("%5d %5.3f %5d %5d   %5.3f  %s\n", i,priority[i],parent[i],length[i],priority[i]*length[i],outString);
  		expected+=priority[i]*length[i];
	}

	printf("Expected bits per symbol: %f\n",expected);

	// Print the internal nodes
	printf("   i  prob    left right parent\n");

	for (i=n;i<m;i++)
  	printf("%5d %5.3f %5d %5d  %5d\n",i,priority[i],left[i],right[i],parent[i]);

free(priority);
free(left);
free(right);
free(parent);
free(outString);
free(length);
free(pq);
free(qp);
return 0;
}
