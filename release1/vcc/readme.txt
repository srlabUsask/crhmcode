Please execute the following steps for running the visual version of the CRHM software.

1. I guess you have the boost library folder 'boost_1_34_1'. Put this folder in the 'C:' drive. If you do not have this folder, you can get it from the following link.
   https://drive.google.com/open?id=1mXmNCzQwwqz4W81GkJ2ec_QWVNMgttDK

2. Register the 'TeeChart2018.ocx' file using the following command.
	Regsvr32 <path to the ocx file>
   If the ocx file is in the folder 'C:/test'. The command will look like the following
   	Regsvr32 C:/test/TeeChart2018.ocx
   You will get a relevant message after successful registration.
   
3. You are now ready to run the visual version of the CRHM software. Go to the folder 'crhmsoftware'. You will see that there is a file called 'CRHM_GUI.exe'. Double click this file to see the software dialog.

4. The 'crhmsoftware' folder contains some project files (.prj files) and their respective observation files (.obs files). You can test the software by running the 'BadLake1974-1975.prj' file. The 'smithcreek.prj' file and the associated obs files are also stored in the 'crhmsoftware' folder. You can try running the 'smithcreek.prj' as well.