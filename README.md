# CRHMcode

CRHMcode is a project to convert the Cold Regions Hydrological Modelling (CRHM) platform from Borland C++ to more modern C++ compilers. Further documentation can be found here: https://wiki.usask.ca/display/CRHMdoc/CRHM+-+Cold+Region+Hydrological+Model

## CRHM: The Cold Regions Hydrological Modelling platform

The original version of CRHM can be found here: https://www.dropbox.com/s/19o5oqpw49ko4ia/CRHM_Distribution.zip?dl=0

This version of CRHM uses the Borland C++ compiler and is referred to as Borland CRHM in further documentation in this repository.

## CRHMcode GCC and CRHMcode GUI

One of the objectives of the modernization of the CRHM software was to separate the core modeling functionality from the graphical user interface of Borland CRHM. This has been accomplished and two software products have been created. CRHMcode GCC is the core modeling functionality of CRHM with a simple command line interface. It has been made to compile with the GNU Compiler Collection (GCC). The other product is CRHMcode GUI a recreation of the graphical user interface of Borland CRHM built with Microsoft Foundation Class Library and Microsoft Visual Studio. Both products use the same code to run their hydrological simulations and project files and simulation results are compatible between the two.

Both versions support the same command line interface which is described here: https://github.com/srlabUsask/crhmcode/wiki/Using-CRHMcode-Command-Line-Interface

### CRHMcode CLI

CRHMcode CLI can be compiled on any system that supports the GCC C++ compiler. Instructions for compiling it can be found here: https://github.com/srlabUsask/crhmcode/wiki/Building-CRHMcode-GCC

It is likely that other C++ compilers can be used to compile and run CRHMcode CLI but only the GCC compiler has been tested.

CRHMcode CLI will be available as a source distribution designed to be built with the CMake set of tools.


### CRHMcode GUI

CRHMcode GCC can be built for development by following the instructions found here: https://github.com/srlabUsask/crhmcode/wiki/Building-CRHMcode-GUI-for-development-with-Microsoft-Visual-Studio

CRHMcode GUI will be available as a Windows Installer file (.msi) allowing it to be installed on Windows systems.
