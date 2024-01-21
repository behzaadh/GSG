function out = read_gsg_all(filename)
% filename = 'reservoir.gsg';

if ~exist('filename', 'var')
    error(['''' filename ''' does not exist']); 
end

% Open file
fclose all;
fid = fopen(filename);
if fid < 3 
    error 'Error while opening file'; 
end
% header skip
idx_start = 67;
fseek(fid, idx_start, 'bof');
noResult = 1;
while ~feof(fid)
    size_header = fread(fid, 1, 'int32', 0, 'l');
    keyword = deblank(fread(fid, size_header, 'uint8=>char')');
    if strcmp(keyword,'PROP')
        idx_start = ftell(fid) - 8;
        noResult = 0;
        break;
    elseif strcmp(keyword,'AXES')
        fseek(fid, 72, 'cof');
    elseif strcmp(keyword,'GRID')
        fseek(fid, 8, 'cof');
    elseif strcmp(keyword,'GRID_0')
        fseek(fid, 44, 'cof');
    end
end

if noResult == 1
    disp('No props!');
    fclose(fid);
    return;
end
out = struct;

fseek(fid, idx_start, 'bof');
while ~feof(fid)
    size_skip = fread(fid, 1, 'int32', 0, 'l');
    keyword = deblank(fread(fid, size_skip, 'uint8=>char')');
    if strcmp(keyword,'CASE_PROPS')
        disp('All properties have been read successfully!');
        break;
    end
    fseek(fid, 8, 'cof');
    size_header = fread(fid, 1, 'int32', 0, 'l');
    keyword = deblank(fread(fid, size_header, 'uint8=>char')');
    keyword = strrep(keyword,'[','_');
    keyword = strrep(keyword,']','_');
    fseek(fid, 4, 'cof');
    type = fread(fid, 1, 'int64', 0, 'l');
    array_size = fread(fid, 1, 'int32', 0, 'l');
    
    data = [];
    if (isempty(type))
        break;
    end

    switch type
        case 0
            data = fread(fid, array_size, 'int32', 0, 'l');
        case 1
            data = fread(fid, array_size, 'float', 0, 'l');
        case 2
            data = fread(fid, array_size, 'double', 0, 'l');
        otherwise
            disp('No valid type!')
            fclose(fid);
            return;
    end
    
    out.(keyword) = data;
end

fclose(fid);
end