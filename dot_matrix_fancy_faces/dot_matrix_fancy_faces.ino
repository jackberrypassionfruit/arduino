#include "LedControl.h"
#include "binary.h"

// LedControl lc=LedControl(12,11,10,1);

#define PIN_DIN 1
#define PIN_CS  22
#define PIN_CLK 23

struct Face {
  char emotion[10];
  int pixels[9];
};

LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_CS, 1);

// delay time between faces
unsigned long delaytime=1000;

// // happy face
// byte hf[8]= {B00111100, B01000010, B10010101, B10100001, B10100001, B10010101, B01000010, B00111100};
// neutral face
byte nf[8]= {B00111100, B01000010, B10010101, B10010001, B10010001, B10010101, B01000010, B00111100};
// sad face
byte sf[8]= {B00111100, B01000010, B10100101, B10010001, B10010001, B10100101, B01000010, B00111100};

// happy face
byte hf[8];
int hf_int[8]= {00111100, 01000010, 10010101, 10100001, 10100001, 10010101, 01000010, 00111100};
// // neutral face
// int nf_int[8]= {00111100, 01000010, 10010101, 10010001, 10010001, 10010101, 01000010, 00111100};
// // sad face
// int sf_int[8]= {00111100, 01000010, 10100101, 10010001, 10010001, 10100101, 01000010, 00111100};

// void turn_frown_upside_down(int face[8]) {
//   int face_rotated[8];

//   // copy the array
//   // for testing
//   for (int i = 0; i < (sizeof(face) / sizeof(face[0])); i++) {
//     face_rotated[i] = face[i];
//   }

//   // convert array from int[] to byte[]
//   for (int i = 0; i < (sizeof(face_rotated) / sizeof(face_rotated[0])); i++) {
//     hf[i] = byte(face_rotated[i]);
//   }
// }


void setup() {
  Serial.begin(115200);
  Serial.println("Test");
  // turn_frown_upside_down(hf_int);
  for (int i = 0; i < (sizeof(hf_int) / sizeof(hf_int[0])); i++) {
    hf[i] = byte(hf_int[i]);
  }
  
  Serial.print("int hf_int[0]");
  Serial.print(hf_int[0]);
  Serial.print("byte hf[0]");
  Serial.print(int(hf[0]));
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,2);
  // Clear the display
  lc.clearDisplay(0);  
}

void drawFaces(){
  // Display sad face
  for (int i = 0; i<=7; i++) {
    lc.setRow(0,i,sf[i]);
  } 
  delay(delaytime);
  
  // Display neutral face
  for (int i = 0; i<=7; i++) {
    lc.setRow(0,i,nf[i]);
  }
  delay(delaytime);
  
  // Display happy face
  for (int i = 0; i<=7; i++) {
    lc.setRow(0,i,hf[i]);
  }
  delay(delaytime);
}

void loop(){
  drawFaces();
}
