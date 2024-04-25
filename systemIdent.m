%% from experiment
exp_data = Pole_pos90_use;
[exp_peaks,exp_locs] = findpeaks(exp_data);
exp_num_cycles = numel(exp_peaks)-1;
exp_total_time = (exp_locs(end) - exp_locs(1))*0.01;    %secound
exp_avg_period = exp_total_time/exp_num_cycles;
figure("Name","exp_peaks");
findpeaks(exp_data)
title('experiment peaks')
%% from model 
model_data = SDOSimTest_Log.simulationData.Data;
[model_peaks,model_locs] = findpeaks(model_data);
model_num_cycles = numel(model_peaks)-1;
model_total_time = (model_locs(end) - model_locs(1))*0.01;    %secound
model_avg_period = model_total_time/model_num_cycles;
figure("Name","model_peaks");
findpeaks(model_data)
title('model peaks')