#include "nxr_can.h"
#include <iostream>
using namespace std;


void nxr_encode(P_NXR_ID *n_id, P_NXR_DATA *n_data){
	nxr_id_encode(*n_id);
	nxr_data_encode(*n_data);
}

void nxr_decode(P_NXR_ID *n_id, P_NXR_DATA *n_data){
	
}

void nxr_print_frame(P_NXR_ID *n_id, P_NXR_DATA *n_data){
	
}

void nxr_id_encode(P_NXR_ID *x){
	*x.id = 0;
    *x.prono = *x.prono & 0x01FF;
    *x.id += *x.prono;
    *x.id = *x.id << 1;
    *x.id += *x.ptp;
    *x.id = *x.id << 8;
    *x.id += *x.dst;
    *x.id = *x.id << 8;
    *x.id += *x.src;
    *x.id = *x.id << 3;
    *x.grp = *x.grp & 0x7;
    *x.id += *x.grp;
	return
}

void nxr_data_encode(P_NXR_DATA *x) {
	*x.data_array[0] = *x.func;
	*x.data_array[1] = 0x0;
	shortbyte y;
	y.usi = *x.reg;
	*x.data_array[2] = *y.b[0];
	*x.data_array[3] = *y.b[1];
	byte_data buf;
	if (*x.isfloat) {
		buf.f = *x.float_data;
		for (int i = 0; i < 4; i++) *x.data_array[7 - i] = buf.b[i];
	}
	else {
		buf.i = *x.int_data;
		for (int i = 0; i < 4; i++) *x.data_array[4 + i] = buf.b[i];
	}
	return
}