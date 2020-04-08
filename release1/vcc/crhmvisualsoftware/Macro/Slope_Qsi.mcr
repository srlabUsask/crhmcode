Slope_Qsi
declobs, Qsi, NHRU, "Created short-wave", (W/m2)
declreadobs, Qsi, NOBS, "measured short-wave", (W/m2)
declgetvar, global, Qdro, "short-wave direct", (W/m2)
declgetvar, global, Qdfo, "short-wave diffuse", (W/m2)
declgetvar, global, Qdflat, "short-wave both", (W/m2)
declvar, Short, NHRU, "short-wave", (W/m2)
declvar, ShortC, NHRU, "corrected short-wave for slope", (W/m2)
setpeer, "Qdro"
command
Short[hh] = Qdro[hh] + Qdfo[hh]
if(Qdflat[hh] > 0.01)
  ShortC[hh] = Qsi[hh]/Qdflat[hh]*Short[hh]
  Qsi[hh] = ShortC[hh]
else
  ShortC[hh] = 0
  Qsi[hh] = 0
endif
end
