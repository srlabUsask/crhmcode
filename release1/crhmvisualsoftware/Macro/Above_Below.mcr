Display displays Above  t >= 0,  Below < 0. 09/02/11
declreadobs, t, NOBS, "temperature", (°C)
declvar, Above, NHRU, "Temperature above zero", (°C)
declvar, Below, NHRU, "Temperature below zero", (°C)
command
if(t[hh] >= 0.0)
  Above[hh] = t[hh]
  Below[hh] =  NO_DISPLAY
else
   Above[hh] = NO_DISPLAY
   Below[hh] = t[hh]
endif
end
