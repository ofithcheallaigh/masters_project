% In this script, I am trying going to generate a subset where there is
% 5000 samples from grip position

N = 5000; % number of samples per grid I want
data = grid0closeddoorclearhallway;

resultsTable = table();

conditions = {'Grid 0';'Grid 1';'Grid 2';'Grid 3';'Grid 4';'Grid 5';'Grid 6';'Grid 7';'Grid 8';'Grid 9'};


idx_0 = find(data.Grid == 0);
idx_1 = find(data.Grid == 1);
idx_2 = find(data.Grid == 2);
idx_3 = find(data.Grid == 3);
idx_4 = find(data.Grid == 4);
idx_5 = find(data.Grid == 5);
idx_6 = find(data.Grid == 6);
idx_7 = find(data.Grid == 7);
idx_8 = find(data.Grid == 8);
idx_9 = find(data.Grid == 9);




idxs = [idx_0; idx_1; idx_2; idx_3; idx_4; idx_5; idx_6; idx_7; idx_8; idx_9];

T = table(conditions, idxs);

