% main_svm
clear;
addpath('../data/');

%% get train data

trainImages = loadMNISTImages('train-images-idx3-ubyte');%768*60000
trainLabels = loadMNISTLabels('train-labels-idx1-ubyte');%60000*1

trainImages = reshape(trainImages,28,28,60000);
trainFeatures = zeros(256,60000);%256*60000

for i = 1 : 60000
    trainFeatures(:,i) = lbp(trainImages(:,:,i));
end

% !!!here we save data to 'trainFeatures.mat'!!! 

%% make 10 classifier

% trainFeatures = trainFeatures(:,[1:1000]);
% trainLabels = trainLabels(1:1000);

% case 0
load('trainFeatures.mat')
trainLabels = (trainLabels==0) +0;
SVMModel_0 = fitcsvm(trainFeatures',trainLabels);
disp('done0')

% case 1
load('trainFeatures.mat')
trainLabels = (trainLabels==1) +0;
SVMModel_1 = fitcsvm(trainFeatures',trainLabels);
disp('done1')

% case 2
load('trainFeatures.mat')
trainLabels = (trainLabels==2) +0;
SVMModel_2 = fitcsvm(trainFeatures',trainLabels);
disp('done2')

% case 3
load('trainFeatures.mat')
trainLabels = (trainLabels==3) +0;
SVMModel_3 = fitcsvm(trainFeatures',trainLabels);
disp('done3')

% case 4
load('trainFeatures.mat')
trainLabels = (trainLabels==4) +0;
SVMModel_4 = fitcsvm(trainFeatures',trainLabels);
disp('done4')

% case 5
load('trainFeatures.mat')
trainLabels = (trainLabels==5) +0;
SVMModel_5 = fitcsvm(trainFeatures',trainLabels);
disp('done5')

% case 6
load('trainFeatures.mat')
trainLabels = (trainLabels==6) +0;
SVMModel_6 = fitcsvm(trainFeatures',trainLabels);
disp('done6')

% case 7
load('trainFeatures.mat')
trainLabels = (trainLabels==7) +0;
SVMModel_7 = fitcsvm(trainFeatures',trainLabels);
disp('done7')

% case 8
load('trainFeatures.mat')
trainLabels = (trainLabels==8) +0;
SVMModel_8 = fitcsvm(trainFeatures',trainLabels);
disp('done8')

% case 9
load('trainFeatures.mat')
trainLabels = (trainLabels==9) +0;
SVMModel_9 = fitcsvm(trainFeatures',trainLabels);
disp('done9')

% collect
SVMModels = {SVMModel_0 SVMModel_1 SVMModel_2 SVMModel_3 SVMModel_4 SVMModel_5 SVMModel_6 SVMModel_7 SVMModel_8 SVMModel_9 };
clear SVMModel_0 SVMModel_1 SVMModel_2 SVMModel_3 SVMModel_4 SVMModel_5 SVMModel_6 SVMModel_7 SVMModel_8 SVMModel_9


%% predict for train data

classifyResult = zeros(60000,10);

for i = 1:10
    classifyResult(:,i)  = SVMModels{i}.predict(trainFeatures');
end

finalResult = OvR(classifyResult);
ppp = finalResult==trainLabels;
disp 'ѵ����������ȷ�ʲ���'
sum(ppp)/60000;

%% get test data

testImages = loadMNISTImages('t10k-images-idx3-ubyte');%768*10000
testLabels = loadMNISTLabels('t10k-labels-idx1-ubyte');%10000*1

testImages = reshape(testImages,28,28,10000);
testFeatures = zeros(256,10000);%256*10000
for i = 1 : 10000
    testFeatures(:,i) = lbp(testImages(:,:,i));
end



%% predict for test data

classifyResult = zeros(10000,10);
for i = 1:10
    classifyResult(:,i)  = SVMModels{i}.predict(testFeatures');
end

finalResult = OvR(classifyResult);
ppp = finalResult==testLabels;
disp '������������ȷ�ʲ���'
sum(ppp)/10000
