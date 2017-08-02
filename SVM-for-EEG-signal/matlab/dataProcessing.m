function dataProcessing (usage, channelLocationFile)
% Function for preprocessing trainig or testing dataset for SVM (Support Vector Machine).
% The EEGLAB and the ERPLAB are needed for correct running.
%
% Function has two arguments. The first one says what kind of action will be done.
% Argument could be 'train' or 'test'. The second one is a path to file for
% channel location. This file is included in EEGLAB directory.
%
% In given directory, files with .vhdr extension are selected and
% processed. To each .vhdr file match .eeg and .vmrk files.
% Signal is read end edited by EEGLAB and ERPLAB functions.
%
% ********** Signal processing: ************
% 1) Location of electrodes channels
% 2) Application of basic IIR filter
% 3) Creation of event list 
% 4) Selection of epochs
% 5) Artefact detection
% 6) Signal averaging
% 7) Finding peak latency and amplitude for each number in averaged
% signal
% 
% ************* Data parser ****************
% Data from each epoch are parsed to one file.
% For training, the scheme is: 
%   <class> <index1>:<value1> <index2>:<value2> ...
%
% For test, the scheme is almost the same, but the <class> number is
% not important.
% ******************************************
%
% Author: Tereza Štanglová
% University of West Bohemia, Czech Republic
% 2015

if nargin ~= 2
    fprintf(1, 'Wrong argument. Please, read help.\n');
    return;
end
if strcmp(usage, 'train')
    action = 0;
elseif strcmp(usage, 'test')
    action = 1;
else 
    fprintf(1, 'Wrong argument. Please, read help.\n');
    return;
end

% name of directory with .vhdr files
workdirname = uigetdir('', 'Select the directory');

if workdirname == 0
    return
end

workdir = dir(workdirname);

if action == 0
    trainDir = 'training_data'; % directory for results
    trainDirPath = strcat(workdirname,'/', trainDir);
    
    if ~exist(trainDirPath, 'dir')
        mkdir(workdirname, trainDir);
    end

elseif action == 1
    testDir = 'test_data'; % directory for results
    testDirPath = strcat(workdirname,'/', testDir); 
    
    if ~exist(testDirPath, 'dir')
        mkdir(workdirname, testDir);
    end
end

erpSetsDir = 'erp_sets'; % directory for erp sets
erpSetsDirPath = strcat(workdirname,'/', erpSetsDir);

AmpLatDirName = 'amp_lat'; % directory for file with amplitude and latency values
AmpLatDirPath = strcat(workdirname,'/', AmpLatDirName);

if ~exist(erpSetsDirPath, 'dir')
    mkdir(workdirname, erpSetsDir);
end

if ~exist(AmpLatDirPath, 'dir')
    mkdir(workdirname, AmpLatDirName);
end

numberOfFiles = size(workdir, 1);

% ==== number for statistic ====
totalCount=0; % total count of files
acceptedCount=0; % count of accepted files

