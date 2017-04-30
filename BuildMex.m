function BuildMex(varargin)
%BUILDMEX Compile nominated lab MEX file.
if nargin == 0
    fprintf('Usage: BuildMex(''file1.cpp'', ''file2.cpp'', ...)\n')
end
include = fullfile(pwd, 'Header Files');
source = fullfile(pwd, 'MEX Source Files');
    function Build(name)
        tic
        fprintf('\nBuilding %s... \n', name)
        mex(['-I' include], fullfile(source, name));
        fprintf('Elapsed time: %g sec\n', toc)
    end
cellfun(@Build, varargin);
end
