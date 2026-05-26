# Hot Reloading in C

Hot Reloading is useful in projects where quick iteration is required, such as in game dev where you want to quickly see the outcome of your changes without having to recompile everything.

The purpose of this is to build a basic Hot Reloading example with raylib, but it can be used in any project, it is just easier to see the changed with a GUI.

Chechout [Hot Reloading in Zig](https://github.com/glasPal6/Zig_Hot_Reloading) for a zig version.

## Build (macOS)

1. Make sure `lib/` folder contains these:
    - libraylib.a
    - libEGL.so/libEGL.dylib
    - libGLESv2.so/libGLESv2.dylib
2. Make sure `include/` has raylib headers (should be copied automatically)

### CMake build
```sh
mkdir -p build
cd build
cmake ..
make
```

Result:
- `main` (app)
- `libplug.dylib` (hotloadable)

### Run
```sh
./main/main_cpu
```

### Rebuild only the plugin after editing it
```sh
make plug
```

### If you see errors about *_CFArray* or *OBJC_CLASS_*, you are missing necessary macOS frameworks in the link step.
Add these to CMakeLists.txt target_link_libraries for both `plug` and `main` targets:
- CoreVideo
- IOKit
- CoreFoundation
- Cocoa

Example CMake:
```cmake
target_link_libraries(plug
    PRIVATE
      ${CMAKE_SOURCE_DIR}/lib/libraylib.a
      ${CMAKE_SOURCE_DIR}/lib/libEGL.dylib
      ${CMAKE_SOURCE_DIR}/lib/libGLESv2.dylib
      m pthread
      -framework CoreVideo
      -framework IOKit
      -framework CoreFoundation
      -framework Cocoa
)
```

And similar for `main` target.
# Basic background theory

In C there are static and dynamic libraries. A static library is a library that is linked into the project and the code is included in the binary. We cannot change something in the binary while it is running so we cannot us static libraries for this use case. 

A dynamic library is a library that is linked at runtime and loads the functions into a lookup table that that is used at runtime. All we do is rebuild the table with the updated functions and presto, we have hot reloading.
