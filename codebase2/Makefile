CC=g++
BOOST = boost_1_73_0 
IDIR = src
ODIR = obj
SDIR = src
LIBS = -lstdc++
DFLAGS = -g -O0 -fPIC -mstack-arg-probe -fstack-protector-all -fstack-check -fno-omit-frame-pointer
CFLAGS = -Wno-switch -Wno-c++11-extensions -Wno-logical-op-parentheses -Wno-c++11-extra-semi -Wno-dangling-else -Wno-null-conversion -Wno-pragma-once-outside-header -Wno-string-plus-int -Wno-string-plus-char
#CFLAGS = -I$(BOOST) -Wno-switch -Wno-c++11-extensions -Wno-logical-op-parentheses -Wno-c++11-extra-semi -Wno-dangling-else -Wno-null-conversion -Wno-pragma-once-outside-header -Wno-string-plus-int -Wno-string-plus-char -Wno-return-stack-address -Wno-null-arithmetic -Wno-return-stack-address -Wno-macro-redefined -Wno-unused-value -Wno-tautological-constant-out-of-range-compare -Wno-enum-compare -Wno-empty-body -Wno-parentheses -Wno-unknown-escape-sequence -Wno-return-type -Wno-return-type -Wno-int-to-void-pointer-cast
#CFLAGS = -I$(BOOST) -Wno-switch -Wno-c++11-extensions -Wno-logical-op-parentheses -Wno-c++11-extra-semi -Wno-dangling-else -Wno-null-conversion -Wno-pragma-once-outside-header -Wno-string-plus-int -Wno-string-plus-char -Wno-null-arithmetic -Wno-return-stack-address -Wno-macro-redefined -Wno-unused-value -Wno-tautological-constant-out-of-range-compare -Wno-enum-compare -Wno-empty-body -Wno-parentheses -Wno-unknown-escape-sequence -Wno-return-type -Wno-int-to-void-pointer-cast -Wno-invalid-source-encoding
CFLAGS = -I$(BOOST) -I$(SDIR)/core -I$(SDIR)/macro -I$(SDIR)/plugins/hype -I$(SDIR)/plugins/newmodules -std=c++11
#DFLAGS = -ggdb -O0 -fPIC -mstack-arg-probe -fstack-protector-all -fstack-check -fno-omit-frame-pointer -fsanitize=address
DFLAGS = -fsanitize=address

_DEPS = core/ClassCRHM.h core/ClassModule.h core/Common.h macro/CRHM_parse.h core/CRHMMain.h core/GlobalCommon.h core/GlobalDll.h plugins/hype/Hype_CRHM.h plugins/hype/Hype_lake.h Hype_river.h plugins/hype/Hype_routines.h macro/MacroUnit.h plugins/newmodules/NewModules.h plugins/newmodules/SnobalDefines.h core/StandardConverterUtility.h core/TStringList.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ClassCRHM.o ClassModule.o Common.o CRHM_parse.o CRHMmain.o GlobalDll.o Hype_CRHM.o Hype_lake.o Hype_river.o Hype_routines.o MacroUnit.o main.o NewModules.o StandardConverterUtility.o TStringList.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


crhm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(LIBS)

$(ODIR)/main.o: $(SDIR)/core/main.cpp | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/%.cpp $(SDIR)/core/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/macro/%.cpp $(SDIR)/macro/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/plugins/hype/%.cpp $(SDIR)/plugins/hype/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/plugins/newmodules/%.cpp $(SDIR)/plugins/newmodules/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

clean: 
	rm -f $(ODIR)/*.o

$(ODIR):
	mkdir $(ODIR)
	
%.obs: %.prj crhm
	time ./crhm $<
	cp CRHM_output_1.obs $*.obs

%.diff: %.prj crhm
	time ./crhm $<
	cp CRHM_output_1.obs $*_1.obs
	time ./crhm $*.prj
	cp CRHM_output_1.obs $*_2.obs
	diff $*_1.obs $*_2.obs > $@
	wc -l $@	
