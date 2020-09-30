#include <stdbool.h>

//constants to remove magic numbers
#define COMMENT_CHARACTER '-'
#define TOKEN_CHARACTER " "
#define maxLineLength 255

// data types
typedef struct {
  char *name;
  int daysToWater;
  bool priority;
  int waterInterval;
} plant;

typedef struct plantPriorityQueueNode {
  plant *plt;
  struct plantPriorityQueueNode *next;
} plantPriorityQueueNode;

typedef struct {
  plantPriorityQueueNode *first;
  int noOfPlants;
} plantPriorityQueue;

/*
 functions in plant.c
*/

// heap allocated memory for a plant with following 'fields'
plant *plantConstructor(char *name, int days, int dayInterval, bool priority);

// heap allocated memory for a queue node with the plant parameter as a field
plantPriorityQueueNode *newQueueNode(plant *plt);

// helper function to insert a plant into the priority queue 
void plantQueueInsert(plantPriorityQueueNode **prev, plantPriorityQueueNode **curr, plant *plt)

// main function to build the priority queue, used in screen.c
plantPriorityQueue *plantInitialise(const char *filename);

// function to free the queue, all nodes and all plants in the nodes
void freeQueue(plantPriorityQueue *queue);

// helper function to write a plant to a file in the specified format in plantList.txt
void plantText(FILE *fp, const plant *plt);

// function to update the plant after the necessary plants have been watered that day
void updateFile(plantPriorityQueue *queue, const char* filename);





  
