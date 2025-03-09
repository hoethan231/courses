# -*- coding: utf-8 -*-
"""
@author: jahan
Tested with Python 2.7
updated: 10/2/2020 to work with Python 3.7
"""
 
import warnings
warnings.filterwarnings("ignore")

import pandas as pd
import matplotlib.pyplot as plt
from pandas import set_option
from pandas import read_csv
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import Normalizer
from numpy import set_printoptions
import seaborn as sns
from pandas.plotting import scatter_matrix
import numpy as np
import statsmodels.api as sm
from sklearn.linear_model import LinearRegression
from sklearn.feature_selection import RFE


filePath = 'C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_188/data/'
filename = 'Baseball_salary.csv'
data1 = read_csv(filePath+filename)

# there are 4 columns that are text/strings and we need to remove them
# in this case, we are not considering the categorical data such as League, Division, and New League
data1 =  data1.drop(['Unnamed: 0', 'League', 'Division', 'NewLeague'], axis=1)
# clean the data, i.e. remove any NA (not a number)
data1 = data1.dropna()
# separate array into input and output components (Numpy arrays)



array = data1.values
# # separate array into input and output components
X = array[:,0:16]
Y = array[:,16]

# Replace Salary column with log salary

salaryLog = np.log(Y)

data1['LogSalary'] = salaryLog
del data1['Salary']

# ## save features as pandas dataframe for stepwise feature selection
X1 = data1.drop(data1.columns[16], axis = 1)
Y1 = data1.drop(data1.columns[0:16], axis = 1)

# update Y array
Y = data1.values[:,16]
# calculate descriptive statistics for the original data
descriptionData1 = data1.describe()
print(descriptionData1)

# plot histograms
data1.hist()
plt.show()

## correlation heat map, pay attention to correlation between all predicators/features and each predictor and the output
plt.figure() # new plot
corMat = data1.corr(method='pearson')
print(corMat)

## plot correlation matrix as a heat map
sns.heatmap(corMat, square=True)
plt.yticks(rotation=0)
plt.xticks(rotation=90)
plt.title("Correlation Matrix Heatmap for Original Data")
plt.show()
#
## scatter plot of all data
#plt.figure()
scatter_matrix(data1)
plt.title("Scatter Plot Matrix for Original Data")
plt.show()

################# Standardization ##################
# now standardize the data and perform EDA
scaler = StandardScaler().fit(X)
rescaledX = scaler.transform(X)

# summarize transformed data
set_printoptions(precision=3)
print(rescaledX[0:5,:])

nn = data1.columns
# you can make a new data frame with the standardized data
dataStandDf = pd.DataFrame(rescaledX, columns = nn[0:16])
dataStandDf['LogSalary'] = Y

#standardize x and y
dataStandDfX =dataStandDf.iloc[:,0:16]
dataStandDfY = dataStandDf['LogSalary']

# First perform exploratory data analysis using correlation and scatter plot
# look at the first 20 rows of data
peek = dataStandDf.head(20)
print(peek)

# descriptive statistics for standardize data: mean, max, min, count, 25 percentile, 50 percentile, 75 percentile

# show descriptive stats after standardization
set_option('display.width', 100)
set_option('precision', 1)
descriptionStand = dataStandDf.describe()
print(descriptionStand)


# Now plot the histogram after standardization
dataStandDf.hist()
plt.show()

## correlation heat map, pay attention to correlation between all predicators/features and each predictor and the output
plt.figure() # new plot
corMatStand = dataStandDf.corr(method='pearson')
print(corMatStand)

## plot correlation matrix as a heat map
sns.heatmap(corMatStand, square=True)
plt.yticks(rotation=0)
plt.xticks(rotation=90)
plt.title("Correlation Matrix Heatmap for Standardized Data")
plt.show()
#
## scatter plot of all data
scatter_matrix(dataStandDf)
plt.title("Scatter Plot Matrix for Standardized Data")
plt.show()


################# Normalization ##################
# now normalize the data and perform EDA
# separate array into input and output components
scalerNorm = Normalizer().fit(X)
normalizedX = scalerNorm.transform(X)
# summarize transformed data
set_printoptions(precision=3)
print(normalizedX[0:5,:])

# you can make a new data frame with the normalized data
dataNormDf = pd.DataFrame(normalizedX, columns = nn[0:16])
dataNormDf['LogSalary'] = Y 

#Normalized x and y
dataNormDfX =dataNormDf.iloc[:,0:16]
dataNormDfY = dataNormDf['LogSalary']

# show descriptive stats after standardization
set_option('display.width', 100)
set_option('precision', 1)
descriptionNorm = dataNormDf.describe()
print(descriptionNorm)

# we look at the distribution of data and its descriptive statistics
dataNormDf.hist()
plt.show()

## correlation heat map, pay attention to correlation between all predicators/features and each predictor and the output
plt.figure() # new plot
corMatNorm = dataNormDf.corr(method='pearson')
print(corMatNorm)

