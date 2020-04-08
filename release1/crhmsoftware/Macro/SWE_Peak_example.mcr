SWE_peak macro to record SWE peak and Julian date 09/02/11
declgetvar, *, SWE, (mm)
declvar, Peak_SWE, NHRU, "peak SWE", (mm)
declvar, Day_Peak_SWE, NHRU, "day peak SWE occurred", ()
setpeer, "Prob"
command
  if(STEP == 1)
    Peak_SWE[hh] = 0
    Day_Peak_SWE[hh] = 0
  endif
  if(SWE[hh]  > Peak_SWE[hh])
    Peak_SWE[hh] = SWE[hh]
    Day_Peak_SWE[hh] = JULIAN
  endif
end
