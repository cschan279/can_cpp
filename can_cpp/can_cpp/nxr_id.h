#ifndef NXR_ID_H
#define NXR_ID_H
typedef unsigned char byte;

struct nxr_id {
    int prono = 0x60;
    bool ptp = true;
    byte dst = 0xf0;
    byte src = 0x00;
    byte grp = 0x00;
    unsigned int id = 0;
};

nxr_id encode(nxr_id x);
nxr_id decode(nxr_id x);
void print_ex_id(nxr_id x);

#endif