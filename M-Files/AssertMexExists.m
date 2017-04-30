function AssertMexExists(mexfile)
%ASSERTMEXEXISTS  Print error message if file does not exist
assert(exist(mexfile, 'file') == 3, ...
    'Please compile %s.cpp with mex', mexfile)
