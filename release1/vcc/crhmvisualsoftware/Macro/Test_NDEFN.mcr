Test_NDEFN
declvar, Test_NDEFN, NDEFN, "Test 2D variable", ()
declvar, Test_NDEFN_P, NDEFN, "Test 2D variable", ()
declgetvar, pbsm_M, Results, ()
declparam, Distrib, NDEFN, [1.0], 0.0, 100.0, "Test 2D parametert", "()"
command
  Test_NDEFN[hh][1] = Results[hh][1]
  Test_NDEFN_P[hh][1] = Distrib[hh][1]
end
