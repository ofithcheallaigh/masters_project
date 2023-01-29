import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import cm
import seaborn as sns

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


data = pd.read_csv('2. Data Processing\\0. Data\openhallway_displaystand_final_dataset.csv')

# print(data.shape)
feature_names = ['Channel1','Channel2']
response = data['LabelObject']

data.LabelObject.replace(('Yes', 'No'), (1, 0), inplace=True)

# print(data.tail(10))

X = data[feature_names]
y = data['LabelObject']

# sns.scatterplot(x='Channel1', y='Channel2', data=data, hue='LabelObject', ec=None)
# plt.show()

# plt.scatter(data['Channel1'],data['Channel2'],)
# plt.show()

# cmap = cm.get_cmap('gnuplot')
# scatter = pd.plotting.scatter_matrix(X, c=y, marker='o', s=40, hist_kwds={'bins':15}, figsize=(9,9), cmap=cmap)
# plt.suptitle('Scatter-matrix for each input variable')
# plt.show()
# plt.savefig('object_scatter_matrix. Object: Display Stand')


# Creating Training and Test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
scaler=MinMaxScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# print(y_test)



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
plt.savefig('bbject_scatter_matrix_object_display_stand.jpg')


""" # Model: Logistic regression
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

# Model: SVM
svm = SVC()
svm.fit(X_train, y_train)
print('Accuracy of SVM classifier on training set: {:.2f}'.format(svm.score(X_train, y_train))) # 0.91
print('Accuracy of SVM classifier on test set: {:.2f}'.format(svm.score(X_test, y_test))) # 0.80"""
