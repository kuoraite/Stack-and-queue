// nedas.gulbickas@mif.stud.vu.lt, PS 1gr., 2022
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"


Queue* createQueue(int *error){

   *error = 0;

   Queue *que = (Queue *) malloc(sizeof(Queue));
   if(que == NULL){
      *error = -3;
      return NULL;
   }

   (*que).nodeCount = 0;
   (*que).head = NULL;
   (*que).tail = NULL;

   return que;
}

int isQueueEmpty(Queue *que, int *error){

   *error = 0;

   if(!que){
      *error = -2;
      return -1;
   }

   if((*que).nodeCount == 0){
      *error = -1;
      return 0;
   }

   return 1;
}

int enQueue(Queue *que, void *data, size_t dataSize, int *error){

   *error = 0;

   if(!que){
      *error = -2;
      return -1;
   }

   if(!data || dataSize <= 0){
      *error = -4;
      return -1;
   }

   // New Node
   Node *node = malloc(sizeof(node));
   if(!node){
      *error = -3;
      return -1;
   }

   // Allocating data to store passed variable
   node->value = (void *)malloc(dataSize);
   if(node->value == NULL){
      *error = -3;
      return -1;
   }

   memcpy((*node).value, data, dataSize);
   node->next = NULL;

   // Hooking up head/tail
   que->nodeCount += 1;

   // If it is first node
   if(!que->head && !que->tail){
      que->head = node;
      que->tail = node;
   }
   else{
      que->tail->next = node;
      que->tail = node;
   }

   return 0;
}

int deQueue(Queue *que, void *dataBlock, size_t dataSize, int *error){

   *error = 0;

   if(!que){
      *error = -2;
      return -1;
   }

   if(isQueueEmpty(que, error) == 0){
      *error = -1;
      return -1;
   }

   if(!dataBlock || dataSize <= 0){
      *error = -4;
      return -1;
   }

   // Copy data from head
   memcpy(dataBlock, que->head->value, dataSize);

   // Moving queue's head
   Node *temp = que->head;
   que->head = que->head->next;
   // Free previous head node
   free(temp->value);
   free(temp);

   que->nodeCount -= 1;
   // If it was a last element
   if(isQueueEmpty(que, error) == 0){
      que->tail = NULL;
   }

   return 0;
}

int peekQueue(Queue *que, void *dataBlock, size_t dataSize, int *error){

   *error = 0;

   if(!que){
      *error = -2;
      return -1;
   }

   if(isQueueEmpty(que, error) == 0){
      *error = -1;
      return -1;
   }

   memcpy(dataBlock, que->head->value, dataSize);

   return 0;
}

int queueLength(Queue *que, int *error){

   *error = 0;

   if(!que){
      *error = -2;
      return -1;
   }

   if(isQueueEmpty(que, error) == 0){
      *error = -1;
      return 0;
   }

   return que->nodeCount;
}


int deleteQueue(Queue **que, int *error){

   *error = 0;

   if(!(*que)){
      *error = -2;
      return -1;
   }

   Node *currentNode = (*que)->head;
   Node *temp = NULL;

   while(currentNode != NULL){
      temp = currentNode->next;
      free(currentNode->value);
      free(currentNode);

      currentNode = temp;
   }

   *que = realloc(*que, 0);


   return 0;
}


