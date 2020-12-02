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
DFLAGS =

#_DEPS = core/ClassCRHM.h core/ClassModule.h core/Common.h macro/CRHM_parse.h core/CRHMMain.h core/GlobalCommon.h core/GlobalDll.h plugins/waterquality/WQ_CRHM.h plugins/waterquality/WQ_Soil_NPCcycling.h macro/MacroUnit.h plugins/newmodules/NewModules.h plugins/newmodules/SnobalDefines.h core/StandardConverterUtility.h core/TStringList.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Administer.o ClassCRHM.o ClassData.o ClassVar.o ClassPar.o Classfilter.o ClassFtoC.o ClassCtoK.o ClassReplace.o ClassKtoC.o Classlog.o Classlogv.o ClassTimeshift.o ClassRH_WtoI.o Classea.o Classrh.o Classsin.o Classcos.o ClassModule.o Common.o CRHMmain.o GlobalDll.o WQ_CRHM.o WQ_Soil_NPCcycling.o MacroUnit.o main.o NewModules.o StandardConverterUtility.o TStringList.o ClassBasin.o ClassGlobal.o ClassObs.o ClassIntcp.o Classpbsm.o ClassNO_pbsm.o Classtsurface.o Classalbedo.o Classnetall.o MacroClass.o ClassMacro.o Classebsm.o ClassTs.o Classabs.o Classexp.o Classexpv.o Classpulse.o Classrandom.o Classrefwind.o ClassMissing.o ClassMissingInter.o Classsquare.o Classramp.o Classpoly.o Classpolyv.o Classpow.o Classpowv.o Classtime.o Classjulian.o ClassNeedle.o ClassSimpleRichard.o Classevap.o ClassevapD.o Classsbsm.o Classcrack.o ClassKevin.o ClassGreencrack.o Classfrostdepth.o Classfrozen.o ClassNetroute.o Classinterception.o ClassGreenAmpt.o Classalbedoparam.o Classalbedoobs.o snowcover.o ClassClark.o ClassMuskingum.o VarCHRM.o execbase.o ClassHtobs.o Myparser.o ClasspbsmSnobal.o Convert.o ClassalbedoRichard.o ClassMissingrepl.o ClassForce.o Classadd.o Classsub.o Classmul.o Classdiv.o ClassaddV.o ClasssubV.o ClassMissing0.o ClassMissingC.o ClassMissingFlagAfter.o ClassMissingFlag.o ClassmulV.o ClassdivV.o ClassalbedoBaker.o ClassHMSA.o Classwalmsley_wind.o ClassNetroute_M.o ClassREWroute2.o ClassLongVt.o Classpbsm_M.o ClassNetroute_D.o ClassNetroute_M_D.o DefCRHM.o ClassWQ_Gen_Mass_Var_Netroute.o Classlapse_rate_Monthly_Mod.o ClassGlacier_melt_debris_cover_estimate_Mod.o ClassSoilPrairie.o ClassGlacier_debris_cover.o Class_lapse_rate_Monthly.o ClassWQ_Gen_Mass_Var_Soil.o ClassGrow_crops_annually.o ClassWQ_Soil.o ClassWQ_Netroute.o ClassWQ_pbsm.o ClassWQ_Netroute_M_D.o ClassWQ_Test_Hype.o ClassWQ_pbsmSnobal.o ClassWQ_mass_conc.o ClassWQ_Substitute_Hype.o Defdeclparam.o Defdeclvar.o Defdecldiag.o Defdeclstatvar.o Defdecllocal.o Defdeclobs.o Defdeclgetvar.o Defdeclputvar.o Defdeclputparam.o Defdeclreadobs.o Defdeclobsfunc.o ClassSetSoil.o ClassVolumetric.o ClassAnnan.o Classcalcsun.o ClassObstoPar.o ClassPrairieInfil.o ClassCRHMCanopy.o ClassPSPnew.o Classbrushintcp.o ClassAyers.o ClassSlope_Qsi.o ClassfrozenAyers.o ClassSoil.o Classevap_Resist.o ClassevapD_Resist.o ClassShutWall.o Classconst.o ClassSim.o ClassSmear.o ClassShutWallD.o ClassIceBulb.o Classlake.o ClassalbedoWinstral.o ClassK_Estimate.o ClassevapX.o Class3D_param.o ClassMeltRunoff_Lag.o ClassMeltRunoff_Kstorage.o ClassREWroute.o ClassXG.o Classcontribution.o ClassSoilX.o ClassMod_Exec.o ClassFlowInSnow.o ClassSoilDS.o Classalbedoobs2.o Classwinter_meltflag.o Class_z_s_rho.o Classqmelt.o Classquinton.o Classqdrift.o ClassXGAyers.o ClassCRHMCanopyClearing.o ClassCRHMCanopyClearingGap.o ClassREWroute_stream.o ClassICEflow.o Classglacier.o Classglacier_debris.o ClassSWEslope.o ClassTestSparse.o ClassGrow_Crop.o ClassSnobalX.o ClassSnobalCRHM.o Classshared.o ClassNOP.o ClassSnobalBase.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


