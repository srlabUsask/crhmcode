Grow_Crop
declparam, Ht, NHRU,"[0.1, 0.25, 1.0]", 0.001, 100.0, "vegetation height", (m)
declparam, Init_Crop_Ht, NHRU,"[0.001]", 0.001, 100.0, "initial crop height", (m)
declparam, Crop_Grow_Rate, NHRU,"[0.0]", 0.0, 1.0, "crop growth rate", (m/d)
declparam, JCrop_Start, NHRU,"[121]", 1, 366, "start Julian day", ()
declparam, JCrop_Mature, NHRU,"[182]", 1, 366, "maturity Julian day", ()
declparam, JCrop_Harvest, NHRU,"[228]", 1, 366, "harvest Julian day", ()
declvar, Crop_Ht, NHRU, "crop height", (m)
command
if(STEP == 1)
Ht[hh] = Init_Crop_Ht[hh]
Crop_Ht[hh] = Ht[hh]
endif

if(LASTINT)
if(JULIAN >= JCrop_Start[hh] && JULIAN < JCrop_Mature[hh] && Crop_Grow_Rate[hh] > 0.0)
Ht[hh] =  Ht[hh] + Crop_Grow_Rate[hh]
else if(JULIAN == JCrop_Harvest[hh])
Ht[hh] =  Init_Crop_Ht[hh]
endif
endif

Crop_Ht[hh] = Ht[hh]
endif
end
