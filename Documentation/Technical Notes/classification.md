# Classification

These set of notes aim to set the goundwork for classification within the world of machine learning.

Generally speaking, there are three different types of machine leaning:
1. Supervised leaning
    - Labelled data
    - Direct feedback
    - Predict the outcome
2. Unsupervised learning
    - No labels/targets
    - No feedback
    - Finds the hidden structure in data
3. Reinforement learning
    - Decision process
    - Reward system
    - Learn series of action

Classification is a subcategory of supervised learning. In classification, the aim is to preicat the class labels for new instances or data, based on past observations. 

The standard example used to try and explain classification is the email span detection system. This is an example of a binary classifier, since there are only two possible outcomes: spam and not spam. 

Typically, binary classification tasks involve one class that is said to be a "normal state". It follows the other class is the "not normal" state, or to be more precise, the "abnormal state". In the email example, "not spam" is the normal state, and "spam" is the abnormal state. In another common example, "not cancer" is the normal state, and "caner" is the abnormal state. Again, typially, the normal state is denoted by class label 0, and the abnormal state is denited by the class label 1. 

There are a number of popular classification algorithms that can be used for binary classification:
1. Logistic Regression
2. k-Nearest Neigbour
3. Decision Trees
4. Support Vector Machines
5. Naive Bayes

Some of the above can be used for multi-classification systems, which others (logistic regression, SVM) are specifically aimed at binary classification.