crhm_compilation:
	@echo "Generating the executable"
	g++ -Iboost_1_34_1 codeconsole/*.cpp -o crhm -w -Wfatal-errors -lstdc++
	@echo "\nThe executable named 'crhm' has been generated"
	@echo "\nNow, running crhm on the badlake project\n"	
	./crhm BadLake1974-1975.prj
	@echo "\nCheck that the output file 'CRHM_output_1.obs' has been generated."