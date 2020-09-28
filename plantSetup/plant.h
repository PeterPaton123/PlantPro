#include <stdbool.h>

#define COMMENT_CHARACTER '-'
#define TOKEN_CHARACTER " "


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



  
