CC=g++
BOOST = boost_1_73_0
IDIR = src
ODIR = obj
SDIR = src
LIBS = -lstdc++
DFLAGS = -g -O0 -fPIC -mstack-arg-probe -fstack-protector-all -fstack-check -fno-omit-frame-pointer
CFLAGS = -Wno-switch -Wno-c++11-extensions -Wno-logical-op-parentheses -Wno-c++11-extra-semi -Wno-dangling-else -Wno-null-conversion -Wno-pragma-once-outside-header -Wno-string-plus-int -Wno-string-plus-char
CFLAGS = -I$(BOOST) -I$(SDIR)/core -I$(SDIR)/macro -I$(SDIR)/plugins/waterquality -I$(SDIR)/plugins/newmodules -I$(SDIR)/plugins/coremodules -I$(SDIR)/gcc -std=c++11 -lboost_system
DFLAGS = -fsanitize=address

#_DEPS = core/ClassCRHM.h core/ClassModule.h core/Common.h macro/CRHM_parse.h core/CRHMMain.h core/GlobalCommon.h core/GlobalDll.h plugins/waterquality/WQ_CRHM.h plugins/waterquality/WQ_Soil_NPCcycling.h macro/MacroUnit.h plugins/newmodules/NewModules.h plugins/newmodules/SnobalDefines.h core/StandardConverterUtility.h core/TStringList.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ClassCRHM.o ClassModule.o Common.o CRHM_parse.o CRHMmain.o GlobalDll.o WQ_CRHM.o WQ_Soil_NPCcycling.o MacroUnit.o main.o NewModules.o StandardConverterUtility.o TStringList.o ClassBasin.o ClassGlobal.o ClassObs.o ClassIntcp.o Classpbsm.o ClassNO_pbsm.o Classtsurface.o Classalbedo.o Classnetall.o Classebsm.o ClassTs.o ClassNeedle.o ClassSimpleRichard.o Classevap.o ClassevapD.o Classsbsm.o Classcrack.o ClassKevin.o ClassGreencrack.o Classfrostdepth.o Classfrozen.o ClassNetroute.o Classinterception.o ClassGreenAmpt.o Classalbedoparam.o Classalbedoobs.o ClassHtobs.o ClasspbsmSnobal.o ClassalbedoRichard.o ClassalbedoBaker.o ClassHMSA.o Classwalmsley_wind.o ClassNetroute_M.o ClassREWroute2.o ClassLongVt.o Classpbsm_M.o ClassNetroute_D.o ClassNetroute_M_D.o ClassSetSoil.o ClassVolumetric.o ClassAnnan.o Classcalcsun.o ClassObstoPar.o ClassPrairieInfil.o ClassCRHMCanopy.o ClassPSPnew.o Classbrushintcp.o ClassAyers.o ClassSlope_Qsi.o ClassfrozenAyers.o ClassSoil.o Classevap_Resist.o ClassevapD_Resist.o ClassShutWall.o ClassShutWallD.o ClassIceBulb.o Classlake.o ClassalbedoWinstral.o ClassK_Estimate.o ClassevapX.o Class3D_param.o ClassMeltRunoff_Lag.o ClassMeltRunoff_Kstorage.o ClassREWroute.o ClassXG.o Classcontribution.o ClassSoilX.o ClassMod_Exec.o ClassFlowInSnow.o ClassSoilDS.o Classalbedoobs2.o Classwinter_meltflag.o Class_z_s_rho.o Classqmelt.o Classquinton.o Classqdrift.o ClassXGAyers.o ClassCRHMCanopyClearing.o ClassCRHMCanopyClearingGap.o ClassREWroute_stream.o ClassICEflow.o Classglacier.o Classglacier_debris.o ClassSWEslope.o ClassTestSparse.o ClassGrow_Crop.o ClassSnobalX.o ClassSnobalCRHM.o Classshared.o ClassNOP.o ClassSnobalBase.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


crhm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(LIBS)

$(ODIR)/main.o: $(SDIR)/gcc/main.cpp | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/%.cpp $(SDIR)/core/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/macro/%.cpp $(SDIR)/macro/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/plugins/waterquality/%.cpp $(SDIR)/plugins/waterquality/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/plugins/newmodules/%.cpp $(SDIR)/plugins/newmodules/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/plugins/coremodules/%.cpp $(SDIR)/plugins/coremodules/%.h | $(ODIR)
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
