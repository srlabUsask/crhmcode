Please execute the following instructions in order to run the GCC version of CRHM on a project.

1. Let us assume that this readme.txt file and all other contents are residing in a folder called 'codebase'.

2. I guess you already have the latest boost library folder 'boost_1_73_0'. Put this boost library folder in the 'codebase' folder. If you do not have the boost library folder, you can get it from the following link.

   https://www.boost.org/users/history/version_1_73_0.html

3. If you want to run a project, you need to put the project file (.prj file) in the 'codebase' folder.

4. Make sure the necessary observation files are at the required locations.

5. Go into the 'codebase' folder using a terminal.

6. Run the Makefile using the command "make".

7. The executable "crhm" has now been generated. Now execute the following command for running the project 'badlake.prj'.

./crhm badlake.prj

8. After successful execution, an output file 'CRHM_output_1.obs' will be generated in the 'codebase' folder.