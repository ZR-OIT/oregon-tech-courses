import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from sklearn import decomposition

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

# One feature in dataset (sepal length)
# one_dimension = x[:, :1]
# print(one_dimension)

# Store the feature and class names
features = iris.feature_names
classes = iris.target_names

print('Feature names:')
print(features)
print('Class names:')
print(classes)

# Use KNN to classify one dimension
# Split dataset for training and test
# x_train, x_test, y_train, y_test = train_test_split(one_dimension, y, test_size=0.2, shuffle=False)

# Use KNN to classify all four dimensions
# Split dataset for training and test
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, shuffle=False)

# Call the KNN classifier
classifier = KNeighborsClassifier(n_neighbors=7)

# Fit the data with KNN
classifier.fit(x_train, y_train)

# Predict the data
y_pred = classifier.predict(x_test)

# print('Report for single dimension:')
print('Report for all four dimensions:')
print(classification_report(y_test, y_pred))

# With help from:
# -> https://scikit-learn.org/stable/auto_examples/datasets/plot_iris_dataset.html
# -> https://matplotlib.org/tutorials/index.html

# Create 3D plot
fig = plt.figure(1, figsize=(4, 3))
ax = Axes3D(fig, rect=[0, 0, .95, 1], elev=48, azim=134)
plt.cla()
pca = decomposition.PCA(n_components=3)
pca.fit(x)
x = pca.transform(x)

for name, label in [('Setosa', 0), ('Versicolour', 1), ('Virginica', 2)]:
    ax.text3D(x[y == label, 0].mean(),
              x[y == label, 1].mean() + 1.5,
              x[y == label, 2].mean(), name,
              horizontalalignment='center',
              bbox=dict(alpha=.5, edgecolor='w', facecolor='w'))
# Reorder the labels to have colors matching the cluster results
y = np.choose(y, [1, 2, 0]).astype(np.float)
ax.scatter(x[:, 0], x[:, 1], x[:, 2], c=y, cmap=plt.cm.nipy_spectral,
           edgecolor='k')

ax.set_title('Iris dataset')

ax.set_xlabel(features[0])
ax.w_xaxis.set_ticklabels([])

ax.set_ylabel(features[2])
ax.w_yaxis.set_ticklabels([])

ax.set_zlabel(features[1])
ax.w_zaxis.set_ticklabels([])

plt.show()