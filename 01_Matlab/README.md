# Deploying a pretrained onnx model using Matlab

## 1. Convert onnx model to Matlab DAGNetwork object

**Note:** Directed acyclic graph (DAG) network for deep learning

### Import model from onnx file:
```matlab
net2 = importONNXNetwork('model31.onnx', 'OutputLayerType', 'classification');
```
**needed licences:** matlab, neural_network_toolbox

### save network:
```matlab
save('network_modle31.mat', net2);
```

## 2. Create a function that utilizes the network
Implemented in `model31_func.m`:
```matlab
% Copyright 2018 The MathWorks, Inc.

function out = model31_func(in) 
%#codegen

% A persistent object mynet is used to load the DAG network object.
% At the first call to this function, the persistent object is constructed and
% set up. When the function is called subsequent times, the same object is reused 
% to call predict on inputs, avoiding reconstructing and reloading the
% network object.

persistent mynet;
if isempty(mynet)
       mynet = coder.loadDeepLearningNetwork('network_modle31.mat','net2');
end

out = mynet.predict(in);
```
## 3. Unit test
Implemented in `unitTest.m`:
```matlab
% This code:
% 1. Unit-tests pytorch against imported onnx model to matlab:
%    Using:
%       a. inputs from the recoreded pytorch inputs-outputs file "unitTest_pytorch.csv"
%       b. loaded pytorch model model31.onnx
%    Infer matlab outputs and compare to outputs in "unitTest_pytorch.csv".
% 2. Generate "unitTest.h":
%    Recorded inputs of pytorch in c format for unit-testing pytorch
%    againts generated code (used in ../02_Cmake).
% 3. Generate "unitTest_out.h":
%    Recorded outputs of pytorch in c format for unit-testing pytorch
%    againts generated code (used in ../02_Cmake).
%
% 
% Needed matlab licenses:
% 1. distrib_computing_toolbox
% 2. matlab
% 3. neural_network_toolbox

A = load('unitTest_pytorch.csv');
....
...
..
.
```

## 4. Code generation
Implemented in `buildGenericCoder.m`:
```matlab
% This code generates c code of network stored in network_model31.mat and
% used by model31_func.m
%
% The licenses needed to run this code are:
% 1. identification_toolbox
% 2. matlab
% 3. matlab_coder
% 4. neural_network_toolbox
% 5. rtw_embedded_coder
%
% It is usually beneficial to run unitTest.m when deploying generated code.

cfg = coder.config('lib');
cfg.TargetLang = 'C++';
cfg.GenCodeOnly = true;
cfg.GenerateReport = true;
dlconfig = coder.DeepLearningConfig(TargetLibrary='none');
cfg.DeepLearningConfig = dlconfig;
codegen -config cfg model31_func -args {ones(1, 16, 'single')}
``` 
**Needed licenses:**
identification_toolbox
matlab
matlab_coder
neural_network_toolbox
rtw_embedded_coder


## Next steps are done in the 02_CMake folder