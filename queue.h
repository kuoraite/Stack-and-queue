// nedas.gulbickas@mif.stud.vu.lt, PS 1gr., 2022

// User manual for using queue data structure.

// Realization of the function can be found in "queue.c";
// Testing is done in "main1.c";

#ifndef QUEUE_HEADER
   #define QUEUE_HEADER

   /*
      IMPORTAT:
         1. Do not change field values of Queue variable yourself;
         2. Always remember to use deleteQueue() function to avoid memory leaks;
         3. Example of creating and initializing new queue element:
            Queue *queue = createQueue(...);
         4. Every function accepts pointer to integer "error", to provide
         addition information about work of the function;
   */


   // Private
   typedef struct Node{
      struct Node *next;
      void *value;
   }Node;


   typedef struct Queue{
      Node *head; // Private
      Node *tail; // Private
      int nodeCount; // Private
   }Queue;

   /*
      Function return values

      If function failed it returns:
      -1 or NULL;

      More detailed information about function work
      is passed into variable "error";

      Possible error values:
       0 - everything went well;
      -1 - queue is empty;
      -2 - no/invalid queue provided;
      -3 - unable to allocate more memory;
      -4 - missing/invalid additional data;

   */

   // Creates Empty queue;
   // On success: returns newly allocated queue structure;
   Queue* createQueue(int *error);

   // Checks if queue is empty;
   // On success: if empty returns - 0, else - 1;
   int isQueueEmpty(Queue *que, int *error);

   // Enqueues new element to the queue;
   // Use:
   // "data" - pointer to a variable of any type to be storer in a queue,
   // "dataSize" - size of "data" type in bytes;
   // On success: returns 0;
   int enQueue(Queue *que, void *data, size_t dataSize, int *error);

   // Dequeues element from queue and returns it in variable "dataBlock";
   // Use:
   // "dataBlock" - pointer to a variable where dequeued value will
   // be stored, IMPORTANT: make sure to use same variable type as enQueuing.
   // "dataSize" - size of "dataBlock" type in bytes;
   // On success: returns 0;
   int deQueue(Queue *que, void *dataBlock, size_t dataSize, int *error);

   // Peeks element value stored in queue's head and returns it
   // in variable "dataBlock" (without removing it from queue);
   // "dataBlock"/"dataSize" - same as in function deQueue();
   // On success: returns 0;
   int peekQueue(Queue *que, void *dataBlock, size_t dataSize, int *error);

   // Returns queue length;
   int queueLength(Queue *que, int *error);

   // Deletes whole queue;
   // On success: returns 0;
   int deleteQueue(Queue **que, int *error);

#endif
