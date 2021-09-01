#include "mex.h"

extern void dllbody_(float *ro);

void mexFunction
  (int nlhs, mxArray *plhs[],
   int nrhs, const mxArray *prhs[])
{
  mexPrintf ("DLLMEX enter nl=%d nr=%d\n", nlhs, nrhs);

  static float ro;
  mexPrintf ("DLLMEX before ro=%f\n", ro);
  dllbody_(&ro);

  mexCallMATLAB(nlhs,plhs, nrhs,prhs, "callee");

  mexPrintf ("DLLMEX leave ro=%f\n", ro);
}

