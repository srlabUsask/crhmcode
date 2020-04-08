No_Display_Macro
declreadobs, Qdflat_err, NOBS, "measured short-wave", (W/m^2)
declvar,No_Display, NHRU, "no errors", ()
command
  if(Qdflat_err[hh] > -9999 && Qdflat_err[hh] < 9999)
    No_Display[hh] = Qdflat_err[hh]
  else
    No_Display[hh] = NO_DISPLAY
  endif
end
