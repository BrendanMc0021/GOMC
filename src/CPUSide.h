/*******************************************************************************
GPU OPTIMIZED MONTE CARLO (GOMC) 2.75
Copyright (C) 2022 GOMC Group
A copy of the MIT License can be found in License.txt
along with this program, also can be found at <https://opensource.org/licenses/MIT>.
********************************************************************************/
#ifndef CPU_SIDE_H
#define CPU_SIDE_H

//Member vars
#include "Clock.h"
#include "ConsoleOutput.h"
#include "PDBOutput.h"
#include "ExtendedSystemOutput.h"
#include "BlockOutput.h"
#include "HistOutput.h"
#include "ConfigSetup.h"
#include "OutputVars.h"
#include "CheckpointOutput.h"
#include "EnPartCntSampleOutput.h"
#include "FreeEnergyOutput.h"
#include "PSFOutput.h"

#include <vector>

class System;
class StaticVals;
class OutputableBase;

struct CPUSide {
  CPUSide(System & sys, StaticVals & statV, Setup & set);
  void Init(PDBSetup const& pdbSet, 
            config_setup::Input const& in,
            config_setup::Output const& out,
            config_setup::SystemVals const& sys,
            const ulong tillEquil, 
            const ulong totSteps, 
            ulong startStep);
  void Output(const ulong step);

  ulong equilSteps;
private:
  Clock timer;
  std::vector<OutputableBase *> outObj;
  OutputVars varRef;
  PDBOutput pdb;
  PSFOutput psf;
  ExtendedSystemOutput xstBinary;
  ConsoleOutput console;
  BlockAverages block;
  Histogram hist;
  CheckpointOutput checkpoint;
#if ENSEMBLE == GCMC
  EnPartCntSample sample_N_E;
#endif
#if ENSEMBLE == NVT || ENSEMBLE == NPT
  FreeEnergyOutput freeEnergy;
#endif
};

#endif /*CPU_SIDE_H*/
