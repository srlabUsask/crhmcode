To build the GCC version of CRHM using the supplied Makefile:

1. Download chrmcode from github.
2. Download the boost_1_73_0 library and place it in the crhmcode/codebase/ directory.
3. Using a terminal program change to the crhmcode/codebase/ directory.
4. Enter ‘make’ or ‘make crhm’ and the crhm executable will be created by compiling and linking the code.

Running the GCC version of CRHM:

1. Using a terminal program change to the directory with the crhm executable and the project file. 
2. To run a project, enter ‘./crhm filename.prj’ and 'CRHM_output_1.obs’ will be created. 
For example entering './crhm badlake.prj will run crhm and the output will be in ‘CRHM_output_1.obs'

Running the GCC version of CRHM using the supplied Makefile:

1. Using a terminal program change to the crhmcode/codebase/ directory (or a directory that has the crhm executable, the project file and the Makefile). 
2. Run a project by entering ‘make filename.obs’ and crhm will be run on filename.prj and the output will be found in filename.obs. 
For example, entering ‘make badlake.obs’ will run crhm on badlake.prj and create badlake.obs as output.
