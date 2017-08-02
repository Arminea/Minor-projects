SVM-for-EEG-signal
======================
author: Tereza Štanglová


Description:
----------------------
This work is my school project. It's about classification of EEG signal. Input data sets were given by my teachers at the university.

EEG data sets are from the neuro experiments. The experiments were about number estimate. The subject, mostly child 13-16 y.o., chose one number from scale 1-9. He was looking at monitor with changing numbers. The number he chose was a target stimul. The rest of numbers were non-target stimul.  

My task is to create a tool for recognition of target stimul, which number is a target stimul. Whole work is divided in two parts. The first part is about preprocessing of data sets in Matlab. I use EEGLAB and ERPLAB toolboxes. The second part is about SVM. For this part I use a library for Support Vector Machine (http://www.csie.ntu.edu.tw/~cjlin/libsvm/) written by Chih-Chung Chang and Chih-Jen Lin. I didn't write my own code for SVM because this library is well optimized and easy to use for begginers.

Matlab script:
----------------------
Script has two input parameters. The first one is a path to file for finding electrodes channels. This file is usually put in EEGLAB directory. The EEGLAB and the ERPLAB are needed for correct running. The second input parametr is a number, 0 for training data set or 1 for test data set. Only the first parametr is required. Training data set is default setting. Files with signal are processed according this scheme:

1) Location of electrodes channels

2) Application of basic IIR filter

3) Creation of event list 

4) Selection of epochs

5) Artefact detection

6) Signal averaging

7) Finding peak latency and amplitude for each number in averaged signal

After finding latency and amplitude, this values are written in separated output files. That's not suitable for SVM library. Script has a second part which is a parser. These files are parsed ccording the user's input parameter. 

For training data set: For each number is created a file which has a structure required by SVM library. The structure is

```<class> <index1>:<value1> <index2>:<value2> ... ```

For test data: Values of latency and amplitude are written in separate files for each epoch. There is the ```<class>``` number not important.

SVM:
----------------------
Downloaded files contain executable files for windows in \windows directory. I've wrote a batch script which create a directory structure with scaled files, models and results of prediction.

Run a script 'EEGclassification.bat' in command line with parameter 'help' and a short documentation will be in console. The whole script is full of comments.

C:\UserName\SomeDir>EEGclassification.bat help

Next parameters for script are '0' or '1'. Zero indicates that the model is already created. One indicates that we want to create a new model for prediction.

Data processing is performed in several steps:
1) Transform data to the format of an SVM package (this is done in matlab script).

2) Data scaling.

3) Consider which kernel we can use. In this case a RBF kernel is used.

4) Use cross-validation to find the best values of all required parameter.

5) Use the best parameters to training.

6) Test
