Decide_Opportunity
declobs, t0_inhibit#, NHRU, "inhibit incrementing of opportunity time", ()
declgetvar, obs, hru_t, "(°C)"
declreadobs, Qsi, NOBS, "measured short-wave", (W/m^2)
command
if(hru_t[hh] > 0 && Qsi[hh] > 100)
  t0_inhibit#[hh] =1
else
  t0_inhibit#[hh] =0
endif
end
