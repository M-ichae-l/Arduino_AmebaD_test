#include "image.h"
#include "epdif.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1

EpdIf EPD;
unsigned char image[1024];
Paint paint(image, 0, 0);     // width should be the multiple of 8
unsigned long time_start_ms;
unsigned long time_now_s;

void setup() {
    pinMode(BUSY_Pin, INPUT);   // BUSY_Pin    8
    pinMode(RES_Pin, OUTPUT);   // RES_Pin     9
    pinMode(DC_Pin, OUTPUT);    // DC_Pin     10
    pinMode(CS_Pin, OUTPUT);    // CS_Pin     11
    pinMode(SCK_Pin, OUTPUT);   // SCK_Pin    12
    pinMode(SDI_Pin, OUTPUT);   // SDI_Pin    13
}

void loop() {
    DisplayText();
    EPD.EPD_Sleep();
}

void DisplayText(void) {
    EPD.EPD_SetRAMValue_BaseMap(gImage_basemapNA);

    paint.SetRotate(ROTATE_0);
    paint.SetWidth(128);
    paint.SetHeight(24);

    paint.Clear(COLORED);
    paint.DrawStringAt(0, 4, "Hello Ameba", &Font16, UNCOLORED);
    EPD.EPD_SetFrame(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());

    paint.Clear(UNCOLORED);
    paint.DrawStringAt(0, 4, "1234567890", &Font16, COLORED);
    EPD.EPD_SetFrame(paint.GetImage(), 0, 40, paint.GetWidth(), paint.GetHeight());

    paint.Clear(COLORED);
    paint.DrawStringAt(0, 4, "+_*/><:*&^%", &Font16, UNCOLORED);
    EPD.EPD_SetFrame(paint.GetImage(), 0, 70, paint.GetWidth(), paint.GetHeight());

    EPD.EPD_UpdateDisplay();
}
