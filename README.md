CRCTool
=======

This is the CRC-32 tool I wrote for university homework.

Dependencies
------------

This program has the following requirements:
- C++11 compiler (GCC 4.6+, Clang 3.0+, MSVC 11+)
- CMake 2.8.9 or newer
- Qt5 Framework

Building
--------

I recommend to set the following CMake variables:
- *CMAKE_INSTALL_PREFIX* - Path for `make install`
- *CMAKE_PREFIX_PATH* - Qt5 directory

You have to run CRCTool in the install directory if
you want the language files to load correctly.
`cd crctool/dist && ./CRCTool`
