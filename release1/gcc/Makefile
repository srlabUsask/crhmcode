CC=g++
BOOST = boost_1_34_1 
IDIR = src
ODIR = obj
SDIR = src
LIBS = -lstdc++
DFLAGS = -g -O0 -fPIC -mstack-arg-probe -fstack-protector-all -fstack-check -fno-omit-frame-pointer
CFLAGS = -Wno-switch -Wno-c++11-extensions -Wno-logical-op-parentheses -Wno-c++11-extra-semi -Wno-dangling-else -Wno-null-conversion -Wno-pragma-once-outside-header -Wno-string-plus-int -Wno-string-plus-char
CFLAGS = -I$(BOOST) -Wno-switch -Wno-c++11-extensions -Wno-logical-op-parentheses -Wno-c++11-extra-semi -Wno-dangling-else -Wno-null-conversion -Wno-pragma-once-outside-header -Wno-string-plus-int -Wno-string-plus-char -Wno-return-stack-address -Wno-null-arithmetic -Wno-return-stack-address -Wno-macro-redefined -Wno-unused-value -Wno-tautological-constant-out-of-range-compare -Wno-enum-compare -Wno-empty-body -Wno-parentheses -Wno-unknown-escape-sequence -Wno-return-type -Wno-return-type -Wno-int-to-void-pointer-cast
DFLAGS =

_DEPS = ClassCRHM.h ClassModule.h Common.h CRHM_parse.h CRHMMain.h GlobalCommon.h GlobalDll.h Hype_CRHM.h Hype_lake.h Hype_river.h Hype_routines.h MacroUnit.h NewModules.h SnobalDefines.h StandardConverterUtility.h TStringList.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ClassCRHM.o ClassModule.o Common.o CRHM_parse.o CRHMmain.o GlobalDll.o Hype_CRHM.o Hype_lake.o Hype_river.o Hype_routines.o MacroUnit.o main.o NewModules.o StandardConverterUtility.o TStringList.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


crhm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(LIBS)

crhm_test: crhm
	./crhm BadLake1974-1975.prj

smithcreek.obs:  crhm
	./crhm smithcreek.prj
	cp CRHM_output_1.obs smithcreek.obs

$(ODIR)/main.o: $(SDIR)/main.cpp | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(SDIR)/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

clean: 
	rm -f $(ODIR)/*.o

$(ODIR):
	mkdir $(ODIR)
        
        
        


