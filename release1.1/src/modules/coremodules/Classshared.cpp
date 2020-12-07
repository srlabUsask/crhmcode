//created by Manishankar Mondal

#include "Classshared.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

Classshared* Classshared::klone(string name) const{
  return new Classshared(name);
}

void Classshared::decl(void) {

  Description = "'System module only. NEVER use!'";

}

void Classshared::init(void) {

}