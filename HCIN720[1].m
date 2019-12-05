dataTrain=[cpu(1:19,:);fridge(1:19,:);Microwave(1:19,:);tv(1:19,:)];
dataFFT=abs(fft(dataTrain));
dataFFTFeatures=[mean(dataFFT')',var(dataFFT')',std(dataFFT')',skewness(dataFFT')',kurtosis(dataFFT')',min(dataFFT')',max(dataFFT')',median(dataFFT')'];

%train split
dataTrainF=[dataFFTFeatures(1:15,:),ones(15,1);dataFFTFeatures(20:34,:),2*ones(15,1);dataFFTFeatures(39:53,:),3*ones(15,1);dataFFTFeatures(58:72,:),4*ones(15,1)];
%test split
dataTestF=[dataFFTFeatures(16:19,:);dataFFTFeatures(35:38,:);dataFFTFeatures(54:57,:);dataFFTFeatures(73:76,:)];
%training
[trainedClassifier, validationAccuracy] = trainClassifier(dataTrainF);
%testing
yfit = trainedClassifier.predictFcn(dataTestF);


%% 1v all
