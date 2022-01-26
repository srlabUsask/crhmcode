//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassNOP.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassNOP* ClassNOP::klone(string name) const{
  return new ClassNOP(name);
}

void ClassNOP::decl(void) {

  Description = "'NO operation module. Use only in macro declstruct as filler.'";

}

void ClassNOP::init(void) {

}

void ClassNOP::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessage(hh, string("'" + Name + " (NOP)'").c_str(), TExtra::BLANK);
  }
  LogDebug(" ");
}
