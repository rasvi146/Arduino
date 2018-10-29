function addData(type, data)
    switch type 
        case 'chins_crossfit'
            load trainingData.mat
            today = datenum(date);
            trainingData.chins.crossfit.days_since_last_data(end+1) = datenum(date) - sum(trainingData.chins.crossfit.days_since_last_data) - datenum(trainingData.startDate);
            trainingData.chins.crossfit.count(end+1) = data;
            save('trainingData.mat','trainingData');
        case 'chins_strict'
            load trainingData.mat
            today = datenum(date);
            trainingData.chins.strict.days_since_last_data(end+1) = datenum(date) - sum(trainingData.chins.strict.days_since_last_data) - datenum(trainingData.startDate);
            trainingData.chins.strict.count(end+1) = data;
            save('trainingData.mat','trainingData');
        case 'bench_3x3'
            load trainingData.mat
            today = datenum(date);
            trainingData.bench.reps_3x3.days_since_last_data(end+1) = datenum(date) - sum(trainingData.bench.reps_3x3.days_since_last_data) - datenum(trainingData.startDate);
            trainingData.bench.reps_3x3.weight(end+1) = data;
            save('trainingData.mat','trainingData');
        case 'bench_max'
            load trainingData.mat
            today = datenum(date);
            trainingData.bench.reps_max.days_since_last_data(end+1) = datenum(date) - sum(trainingData.bench.rep_max.days_since_last_data) - datenum(trainingData.startDate);
            trainingData.bench.reps_max.weight(end+1) = data;
            save('trainingData.mat','trainingData');
        otherwise
            fprintf('ERROR: \n addData(type, data) \n type is: \n   * chins_crossfit \n   * chins_strict \n   * bench_3x3 \n   * bench_max \n')
            fprintf(' data is: \n   * amount \n   * weight \n')
    end
end