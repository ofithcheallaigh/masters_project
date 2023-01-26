closed = closeddoorfinaldataset;
open = openhallwayfinaldataset;

T = vertcat(closed,open); % Brings arrays together

% Convert Yes to 1 and No to 2
T.LabelObject = grp2idx(T.LabelObject);

[rows,cols] = size(T);

idx = randperm(rows);

splitPercentage = 0.70;
% m1 is the number of the training data
m1 = round(splitPercentage*rows);
trainingData = T(idx(1:m1),:);
test_data = T(idx(m1+1:end),:);

predictor_names = {'Channel1', 'Channel2'};

predictors = trainingData(:,predictor_names);
response = trainingData.LabelObject;

toNormalise = T(:,predictor_names);
N = normalize(toNormalise,'range');

mdl = fitcknn(N,T.LabelObject,'NumNeighbors',3);
cvmdl1 = crossval(mdl,'KFold',5);
cvmdl2 = crossval(mdl,'Holdout',0.3);

cvm1loss = kfoldLoss(cvmdl1, 'LossFun', 'ClassifError');
Accuracy1 = 1 - kfoldLoss(cvmdl1, 'LossFun', 'ClassifError');

cvm2loss=kfoldLoss(cvmdl2, 'LossFun', 'ClassifError');
Accuracy2 = 1 - kfoldLoss(cvmdl2, 'LossFun', 'ClassifError');


