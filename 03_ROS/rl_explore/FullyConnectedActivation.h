//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: FullyConnectedActivation.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Jul-2021 10:34:40
//

#ifndef FULLYCONNECTEDACTIVATION_H
#define FULLYCONNECTEDACTIVATION_H

// Include Files
#include "rtwtypes.h"
//XXX#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace layer {
void FullyConnectedActivation_predict(const float X1[16], float Z1[400]);

void b_FullyConnectedActivation_predict(const float X1[400], float Z1[300]);

} // namespace layer
} // namespace coder

#endif
//
// File trailer for FullyConnectedActivation.h
//
// [EOF]
//
