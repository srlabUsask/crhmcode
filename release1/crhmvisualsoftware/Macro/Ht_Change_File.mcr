Ht_Change
declparam, Ht, NHRU, [0.1, 0.25, 1.0], 0.001, 100.0, "vegetation height", (m)
declvar, Ht_Var, NHRU, "vegetation height", (m)
declreadobs, Heights, NOBS, "vegetation heights", (m)
setpeer, "" -1
command
  Ht[hh] =  Heights[hh]
  Ht_Var[hh] = Ht[hh]
end
