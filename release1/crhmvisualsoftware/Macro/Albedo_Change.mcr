Albedo_Change
declparam, Albedo_change, NHRU,0.001, 0.0, 1.0, "albedo step", (m)
declparam, Albedo_min, NHRU,0.1, 0.01, 1.0, "minimum albedo", (m)
declparam, Albedo_max, NHRU,0.1, 0.01, 1.0, "maximum albedo", (m)
declparam, Albedo_Julian, NHRU,195, 1, 366, "Julian day", ()
declvar, Albedo, NHRU, "vegetation Albedo", ()
declvar, Albedo_Start, NHRU, "vegetation Albedo", ()
command
  if(STEP == 1)
    Albedo[hh] =Albedo_min[hh]
  endif

  if(JULIAN >= Albedo_Julian)
    Albedo_Start[hh] = JULIAN

    if(LASTINT)
      Albedo[hh] =  Albedo[hh] + Albedo_change[hh]
    endif

    if(Albedo[hh] > Albedo_max[hh])
        Albedo[hh] = Albedo_max[hh]
    endif
  endif
end
