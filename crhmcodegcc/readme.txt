Please execute the following instructions in order to run the GCC version of CRHM on a project.

1. Unzip the zipped file. You will get a folder called "crhmgcc".
2. Make sure that the folder contains at least four things: (1) a folder named 'boost_1_34_1', (2) a folder named 'codeconsole', (3) a file named 'BadLake1974-1975.prj', and (4) a file named 'Badlake73_76.obs'.
3. If you want to run a project, you need to put the project file (.prj file) in the 'crhmgcc' folder.
4. Make sure the necessary observation files are the required locations.
5. Go into the "crhmgcc" folder using a terminal.
6. run the following command for compiling the code and generating the executable.

g++ -Iboost_1_34_1 codeconsole/*.cpp -o output.out -w -fpermissive -Wfatal-errors -lstdc++

7. The executable "output.out" has now been generated. Now execute the following command for running the project 'BadLake1974-1975.prj'.

./output.out BadLake1974-1975.prj

8. After successful execution, an output file 'CRHM_output_1.obs' will be generated.