for i = 1:numberOfFiles
    
    file = workdir(i).name;
    if file(1) ~= '.' % to exclude '.' and '..' dir
       [pathstr, name, ext] = fileparts(file);
       if strcmp(ext, '.vhdr')
           totalCount=totalCount+1;
           
           fprintf(1, '\nThe %d. dataset "%s" is processing.\n\n', totalCount, name);
           splitedName = regexp(name,'_','split');

           
           
           erpFile = strcat('erpSet_', name, '.erp');
           
       % beginning od code for signal processing     
       
            EEG = pop_loadbv(workdirname, file, [], [1 2 3]); % load Pz, Cz, Fz electrode
            EEG.setname = name;
            EEG = eeg_checkset( EEG );
            
            % channel location
            try
                EEG = pop_chanedit(EEG, 'lookup', channelLocationFile);
            catch
                fprintf(1, '\nThe path for channel location file is wrong! Script has stopped. Please, enter new path.\n');
                return;
            end
            EEG = eeg_checkset( EEG );
            
            % basic IIR filter
            EEG = pop_basicfilter( EEG,  1:3 , 'Cutoff',  30, 'Design', 'butter', 'Filter', 'lowpass', 'Order',  2 );
            EEG = eeg_checkset( EEG );
            
            % events with the same information are marked
            EEG = pop_editeventlist( EEG , 'AlphanumericCleaning', 'on', 'BoundaryNumeric', ...
                { -99}, 'BoundaryString', { 'boundary' }, 'List', 'eventList.txt', 'SendEL2', 'EEG', 'Warning', 'off' );
            EEG = eeg_checkset( EEG );
            
            % signal is separated to epochs by markers
            % epoch is in interval 200 ms before event and 800 second after
            % event
            % the second interval is for baseline correction
            EEG = pop_epochbin( EEG , [-200.0  800.0], [-50 0]);
            EEG = eeg_checkset( EEG );
            
            % artefacts detection, epochs with artefacts are removed
            EEG  = pop_artextval( EEG , 'Channel',  1:3, 'Flag',  1, 'Threshold', [ -50 80], 'Twindow', [ -200 799] );
            EEG = eeg_checkset( EEG );
            
            % avarage
            ERP = pop_averager( EEG , 'Criterion', 'good', 'ExcludeBoundary', 'on', 'SEM', 'on');
            
            % we need to have some epoch from each number
            rejectCount=0;
            for fn = 1:9
               if ERP.ntrials.accepted(fn) == 0
                   rejectCount=rejectCount+1;
               end
            end
            
            if rejectCount ~= 0
                % script will continue without this sample
                continue;
            else % file has epochs from each number
                acceptedCount=acceptedCount+1; 
                
                % erp set is saved
                ERP = pop_savemyerp(ERP, 'erpname', 'erpPokus', 'filename', erpFile, 'filepath', erpSetsDirPath);

                for j=1:9
                    if action == 0
                        % files for peak amplitude and latency
                        ampFile = strcat(AmpLatDirPath, '/', int2str(totalCount), '_targ_', splitedName{end}, '_epoch_', int2str(j), '_amp', '.txt');
                        latFile = strcat(AmpLatDirPath, '/', int2str(totalCount), '_targ_', splitedName{end}, '_epoch_', int2str(j), '_lat', '.txt');
                    else
                        % files for peak amplitude and latency
                        ampFile = strcat(AmpLatDirPath, '/', int2str(totalCount), '_targ-', name, '-epoch_', int2str(j), '_amp', '.txt');
                        latFile = strcat(AmpLatDirPath, '/', int2str(totalCount), '_targ-', name, '-epoch_', int2str(j), '_lat', '.txt');
                    end

                    % peak amplitude
                    % pop_geterpvalues( erp set, interval latence (ms), indexy cisel, indexy
                    % elektrod)
                    amp = pop_geterpvalues( ERP, [ 250 450], j, 1:3,  'Baseline', 'pre', ...
                        'FileFormat', 'short', 'Filename', ampFile, 'Fracreplace', 'NaN', ...
                        'InterpFactor', 1, 'Measure', 'peakampbl', 'Neighborhood',3, ...
                        'Peakpolarity', 'positive', 'Peakreplace', 'absolute', 'Resolution', 3);

                    % peak latency
                    lat = pop_geterpvalues( ERP, [ 250 450], j, 1:3 , 'Baseline', 'pre', ...
                        'FileFormat', 'short', 'Filename', latFile, 'Fracreplace', 'NaN', ...
                        'InterpFactor', 1, 'Measure', 'peaklatbl', 'Neighborhood', 3, ...
                        'Peakpolarity', 'positive', 'Peakreplace', 'absolute', 'Resolution',3 );

                end
            end

            clearvars EEG ERP;
       
            % end od code for signal processing
       
            fprintf(1, '\nThe %d. dataset is done.\n', acceptedCount);
       
       end    
    end
    
end

fprintf(1, '\nTotal count of files is %d where %d files are accepted.\n\n', totalCount, acceptedCount);

