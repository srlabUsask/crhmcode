//created by Manishankar Mondal

#include "ClassNOP.h"
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