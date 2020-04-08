Ht_Change
declparam, Ht, NHRU,0.1, 0.01, 100.0, description, (m)
declparam, Ht_change, NHRU,0.1, 0.01, 1.0, description, (m)
declparam, Ht_min, NHRU,0.1, 0.01, 3.0, description, (m)
declparam, Ht_max, NHRU,0.1, 0.01, 3.0, description, (m)
declvar, Ht_Var, NHRU, "vegetation height", (m)
declvar, Date_Var, NHRU, "finds date", (m)
declvar, Date_Julian, NHRU, "Julian date", ()
command
  if(STEP == 1)
    Ht[hh] = Ht_min[hh]
  else
    if(LASTINT)
      Ht[hh] =  Ht[hh] + Ht_change[hh]
    endif
    if( Ht[hh] > Ht_max[hh])
        Ht[hh] = Ht_max[hh]
    endif
  endif
  if(Ht[hh] > 0.17)
    Ht_Var[hh] = Ht[hh]
  else
    Ht_Var[hh] = NO_DISPLAY
  endif
  if(MONTH == 5 && DAY == 27 && FIRSTINT)
    Date_Var[hh] = 1
  endif
  Date_Julian[hh] = JULIAN
end
