CC=g++
BOOST = boost_1_73_0
IDIR = src
ODIR = obj
SDIR = src
LIBS = -lstdc++

DFLAGS = -D ACTIVE_LOG_LEVEL=2

CFLAGS = -Wno-switch -Wno-c++11-extensions -Wno-logical-op-parentheses \
-Wno-c++11-extra-semi -Wno-dangling-else -Wno-null-conversion \
-Wno-pragma-once-outside-header -Wno-string-plus-int -Wno-string-plus-char

CFLAGS = -I. -I$(BOOST) -I$(SDIR)/core -I$(SDIR)/macro \
-I$(SDIR)/modules/waterquality -I$(SDIR)/modules/newmodules \
-I$(SDIR)/modules/coremodules -I$(SDIR)/gcc -std=c++11

CORE_OBJS = GlobalDll.o StandardConverterUtility.o

ClassCRHM_OBJS = ClassCRHM.o ClassData.o Classfilter.o ClassModel.o \
ClassPar.o ClassVar.o Convert.o MacroClass.o Tresult.o

Filter_OBJS = Classabs.o Classadd.o ClassaddV.o Classconst.o Classcos.o \
ClassCtoK.o Classdiv.o ClassdivV.o Classea.o Classexp.o Classexpv.o \
ClassForce.o ClassFtoC.o Classjulian.o ClassKtoC.o Classlog.o Classlogv.o \
ClassMissing.o ClassMissing0.o ClassMissingC.o ClassMissingFlag.o \
ClassMissingFlagAfter.o ClassMissingInter.o ClassMissingrepl.o Classmul.o \
ClassmulV.o Classpoly.o Classpolyv.o Classpow.o Classpowv.o Classpulse.o \
Classramp.o Classrandom.o Classrefwind.o ClassReplace.o Classrh.o \
ClassRH_WtoI.o ClassSim.o Classsin.o ClassSmear.o Classsquare.o Classsub.o \
ClasssubV.o Classtime.o ClassTimeshift.o

ClassModule_OBJS = Administer.o ClassClark.o ClassModule.o ClassMuskingum.o Myparser.o

Common_OBJS = Common.o snowcover.o

CRHM_parse_OBJS = CRHM_parse.o VarCHRM.o

EXEC_OBJS = execbase.o

CRHMmain_OBJS = CRHMmain.o CRHMLogger.o

MacroUnit_OBJS = ClassMacro.o MacroUnit.o

DefCRHM_OBJS = DefCRHM.o Defdecldiag.o Defdeclgetvar.o Defdecllocal.o \
Defdeclobs.o Defdeclobsfunc.o Defdeclparam.o Defdeclputparam.o \
Defdeclputvar.o Defdeclreadobs.o Defdeclstatvar.o Defdeclvar.o

TStringList_OBJS = TStringList.o

GCC_OBJS = main.o

