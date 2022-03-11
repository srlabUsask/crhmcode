//created by Manishankar Mondal

#include "Classshared.h"

#include <algorithm>
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM/ClassCRHM.h"
#include "../newmodules/SnobalDefines.h"
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