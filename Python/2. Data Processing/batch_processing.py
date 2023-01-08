# Imports
import os
import glob
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Change working folder
filepath = 'D:/Courses/UUJ/Research Project/masters_project/Data Collection/RawDataCollection/Closed Door'
# Change the working dir
os.chdir(filepath)
# list the contents
dir_contents = os.listdir()
# dir_contents

# I only want the .csv files
ext = '*.csv'
files = glob.glob(ext)
print(len(files))  

for file in range(len(files)):
    # print(files[file])
    filename = files[file]
    # filename = filename[:-4]
    # print(filename)

    df = pd.read_csv(files[file])
    col_names = df.columns
    df = df[col_names[0]]

    # Now start pulling out the data
    ch1_start_idx = [i for i,x in enumerate(df.str.contains("Ch1:")) if x]
    ch2_start_idx = [i for i,x in enumerate(df.str.contains("Ch2:")) if x]
    # print("Channel 1 start indexes are:", ch1_start_idx)
    # print("Channel 2 start indexes are:", ch2_start_idx)

    ch1_end_idx = [i for i,x in enumerate(df.str.contains("Ch1 End")) if x]
    ch2_end_idx = [i for i,x in enumerate(df.str.contains("Ch2 End")) if x]
    # print("Channel 1 end indexes are:", ch1_end_idx)
    # print("Channel 2 end indexes are:", ch2_end_idx)

    ch1_time_idx = [i for i,x in enumerate(df.str.contains("Channel 1 time")) if x]
    ch2_time_idx = [i for i,x in enumerate(df.str.contains("Channel 2 time")) if x]
    # print("Channel 1 time indexes is:", ch1_time_idx)
    # print("Channel 2 time indexes is:", ch2_time_idx)

    # Now I need to slide up the data to remove the timestamps and turn the strong 
    # formatted number into an int
    str_numbers = df.str[-4:] # this will give just the last few numbers
    ch1_str_nums = str_numbers.iloc[3:ch1_end_idx[0]] # This is the actual distance numbers

    # Converting to int
    ch1_int_nums = pd.to_numeric(ch1_str_nums, errors='coerce').fillna(0).astype(np.int64)

    ch2_str_nums = str_numbers.iloc[ch2_start_idx[0]+1:ch2_end_idx[0]]
    # ch2_str_nums
    ch2_int_nums = pd.to_numeric(ch2_str_nums, errors='coerce').fillna(0).astype(np.int64)

    # # Plotting the data
    # plt.plot(ch1_int_nums)
    # plt.title("Obstacle: Closed Door, Grid 1")
    # plt.xlabel("Sample")
    # plt.ylabel("Distance")
    # plt.ylim(0,5000) # Max limit used for all plots
    # plt.show()

    final_df = pd.DataFrame(data=[ch1_int_nums,ch2_int_nums])
final_df.head
# final_df.to_csv(filename, sep=',', index=False)