ea_RH
declvar, RH, NHRU, "calculated rh", (kPa)
declgetvar, obs, hru_t, (C)
declgetvar, obs, hru_ea,  (kPa)
command
RH[hh] = hru_ea[hh]/estar(hru_t[hh])*100
end
