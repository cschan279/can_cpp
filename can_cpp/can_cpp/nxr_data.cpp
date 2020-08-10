#include "nxr_data.h"
#include <iostream>
using namespace std;

nxr_data encode(nxr_data x) {
	x.data_array[0] = x.func;
	x.data_array[1] = 0x0;
	shortbyte y;
	y.usi = x.reg;
	x.data_array[2] = y.b[0];
	x.data_array[3] = y.b[1];
	byte_data buf;
	if (x.isfloat) {
		buf.f = x.float_data;
		for (int i = 0; i < 4; i++) x.data_array[7 - i] = buf.b[i];
	}
	else {
		buf.i = x.int_data;
		for (int i = 0; i < 4; i++) x.data_array[4 + i] = buf.b[i];
	}
	return x;
}

nxr_data decode(nxr_data x) {
	x.func = x.data_array[0];
	x.errc = (x.data_array[1] != 0xf0);
	shortbyte y;
	y.b[0] = x.data_array[2];
	y.b[1] = x.data_array[3];
	x.reg = y.usi;
	/*~~~~~early escape~~~~~*/
	if (x.errc) return x;
	/*~~~~~early escape~~~~~*/
	byte_data z;
	if (x.func == 0x41) {
		x.isfloat = true;
		for (int i = 0; i < 4; i++) z.b[3 - i] = x.data_array[i+4];
		x.float_data = z.f;
		x.fault = false;
	}
	else if (x.func == 0x42) {
		x.isfloat == false;
		for (int i = 0; i < 4; i++) z.b[i] = x.data_array[i + 4];
		x.int_data = z.i;
		x.fault = false;
	}
	else {
		x.fault = true; // unknown data_type
	}
	return x;
}

/*
struct nxr_data {
	byte func;
	bool errc; // true(error) if not equal to 0xf0
	unsigned short int reg;
	bool isfloat;
	float float_data;
	unsigned int int_data;
	byte data_array[8];
	bool fault; // true if problem during decode
};
*/

void print_nxr_data(nxr_data x) {
	if (x.errc) printf("error frame\n");
	else if (x.fault) printf("unknown data type\n");
	else {
		if (x.isfloat) {
			printf("Float data for %x: %f\n", x.reg, x.float_data);
		}
		else {
			printf("Int data for %x: %i\n", x.reg, x.int_data);
		}
	}
	for (int i = 0; i < 8; i++) { 
		
		printf("%02x", x.data_array[i]);
		if (i == 0 || i == 1 || i == 3) printf(" ");
	}
	printf("\n");
}