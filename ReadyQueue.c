//Hasib Ziai			
//Vidit Chopra		 
/*
This ready-queue is implemented like a queue that uses the first in, first out (FIFO)
principle: items are removed from a queue in the order in which they were inserted.
However, this ready-queue contains the pointers to the first slist_node as well as the last
slist_node in the list. Each slist_node has a pointer that points to the next slist_node in the readyqueue.
Below is a list of Application Programming Interface (API):
§ create_slist_node creates a slist_node with the given data
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

bool is_empty(queue * theQueue);


// Queue slist_node and the slist_node creation function
struct slist_node {
	void *data;
	slist_node *next;
};

slist_node *create_slist_node(void *theData) {
	slist_node *nodePointer = (slist_node *)malloc(sizeof(slist_node));
	nodePointer->data = theData;
	nodePointer->next = NULL;
	return nodePointer;
};
/*																		*/


/*							Queue Struct								*/
struct queue {
	slist_node *rear;
	slist_node *front;
	int numberOfItems;
};
/*																		*/

/*		Create the queue and allocate memory	*/
queue *create_queue() {
	queue* theQueue = (queue *)malloc(sizeof(queue));
	theQueue->numberOfItems = 0;
	theQueue->front = NULL;
	theQueue->rear = NULL;

	return theQueue;
}
//


//enqueue : inserts element to back of queue
void enqueue(queue *theQueue, void *theData) {
	slist_node * temp_node = create_slist_node(theData);
	temp_node->next = theQueue->rear;
	theQueue->rear = temp_node;
	theQueue->numberOfItems++;

};


//dequeue : removes the element at the front of the queue
void dequeue(queue * theQueue) {
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
		return;
	}
	else if (theQueue->numberOfItems == 1) {
		theQueue->front = NULL;
		theQueue->numberOfItems--;
		return;
	}
	else {
		slist_node * curr = theQueue->rear;
		slist_node * fwd = curr->next;

		while (fwd->next != NULL) {
				curr = curr->next;
				fwd = fwd->next;
		}
		theQueue->front = curr;
		theQueue->front->next = NULL;
		theQueue->numberOfItems--;
		return;
	}
};


//front : returns the element at the front of the queue without removing it
slist_node * front(queue *theQueue) {
	slist_node * theNode = NULL;
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
	}
	else {
		theNode = theQueue->front;
	}
	return theNode;
};


//back : returns element at back of queue without removing it. 
slist_node * back(queue *theQueue) {
	slist_node * theNode = NULL;
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
	}
	else {
		theNode = theQueue->rear;
	}
	return theNode;
};


//size : return the size of the queue
int size(queue * theQueue) {
	return theQueue->numberOfItems;
}


//empty : returns true if queue is empty
bool is_empty(queue * theQueue) {
	if (theQueue->numberOfItems == 0) { return 1; }
	else return 0;
}


//printAll - prints all nodes in the queue
void printAll(queue *theQueue) {
	if (is_empty(theQueue)) {
		fprintf(stderr, "queue is empty\n");
		return;
	}
	slist_node *theNode = theQueue->rear;
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

	slist_node *theNode = theQueue->rear;
	printf("My current queue: { ");
	while (theNode != NULL) {
		printf("%i ", theNode->data);
		theNode = theNode->next;
	}
	printf("}\n");

}


int main() {
	//implement unit test

	queue *intQueue = create_queue();

	enqueue(intQueue, 1);
	enqueue(intQueue, 2);
	enqueue(intQueue, 3);

	printAll(intQueue);		//3,2,1
	printAllIntegers(intQueue); //3,2,1
	printf("%d : Size of Queue \n", size(intQueue));	//3

	dequeue(intQueue);
	printAllIntegers(intQueue);	//3,2
	dequeue(intQueue);
	printAllIntegers(intQueue);	//3
	dequeue(intQueue);
	printAllIntegers(intQueue);	//empty

	dequeue(intQueue);	//should be empty
	printAll(intQueue); //empty

	system("PAUSE");
	return 0;
}
