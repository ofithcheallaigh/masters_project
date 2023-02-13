% closed = closeddoorfinaldataset;
% open = midhallwayclearfinaldataset;
% 
% inputTable = vertcat(closed,open); % Brings arrays together

data_folder = "D:\Courses\UUJ\Research Project\masters_project\MATLAB\Data";
run_folder = pwd;

cd(data_folder);
[file,path] = uigetfile('*.csv','Select One or More Files','MultiSelect','on');

input_table = readtable(strcat(path,file));

inputTable = input_table;

% Change the Pclass from number to char (categorical variable) for
% convience 
% inputTable.Pclass= num2str(inputTable.Pclass);

% ~~Predictors and Response~~
% This code processes the data into the correct shape for training the
% model
predictorNames = {'Channel1','Channel2'};
toNormalise = inputTable(:,predictorNames);
N = normalize(toNormalise,'range');
predictors = N;
% predictors = inputTable(:,predictorNames);  % Could also be predictorNames = inputTable(:,[3,5,12]);
response = inputTable.Grid;

% ~~Train the classifier~~
% This code specifies all the classifier options and trains the classifier
% option and trains the classifier
% trainedDecisionTreeModel = fitctree(predictors,response,'OptimizeHyperparameters','auto');
% trainedDecisionTreeModel = fitctree(predictors,response);

% ~~Graphic respresentation of the tree~~
% view(trainedDecisionTreeModel,'mode','graph')

results = zeros(1,50);
for n = 1:50
    Mdl_n = fitctree(predictors,response,'MaxNumSplits',n,'CrossVal','on');
    % view(Mdl_n.Trained{1}, 'mode', 'graph')
    validationAccuracy1 = 1 - loss(Mdl_n.Trained{1},predictors,response);
    results(n) = results(n) + validationAccuracy1;
end
% results = results * 100;