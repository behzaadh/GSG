function write_gsg_all(filename,out,fieldName)
% filename = 'reservoir.gsg';

if ~exist('filename', 'var')
    error(['''' filename ''' does not exist']); 
end

% Open file
fclose all;
fid = fopen(filename, 'r');
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

fseek(fid, idx_start, 'bof');
while ~feof(fid)
    size_skip = fread(fid, 1, 'int32', 0, 'l');
    if size_skip == 10
        keyword = deblank(fread(fid, size_skip, 'uint8=>char')');
        if strcmp(keyword,'CASE_PROPS')
            disp('All properties have been read successfully!');
        end
    end
    fseek(fid, size_skip+8, 'cof');
    size_header = fread(fid, 1, 'int32', 0, 'l');
    keyword = deblank(fread(fid, size_header, 'uint8=>char')');
    keyword = strrep(keyword,'[','_');
    keyword = strrep(keyword,']','_');
    fseek(fid, 4, 'cof');
    type = fread(fid, 1, 'int64', 0, 'l');
    array_size = fread(fid, 1, 'int32', 0, 'l');

    if (isempty(type))
        break;
    end

    switch type
        case 0
            start_idx.(keyword) = ftell(fid);
            fseek(fid, array_size*4, 'cof');
        case 2
            start_idx.(keyword) = ftell(fid);
            fseek(fid, array_size*8, 'cof');
        otherwise
            disp('No valid type!')
    end

end

fclose(fid);

for i = 1:length(fieldName)
    name = fieldName(i);
    write_gsg(filename,start_idx.(name),out.(name));
end

end