//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: model31_func.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Jul-2021 10:34:40
//

// Include Files
#include "model31_func.h"
#include "model31_func_data.h"
#include "model31_func_initialize.h"
#include "model31_func_internal_types.h"
#include "predict.h"

// Variable Definitions
static boolean_T mynet_not_empty;

// Function Definitions
//
// A persistent object mynet is used to load the DAG network object.
//  At the first call to this function, the persistent object is constructed and
//  set up. When the function is called subsequent times, the same object is
//  reused to call predict on inputs, avoiding reconstructing and reloading the
//  network object.
//
// Arguments    : const float in[16]
//                float out[3]
// Return Type  : void
//
void model31_func(const float in[16], float out[3])
{
  static coder::ctarget::DeepLearningNetwork mynet;
  if (!isInitialized_model31_func) {
    model31_func_initialize();
  }
  //  Copyright 2018 The MathWorks, Inc.
  if (!mynet_not_empty) {
    mynet.IsInitialized = false;
    mynet_not_empty = true;
  }
  coder::ctarget::DeepLearningNetwork_predict(&mynet, in, out);
}

//
// A persistent object mynet is used to load the DAG network object.
//  At the first call to this function, the persistent object is constructed and
//  set up. When the function is called subsequent times, the same object is
//  reused to call predict on inputs, avoiding reconstructing and reloading the
//  network object.
//
// Arguments    : void
// Return Type  : void
//
void model31_func_init()
{
  mynet_not_empty = false;
}

//
// File trailer for model31_func.cpp
//
// [EOF]
//
