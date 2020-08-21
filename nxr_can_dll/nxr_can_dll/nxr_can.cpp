#include "pch.h"
#include "nxr_can.h"
#include <iostream>
using namespace std;


void nxr_encode(P_NXR_ID *n_id, P_NXR_DATA *n_data){
	nxr_id_encode(n_id);
	nxr_data_encode(n_data);
}

void nxr_decode(P_NXR_ID *n_id, P_NXR_DATA *n_data){
	nxr_id_decode(n_id);
	nxr_data_decode(n_data);
}

void nxr_print(P_NXR_ID *n_id, P_NXR_DATA *n_data){
	nxr_id_print(n_id);
	nxr_data_print(n_data);
}

void nxr_id_encode(P_NXR_ID *x){
	(*x)->id = 0;
    (*x)->prono = (*x)->prono & 0x01FF;
	(*x)->id += (*x)->prono;
	(*x)->id = (*x)->id << 1;
	(*x)->id += (*x)->ptp;
	(*x)->id = (*x)->id << 8;
	(*x)->id += (*x)->dst;
	(*x)->id = (*x)->id << 8;
	(*x)->id += (*x)->src;
	(*x)->id = (*x)->id << 3;
	(*x)->grp = (*x)->grp & 0x7;
	(*x)->id += (*x)->grp;
	return;
}

void nxr_data_encode(P_NXR_DATA *x) {
	(*x)->data_array[0] = (*x)->func;
	(*x)->data_array[1] = 0x0;
	shortbyte y;
	y.usi = (*x)->reg;
	(*x)->data_array[2] = y.b[0];
	(*x)->data_array[3] = y.b[1];
	databyte buf;
	if ((*x)->isfloat) {
		buf.f = (*x)->float_data;
		for (int i = 0; i < 4; i++) (*x)->data_array[7 - i] = buf.b[i];
	}
	else {
		buf.i = (*x)->int_data;
		for (int i = 0; i < 4; i++) (*x)->data_array[4 + i] = buf.b[i];
	}
	return;
}


void nxr_id_decode(P_NXR_ID* x) {
	UINT id = (*x)->id;
	(*x)->grp = (id & 0x7);
	(*x)->src = (id >> 3) & 0xFF;
	(*x)->dst = (id >> 11) & 0xFF;
	(*x)->ptp = (id >> 19) & 0x1;
	(*x)->prono = (id >> 20) & 0x1FF;
	return;
}

void nxr_data_decode(P_NXR_DATA* x) {
	(*x)->func = (*x)->data_array[0];
	(*x)->errc = ((*x)->data_array[1] != 0xf0);
	shortbyte y;
	y.b[0] = (*x)->data_array[2];
	y.b[1] = (*x)->data_array[3];
	(*x)->reg = y.usi;
	/*~~~~~early escape~~~~~*/
	if ((*x)->errc) return;
	/*~~~~~early escape~~~~~*/
	databyte z;
	if ((*x)->func == 0x41) {
		(*x)->isfloat = true;
		for (int i = 0; i < 4; i++) z.b[3 - i] = (*x)->data_array[i + 4];
		(*x)->float_data = z.f;
		(*x)->fault = false;
	}
	else if ((*x)->func == 0x42) {
		(*x)->isfloat = false;
		for (int i = 0; i < 4; i++) z.b[i] = (*x)->data_array[i + 4];
		(*x)->int_data = z.i;
		(*x)->fault = false;
	}
	else {
		(*x)->fault = true; // unknown data_type
	}
	return;
}

void nxr_id_print(P_NXR_ID* x) {
	printf("\n====================\n");
	UINT id = (*x)->id;
	printf("%03x %01x ", (*x)->prono, (*x)->ptp);
	printf("%02x %02x %01x\n", (*x)->dst, (*x)->src, (*x)->grp);
	int split[] = { 2, 10, 18, 19 };
	for (int i = 0; i < 29; i++) {
		printf("%x", (((id << i) & 0x10000000) / 0x10000000));
		if ((i == 8) || (i == 9) || (i == 17) || (i == 25)) {
			printf(" ");
		}
	}
	printf("\n~~~~~~~~~~~~~~~~~~~~\n");
}

void nxr_data_print(P_NXR_DATA* x) {
	if ((*x)->errc) printf("error frame\n");
	else if ((*x)->fault) printf("unknown data type\n");
	else {
		if ((*x)->isfloat) {
			printf("Float data for %x: %f\n", (*x)->reg, (*x)->float_data);
		}
		else {
			printf("Int data for %x: %i\n", (*x)->reg, (*x)->int_data);
		}
	}
	for (int i = 0; i < 8; i++) {
		printf("%02x ", (*x)->data_array[i]);
		if (i == 0 || i == 1 || i == 3) printf(" | ");
	}
	printf("\n====================\n");
}