COREMODULES_OBJS = Class_z_s_rho.o Class3D_param.o Classalbedo.o \
ClassalbedoBaker.o Classalbedoobs.o Classalbedoobs2.o Classalbedoparam.o \
ClassalbedoRichard.o ClassalbedoWinstral.o ClassAnnan.o ClassAyers.o \
ClassBasin.o Classbrushintcp.o Classcalcsun.o Classcontribution.o \
Classcrack.o ClassCRHMCanopy.o ClassCRHMCanopyClearing.o \
ClassCRHMCanopyClearingGap.o Classebsm.o Classevap.o Classevap_Resist.o \
ClassevapD.o ClassevapD_Resist.o ClassevapX.o ClassFlowInSnow.o \
Classfrostdepth.o Classfrozen.o ClassfrozenAyers.o Classglacier.o \
Classglacier_debris.o ClassGlobal.o ClassGreenAmpt.o ClassGreencrack.o \
ClassGrow_Crop.o ClassHMSA.o ClassHtobs.o ClassIceBulb.o ClassICEflow.o \
ClassIntcp.o Classinterception.o ClassK_Estimate.o ClassKevin.o Classlake.o \
ClassLongVt.o ClassMeltRunoff_Kstorage.o ClassMeltRunoff_Lag.o ClassMod_Exec.o \
ClassNeedle.o Classnetall.o ClassNetroute.o ClassNetroute_D.o ClassNetroute_M.o \
ClassNetroute_M_D.o ClassNO_pbsm.o ClassNOP.o ClassObs.o ClassObstoPar.o \
Classpbsm.o Classpbsm_M.o ClasspbsmSnobal.o ClassPrairieInfil.o ClassPSPnew.o \
Classqdrift.o Classqmelt.o Classquinton.o ClassREWroute.o ClassREWroute_stream.o \
ClassREWroute2.o Classsbsm.o ClassSetSoil.o Classshared.o ClassShutWall.o \
ClassShutWallD.o ClassSimpleRichard.o ClassSlope_Qsi.o ClassSnobalBase.o \
ClassSnobalCRHM.o ClassSnobalX.o ClassSoil.o ClassSoilDS.o ClassSoilX.o ClassSWEslope.o \
ClassTestSparse.o ClassTs.o Classtsurface.o ClassVolumetric.o Classwalmsley_wind.o \
Classwinter_meltflag.o ClassXG.o ClassXGAyers.o

NEWMODULES_OBJS = NewModules.o

Waterquality_OBJS = Class_lapse_rate_Monthly.o ClassGlacier_debris_cover.o \
ClassGlacier_melt_debris_cover_estimate_Mod.o ClassGrow_crops_annually.o \
Classlapse_rate_Monthly_Mod.o ClassSoilPrairie.o ClassWQ_Gen_Mass_Var_Netroute.o \
ClassWQ_Gen_Mass_Var_Soil.o ClassWQ_mass_conc.o ClassWQ_Netroute.o ClassWQ_Netroute_M_D.o \
ClassWQ_pbsm.o ClassWQ_pbsmSnobal.o ClassWQ_Soil.o ClassWQ_Substitute_Hype.o \
ClassWQ_Test_Hype.o WQ_CRHM.o WQ_Soil_NPCcycling.o


ALL_OBS = $(CORE_OBJS) $(ClassCRHM_OBJS) $(Filter_OBJS) $(ClassModule_OBJS) \
$(Common_OBJS) $(CRHM_parse_OBJS) $(EXEC_OBJS) $(CRHMmain_OBJS) \
$(MacroUnit_OBJS) $(DefCRHM_OBJS) $(GCC_OBJS) $(TStringList_OBJS) \
$(COREMODULES_OBJS) $(NEWMODULES_OBJS) $(Waterquality_OBJS)

OBJ = $(patsubst %,$(ODIR)/%,$(ALL_OBS))


crhm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(LIBS)

$(ODIR)/main.o: $(SDIR)/gcc/main.cpp | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/%.cpp $(SDIR)/core/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/ClassModule/%.cpp $(SDIR)/core/ClassModule/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/ClassCRHM/%.cpp $(SDIR)/core/ClassCRHM/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/ClassCRHM/Filters/%.cpp  $(SDIR)/core/ClassCRHM/Filters/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/TStringList/%.cpp $(SDIR)/core/TStringList/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/Common/%.cpp $(SDIR)/core/Common/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/CRHM_parse/%.cpp $(SDIR)/core/CRHM_parse/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/CRHM_parse/exec/%.cpp $(SDIR)/core/CRHM_parse/exec/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/CRHMmain/%.cpp $(SDIR)/core/CRHMmain/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/MacroUnit/%.cpp $(SDIR)/core/MacroUnit/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/core/MacroUnit/DefCRHM/%.cpp $(SDIR)/core/MacroUnit/DefCRHM/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/macro/%.cpp $(SDIR)/macro/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/modules/waterquality/%.cpp $(SDIR)/modules/waterquality/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/modules/newmodules/%.cpp $(SDIR)/modules/newmodules/%.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/%.o: $(SDIR)/modules/coremodules/%.cpp $(SDIR)/modules/coremodules/%.h | $(ODIR)
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
