echo "@@@@@@@@@ Buffer_Overflow"
cd  Buffer_Overflow
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning


echo "@@@@@@@@@ Currency"
cd ../Currency
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning


echo "@@@@@@@@@ Exception_Handling_Error"
cd ../Exception_Handling_Error
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning



#echo "@@@@@@@@@ Incomplete comparison"
#cd ../Incomplete comparison
#find . -name "*.so" -delete
#rm -rf build/ *.egg-info/
#python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Insufficient_Error_Checking"
cd ../Insufficient_Error_Checking
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Integer_Overflow"
cd ../Integer_Overflow
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Memory_Management_Error"
cd ../Memory_Management_Error
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Reference_Count_Error"
cd ../Reference_Count_Error
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Type_Mismatch(Format String)"
cd ../"Type_Mismatch(Format String)"
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Type_Mismatch (Flag)"
cd ../"Type_Mismatch (Flag)"
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning

echo "@@@@@@@@@ Unchecked_Number"
cd ../"Unchecked_Number"
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --force | grep warning