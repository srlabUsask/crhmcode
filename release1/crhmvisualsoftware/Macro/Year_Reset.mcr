Year_Reset
declgetvar, *, hru_cum_actet, "cumulative evaporation", (mm)
command
  if(LASTINT == 1 && JULIAN == 365)
    hru_cum_actet[hh] = 0.0
  endif
end
