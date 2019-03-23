// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 
#include "Arduino.h"
#include "ShakeUI.h"
#include "SystemTickCounter.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shake shake icon
static const unsigned char smallTweet [] = 
{
    0x00,0x00,0x38,0xf0,0xe0,0xe0,0xc0,0xc0,0xf0,0xfc,0xfa,0xfa,0xd8,0xf0,0xe0,0x80,
    0x40,0x00,
    0x00,0x04,0x08,0x18,0x19,0x3b,0x3f,0x3f,0x3f,0x3f,0x3f,0x1f,0x1f,0x0f,0x07,0x01,
    0x01,0x00,
};

void DrawAppTitle(const char* text)
{
    char sz[32];
    snprintf(sz, 32, "   %s", text);
    Screen.print(0, sz);
    Screen.draw(0, 0, 18, 2, (unsigned char*)smallTweet);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shake shake animation
static const unsigned char shakeImag1 [] =
{
    0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,0x38,0x9C,0xDE,0xEF,0x77,0x76,0xB0,0x80,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0x70,0x70,0x70,0x78,0x38,0x38,0x78,0xF8,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x06,0x87,0xC3,0xF9,0xFE,0x7F,0x7F,0x7F,0x73,0xE3,0xE1,0xE1,0xC1,0x81,0x00,0xC0,0xE0,0xF0,0x38,0x18,0x1C,0x1C,0x0C,0x0F,0x8F,0x8F,0x8E,0xFC,0xFC,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x07,0x01,0x00,0x00,0x70,0xF0,0xE0,0xE0,0x61,0x61,0x63,0xE3,0xFF,0x7E,0x79,0xFF,0xCF,0x86,0xC7,0xC7,0xC7,0xC3,0xC3,0xE3,0x61,0x63,0x73,0x7F,0xFE,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xF7,0xFF,0x3F,0x18,0x00,0x00,0x00,0x07,0x7F,0xFF,0xFC,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x01,0x1F,0x3F,0xB1,0xF1,0x70,0x30,0x30,0x18,0x18,0x18,0x1C,0x1F,0xFF,0xF3,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x38,0x7C,0xFE,0xFE,0xEF,0xC7,0x83,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xFF,0xFF,0xFF,0xF0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xE3,0xE7,0xE6,0xEE,0xEC,0xEE,0xE6,0x76,0x7F,0x7F,0xBF,0xCF,0xF0,0x7C,0x3C,0xC0,0xF8,0xFC,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x0F,0x1E,0x3C,0x78,0xF8,0xF0,0xF0,0xF8,0x7C,0x3F,0x1F,0x07,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x09,0x1D,0x0E,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

static const unsigned char shakeImag2 [] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,0x38,0x9C,0xDE,0xEF,0x77,0x76,0xB0,0x80,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0x70,0x70,0x70,0x78,0x38,0x38,0x78,0xF8,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x06,0x87,0xC3,0xF9,0xFE,0x7F,0x7F,0x7F,0x73,0xE3,0xE1,0xE1,0xC1,0x81,0x00,0xC0,0xE0,0xF0,0x38,0x18,0x1C,0x1C,0x0C,0x0F,0x8F,0x8F,0x8E,0xFC,0xFC,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x07,0x01,0x00,0x00,0x70,0xF0,0xE0,0xE0,0x61,0x61,0x63,0xE3,0xFF,0x7E,0x79,0xFF,0xCF,0x86,0xC7,0xC7,0xC7,0xC3,0xC3,0xE3,0x61,0x63,0x73,0x7F,0xFE,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xF7,0xFF,0x3F,0x18,0x00,0x00,0x00,0x07,0x7F,0xFF,0xFC,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x01,0x1F,0x3F,0xB1,0xF1,0x70,0x30,0x30,0x18,0x18,0x18,0x1C,0x1F,0xFF,0xF3,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x38,0x7C,0xFE,0xFE,0xEF,0xC7,0x83,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xFF,0xFF,0xFF,0xF0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xE3,0xE7,0xE6,0xEE,0xEC,0xEE,0xE6,0x76,0x7F,0x7F,0xBF,0xCF,0xF0,0x7C,0x3C,0xC0,0xF8,0xFC,0x38,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x0F,0x1E,0x3C,0x78,0xF8,0xF0,0xF0,0xF8,0x7C,0x3F,0x1F,0x07,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x09,0x1D,0x0E,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,
};

static const unsigned char shakeImag3 [] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,0x38,0x9C,0xDE,0xEF,0x77,0x76,0xB0,0x80,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0x70,0x70,0x70,0x78,0x38,0x38,0x78,0xF8,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x06,0x87,0xC3,0xF9,0xFE,0x7F,0x7F,0x7F,0x73,0xE3,0xE1,0xE1,0xC1,0x81,0x00,0xC0,0xE0,0xF0,0x38,0x18,0x1C,0x1C,0x0C,0x0F,0x8F,0x8F,0x8E,0xFC,0xFC,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x07,0x01,0x00,0x00,0x70,0xF0,0xE0,0xE0,0x61,0x61,0x63,0xE3,0xFF,0x7E,0x79,0xFF,0xCF,0x86,0xC7,0xC7,0xC7,0xC3,0xC3,0xE3,0x61,0x63,0x73,0x7F,0xFE,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xF7,0xFF,0x3F,0x18,0x00,0x00,0x00,0x07,0x7F,0xFF,0xFC,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x01,0x1F,0x3F,0xB1,0xF1,0x70,0x30,0x30,0x18,0x18,0x18,0x1C,0x1F,0xFF,0xF3,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x7C,0xFE,0xFE,0xEF,0xC7,0x83,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xFF,0xFF,0xFF,0xF0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xE3,0xE7,0xE6,0xEE,0xEC,0xEE,0xE6,0x76,0x7F,0x7F,0xBF,0xCF,0xF0,0x7C,0x3C,0xC0,0xF8,0xFC,0x38,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x0F,0x1E,0x3C,0x78,0xF8,0xF0,0xF0,0xF8,0x7C,0x3F,0x1F,0x07,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x09,0x1D,0x0E,0x0F,0x07,0x03,0x00,0x00,
};

