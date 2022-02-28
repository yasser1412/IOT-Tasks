import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split 
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC

data = pd.read_csv("readings.csv",sep=";")

labels = data.iloc[:,-1]
data = data.iloc[:,0:-1]

# Splitting the data to some to train and some to test
X_train, X_test, y_train, y_test = train_test_split(data,labels,test_size=0.2,random_state=42)

## KNN Model 
clf = KNeighborsClassifier() 

## SVC Model
# clf = SVC(kernel = 'rbf')

## Decision Tree Model
# clf = DecisionTreeClassifier()

## Training the model
clf.fit(X_train, y_train)

## Test .. it should print [2]
# predicted_labels = clf.predict([[30,23,10,10,21,19]])
# print(predicted_labels)

# Printing accuracy
print(clf.score(X_test,y_test))

from joblib import dump, load
dump(clf, 'model.joblib') 
