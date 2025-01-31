# Hot Reloading in C

Hot Reloading is useful in projects where quick iteration is required, such as in game dev where you want to quickly see the outcome of your changes without having to recompile everything.

The purpose of this is to build a basic Hot Reloading example with raylib, but it can be used in any project, it is just easier to see the changed with a GUI.

Chechout [Hot Reloading in Zig](https://github.com/glasPal6/Zig_Hot_Reloading) for a zig version.

## Build

To initially run `main`, run the following command:
```
mkdir build
cd build
cmake -DHOTRELOAD_ENABLE=ON ..
make
./main
```
The option to enable or disable hot reloading is done by passind```-DHOTRELOAD_ENABLE``` flag to the CMake file. 

Once ```main``` is runnig, you can change ```plug.c``` and then run:
```
make plug
```
which will reload the plugin into the main executable that is running. In this case, ```libplug``` is reloaded by pressing the R key in the main executable.

# Basic background theory

In C there are static and dynamic libraries. A static library is a library that is linked into the project and the code is included in the binary. We cannot change something in the binary while it is runnig so we cannot us static libraries for this use case. 

A dynamic library is a library that is linked at runtime and loads the functions into a lookup table that that is used at runtime. All we do is rebuild the table with the updated functions and presto, we have hot reloading.
