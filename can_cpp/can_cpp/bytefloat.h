#ifndef BYTEFLOAT_H
#define BYTEFLOAT_H
#pragma once
typedef unsigned char byte;
typedef union bytef bytef;
union bytef {
    float f;
    byte b[4];
};
void float2byte(float f, byte* b);
float byte2float(byte* b);

#endif