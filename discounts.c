//
//	Hasibullah Ziai  
//	Vidit Chopra
//
//  discounts.c
//  Assignment4_SharedMemory
//

// TODO: Include additional header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define SIZE 5

// Function prototypes
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest);
void compute_discounts(float price[], float discount[]);
void display_discounts(void);

const char *name = "OS";
const int SHSIZE = 4096;



/*******************************************************************
 * Calculate the highest and lowest numbers in the given array.    *
 ******************************************************************/
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest) {
   int ix;
   if (numItems < 0) {
      printf("No scores to calculate highest and lowest\n");
      *highest = 0;
      *lowest = 0;
      return;
   }
   *highest = numbers[0];
   *lowest = numbers[0];
   for (ix = 0; ix < numItems; ix++) {
      if (numbers[ix] > *highest) {
         *highest = numbers[ix];
      }
      else if (numbers[ix] < *lowest) {
         *lowest = numbers[ix];
      }
   }
}

/*******************************************************************
 * Calculate the total sale and the average, lowest and highest    *
 * prices for each item.                                           *
 * Establish the shared-memory object and share the computed data. *
 ******************************************************************/
void compute_discounts(float price[], float discount[]) {
    
	char text[128];
   
    float tmp_prices[5];
    float highest;
    float lowest;
    float total;
    float average;
    int shm_fd;
    void *ptr;
    int i;
    int j;
    int h;
   /* TODO:
    * Create the write shared memory segment.
    * Terminate the program if error.
    */
   shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
   if (shm_fd == -1){
	printf("Shared memory failed\n");
	exit(-1);
   }
   	
   /* TODO: Configure the size of the shared memory segment */
   ftruncate(shm_fd, SHSIZE);
   
   /* TODO: Map the shared memory segment in the address space of the process.
    *       Terminate if fail to map.
    */
   ptr = mmap(0, SHSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); 
   if (ptr == MAP_FAILED){
	printf("Map failed\n");
	exit(-1);
   }
   /**
    * TODO:
    * Calculate the total sale, the average, lowest and highest prices for each
    * item for each discount: 5%, 10%, 15%, 20%, 25%
    */
   for (j=0; j<SIZE; j++){	
	   total = 0.0;
	for (i=0; i<SIZE; i++){			
		tmp_prices[i] = price[i] - (price[i]*(discount[j]/100));
		total += tmp_prices[i];
							
	}
	compute_lowest_highest(5, tmp_prices, &highest, &lowest);
		
	

	average=total/5;

        sprintf(text, "%2.0f", discount[j]);
        sprintf(ptr, "%s", text);
        ptr += strlen(text);

		sprintf(ptr, "\t");
		ptr += strlen("\t");

        sprintf(text, "%4.2f", total);
        sprintf(ptr, "%s", text);
        ptr += strlen(text);


		sprintf(ptr, "\t");
		ptr += strlen("\t");

		sprintf(text, "%4.2f", average);
		sprintf(ptr, "%s", text);
		ptr += strlen(text);

		sprintf(ptr, "\t");
		ptr += strlen("\t");

		sprintf(text, "%4.2f", highest);
		sprintf(ptr, "%s", text);
		ptr += strlen(text);

		sprintf(ptr, "\t");
		ptr += strlen("\t");

		sprintf(text, "%4.2f", lowest);
		sprintf(ptr, "%s", text);
		ptr += strlen(text);

        sprintf(ptr, "\n");
        ptr += strlen("\n");


   }
   
      
	/**
      	* TODO: write the percentage discount, total sale, average price, lowest and
      	* highest prices to the shared memory region.
      	*
       	* Note: must increment the value of ptr after each write.
      	*/

   		
   //sprintf(ptr,"%s",;
   
}

/*******************************************************************
 * Output and display the computed total sale and the average,     *
 * lowest and highest prices for each item.                        *
 * Open the read-only shared-memory object and read data from the  *
 * shared memory region, then remove the shared memory segment.    *
 ******************************************************************/
void display_discounts(void) {
   
   int shm_fd;
   void *ptr;
   /* TODO: open the read-only shared memory segment.
    * Terminate the program if error.
    */
   shm_fd = shm_open(name, O_RDONLY, 0666);
   if (shm_fd == -1) {
	printf("read of shared memory failed\n");
	exit(-1);
   }
   /* TODO: Map the shared memory segment in the address space of the process
    *       Terminate if fail to map.
    */
   ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
   if (ptr == MAP_FAILED) {
	printf("Parent Map Failed\n");  
	exit(-1);
   } 

   /* TODO: Print header */
   printf("Discount | Total | Average | Highest | Lowest \n");
   /* TODO: read from the shared memory region */
   printf("%s",(char *)ptr);
   /* TODO: Remove the shared memory segment. Terminate the program if error.
    */
   if (shm_unlink(name) == -1) {
	printf("Error removing shared memory %s\n",name);
	exit(-1);
   }
}


int main()
{
   /*Size of shared memory segment and name*/
 
   
   /*shared memory file descriptor*/
   int shm_fd;
   /*pointer to shared memory object*/
   void *ptr;   

   float *arrayOfarrays[SIZE];
   float prices[SIZE] = {1000, 1500, 720, 850, 970};
   float discounts[SIZE] = {5, 10, 15, 20, 25};

   /* TODO: Error check to make sure the child was successfully created */
    pid_t pid;
    int status = 0;

    pid=fork();

    if (pid == -1){
    	fprintf(stderr, "We cannot fork, ERROR!! %d\n", errno);
    	exit(EXIT_FAILURE);
    }
   
   /*** TODO: If I am child, I will do this: ****/
   /* Compute the total sale, the average, lowest and highest prices
    * for the five items for each discount rate
    */
   else if (pid == 0){
	float highest;
	float lowest;
	
	compute_discounts(prices, discounts);
	//compute_highest_lowest(SIZE, prices, &highest, &lowest);

   /*** TODO: If I am a parent, I will do the following ***/
   /* Wait for my child process to compute and share the computed data, then
    * display the data
    */
}
   else{
	wait(NULL);
	display_discounts();
   return 0;
}
}
