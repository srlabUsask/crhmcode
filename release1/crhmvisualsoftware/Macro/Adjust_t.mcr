Adjust_t change monthly air temperature
declreadobs, t, NHRU," temperature observation", (°C)
declreadobs, t2, NHRU,"second temperature observation", (°C)
declparam, Delta_t, NHRU, [5.0], -20.0, 20.0, "temperature adjustment", (m)
setpeer "" 50
command
  var i
  i = 0
  if(STEP == 1 && hh == 1)
     ReadAheadObs = i
     while(ReadAheadObs  == 0)
       if(MONTH == 3)
         t2[hh] = t[hh] + Delta_t[hh]
         WriteAheadObs = i
       endif
         i = i + 1
         ReadAheadObs = i
    endwhile
    ReadAheadObs = 0 // optional
  endif
end
