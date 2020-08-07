#ifndef NXR_DATA_H
#define NXR_DATA_H
typedef unsigned char byte;

typedef union shortbyte shortbyte;

union shortbyte {
	unsigned short int usi;
	byte b[2];
};

union byte_data {
	float f;
	unsigned int i;
	byte b[4];
};
struct nxr_data {
	byte func;
	byte errc;
	unsigned short int reg;
	bool isfloat;
	float float_data;
	unsigned int int_data;
	byte data_array[8];
};

#endif