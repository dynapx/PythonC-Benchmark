#####
echo "@@@@@@@@@ Buffer_Overflow"
cd  Buffer_Overflow
find . -name "*.so" -delete
rm -rf build/ *.egg-info/

scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

#
echo "@@@@@@@@@ Currency"
cd ../Currency
find . -name "*.so" -delete
rm -rf build/ *.egg-info/

scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
#
#
echo "@@@@@@@@@ Exception_Handling_Error"
cd ../Exception_Handling_Error
find . -name "*.so" -delete
rm -rf build/ *.egg-info/

scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build



#echo "@@@@@@@@@ Incomplete comparison"
#cd ../Incomplete comparison
#find . -name "*.so" -delete
#rm -rf build/ *.egg-info/
#python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Insufficient_Error_Checking"
cd ../Insufficient_Error_Checking
find . -name "*.so" -delete
rm -rf build/ *.egg-info/

scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
#
echo "@@@@@@@@@ Integer_Overflow"
cd ../Integer_Overflow
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -enable-checker core -enable-checker unix -enable-checker security -enable-checker nullability  -enable-checker alpha.security -enable-checker alpha.unix  python setup.py build
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build


cd ../Memory_Management_Error
echo "@@@@@@@@@ Memory_Management_Error"
#cd ../Memory_Management_Error
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -enable-checker core -enable-checker unix -enable-checker security -enable-checker nullability  -enable-checker alpha.security -enable-checker alpha.unix  python setup.py build
#scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

echo "@@@@@@@@@ Reference_Count_Error"
cd ../Reference_Count_Error
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -enable-checker core -enable-checker unix -enable-checker security -enable-checker nullability  -enable-checker alpha.security -enable-checker alpha.unix  python setup.py build
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
#
echo "@@@@@@@@@ Type_Mismatch(Format String)"
cd ../"Type_Mismatch(Format String)"
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
#
echo "@@@@@@@@@ Type_Mismatch (Flag)"
cd ../"Type_Mismatch (Flag)"
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
#
echo "@@@@@@@@@ Unchecked_Number"
cd ../"Unchecked_Number"
find . -name "*.so" -delete
rm -rf build/ *.egg-info/

scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build