#!/bin/sh

echo "hello"
cd build
sed -i.bak "s/--parents//g" Makefile
make dist
mv SmartCalc1.0.0.tar.gz ../