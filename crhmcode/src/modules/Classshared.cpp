//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "Classshared.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

Classshared* Classshared::klone(string name) const{
  return new Classshared(name);
}

void Classshared::decl(void) {

  Description = "'System module only. NEVER use!'";

}

void Classshared::init(void) {

}