crhm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(LIBS)

$(ODIR)/main.o: $(SDIR)/gcc/main.cpp | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/TStringList.o: $(SDIR)/core/TStringList/TStringList.cpp $(SDIR)/core/TStringList/TStringList.h $(SDIR)/core/TStringList/TStrings.h $(SDIR)/core/TStringList/TObjects.h $(SDIR)/core/TStringList/StringandObject.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassCRHM.o: $(SDIR)/core/ClassCRHM/ClassCRHM.cpp  $(SDIR)/core/ClassCRHM/ClassCRHM.h $(SDIR)/core/ClassCRHM/ClassModel.h $(SDIR)/core/ClassCRHM/Tresult.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassData.o: $(SDIR)/core/ClassCRHM/ClassData.cpp  $(SDIR)/core/ClassCRHM/ClassData.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassVar.o: $(SDIR)/core/ClassCRHM/ClassVar.cpp  $(SDIR)/core/ClassCRHM/ClassVar.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassPar.o: $(SDIR)/core/ClassCRHM/ClassPar.cpp  $(SDIR)/core/ClassCRHM/ClassPar.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classfilter.o: $(SDIR)/core/ClassCRHM/Classfilter.cpp  $(SDIR)/core/ClassCRHM/Classfilter.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassFtoC.o: $(SDIR)/core/ClassCRHM/Filters/ClassFtoC.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassFtoC.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassCtoK.o: $(SDIR)/core/ClassCRHM/Filters/ClassCtoK.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassCtoK.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassReplace.o: $(SDIR)/core/ClassCRHM/Filters/ClassReplace.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassReplace.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassKtoC.o: $(SDIR)/core/ClassCRHM/Filters/ClassKtoC.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassKtoC.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassTimeshift.o: $(SDIR)/core/ClassCRHM/Filters/ClassTimeshift.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassTimeshift.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassRH_WtoI.o: $(SDIR)/core/ClassCRHM/Filters/ClassRH_WtoI.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassRH_WtoI.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classea.o: $(SDIR)/core/ClassCRHM/Filters/Classea.cpp  $(SDIR)/core/ClassCRHM/Filters/Classea.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classrh.o: $(SDIR)/core/ClassCRHM/Filters/Classrh.cpp  $(SDIR)/core/ClassCRHM/Filters/Classrh.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classsin.o: $(SDIR)/core/ClassCRHM/Filters/Classsin.cpp  $(SDIR)/core/ClassCRHM/Filters/Classsin.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classcos.o: $(SDIR)/core/ClassCRHM/Filters/Classcos.cpp  $(SDIR)/core/ClassCRHM/Filters/Classcos.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classabs.o: $(SDIR)/core/ClassCRHM/Filters/Classabs.cpp  $(SDIR)/core/ClassCRHM/Filters/Classexp.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classexp.o: $(SDIR)/core/ClassCRHM/Filters/Classexp.cpp  $(SDIR)/core/ClassCRHM/Filters/Classabs.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classpulse.o: $(SDIR)/core/ClassCRHM/Filters/Classpulse.cpp  $(SDIR)/core/ClassCRHM/Filters/Classpulse.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classexpv.o: $(SDIR)/core/ClassCRHM/Filters/Classexpv.cpp  $(SDIR)/core/ClassCRHM/Filters/Classexpv.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classpoly.o: $(SDIR)/core/ClassCRHM/Filters/Classpoly.cpp  $(SDIR)/core/ClassCRHM/Filters/Classpoly.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classpolyv.o: $(SDIR)/core/ClassCRHM/Filters/Classpolyv.cpp  $(SDIR)/core/ClassCRHM/Filters/Classpolyv.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classlog.o: $(SDIR)/core/ClassCRHM/Filters/Classlog.cpp  $(SDIR)/core/ClassCRHM/Filters/Classlog.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classlogv.o: $(SDIR)/core/ClassCRHM/Filters/Classlogv.cpp  $(SDIR)/core/ClassCRHM/Filters/Classlogv.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classpow.o: $(SDIR)/core/ClassCRHM/Filters/Classpow.cpp  $(SDIR)/core/ClassCRHM/Filters/Classpow.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classpowv.o: $(SDIR)/core/ClassCRHM/Filters/Classpowv.cpp  $(SDIR)/core/ClassCRHM/Filters/Classpowv.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classtime.o: $(SDIR)/core/ClassCRHM/Filters/Classtime.cpp  $(SDIR)/core/ClassCRHM/Filters/Classtime.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classjulian.o: $(SDIR)/core/ClassCRHM/Filters/Classjulian.cpp  $(SDIR)/core/ClassCRHM/Filters/Classjulian.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classrandom.o: $(SDIR)/core/ClassCRHM/Filters/Classrandom.cpp  $(SDIR)/core/ClassCRHM/Filters/Classrandom.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classrefwind.o: $(SDIR)/core/ClassCRHM/Filters/Classrefwind.cpp  $(SDIR)/core/ClassCRHM/Filters/Classrefwind.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classsquare.o: $(SDIR)/core/ClassCRHM/Filters/Classsquare.cpp  $(SDIR)/core/ClassCRHM/Filters/Classsquare.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classramp.o: $(SDIR)/core/ClassCRHM/Filters/Classramp.cpp  $(SDIR)/core/ClassCRHM/Filters/Classramp.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classadd.o: $(SDIR)/core/ClassCRHM/Filters/Classadd.cpp  $(SDIR)/core/ClassCRHM/Filters/Classadd.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classsub.o: $(SDIR)/core/ClassCRHM/Filters/Classsub.cpp  $(SDIR)/core/ClassCRHM/Filters/Classsub.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classmul.o: $(SDIR)/core/ClassCRHM/Filters/Classmul.cpp  $(SDIR)/core/ClassCRHM/Filters/Classmul.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classdiv.o: $(SDIR)/core/ClassCRHM/Filters/Classdiv.cpp  $(SDIR)/core/ClassCRHM/Filters/Classdiv.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassaddV.o: $(SDIR)/core/ClassCRHM/Filters/ClassaddV.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassaddV.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClasssubV.o: $(SDIR)/core/ClassCRHM/Filters/ClasssubV.cpp  $(SDIR)/core/ClassCRHM/Filters/ClasssubV.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassmulV.o: $(SDIR)/core/ClassCRHM/Filters/ClassmulV.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassmulV.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassdivV.o: $(SDIR)/core/ClassCRHM/Filters/ClassdivV.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassdivV.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Classconst.o: $(SDIR)/core/ClassCRHM/Filters/Classconst.cpp  $(SDIR)/core/ClassCRHM/Filters/Classconst.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassSim.o: $(SDIR)/core/ClassCRHM/Filters/ClassSim.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassSim.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassSmear.o: $(SDIR)/core/ClassCRHM/Filters/ClassSmear.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassSmear.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMissing.o: $(SDIR)/core/ClassCRHM/Filters/ClassMissing.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassMissing.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMissingInter.o: $(SDIR)/core/ClassCRHM/Filters/ClassMissingInter.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassMissingInter.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMissing0.o: $(SDIR)/core/ClassCRHM/Filters/ClassMissing0.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassMissing0.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMissingC.o: $(SDIR)/core/ClassCRHM/Filters/ClassMissingC.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassMissingC.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMissingFlag.o: $(SDIR)/core/ClassCRHM/Filters/ClassMissingFlag.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassMissingFlag.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMissingFlagAfter.o: $(SDIR)/core/ClassCRHM/Filters/ClassMissingFlagAfter.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassMissingFlagAfter.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMissingrepl.o: $(SDIR)/core/ClassCRHM/Filters/ClassMissingrepl.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassMissingrepl.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassForce.o: $(SDIR)/core/ClassCRHM/Filters/ClassForce.cpp  $(SDIR)/core/ClassCRHM/Filters/ClassForce.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/MacroClass.o: $(SDIR)/core/ClassCRHM/MacroClass.cpp  $(SDIR)/core/ClassCRHM/MacroClass.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Convert.o: $(SDIR)/core/ClassCRHM/Convert.cpp  $(SDIR)/core/ClassCRHM/Convert.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassModule.o: $(SDIR)/core/ClassModule/ClassModule.cpp $(SDIR)/core/ClassModule/ClassModule.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Administer.o: $(SDIR)/core/ClassModule/Administer.cpp $(SDIR)/core/ClassModule/Administer.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Myparser.o: $(SDIR)/core/ClassModule/Myparser.cpp $(SDIR)/core/ClassModule/Myparser.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassClark.o: $(SDIR)/core/ClassModule/ClassClark.cpp $(SDIR)/core/ClassModule/ClassClark.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMuskingum.o: $(SDIR)/core/ClassModule/ClassMuskingum.cpp $(SDIR)/core/ClassModule/ClassMuskingum.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Common.o: $(SDIR)/core/Common/Common.cpp $(SDIR)/core/Common/Common.h $(SDIR)/core/Common/CRHM_namespace.h $(SDIR)/core/Common/CRHMException.h $(SDIR)/core/Common/VandP.h $(SDIR)/core/Common/CRHM_constants.h $(SDIR)/core/Common/CHAD_constants.h $(SDIR)/core/Common/PBSM_constants.h| $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/snowcover.o: $(SDIR)/core/Common/snowcover.cpp $(SDIR)/core/Common/snowcover.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/VarCHRM.o: $(SDIR)/core/CRHM_parse/VarCHRM.cpp $(SDIR)/core/CRHM_parse/VarCHRM.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/execbase.o: $(SDIR)/core/CRHM_parse/exec/execbase.cpp $(SDIR)/core/CRHM_parse/exec/execbase.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/CRHMmain.o: $(SDIR)/core/CRHMmain/CRHMmain.cpp $(SDIR)/core/CRHMmain/CRHMmain.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/MacroUnit.o: $(SDIR)/core/MacroUnit/MacroUnit.cpp $(SDIR)/core/MacroUnit/MacroUnit.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/ClassMacro.o: $(SDIR)/core/MacroUnit/ClassMacro.cpp $(SDIR)/core/MacroUnit/ClassMacro.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/DefCRHM.o: $(SDIR)/core/MacroUnit/DefCRHM/DefCRHM.cpp $(SDIR)/core/MacroUnit/DefCRHM/DefCRHM.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclparam.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclparam.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclparam.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclvar.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclvar.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclvar.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdecldiag.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdecldiag.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdecldiag.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclstatvar.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclstatvar.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclstatvar.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdecllocal.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdecllocal.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdecllocal.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclobs.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclobs.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclobs.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclgetvar.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclgetvar.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclgetvar.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclputvar.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclputvar.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclputvar.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclputparam.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclputparam.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclputparam.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclreadobs.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclreadobs.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclreadobs.h | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

$(ODIR)/Defdeclobsfunc.o: $(SDIR)/core/MacroUnit/DefCRHM/Defdeclobsfunc.cpp $(SDIR)/core/MacroUnit/DefCRHM/Defdeclobsfunc.h | $(ODIR)
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
