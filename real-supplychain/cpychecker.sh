



cd numpy/numpy-2.2.5
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
export CC="path-to/gcc-with-cpychecker"
spin build


cd ../..
cd cffi/cffi-1.17.1
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
python setup.py build_ext --inplace  --f


cd ../..
cd protobuf
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f
##python3 setup.py build_ext --inplace  --f 2>&1| grep -i 'warning:' | wc -l


cd ../
cd wrapt/wrapt-1.17.2
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f


cd ../..
cd psutil/psutil-7.0.0
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f


cd ../..
cd multidict/multidict-6.4.3
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f


cd ../..
cd grpcio
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f
##python3 setup.py build_ext --inplace  --f | grep -i "warning: flags do not match callback signature"
##

cd ../
cd pillow/pillow-11.2.1
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f

cd ../..
#cd scipy
#find . -name "*.so" -delete
#export CC="path-to/gcc-with-cpychecker"
#rm -rf build/ *.egg-info/
#python3 setup.py build_ext --inplace  --f

cd    ../..
cd greenlet/greenlet-3.2.1
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f

cd ../..
cd  lxml/lxml-5.4.0
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f


cd ../..
cd msgpack/msgpack-1.1.0
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f

cd ../..
cd grpcio-tools/grpcio_tools-1.72.0
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f

cd ../..
cd coverage/coverage-7.8.0
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f

cd ../..
cd regex/regex-2024.11.6
find . -name "*.so" -delete
export CC="path-to/gcc-with-cpychecker"
rm -rf build/ *.egg-info/
python3 setup.py build_ext --inplace  --f



