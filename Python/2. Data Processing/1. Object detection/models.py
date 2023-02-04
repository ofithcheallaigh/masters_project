import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import cm
import seaborn as sns
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler

from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OneHotEncoder

from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC
from sklearn import neighbors

# Read in the data
dataset1 = pd.read_csv("2. Data Processing\\0. Data\midhallway_displaystand_final_dataset.csv")
dataset2 = pd.read_csv("2. Data Processing\\0. Data\midhallway_clear_final_dataset.csv")

# This bit of code is used to change the grid number of the "no object dataset" to 0
# This is needed for the grid number detection work 
mod_dataset2 = dataset2 # Get the data we are intersted in
mod_dataset2.drop(['Grid'],axis=1) # Dropping the original grid with various grid numbers
mod_dataset2['Grid'] = 0 # Replacing with new grid with 0
dataset2 = mod_dataset2 # Reassign to dataset2

data = np.vstack((dataset1,dataset2)) # Create a variable with one dataset stacked on the other


data = pd.DataFrame(data) # Convert to DataFrame
data.columns=["Channel1","Channel2","LabelObject","Grid"] # Assign column names
# data.to_csv('out.txt') # This was here to output a text file to show Ian

# pick out rows depending on grid num
# This was added in to just pick out grid pos 1
# grid1_data = data.loc[data['Grid']==1]
# data = grid1_data

feature_names = ['Channel1','Channel2'] # Features we are interested in
response = data['LabelObject'] # Response we are interested in

# Replaces Yes/No with 1/0. Required because some algo will not accept categorical data
data.LabelObject.replace(('Yes', 'No'), (1, 0), inplace=True) 

# X and y are what will be passed through the algorithms to train the model
X = data[feature_names]
y = data['LabelObject']


# cmap = cm.get_cmap('gnuplot')
# scatter = pd.plotting.scatter_matrix(X, c=response, marker='o', s=40, hist_kwds={'bins':15}, figsize=(9,9), cmap=cmap)
# pd.plotting.scatter_matrix(for_scatter)
# plt.suptitle('Scatter-matrix for each input variable')
# plt.show()
# plt.savefig('object_scatter_matrix. Object: Display Stand')


# Creating Training and Test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0) # train_test_split is the best way to slipt up the data
scaler=MinMaxScaler() # Using a scaler because there can be a lot of variability in the data values
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)


"""
# This will print the accuracy score for variou neigbour numbers
allResults = []
for kValue in range(1,50):
    knn = neighbors.KNeighborsClassifier(n_neighbors=kValue, metric="minkowski",p=1)
    knn = knn.fit(X_train,y_train)
    accuracy = knn.score(X_test, y_test)
    allResults.append(accuracy)
plt.plot(allResults)
plt.xlabel("Number of Neigbours")
plt.ylabel("Accuracy Score")
plt.title("KNN Accuracy Score for k Between 1 and 100")
plt.show()
plt.savefig('scatter_matrix_object_display_stand.jpg') 
"""

# The sections below generate the model accuracy scores
# Model: Logistic regression
logReg = LogisticRegression()
logReg.fit(X_train, y_train)
print('Accuracy of Logistic regression classifier on training set: {:.2f}'.format(logReg.score(X_train, y_train))) # 0.75
print('Accuracy of Logistic regression classifier on test set: {:.2f}'.format(logReg.score(X_test, y_test))) # 0.47

# Model: Decision tree
clf = DecisionTreeClassifier().fit(X_train, y_train)
print('Accuracy of Decision Tree classifier on training set: {:.2f}'.format(clf.score(X_train, y_train))) # 1.00
print('Accuracy of Decision Tree classifier on test set: {:.2f}'.format(clf.score(X_test, y_test))) # 0.87

# Model: KNN
knn = KNeighborsClassifier()
knn.fit(X_train,y_train)
print('Accuracy of K-NN classifier on training set: {:.2f}'.format(knn.score(X_train, y_train))) # 0.95
print('Accuracy of K-NN classifier on test set: {:.2f}'.format(knn.score(X_test, y_test))) # 1.00

# Model: Linear Discriminant Analysis
lda = LinearDiscriminantAnalysis()
lda.fit(X_train, y_train)
print('Accuracy of LDA classifier on training set: {:.2f}'.format(lda.score(X_train, y_train))) #0.86
print('Accuracy of LDA classifier on test set: {:.2f}'.format(lda.score(X_test, y_test))) # 0.67

# Model: Gaussian Naive Bayes
gnb = GaussianNB()
gnb.fit(X_train, y_train)
print('Accuracy of GNB classifier on training set: {:.2f}'.format(gnb.score(X_train, y_train))) # 0.86
print('Accuracy of GNB classifier on test set: {:.2f}'.format(gnb.score(X_test, y_test))) # 0.67  

""" # Model: SVM
svm = SVC()
svm.fit(X_train, y_train)
print('Accuracy of SVM classifier on training set: {:.2f}'.format(svm.score(X_train, y_train))) # 0.91
print('Accuracy of SVM classifier on test set: {:.2f}'.format(svm.score(X_test, y_test))) # 0.80 """