## plot correlation matrix as a heat map
sns.heatmap(corMatNorm, square=True)
plt.yticks(rotation=0)
plt.xticks(rotation=90)
plt.title("Correlation Matrix Heatmap for Normalized Data")
plt.show()
#
## scatter plot of all data
scatter_matrix(dataNormDf)
plt.title("Scatter Plot Matrix for Normalized Data")
plt.show()


'''--- RFE Feature Selection Original dataframe--- '''

#NUM_FEATURES = len(X.columns) # this is kind of arbitrary but you should get an idea by observing the scatter plots and correlation.
#model = LinearRegression()

model = LinearRegression()   

def RFE_FUNCTION(model, X, y):
    NUM_FEATURES = len(X.columns) 
    for i in range(1,NUM_FEATURES):   
        rfe = RFE(model, n_features_to_select = i)
        fit = rfe.fit(X, y)
        print("Num Features:", fit.n_features_)
        #print("Selected Features:", fit.support_)
        #print("Feature Ranking:", fit.ranking_)
        # calculate the score for the selected features
        score = rfe.score(X,y)
        print("Model Score with selected features is: ", score)
    
'''
Observation: We can see that performance improves as the number of features 
increase and perhaps peaks around 6-10. 
'''
def PRINT_RFE_SELECTION(model,X,y,numfeatures): 
    rfe = RFE(model, n_features_to_select = numfeatures) 
    fit = rfe.fit(X, y) 
    for i in range(X.shape[1]):
        print('Column %s:  Selected %s, Rank: %.3f' % (X.columns[i],fit.support_[i], fit.ranking_[i]))

RFE_FUNCTION(model, X1, Y1)
PRINT_RFE_SELECTION(model, X1,Y1,16)

# stepwise forward-backward selection
# need to change the input types as X in this function needs to be a pandas
# dataframe

 
def stepwise_selection(X, y, 
                       initial_list=[], 
                       threshold_in=0.01, 
                       threshold_out = 0.05, 
                       verbose=True):
    """ Perform a forward-backward feature selection 
    based on p-value from statsmodels.api.OLS
    Arguments:
        X - pandas.DataFrame with candidate features
        y - list-like with the target
        initial_list - list of features to start with (column names of X)
        threshold_in - include a feature if its p-value < threshold_in
        threshold_out - exclude a feature if its p-value > threshold_out
        verbose - whether to print the sequence of inclusions and exclusions
    Returns: list of selected features 
    Always set threshold_in < threshold_out to avoid infinite looping.
    See https://en.wikipedia.org/wiki/Stepwise_regression for the details
    """
    included = list(initial_list)
    while True:
        changed=False
        # forward step
        excluded = list(set(X.columns)-set(included))
        new_pval = pd.Series(dtype='float64',index=excluded)
        for new_column in excluded:
            model = sm.OLS(y, sm.add_constant(pd.DataFrame(X[included+[new_column]]))).fit()
            new_pval[new_column] = model.pvalues[new_column]
        best_pval = new_pval.min()
        if best_pval < threshold_in:
            best_feature = new_pval.argmin()
            included.append(new_pval.keys()[best_feature])

            changed=True
            if verbose:
                print('Add  {:30} with p-value {:.6}'.format(best_feature, best_pval))

        # backward step
        model = sm.OLS(y, sm.add_constant(pd.DataFrame(X[included]))).fit()
        # use all coefs except intercept
        pvalues = model.pvalues.iloc[1:]
        worst_pval = pvalues.max() # null if pvalues is empty
        if worst_pval > threshold_out:
            changed=True
            worst_feature = pvalues.argmax()
            included.remove(pvalues.keys()[worst_feature])
            if verbose:
                print('Drop {:30} with p-value {:.6}'.format(worst_feature, worst_pval))
        if not changed:
            break
    return included

result = stepwise_selection(X1, Y1)

print('Resulting Features for un-modified data:')
print(result)

# ----------------------------------------- 
#     B. STANDARDIZED DATA 
# -----------------------------------------

# Feature Selection Using RFE
model = LinearRegression()  
RFE_FUNCTION(model,dataStandDfX, dataStandDfY)
PRINT_RFE_SELECTION(model, dataStandDfX,dataStandDfY , numfeatures=3)

# B4. Step-wise Feature Selection 
stepwise_selection(dataStandDf, dataStandDfY)

# ----------------------------------------- 
#     C. NORMALIZED DATA 
# -----------------------------------------


# C3. Feature Selection using RFE
model = LinearRegression()  
RFE_FUNCTION(model,dataNormDfX, dataNormDfY)
PRINT_RFE_SELECTION(model, dataNormDfX, dataNormDfY, numfeatures=4)

# B4. Step-wise Feature Selection 
stepwise_selection(dataNormDfX, dataNormDfY)

