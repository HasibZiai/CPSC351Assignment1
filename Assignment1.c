#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Hasib Ziai			889564787
//Vidit Chopra			

typedef struct slist_node slist_node;
typedef struct queue queue;

// Queue node and the node creation function
struct slist_node {
	void *data;
	slist_node *next;
};

slist_node *create_queue_node(void *theData) {
	slist_node *nodePointer = (slist_node *)malloc(sizeof(slist_node));
	nodePointer->data = theData;
	nodePointer->next = NULL;
	return nodePointer;
};

struct queue {
	slist_node *rear;
	slist_node *front;
	int numberOfItems;
};

queue *create_queue() {
	queue* theQueue = (queue *)malloc(sizeof(queue));
	theQueue->numberOfItems = 0;
	theQueue->front = NULL;
	theQueue->rear = NULL;

	return theQueue;
}


//Function isEmpty returns true if queue is empty
bool is_empty(queue *theQueue) {
	return (theQueue->numberOfItems == 0);
};
