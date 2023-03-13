#!/bin/sh

OS=$(uname)

cd build
$1 ../source/SmartCalc.pro
make
if [ ${OS} = Linux ]; then
    cp SmartCalc ../calc/
elif [ ${OS} = Darwin ]; then
    cp -r SmartCalc* ../calc/
else
    echo "\nWindows install is not supported"
fi