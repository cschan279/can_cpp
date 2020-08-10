#include <iostream>
//#include <array>
#include <cstring>
#include "bytefloat.h"
#include "nxr_id.h"
#include "nxr_data.h"
#include "main.h"

using namespace std;



int main() {
    /*
    byte z[4];
    float2byte(1.2f, z);
    //byte z[4] = y.arr;
    for (int i=0; i<4;i++) cout << hex << (int)z[i] << ' ';
    cout << endl;
    byte a[4] = {0x3f, 0x99, 0x99, 0x9a};
    float c = byte2float(a);
    
    cout << c << endl;
    cout << "###########" << endl;
    
    nxr_id test1;
    test1.ptp = true;
    test1.dst = 0x1;
    test1.src = 0xf0;
    test1.grp = 0x3;
    nxr_id test2 = encode(test1);
    print_ex_id(test2);
    */
    nxr_data test;
    byte data[] = { 0x41, 0xf0, 0x00, 0x01, 0x44, 0x2f, 0x00, 0x00 };
    for (int i = 0; i < 8; i++) test.data_array[i] = data[i];
    nxr_data test_res = decode(test);
    print_nxr_data(test_res);


    return 0;
}
