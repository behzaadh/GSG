%% The new reservoir Intersect simulator employs the .gsg file format as a 
% restart file. This file aims to overwrite specified parameters to .gsg 
% such as Intersect restart file format.
% Note that this function is called by write_gsg_all.m function. Try to not
% use it separately.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                     Behzad Hosseinzadeh                                %
%                     contact: behzadh@dtu.dk                            %
%                     version: v1.0                                      %
%                     Date: 2024-01-22                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function write_gsg(filename,idx_start,data)
% filename = 'reservoir.gsg';

if ~exist('filename', 'var')
    error(['''' filename ''' does not exist']); 
end

% Open file
fclose all;
fid = fopen(filename, 'r+');
if fid < 3 
    error 'Error while opening file'; 
end

fseek(fid, idx_start, 'bof');

fwrite(fid, data, 'double', 0, 'l');

fclose(fid);
end