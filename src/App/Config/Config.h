#pragma once

struct Resolution
{
    unsigned short int width;
    unsigned short int height;
};

struct Config
{
    Resolution resolution;
    unsigned char fpsRate;          // 0 <= fpsRate <= 255
    unsigned short int moveAmount;  // 0 <= moveAmount <= 65535
};