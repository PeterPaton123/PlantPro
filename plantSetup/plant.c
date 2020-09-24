#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

plantList *plantInitialise(const char *filename) {
  plantList *list = malloc(sizeof(plantList));
  if (list == NULL) {
    perror("List allocation failed");
    return -1;
  }
  
  plant **plants = NULL;
  int plantCount = 0;
  
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

      plant* pPlant = plantConstructor(tokens[0], (int) tokens[1], (int) tokens[2], (bool) tokens[3]);

      ++plantCount;
      
      if (plantCount == 1) {
	plants = malloc(sizeof(plant*));
      } else {
	plants = realloc(plants, sizeof(plant*) * plantCount);
      }
      if (plants == NULL) {
	perror("Error (re)allocating memory for plants");
	return -1;
      }
      plants[plantCount - 1] = pPlant;
    }
    
  }
  
  fclose(fp);
  list->plts = plants;
  list->noOfPlants = plantCount;
  return list;
}

void freeList(plantList *list) {
  for (int i = 0; i < list->noOfPlants; ++i) {
    free(list->plts[i]);
  }
  free(list->plts);
  free(list);
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
  plantList *plants = plantInitialise("plantList.txt");
  freeList(plants);
  return 0;
}
