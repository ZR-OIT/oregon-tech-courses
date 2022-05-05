import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from sklearn import decomposition
import matplotlib.patches as mpatches

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

# Two features in dataset (sepal length and width)
two_dimensions = x[:, :2]

# Store the feature and class names
features = iris.feature_names
classes = iris.target_names

print('Feature names:')
print(features)
print('Class names:')
print(classes)

# With help from:
# -> https://scikit-learn.org/stable/auto_examples/datasets/plot_iris_dataset.html
# -> https://matplotlib.org/tutorials/index.html

x_min, x_max = two_dimensions[:, 0].min() - .5, two_dimensions[:, 0].max() + .5
y_min, y_max = two_dimensions[:, 1].min() - .5, two_dimensions[:, 1].max() + .5

plt.figure(2, figsize=(8, 6))
plt.clf()

# Plot the training points
plt.scatter(two_dimensions[:, 0], two_dimensions[:, 1], c=y, cmap=plt.cm.Set1,
            edgecolor='k')
plt.xlabel(features[0])
plt.ylabel(features[1])

plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)
plt.xticks(())
plt.yticks(())

plt.suptitle('Iris dataset')
legend_red = mpatches.Patch(color='red', label='Setosa')
legend_orange = mpatches.Patch(color='orange', label='Versicolour')
legend_grey = mpatches.Patch(color='grey', label='Virginica')
plt.legend(handles=[legend_red, legend_orange, legend_grey])

# Split dataset for training and test
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, shuffle=False)

# Call the LDA classifier
classifier = LinearDiscriminantAnalysis(n_components=2)

# Fit the data
classifier.fit(x_train, y_train)

# Predict the data
y_pred = classifier.predict(x_test)

print('Report for LDA 2 dimensions:')
print(classification_report(y_test, y_pred))

# print confusion matrix
print('Confusion matrix:')
print(confusion_matrix(y_test, y_pred))

plt.show()