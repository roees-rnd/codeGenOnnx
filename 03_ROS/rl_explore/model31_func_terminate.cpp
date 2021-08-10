//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: model31_func_terminate.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Jul-2021 10:34:40
//

// Include Files
#include "model31_func_terminate.h"
#include "model31_func_data.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void model31_func_terminate()
{
  // omp_destroy_nest_lock(&emlrtNestLockGlobal);  XXX
  isInitialized_model31_func = false;
}

//
// File trailer for model31_func_terminate.cpp
//
// [EOF]
//
