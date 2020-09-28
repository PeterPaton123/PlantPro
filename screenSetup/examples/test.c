
#include "EPD_Test.h"
#include "EPD_2in7b.h"
#include "plant.h"

#include <time.h>
#include <string.h>
#include <stdbool.h>

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
/*
plant *plantConstructor(char *name, int days, bool watered) {
  plant *plt = malloc(sizeof(plant));
  if (plt == NULL) {
    printf("Plant %s malloc failed", name);
  }
  plt->name = calloc(strlen(name) + 1, sizeof(char));
  plt->name = strcpy(plt->name, name);
  plt->daysToWater = days;
  plant *plantConstructor(char *name, int days, bool watered) {
    plant *plt = malloc(sizeof(plant));
    if (plt == NULL) {
      printf("Plant %s malloc failed", name);
    }
    plt->name = calloc(strlen(name) + 1, sizeof(char));
    plt->name = strcpy(plt->name, name);
    plt->daysToWater = days;
    plt->watered = watered;
    return plt;
  }

  plant **plantInitialise() {
    plant **plants = calloc(NO_OF_PLANTS, sizeof(plant*));
    if (plants == NULL) {
      printf("Plants array initialisation failed");
    }
    plants[0] = plantConstructor("plant 1", 0, true);
    plants[1] = plantConstructor("p2", 0, false);
    plants[2] = plantConstructor("plant number three", 0, true);
    plants[3] = plantConstructor("plant 4", 0, false);
    plants[4] = plantConstructor("plant 5", 0, false);
    return plants;
  }

  void plantWrite(UBYTE *black, UBYTE *red, int x, int y, plant *plt) {
    Paint_SelectImage(black);
    Paint_DrawPoint(x, y+7, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawString_EN(x + 7, y, plt->name, &Font12, WHITE, BLACK);
    Paint_SelectImage(red);
    printf("string length %d\n", strlen(plt->name) * 4 + x + 3);
    Paint_DrawLine(x + 5 , y + 15,(strlen(plt->name)*7) + (x + 5 + 7), y+15, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    return;
  }plt->watered = watered;
  return plt;
}

plant **plantInitialise() {
  plant **plants = calloc(NO_OF_PLANTS, sizeof(plant*));
  if (plants == NULL) {
    printf("Plants array initialisation failed");
  }
  plants[0] = plantConstructor("plant 1", 0, true);
  plants[1] = plantConstructor("p2", 0, false);
  plants[2] = plantConstructor("plant number three", 0, true);
  plants[3] = plantConstructor("plant 4", 0, false);
  plants[4] = plantConstructor("plant 5", 0, false);
  return plants;
}

void plantWrite(UBYTE *black, UBYTE *red, int x, int y, plant *plt) {
  Paint_SelectImage(black);
  Paint_DrawPoint(x, y+7, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT); 
  Paint_DrawString_EN(x + 7, y, plt->name, &Font12, WHITE, BLACK);
  Paint_SelectImage(red);
  printf("string length %d\n", strlen(plt->name) * 4 + x + 3);
  Paint_DrawLine(x + 5 , y + 15,(strlen(plt->name)*7) + (x + 5 + 7), y+15, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  return;
}
*/


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
 
#if 1   // Drawing on the image
    /*Horizontal screen*/
    //1.Draw black image
    /*    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawString_CN(130, 20, "Î¢Ñ©µç×Ó", &Font24CN, WHITE, BLACK);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

    //2.Draw red image
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawCircle(160, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(210, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawString_CN(130, 0,"ÄãºÃabc", &Font12CN, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    */

    //Paint_SelectImage(RedImage);
    printf("Start UI \n");
    Paint_DrawRectangle(1, 1, 70, 55, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);   
    Paint_DrawLine(70, 1, 70, 175, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(1, 95, 69, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(1, 135, 69, 135, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    getTime();
    //    EPD_2IN7B_Display(BlackImage, RedImage);
    /* delay(10000);
       getTime();
    */

    Paint_SelectImage(BlackImage);
    //Paint_DrawRectangle(8, 28, 256, 160, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(92, 8, "Tjasa's plants", &Font16, WHITE, BLACK);
    Paint_DrawLine(82, 28, 260, 28, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    plant **plants = plantInitialise();

    plantWrite(BlackImage, RedImage, 87, 35, plants[0]);
    plantWrite(BlackImage, RedImage, 87, 60, plants[1]);
    plantWrite(BlackImage, RedImage, 87, 85, plants[2]);

    
    printf("EPD_Display\r\n");
    EPD_2IN7B_Display(BlackImage, RedImage);
    DEV_Delay_ms(4000);
#endif

    printf("Clear...\r\n");
    //    EPD_2IN7B_Clear();

    printf("Goto Sleep...\r\n");
    //EPD_2IN7B_Sleep();
    free(BlackImage);
    BlackImage = NULL;

    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    
    return 0;

}
