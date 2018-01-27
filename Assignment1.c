//Hasib Ziai			889564787
//Vidit Chopra		#891303158

/*
This ready-queue is implemented like a queue that uses the first in, first out (FIFO)
principle: items are removed from a queue in the order in which they were inserted.
However, this ready-queue contains the pointers to the first node as well as the last
node in the list. Each node has a pointer that points to the next node in the readyqueue.
Below is a list of Application Programming Interface (API):
§ create_queue_node creates a node with the given data
§ create_ready_queue creates an empty ready-queue
§ enqueue inserts an element to the back of the queue
2
§ dequeue removes the element at the front of the queue
§ front returns the element at the front of the queue without removing it
§ back returns the element at the back of the queue without removing it
§ size returns the number of elements stored
§ empty returns true if the ready queue is empty. Otherwise, false
§ printAll prints all the nodes in the array queue
§ printAllIntegers prints all the nodes whose data type is an integer
You will need to also implement the unit test driver in order to test your readyqueue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

//enqueue : inserts element to back of queue
void enqueue(queue *theQueue, void *theData) {
	queue_node * temp_node = create_queue_node(theData);
	temp_node->next = theQueue->tail;
	theQueue->tail = temp_node;
	theQueue->numberOfItems++;

};

//dequeue : removes the element at the front of the queue
void dequeue(queue * theQueue) {
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
		return;
	}
	else {
		queue_node curr = theQueue->tail;
		queue_node fwd = curr->next;

		if (fwd == theQueue->head) {
			theQueue->head = curr;
			theQueue->head->next = NULL;
		}
		else {
			curr = curr->next;
			fwd = fwd->next;
		}
	}
};

//front : returns the element at the front of the queue without removing it
queue_node * front(queue *theQueue) {
	queue_node * theNode = NULL;
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
	}
	else {
		theNode = theQueue->head;
	}
	return theNode;
};

//back : returns element at back of queue without removing it. 
queue_node * back(queue *theQueue) {
	queue_node * theNode = NULL;
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
	}
	else {
		theNode = theQueue->tail;
	}
	return theNode;
};

//size : return the size of the queue
int size(queue * theQueue) {
	return theQueue->numberOfItems;
}

//empty : returns true if queue is empty
bool is_empty(queue * theQueue) {
	return (theQueue->numberOfItems == 0);
}

//printAll - prints all nodes in the queue
void printAll(queue *theQueue) {
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
		return;
	}
	queue_node *theNode = (queue_node *)front(theQueue);
	while (theNode != NULL) {
		printf("%p\n", theNode->data);
		theNode = theNode->next;
	}
	printf("\n");
}

//printAllIntegers - print all nodes whose data type is integers.
void printAllIntegers(queue * theQueue) {
	if (is_empty(theQueue)) {
		printf("queue is empty\n");
		return;
	}

	queue_node *theNode = (queue_node *)front(theQueue);
	printf("My current queue: { ");
	while (theNode != NULL) {
		printf("%i ", *((int *)theNode->data));
		theNode = theNode->next;
	}
	printf("}\n");

}


int main() {
	//implement unit test


}