# Requirements

### Microsoft Visual Studio 2019
        Configuration for visual studio can be imported from the configuration
        file available in the github repository.

### Vcpkg with boost library
        In order to compile CRHM needs the Boost library. To install this and
        integrate with Microsoft visual studio follow the tutorial here:
        https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019#installation


### Install TeeChart
    1. Download TeeChart from https://www.steema.com/downloads/net

    2. Run the installer provided.

    3. To make sure the TeeChart ActiveX control is 
        accessible, execute this command to register TeeChart Pro Activex with command prompt: regsvr32.exe c:\yourpath\teechart2020.ocx

# Download and configure project
1. Open visual studio.
2. In dialog window select clone repository.
3. Enter the repository URL https://github.com/srlabUsask/crhmcode.git
4. Click clone and wait until the repository finishes downloading.
5. In bottom right click on the master branch and add a new branch.
6. Add the desired branch ie. justin
7. Switch to the desired branch.
8. In the menu select file->open->project/solution.
9. Select the file crhmcode\release1.1\src\vcc\CRHM_GUI.vcxproj.
10. In the menu select view->property_manager.
11. In the property tree open CRHM_GUI->Debug|Win32->UserMacros.
12. Within user macros under common properties select User Macros.
13. Select the macro ProjectHome and set its value to the location of the src folder within the release1.1 folder.
14. Click apply then okay.
15. In the property tree open CRHM_GUI->Release|Win32->UserMacros.
16. Within user macros under common properties select User Macros.
17. Select the macro ProjectHome and set its value to the location of        the src folder within the release1.1 folder.
17. Click apply then okay.

# To build Debug mode:
1. In the toolbar set configuration to Debug|x86
2. In the menu select build->build solution

# To build Release mode:
1. In the toolbar set configuration to Release|x86
2. In the menu select build->build solution
