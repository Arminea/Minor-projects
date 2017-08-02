@echo off
SET /A ARGS_COUNT=0    
FOR %%A in (%*) DO SET /A ARGS_COUNT+=1    

if %ARGS_COUNT% == 0 GOTO :help_

if NOT %ARGS_COUNT% == 1 (
	ECHO Too much input arguments. Please, enter just one argument.
	GOTO :end
)

:: Help for this script
if "%1" == "help" GOTO :help_

:: New model is generated.
if %1 == 1 GOTO :createModel
:: Created model is used.
if %1 == 0 GOTO :predict
:: Input argument is invalid.
GOTO :skip

:help_
	ECHO Input argument is missing. Enter one argument, whether you want to scale dataset and create a new model ^for SVM.
	ECHO.1 =^> new model, 0 =^> created model
GOTO :end 

:createModel
ECHO Create model
:: Directory for scaled data.
if not exist "scale" mkdir scale

ECHO Scaling
ECHO.=================
:: Parameters for scaling are not saved. 
for %%F in (train\*) do svm-scale "%%F" > "scale\%%~nxF.scale"

:: Directory for model.
if not exist "model" mkdir model 

ECHO Model create
ECHO.=================
:: Model can be created for scaled data only.
:: Model is obtained with probability information.
set /a i=1
SETLOCAL ENABLEDELAYEDEXPANSION

for %%F in (scale\*) do (
	svm-train -b 1 "%%F" "model\!i!.model"
	set /a i=i+1
)
ECHO.

:predict
ECHO Prediction
ECHO.=================
:: Prediction based on model file is done for every data set from directory "in".
:: Test data are obtained with probability estimates.

@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
:: The prediction is used for all scaled input data sets.
for /D %%d in (in\*) do (
	if not exist "out\%%~nxd" mkdir out\%%~nxd
	ECHO.
	ECHO =================
	ECHO Ongoing file is %%d
	ECHO.
	
	set /a j=1
	for %%F in (in\%%~nxd\*) do (
		ECHO.
		ECHO - prediction ^for !j!
		svm-predict -b 1 "%%F" "model\!j!.model" "out\%%~nxd\!j!.predict"
		set /a j=j+1
	)	
)

GOTO :end

:skip
ECHO Input argument is invalid.

:end