function out = read_gsg(filename,idx_start,size_data)
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
% 
% fseek(fid, 0, 'cof');
% buf = fread(fid, 1, 'double', 0, 'l');

% idx = 3643;
% size = 828;

fseek(fid, idx_start, 'cof');

out = fread(fid, size_data, 'double', 0, 'l');

fclose(fid);
end
% -------------- NAME ------------------------ File Index Location --------
% AQUEOUS_COMPONENT_MOLE_FRACTION[1]                     
% AQUEOUS_COMPONENT_MOLE_FRACTION[2]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[3]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[4]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[5]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[6]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[7]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[8]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[9]           
% AQUEOUS_COMPONENT_MOLE_FRACTION[10]          
% AQUEOUS_COMPONENT_MOLE_FRACTION[11]          
% AQUEOUS_COMPONENT_MOLE_FRACTION[12]          
% AQUEOUS_COMPONENT_MOLE_FRACTION[13]          
% AQUEOUS_COMPONENT_MOLE_FRACTION[14]          
% COMPACTION_CURVE_LOCATION                    
% COMPONENT_EQUIV_CONC[0]                      
% COMPONENT_EQUIV_CONC[1]                      
% COMPONENT_EQUIV_CONC[2]                      
% COMPONENT_EQUIV_CONC[3]                      
% COMPONENT_EQUIV_CONC[4]                      
% COMPONENT_EQUIV_CONC[5]                      
% COMPONENT_EQUIV_CONC[6]                      
% COMPONENT_EQUIV_CONC[7]                      
% COMPONENT_EQUIV_CONC[8]                      
% COMPONENT_EQUIV_CONC[9]                      
% COMPONENT_EQUIV_CONC[10]                     
% COMPONENT_EQUIV_CONC[11]                     
% COMPONENT_EQUIV_CONC[12]                     
% COMPONENT_EQUIV_CONC[13]                     
% GAS_SATURATION                               
% OIL_SATURATION                               
% PRESSURE                                     
% RES_PORE_VOLUME                              
% SOLID_COMPONENT_MOLE_FRACTION[1]             
% SOLID_VOLUME_FRACTION                        
% TEMPERATURE                                  
% WATER_SATURATION                             
% LIQUID_COMPONENT_MOLE_FRACTION[1]            
% LIQUID_COMPONENT_MOLE_FRACTION[2]            
% LIQUID_COMPONENT_MOLE_FRACTION[3]            
% LIQUID_COMPONENT_MOLE_FRACTION[4]            
% LIQUID_COMPONENT_MOLE_FRACTION[5]            
% MAX_WATER_CAPILLARY_PRESSURE                 
% MOBILITY_MULTIPLIER                          
% PREV_NODE_PHASESTATE                         
% SOLID_INITIAL_PORE_VOLUME_MULTIPLIER         
% VAPOR_COMPONENT_MOLE_FRACTION[1]             
% VAPOR_COMPONENT_MOLE_FRACTION[2]             
% VAPOR_COMPONENT_MOLE_FRACTION[3]             
% VAPOR_COMPONENT_MOLE_FRACTION[4]             
% VAPOR_COMPONENT_MOLE_FRACTION[5]             
% VAPOR_COMPONENT_MOLE_FRACTION[6]             
