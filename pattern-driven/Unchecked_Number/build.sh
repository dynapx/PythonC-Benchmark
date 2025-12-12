export CASE_PATH=`pwd`


# 1. install C module of the case
rm -rf /tmp/difg/LdaBin*

echo "@@@@@@@@@ C component.........."
rm -rf build
python setup-lda.py build
sda -file `find build/ -name "*preopt.bc"`
rm -rf build
python setup-instm.py build


# 2. translate the python code
CASE=`basename $CASE_PATH`
echo "@@@@@@@@@ Python component.........."
cd ..
python -m pyinspect -E $CASE/ExpList -c -d $CASE

# 3. run the case
echo "@@@@@@@@@ runing the case.........."
export CASE1="0"
cd Temp/$CASE/
cp -f `find  -name "*linux-gnu.so"`  ./
python -m pyinspect -C criterion.xml -i ./ -t ./test_vulns.py