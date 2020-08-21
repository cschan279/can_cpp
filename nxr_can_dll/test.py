from ctypes import *
class P_NXR_ID(Structure):
    _fields_ = [("func", c_ubyte),
                ("errc", c_bool),("reg", c_ushort),
                ("isfloat",c_bool),
                ("float_data",c_float),
                ("int_data",c_uint),
                ("data_array",c_ubyte),
                ("fault",c_bool)]


dll_file = windll.LoadLibrary("./x64/Debug/nxr_can_dll.dll")

print(dir(dll_file))