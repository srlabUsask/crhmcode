Calc_tmean
declreadobs, t, NOBS," temperature observation", (°C)
declvar, Status, NHRU, "indicates if Obs available", ()
declvar, t_mean, NHRU, "calculated t mean", (°C)
command
  var sum, i
  if(STEP == 1)
    t_mean[hh] = 0
  endif
  if(STEP%FREQ == 0)
    sum = 0
    Status[hh] = 0
    for(i = 0; i < FREQ; i=i+1)
      ReadAheadObs = i
      Status[hh] = Status[hh] + ReadAheadObs
      sum = sum + t[hh]
    endfor
     t_mean[hh] = sum/FREQ
  endif
end
