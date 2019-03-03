#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>


#include <Adafruit_NeoMatrix.h>
#include <gamma.h>



#define PIN 6

struct color{
    int r;
    int g;
    int b;
  };
typedef struct color Color;


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(100);
  matrix.setTextColor(colors[0]);
}
int x    = matrix.width();
int pass = 0;
char* message = "This is the message";
int offset = 8*strlen(message);

void loop() {
    matrix.fillScreen(matrix.Color(0,0,150));
    matrix.setCursor(x, 0);
    matrix.setTextColor(matrix.Color(255,255,0));
    matrix.print(message);
    matrix.show();    
  if(--x < -offset) {
    x = matrix.width();
    if(++pass > 5)
      pass = 0;
  }
  delay(50);
}

void printText(Color background, Color text, char* msg){
    matrix.fillScreen(matrix.Color(background.r,background.g,background.b));
    matrix.setCursor(x, 0);
    matrix.setTextColor(matrix.Color(text.r,text.g,text.b));
    matrix.print(message);
    matrix.show();  
  }
