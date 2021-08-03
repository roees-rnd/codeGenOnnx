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