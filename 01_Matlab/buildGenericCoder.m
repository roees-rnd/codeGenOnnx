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
% cfg.HardwareImplementation.TargetHWDeviceType = 'tmp';
codegen -config cfg model31_func -args {ones(1, 16, 'single')}

% load('buildInfo.mat')
% packNGo(buildInfo,'packType','flat','nestedZipFiles',true,...
%     'minimalHeaders',false,'includeReport',false, 'fileName','allFiles'); % fileName','portzingbit'