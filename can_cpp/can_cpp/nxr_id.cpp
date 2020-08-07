#include "nxr_id.h"
#include <iostream>

using namespace std;

nxr_id encode(nxr_id x) {
    x.id = 0;
    x.prono = x.prono & 0x01FF;
    x.id += x.prono;
    x.id = x.id << 1;
    x.id += x.ptp;
    x.id = x.id << 8;
    x.id += x.dst;
    x.id = x.id << 8;
    x.id += x.src;
    x.id = x.id << 3;
    x.grp = x.grp & 0x7;
    x.id += x.grp;
    return x;
}

nxr_id decode(nxr_id x) {
    //unsigned int buf = x.id;
    //x.grp = buf & 0x07;
    x.grp = (x.id & 0x7);
    x.src = (x.id >> 3) & 0xFF;
    x.dst = (x.id >> 11) & 0xFF;
    x.ptp = (x.id >> 19) & 0x1;
    x.prono = (x.id >> 20) & 0x1FF;
    return x;
}


void print_ex_id(nxr_id x) {
    unsigned int id = x.id;
    cout << hex << (int)x.prono << " " << (int)x.ptp << " ";
    cout << (int)x.dst << " " << (int)x.src << " " << (int)x.grp << endl;
    int split[] = { 2, 10, 18, 19 };
    for (int i = 0; i < 29; i++) {
        cout << (((id << i) & 0x10000000) / 0x10000000);
        if ((i == 8) || (i == 9) || (i == 17) || (i == 25)) {
            cout << " ";
        }
    }
    cout << endl;
}
