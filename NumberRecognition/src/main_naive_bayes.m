% main_naive_bayes
clear;
addpath('../data/');

% train
trainImages = loadMNISTImages('train-images-idx3-ubyte');%768*60000
trainLabels = loadMNISTLabels('train-labels-idx1-ubyte');%60000*1

trainImages = (trainImages>0) + 0;
ObjBayes = NaiveBayes.fit(trainImages',trainLabels,'Distribution','mn');

pre0 = ObjBayes.predict(trainImages');
ppp = pre0 == trainLabels;
disp '训练样本通过率'; 
sum(ppp)/length(ppp)

% you need to dispaly the accuracy on test data
testImages = loadMNISTImages('t10k-images-idx3-ubyte');%768*10000
testLabels = loadMNISTLabels('t10k-labels-idx1-ubyte');%10000*1
testImages = (testImages>0) + 0;

test0  = ObjBayes.predict(testImages');
ppp = test0 == testLabels;
disp '测试样本通过率';
sum(ppp)/length(ppp)