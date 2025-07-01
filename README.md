#Computer Graphics Algorithms Collection:
A curated set of intro‑level graphics programming exercises written in C and C++.  Each source file demonstrates a classic algorithm you’ll meet in a typical Computer Graphics (CG) course—ideal for reference, lab assignments, or quick experimentation.


#Prerequisites

Compiler: Any modern C/C++ compiler (e.g. g++ 11+, clang, or MSVC).

Graphics libs:

Windows (MinGW / MSVC): Install WinBGIm for <graphics.h> support or swap to FreeGLUT.

Linux / macOS: Use FreeGLUT + OpenGL headers (sudo apt install freeglut3-dev), then add -lglut -lGL -lGLU when linking.

make (optional) if you want to use the provided sample Makefile.


Building & Running

# Example: compile Cohen–Sutherland demo (Linux/macOS)
g++ Cohen-Sutherlandline.cpp -o cohen -lglut -lGL -lGLU
./cohen

# Windows + WinBGIm
mingw32-g++.exe Assignment_circle.c -o circle.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
circle.exe

Acknowledgements

Originally developed as lab assignments for the CSE 494 – Computer Graphics course at Shahjalal University of Science and Technology.  Thanks to our instructor for inspiring these exercises.




