Please execute the following instructions in order to run the GCC version of CRHM on a project.

1. Let us assume that this readme.txt file and all other contents are residing in a folder called 'crhmcode_gcc'.

2. I guess you already have the boost library folder 'boost_1_34_1'. Put this boost library folder in the 'crhmcode_gcc' folder. If you do not have the boost library folder, you can get it from the following link.

   https://drive.google.com/open?id=1mXmNCzQwwqz4W81GkJ2ec_QWVNMgttDK

3. If you want to run a project, you need to put the project file (.prj file) in the 'crhmcode_gcc' folder.

4. Make sure the necessary observation files are the required locations.

5. Go into the 'crhmcode_gcc' folder using a terminal.

6. Run the Makefile using the command "make".

7. The executable "crhm" has now been generated. Now execute the following command for running the project 'BadLake1974-1975.prj'.

./crhm BadLake1974-1975.prj

8. After successful execution, an output file 'CRHM_output_1.obs' will be generated in the 'crhmcode_gcc' folder.