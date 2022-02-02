# Building CRHM Visual Studio GUI

1. Clone the git repository.
2. Initialize git submodules.
3. Download and configure Visual Studio.
4. Open the project with Visual Studio.
5. Install TeeChart.
6. Install Boost.
7. Select configuration and build.

## 1: Clone the git repository

1. Create a local directory in your desired location.
2. Navigate to the directory in your choice of terminal.
3. Execute the command "git clone https://github.com/srlabUsask/crhmcode
4. Enter your github credentials.
5. Wait for the clone to complete.

## 2: Initialize git submodules

1. Navigate to the directory with the git repository with a command line git tool.
2. Run the command "git submodule init"
3. Run the command "git submodule update"
4. Confirm that the crhmcode/src/libs/spdlog folder has been populated.

## 3: Download and configure Visual Studio

1. Download Visual Studio Installer from Microsoft https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16
2. Run the downloaded installer.
3. Launch Visual Studio installer.
4. Under the installed tab click "More" and select "Import configuration".
5. Select the file "crhmcode/CRHM_Visual_Studio_Config.vsconfig" from the git repository.
6. Import the configuration.

## 4: Open the project with Visual Studio

1. Launch Visual Studio.
2. Select "Open a project or solution."
3. Select the file "crhmcode/vcc/CRHM_GUI.sln"

## 5: Install TeeChart

1. Download TeeChart from https://www.steema.com/downloads/ax
2. Run the installer provided placing the files in a location that you remember.
3. Launch Command Prompt.
4. Navigate to the TeeChart instalation folder.
5. Run the command "regsvr32.exe [PATH TO]\teechart2020.ocx" replacing [PATH TO] with the location you installed TeeChart

## 6: Install Boost

1. Follow the tutorial here to integrate VCPKG with Visual Studio. https://vcpkg.io/en/getting-started.html
2. Launch Command Prompt
3. Navigate to the location of vcpkg
4. Run the command ".\vcpkg install boost"

## 7: Select configuration and build.

### To build Debug mode:
1. In the toolbar set configuration to Debug|x86
2. In the menu select build->build solution

### To build Release mode:
1. In the toolbar set configuration to Release|x86
2. In the menu select build->build solution
