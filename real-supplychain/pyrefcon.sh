


cd cffi/cffi-1.17.1
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../..
cd protobuf
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build


cd ../
cd wrapt/wrapt-1.17.2
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../..
cd psutil/psutil-7.0.0
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../..
cd multidict/multidict-6.4.3
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build


cd ../..
cd grpcio
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../
cd pillow/pillow-11.2.1
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../..
cd greenlet/greenlet-3.2.1
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
cd ../..
cd lxml/lxml-5.4.0
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
cd ../..
cd msgpack/msgpack-1.1.0
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build


cd ../..
cd grpcio-tools/grpcio_tools-1.72.0
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../..
cd coverage/coverage-7.8.0
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../..
cd numpy/numpy-2.2.5
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker spin build


cd ../..
cd pandas
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../
cd scipy/
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python dev.py build

cd ../
cd regex/regex-2024.11.6
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../..
cd pyahocorasick
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build

cd ../
cd python-Levenshtein
find . -name "*.so" -delete
rm -rf build/ *.egg-info/
scan-build -disable-checker core  -enable-checker alpha.core.PythonReferenceCountingChecker python setup.py build
