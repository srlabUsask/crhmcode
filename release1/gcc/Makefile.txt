crhm_compilation:
	@echo "Generating the executable"
	g++ -Iboost_1_34_1 codeconsole/*.cpp -o crhm -w -Wfatal-errors -lstdc++
	@echo "The executable named 'crhm' has been generated"
	@echo "Now, running crhm on the badlake project"	
	./crhm BadLake1974-1975.prj
	@echo "Check that the output file 'CRHM_output_1.obs' has been generated."