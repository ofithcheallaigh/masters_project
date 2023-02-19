% 19/2/23
% This script is here to generate new data sets from the original data sets

data_folder = "D:\Courses\UUJ\Research Project\masters_project\MATLAB\Data";

closedDoor = readtable("grid0_closeddoor_clearhallway.csv");
displayStand = readtable("grid0_displaystand_clearhallway.csv");
largeBin = readtable("grid0_largebin_clearhallway.csv");
storageBox = readtable("grid0_storagebox_clearhallway.csv");

valuesOneIn = vertcat(closedDoor,displayStand,largeBin);
valuesTwoIn = vertcat(closedDoor,displayStand,storageBox);
valuesThreeIn = vertcat(closedDoor,largeBin,storageBox);
valuesFourIn = vertcat(displayStand,largeBin,storageBox);

ValuesOneOut = storageBox;
ValuesTwoOut = largeBin;
ValuesThreeOut = displayStand;
ValuesFourOut = closedDoor;

% d = dictionary;