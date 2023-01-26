closed = closeddoorfinaldataset;
open = openhallwayfinaldataset;

T = vertcat(closed,open); % Brings arrays together
[rows,cols] = size(T);

idx = randperm(rows);

T_rand = T(idx(1:end),:);

% trainingData = inputTable(idx(1:m1),:);