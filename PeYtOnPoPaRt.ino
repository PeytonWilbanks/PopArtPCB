#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(20, 0, NEO_GRB + NEO_KHZ800);
#include <Bounce2.h>
Bounce button = Bounce();

int numGrid = 20;
int numFrames = 3;
int Pin = 1;
int specialTimer = 500;
int switchVal = 0;
long beginTime = millis();
int timerInterval = 100;
int colores;
int whichFrame = 0;
boolean atEnd = false;

char index[20] {

                   0,
                   1,
               2,  3,  4,      5,
           6,  7,  8,  9,  10, 11, 12,
           13, 14, 15, 16, 17, 18, 19,
           
};

char colors[4][3] {
    {0, 0, 0},//black 0
  
    {255, 255, 255},//white 1
  
    {0, 0, 255},// blue 2
  
    {0, 0, 100},// less blue 3
};

char frames[3][20] {   
        {
                   1,
                   1,
                3, 2, 3,    3,
             3, 2, 2, 2, 3, 2, 3,
             3, 2, 2, 2, 2, 2, 3,
           
        },
        {
                   1,
                   1,
                1, 1, 1,    1,
             3, 2, 2, 2, 3, 2, 3,
             3, 2, 2, 2, 2, 2, 3,
        },
        {
                   1,
                   1,
               1, 1, 1,    1,
             1, 1, 2, 1, 2, 1, 1,
             1, 2, 1, 2, 1, 2, 1,
        },
   
};


void setup() {
  strip.begin();
  
  strip.show();
  
  button.attach(Pin, INPUT);
  
  button.interval(20);
}

void loop() {
  button.update();
  if (button.rose()) {
      switchVal++;
}
  if (switchVal > 2) {
      switchVal = 0;
}

switch (switchVal) {
    
    case 0:
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setBrightness(100);
        
        strip.setPixelColor(i, 0, 0, 0);
        
        strip.show();
 }
 break;

    case 1:
      if (millis() - beginTime > timerInterval) {
        colores += 255 * 5;
        
        strip.rainbow(colores);
        
        strip.show();
        
        beginTime = millis();
 }
      if (colores > 65536 * 5) {
        
        colores = 0;
 }
 break;

    case 2:
      if (millis() - beginTime > specialTimer) {
        for (int i = 0; i < numGrid; i++) {
        int whichLED = i;
          
        int whichIndex = index[whichLED];
          
        int whichColor = frames[whichFrame][whichLED];
          
        int r = colors[whichColor][0];
          
        int g = colors[whichColor][1];
          
        int b = colors[whichColor][2];
          
          strip.setPixelColor(whichIndex, r, g, b); 
}
        
        if(whichFrame < numFrames){
          whichFrame++;
} 
        
        if(whichFrame > 2){
          whichFrame = 0;
}
        
        beginTime = millis();
        strip.show();
    }
 break;
  }
}
