import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
import time
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.naive_bayes import GaussianNB
from sklearn.neural_network import MLPClassifier
from sklearn.ensemble import AdaBoostClassifier

# Import iris dataset
# - 3 classes
# - 50 samples per class
# - 150 samples total
# - Four dimensions
# - Classification task
iris = datasets.load_iris()

# Set x and y axis
x = iris.data # All four features in dataset
y = iris.target

# Split dataset for training and test
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, shuffle=False)

start_time = time.time()

# Call the KNN classifier
# classifier = KNeighborsClassifier(n_neighbors=7)

# Call the LDA classifier
# classifier = LinearDiscriminantAnalysis(n_components=2)

# Call the Gaussian Naive Bayes classifier
# classifier = GaussianNB()

# Call the MLP Classifier
# classifier = MLPClassifier()

# Call the AdaBoost classifier
classifier = AdaBoostClassifier()

# Fit the data
classifier.fit(x_train, y_train)

# Predict the data
y_pred = classifier.predict(x_test)

end_time = time.time()
elapsed_time = end_time - start_time

print(classification_report(y_test, y_pred))

print('ELAPSED TIME:', elapsed_time)