static const unsigned char* listShake[4] = { shakeImag1, shakeImag2, shakeImag3, shakeImag1 };
static  int idx = 0;

void DrawShakeAnimation(void)
{
    idx = (idx + 1) % 4;
    Screen.draw(35, 2, 35 + 54, 8, (unsigned char*)listShake[idx]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Checkbox
static const unsigned char imgCheckbox1 [] = 
{
    0x00,0x00,0xfc,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0xfc,0x00,0x00,
    0x00,0x00,0x3f,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3f,0x00,0x00
};

static const unsigned char imgCheckbox2 [] = 
{
    0x00,0x00,0xfc,0x04,0x84,0x84,0x04,0x04,0x84,0x84,0x44,0x24,0x04,0xfc,0x00,0x00,
    0x00,0x00,0x3f,0x20,0x20,0x21,0x23,0x23,0x21,0x20,0x20,0x20,0x20,0x3f,0x00,0x00
};

void DrawCheckBox(int line, int col, int status)
{
    if (status == 0)
    {
        Screen.draw(col, line * 2, col + 16, line * 2 + 2, (unsigned char*)imgCheckbox1);
    }
    else
    {
        Screen.draw(col, line * 2, col + 16, line * 2 + 2, (unsigned char*)imgCheckbox2);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Incoming tweet
static const unsigned char newTweet [] = 
{
    0x00,0x00,0x00,0x00,0xc0,0xc0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x80,0xf0,0xf0,0xf8,0xdc,0xcc,0xcc,0xcc,0xc0,0xc0,0x80,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x0f,0x1f,0xff,0xff,0xfe,0xfc,0xfc,0xfc,0xf8,0xf0,0xf0,0xf8,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,0xf3,0xff,0xff,0xfe,0xfc,0xe0,
    0xe0,0x60,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf3,0xf3,0xcf,0xcf,
    0xcf,0xcf,0x3f,0x3f,0x3f,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0x3f,0x3f,0x3f,0x3f,0xcf,0xcf,0xcf,0xcf,0xf3,0xf3,0x00,0x00,
    0x00,0x00,0x30,0x70,0xe0,0xc0,0xc0,0xc1,0xc3,0xc7,0xcf,0xef,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0x07,
    0x03,0x07,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xfc,0xfc,0xfc,0xf3,0xf3,0xfc,0xfc,0xfe,0xfe,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x03,0x07,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,
    0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x07,0x03,0x03,0x03,0x01,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,
    0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
    0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00
};

static const unsigned char bigCry [] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0xf0,0xf0,0xf8,0xf8,0xfc,0xfc,0xfc,
    0xfc,0xfc,0xfc,0xf8,0xf8,0xf0,0xf0,0xe0,0xc0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xe0,0xf8,0xfe,0xff,0xff,0xe7,0xc3,0x81,0x81,0xc3,0xe7,0xff,0xff,0xff,
    0xff,0xff,0xff,0xe7,0xc3,0x81,0x81,0xc3,0xe7,0xff,0xff,0xfe,0xf8,0xe0,0x00,0x00,
    0x00,0x00,0x07,0x1f,0x7f,0xff,0xff,0xdf,0x8f,0x87,0xc3,0xe3,0xf1,0xf1,0xf8,0xf8,
    0xf8,0xf8,0xf1,0xf1,0xe3,0xc3,0x87,0x8f,0xdf,0xff,0xff,0x7f,0x1f,0x07,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0f,0x0f,0x1f,0x1f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x1f,0x1f,0x0f,0x0f,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00
};

void DrawTweetImage(int line, int col, int status)
{
    if (status == 0)
    {
        Screen.draw(col + 20, line * 2, col + 52, line * 2 + 4, (unsigned char*)bigCry);
    }
    else 
    {
        Screen.draw(col, line * 2, col + 76, line * 2 + 4, (unsigned char*)newTweet);
    }
}