% ==================== DATA PARSER ===================

    d = dir(AmpLatDirPath);
    numberOfFiles = length(d);
    numberOfCycles = (numberOfFiles-2)/18;

    % If 'train' was given as an input parameter, files for each number 
    % will be parsed according a SVM scheme.
    if action == 0
        TRAINING_FILES = { 'train1' 'train2' 'train3' 'train4' 'train5' 'train6' 'train7' 'train8' 'train9' };
        for i=1:numberOfCycles
            for j=1:2:numberOfFiles
                file_amp = d(j).name;

                [pathstr, name, ext] = fileparts(file_amp);
                splitedName = regexp(name,'_','split');

                indexOfDataSet = cellstr(splitedName(1));
                iStr = num2str(i);

                if strcmp(iStr, indexOfDataSet)
                    fileAmpWholeName = strcat(AmpLatDirPath, '/',file_amp);
                    %fprintf(1,'File Amp name: %s\n', file_amp);

                    fid_amp = fopen(fileAmpWholeName);
                      AMP = textscan(fid_amp, '%s %s %s', 1, 'headerlines', 1);
                      %AMP{:}
                    fclose(fid_amp);

                    file_lat = d(j+1).name;
                    fileLatWhileName = strcat(AmpLatDirPath, '/', file_lat);
                    %fprintf(1,'File Lat name: %s\n', file_lat);
                    fid_lat = fopen(fileLatWhileName);
                      LAT = textscan(fid_lat, '%s %s %s', 1, 'headerlines', 1);
                      %LAT{:}
                    fclose(fid_lat);

                    indexOfNumber = cellfun(@str2num, {splitedName{3}});
                    indexOfEpoch = cellfun(@str2num, {splitedName{5}});

                    processed_file = strcat(trainDirPath, '/', TRAINING_FILES(indexOfNumber));

                    % in each file is created text with specific structure
                    % which is required for SVM
                    fid_process = fopen(char(processed_file), 'a+');        
                        if indexOfNumber == indexOfEpoch
                            lineInFile = strcat('1 1:', AMP{1}, ' 2:', LAT{1}, ' 3:', AMP{2}, ' 4:', LAT{2}, ' 5:', AMP{3}, ' 6:', LAT{3}, '\n');
                            fprintf(fid_process, char(lineInFile));
                        else
                            lineInFile = strcat('0 1:', AMP{1}, ' 2:', LAT{1}, ' 3:', AMP{2}, ' 4:', LAT{2}, ' 5:', AMP{3}, ' 6:', LAT{3}, '\n');
                            fprintf(fid_process, char(lineInFile));
                        end    
                    fclose(fid_process);  

                end    

            end 
        end
    % If 'test' was given as an input parameter, for each input file will
    % be created a directory witch nine other files. Each of them for one
    % number. These files will be an input for SVM prediction.
    else
        for i=1:numberOfCycles
            for j=1:2:numberOfFiles
                file_amp = d(j).name;
                    % Creating a new directory for files for prediction
                    if file_amp(1) ~= '.' % to exclude '.' and '..' dir
                        [filePath, fileName, fileExt] = fileparts(file_amp);
                        splitedInputFile = regexp(fileName,'-','split');
                        if ~exist(splitedInputFile{2}, 'dir')
                            mkdir(testDirPath, splitedInputFile{2});
                        end
                    end
                
                [pathstr, name, ext] = fileparts(file_amp);
                splitedName = regexp(name,'_','split');
                
                indexOfDataSet = cellstr(splitedName(1));
                iStr = num2str(i);

                if strcmp(iStr, indexOfDataSet)
                    fileAmpWholeName = strcat(AmpLatDirPath, '/',file_amp);

                    fid_amp = fopen(fileAmpWholeName);
                      AMP = textscan(fid_amp, '%s %s %s', 1, 'headerlines', 1);
                    fclose(fid_amp);

                    file_lat = d(j+1).name;
                    fileLatWhileName = strcat(AmpLatDirPath, '/', file_lat);
                    
                    fid_lat = fopen(fileLatWhileName);
                      LAT = textscan(fid_lat, '%s %s %s', 1, 'headerlines', 1);
                    fclose(fid_lat);

                    indexOfEpoch = cellfun(@str2num, {splitedName{end-1}});
                    processed_file = strcat(testDirPath, '/', splitedInputFile{2}, '/', splitedInputFile{2}, '_number_', num2str(indexOfEpoch));

                    % We need to save one file for each epoch. The SVM
                    % prediction will process this file and a file with
                    % model for corresponding number. The <class> number is
                    % not important.
                    fid_process = fopen(char(processed_file), 'a+'); 
                        lineInFile = strcat('-1 1:', AMP{1}, ' 2:', LAT{1}, ' 3:', AMP{2}, ' 4:', LAT{2}, ' 5:', AMP{3}, ' 6:', LAT{3}, '\n');
                        fprintf(fid_process, char(lineInFile));   
                    fclose(fid_process);  

                end 
            end 
        end
        
    end
    
    fprintf(1,'Data parser is done.\n');
   
end