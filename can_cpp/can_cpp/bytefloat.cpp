#include "bytefloat.h"

//typedef unsigned char byte;


void float2byte(float f, byte* b) {

    bytef buf;
    buf.f = f;

    for (int i = 0; i < 4; i++) {
        b[3 - i] = buf.b[i];
    }
}
float byte2float(byte* b) {
    bytef buf;

    for (int i = 0; i < 4; i++) {
        buf.b[3 - i] = *(b + i);
    }
    return buf.f;
}