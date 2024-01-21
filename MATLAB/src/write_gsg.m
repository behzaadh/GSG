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