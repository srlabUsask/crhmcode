Calc_t
declvar,t_calc, NHRU, "calculated t", (°C)
declvar,Last_tmax, NHRU, "last tmax", (°C)
declvar,Mod_n, NHRU, "step", ()
declgetvar, obs, hru_tmax, (°C)
declgetvar, obs, hru_tmin, (°C)
command
  var D, Diff
  if(LASTINT)
    Last_tmax[hh] = hru_tmax[hh]
  endif
  D = STEP%FREQ/FREQ
  Diff = hru_tmax[hh] - hru_tmin[hh]
  Mod_n[hh] = D
  if(D > 0.625)
    t_calc[hh] = hru_tmax[hh] - Diff*(D - 0.625)/0.375
  else 
    if(D > 0.25)
      t_calc[hh] =  hru_tmin[hh] + Diff*(D - 0.25)/0.375
    else
      Diff = Last_tmax[hh] - hru_tmin[hh]
      t_calc[hh] =  hru_tmin[hh] + Diff*(0.25 - D)/0.625
    endif
  endif
end
