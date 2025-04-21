#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_SCLK 2
#define TFT_MOSI 3
#define TFT_RST 10
#define TFT_CS 7
#define TFT_DC 6

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


void setup() {
  // put your setup code here, to run once:
  tft.initR(INITR_BLACKTAB);  // initialize a ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
