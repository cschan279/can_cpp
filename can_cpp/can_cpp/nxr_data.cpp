#include "nxr_data.h"
#include <iostream>

nxr_data encode(nxr_data x) {
	x.data_array[0] = x.func;
	x.data_array[1] = 0x0;
	shortbyte y;
	y.usi = x.reg;
	x.data_array[2] = y.b[0];
	x.data_array[2] = y.b[1];
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

//nxr_data decode()