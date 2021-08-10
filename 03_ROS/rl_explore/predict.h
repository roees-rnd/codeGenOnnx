//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: predict.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 27-Jul-2021 10:34:40
//

#ifndef PREDICT_H
#define PREDICT_H

// Include Files
#include "rtwtypes.h"
//XXX#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
namespace ctarget {
typedef struct coder_ctarget_DeepLearningNetwork_tag_0 DeepLearningNetwork;

}
} // namespace coder

// Function Declarations
namespace coder {
namespace ctarget {
void DeepLearningNetwork_predict(DeepLearningNetwork *obj,
                                 const float varargin_1[16],
                                 float varargout_1[3]);

}
} // namespace coder

#endif
//
// File trailer for predict.h
//
// [EOF]
//
