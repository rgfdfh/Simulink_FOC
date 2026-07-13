
set MATLAB=D:\MATLAB\Matlab2023a

cd .

if "%1"=="" ("D:\MATLAB\Matlab2023a\bin\win64\gmake"  -f FOC_PointModel.mk all) else ("D:\MATLAB\Matlab2023a\bin\win64\gmake"  -f FOC_PointModel.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1