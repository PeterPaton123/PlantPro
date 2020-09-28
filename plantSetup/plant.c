#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "plant.h"

plant *plantConstructor(char *name, int days, int dayInterval, bool priority) {
  plant *plt = malloc(sizeof(plant));
  if (plt == NULL) {
    printf("Plant %s malloc failed", name);
  }
  plt->name = calloc(strlen(name) + 1, sizeof(char));
  plt->name = strcpy(plt->name, name);
  plt->daysToWater = days;
  plt->priority = priority;
  return plt;
}

plantPriorityQueueNode *newQueueNode(plant *plt) {
  plantPriorityQueueNode *pNode = malloc(sizeof(plantPriorityQueueNode));
    if (pNode == NULL) {
      perror("Error allocating storage for plant node");
    }
    pNode->plt = plt;
    pNode->next = NULL;
    return pNode;
}

void plantQueueInsert(plantPriorityQueueNode **prev, plantPriorityQueueNode **curr, plant *plt) {
  if (*curr == NULL) {
    *curr = newQueueNode(plt);
    return;
  } else {
    if (plt->daysToWater < (*curr)->plt->daysToWater || (plt->daysToWater == (*curr)->plt->daysToWater && plt->priority && !((*curr)->plt->priority))) {
      // if plt has higher priority than curr
      //if (prev == NULL) { // then curr is first node of queue so need to make new node first
        plantPriorityQueueNode *currClone = newQueueNode((*curr)->plt);
        free(*curr);
        *curr = newQueueNode(plt);
        (*curr)->next = currClone;
        return;
    } else {
     plantQueueInsert(curr, &((*curr)->next), plt);
    }
  }
}

plantPriorityQueue *plantInitialise(const char *filename) {
  plantPriorityQueue *pQueue = malloc(sizeof(plantPriorityQueue));
  if (pQueue == NULL) {
    perror("Queue allocation failed");
    return -1;
  }
  
  pQueue->first = NULL;
  pQueue->noOfPlants = 0;
  
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    perror("Error opening file");
    return -1;
  }

  int maxLineLength = 255;
  char buffer[maxLineLength];

  while(fgets(buffer, maxLineLength, fp)) {
    //printf("%s\n", buffer);
    if (buffer[0] != COMMENT_CHARACTER) {
      //tokenise
      char *tokens[4];
      int tokenCount = 0;
      char *token;
      token = strtok(buffer,TOKEN_CHARACTER);
      while(token != NULL) {
	//printf("%s\n", token);
        tokens[tokenCount++] = token;
        token = strtok(NULL, TOKEN_CHARACTER);
      }
      
      bool b = !(strcmp(tokens[3], "1\n"));

      plant* pPlant = plantConstructor(tokens[0], atoi(tokens[1]), atoi(tokens[2]), b);

      //insert queue
      plantQueueInsert(NULL, &(pQueue->first), pPlant);
      pQueue->noOfPlants++;
      
    }
  }
  
  fclose(fp);
  return pQueue;
}

void freeQueue(plantPriorityQueue *queue) {
  plantPriorityQueueNode *currNode = queue->first;
  while (currNode != NULL)  {
      free(currNode->plt);
      plantPriorityQueueNode *nextNode = currNode->next;
      free(currNode);
      currNode = nextNode;
    }
  free(queue);
  return;
}

//
//void plantWrite(UBYTE *black, UBYTE *red, int x, int y, plant *plt) {
// Paint_SelectImage(black);
// Paint_DrawPoint(x, y+7, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
// Paint_DrawString_EN(x + 7, y, plt->name, &Font12, WHITE, BLACK);
// Paint_SelectImage(red);
// printf("string length %d\n", strlen(plt->name) * 4 + x + 3);
// Paint_DrawLine(x + 5 , y + 15,(strlen(plt->name)*7) + (x + 5 + 7), y+15, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//  return;
//}

int main(void) {
  plantPriorityQueue *plants = plantInitialise("plantList.txt");
    plantPriorityQueueNode *currNode = plants->first;
    while (currNode != NULL)  {
      printf("%s", currNode->plt->name);
      currNode = currNode->next;
  }
  freeQueue(plants);
  return 0;
}
