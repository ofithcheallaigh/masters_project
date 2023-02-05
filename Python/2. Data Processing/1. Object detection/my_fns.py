def modify_to_grid_zero_fn(data):
    # mod_dataset2 = dataset2
    data.drop(['Grid'],axis=1) # Dropping the original grid with various grid numbers
    data['Grid'] = 0 # Replacing with new grid with 0
    return data
