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