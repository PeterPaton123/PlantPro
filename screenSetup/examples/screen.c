#include "EPD_Test.h"
#include "EPD_2in7b.h"
#include "plant.h"

#include <time.h>
#include <string.h>
#include <stdbool.h>
#define MAX(int a, int b) (((a) > (b))? (a) : (b)))

void plantWrite(UBYTE *black, UBYTE *red, int x, int y, plant *plt) {
  Paint_SelectImage(black);
  Paint_DrawPoint(x, y+7, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT); 
  Paint_DrawString_EN(x + 7, y, plt->name /* replace - with ' ' */, &Font12, WHITE, BLACK);
  Paint_SelectImage(red);
  printf("string length %d\n", strlen(plt->name) * 4 + x + 3);
  Paint_DrawLine(x + 5 , y + 15,(strlen(plt->name)*7) + (x + 5 + 7), y+15, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  return;
}



int test(void) {
 printf("EPD_2IN7B_test Demo\r\n");

  if(DEV_Module_Init()!=0){
    printf("Error in initialising");
    return -1;
  }

  printf("e-Paper Init and Clear...\r\n");
  EPD_2IN7B_Init();
  EPD_2IN7B_Clear();
  DEV_Delay_ms(500);
  
  //Create a new image cache named IMAGE_BW and fill it with white
  UBYTE *BlackImage, *RedImage;
  UWORD Imagesize = ((EPD_2IN7B_WIDTH % 8 == 0)? (EPD_2IN7B_WIDTH / 8 ): (EPD_2IN7B_WIDTH / 8 + 1)) * EPD_2IN7B_HEIGHT;
  if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
      printf("Failed to apply for black memory...\r\n");
      return -1;
  }
  if((RedImage = (UBYTE *)malloc(Imagesize)) == NULL){
    printf("Failed to apply for red memory...\r\n");
    return -1;
  }

   printf("NewImage:BlackImage and RedImage\r\n");
   Paint_NewImage(BlackImage, EPD_2IN7B_WIDTH, EPD_2IN7B_HEIGHT, 270, WHITE);
   Paint_NewImage(RedImage, EPD_2IN7B_WIDTH, EPD_2IN7B_HEIGHT, 270, WHITE);

    //Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    
    plantPriorityQueue *pQueue = plantInitialise("cd plantList.txt");
    
    int plantsWritten = 0;
    plantPriorityQueueNode *node = pQueue->first;
    
    while (plantsWritten <= MAX(pQueue->noOfPlants, 5) && node != NULL && node->plt->daysToWater == 0) {
		plantWrite(BlackImage, RedImage, 87, 35 + (25 * plantsWritten), node->first);
		node->plt->daysToWater--;
		node = node->next;
		plantsWritten++;
	}
	
	
	freeQueue(pQueue);
}
