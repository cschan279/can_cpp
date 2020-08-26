#ifndef NXR_CAN_H
#define NXR_CAN_H

	#ifdef NXR_CAN_EXPORTS
		#define NXR_CAN_CONV __declspec(dllexport)
	#else
		#define NXR_CAN_CONV __declspec(dllimport)
	#endif

typedef unsigned char       BYTE;
typedef unsigned int        UINT;
typedef unsigned short		USHORT;


union shortbyte {
	USHORT usi;
	BYTE b[2];
};

union databyte {
	float f;
	unsigned int i;
	BYTE b[4];
};

typedef struct _nxr_data {
	BYTE func;
	bool errc;
	USHORT reg;
	bool isfloat;
	float float_data;
	UINT int_data;
	BYTE data_array[8];
	bool fault;
} NXR_DATA, *P_NXR_DATA;

typedef struct _nxr_id {
	USHORT prono = 0x60;
	bool ptp = true;
	BYTE dst;
	BYTE src;
	BYTE grp;
	USHORT id;
} NXR_ID, *P_NXR_ID;

typedef struct _VCI_CAN_OBJ{
	UINT ID;
	UINT TimeStamp;
	BYTE TimeFlag;
	BYTE SendType;
	BYTE RemoteFlag;//is remote frame
	BYTE ExternFlag;//is extend frame
	BYTE DataLen;
	BYTE Data[8];
	BYTE Reserved[3];
}VCI_CAN_OBJ, *PVCI_CAN_OBJ;


extern "C" NXR_CAN_CONV void nxr_encode(P_NXR_ID *n_id, P_NXR_DATA *n_data);
extern "C" NXR_CAN_CONV void nxr_decode(P_NXR_ID *n_id, P_NXR_DATA *n_data);
extern "C" NXR_CAN_CONV void nxr_print(P_NXR_ID *n_id, P_NXR_DATA *n_data);

extern "C" NXR_CAN_CONV void nxr_id_encode(P_NXR_ID* n_id);
extern "C" NXR_CAN_CONV void nxr_id_decode(P_NXR_ID* n_id);
extern "C" NXR_CAN_CONV void nxr_id_print(P_NXR_ID* n_id);

extern "C" NXR_CAN_CONV void nxr_data_encode(P_NXR_DATA* n_data);
extern "C" NXR_CAN_CONV void nxr_data_decode(P_NXR_DATA* n_data);
extern "C" NXR_CAN_CONV void nxr_data_print(P_NXR_DATA* n_data);

#endif