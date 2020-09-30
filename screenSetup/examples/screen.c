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
  char name [255];
  strcpy(name, plt->name);
  for (char* chr = &(name[0]); *chr != '\0'; ++chr) {
	  if (*chr == '-') {
		  *chr = ' ';
	  }
  }
  Paint_DrawString_EN(x + 7, y, name, &Font12, WHITE, BLACK);
  Paint_SelectImage(red);
  //printf("string length %d\n", strlen(plt->name) * 4 + x + 3);
  Paint_DrawLine(x + 5 , y + 15,(strlen(name)*7) + (x + 5 + 7), y+15, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  return;
}

void getTime() {
  // need to remove magic numbers in project defined header file
  time_t rawtime;
  struct tm * timeinfo;
  time( &rawtime);
  timeinfo = localtime(&rawtime);

  char currDate[6] = "\0";
  char currDay[3] = "\0";
  printf("%s\n", asctime(timeinfo));
  strncpy(currDate, asctime(timeinfo) + 4, 6);
  strncpy(currDay, asctime(timeinfo), 3);
  printf("CurrDate: %s\n", currDate);
  Paint_DrawString_EN(7, 7, currDate, &Font12, BLACK, WHITE);
  Paint_DrawString_EN(7, 37, currDay, &Font12, BLACK, WHITE);
}


int test(void) {
  //library set up code
 
 
 //printf("EPD_2IN7B_test Demo\r\n");

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
 
	// end  of library set up
	
	printf("Start UI \n");
    Paint_DrawRectangle(1, 1, 70, 55, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);   
    Paint_DrawLine(70, 1, 70, 175, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(1, 95, 69, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(1, 135, 69, 135, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    getTime();

    Paint_SelectImage(BlackImage);
    //Paint_DrawRectangle(8, 28, 256, 160, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(92, 8, "Tjasa's plants", &Font16, WHITE, BLACK);
    Paint_DrawLine(82, 28, 260, 28, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    
    plantPriorityQueue *pQueue = plantInitialise("../plantSetup/plantList.txt");
    
    int plantsWritten = 0;
    plantPriorityQueueNode *node = pQueue->first;
    
    while (plantsWritten <= MAX(pQueue->noOfPlants, 5) && node != NULL && node->plt->daysToWater == 0) {
		plantWrite(BlackImage, RedImage, 87, 35 + (25 * plantsWritten), node->first);
		node = node->next;
		plantsWritten++;
	}
	
	plantPriorityQueueNode *currNode = pQueue->first;
	while (currNode != NULL) {
		currNode->plt->daysToWater--;
		currNode = currNode->next;
	}
	
	
	freeQueue(pQueue);
	
	
	// library closing code
	
	printf("Clear...\r\n");
    //    EPD_2IN7B_Clear();

    printf("Goto Sleep...\r\n");
    //EPD_2IN7B_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    
    free(RedImage);
    RedImage = NULL;

    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    
    return 0;
}
