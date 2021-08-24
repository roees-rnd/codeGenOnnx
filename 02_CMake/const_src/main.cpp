
#include "main.h"
#include <iostream>
#include "model31_func.h"
#include "model31_func_terminate.h"
#include "unitTest.h"
#include "unitTest_out.h"

#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <fstream>

#include <chrono>
using namespace std::chrono;

// Function Declarations
static void argInit_1x16_real32_T(float result[16]);

static float argInit_real32_T();

static float main_model31_func(float * fv, float *out);

// Function Definitions
//
// Arguments    : float result[16]
// Return Type  : void
//
static void argInit_1x16_real32_T(float result[16])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 16; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = (float)result[idx1]; // argInit_real32_T();
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : void
//
static float main_model31_func(float *fv, float *out)
{
  // float out[3];
  // Initialize function 'model31_func' input arguments.
  // Initialize function input argument 'in'.
  // Call the entry-point 'model31_func'.
  argInit_1x16_real32_T(fv);
  model31_func(fv, out);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  std::ofstream myfile;

  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  float out_[3]={0};
  float fv[16];
  auto start = high_resolution_clock::now();
  int cntr = 0;

  int lenRec = (sizeof(inVec)/sizeof(*inVec)/16);
  float *testRes = new float[lenRec*3];
  std::cout << "Length of array = " << lenRec << std::endl;

  for (int vecNum=0; vecNum<lenRec;vecNum++){
    for (int i=0; i<16 ; i++){
      fv[i] = inVec[vecNum*16+i];
    }

    main_model31_func(fv, out_);
    cntr++;
    
    // Save results:
    for (int ii=0; ii<3; ii++){
      testRes[vecNum*3+ii]=out_[ii];
    }
    
    
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << (float)cntr/((float)duration.count()*0.000001) << " [Hz]" << std::endl;

  std::cout << "writing UT restults to file" << std::endl;
  float err;
  int numErr = 0;
  myfile.open ("outUnitTest.txt");
  for (int jj=0; jj<lenRec; jj++){
    myfile  << testRes[jj*3] << "," << testRes[jj*3+1] << "," << testRes[jj*3+2] << std::endl;
    err=std::abs(testRes[jj*3]-outVec[jj*3])+std::abs(testRes[jj*3+1]-outVec[jj*3+1])+std::abs(testRes[jj*3+2]-outVec[jj*3+2]);
    if (err>0.01){
      numErr++;
      std::cout << "line #" << jj << ", error = " << err << std::endl;
    }
  }
  std::cout << "Number of unit test errors = " << numErr << " out of " << lenRec << std::endl;
  
  // Terminate the application.
  // You do not need to do this more than one time.
  delete[] testRes;
  model31_func_terminate();
  myfile.close();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
