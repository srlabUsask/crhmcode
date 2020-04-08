SicartLong
declreadobs, t, NOBS, "temp", (°C)
declreadobs, ea, NOBS, "vapour pressure", (kPa)
declreadobs, rh, NOBS, "relative humidity", ()
declvar,Qlong, NHRU, "Sicart long", (W/m^2)
command
var tau
tau = 0.75
Qlong[hh] = 1.24*((ea[0]*10)/(t[0]+273.15))^(1/7)*(1 + 0.44*rh[0]/100 - 0.18*tau)*5.67E-8*(t[0]+273.15)^4
end
