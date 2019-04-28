#!/bin/bash

path=./input/input_1500_30_split
files=$(ls $path)
for filename in $files
do
   echo $filename
   kvasir-dtrace --decls-file=daikon-output/$filename.decls --dtrace-file=daikon-output/$filename.dtrace ./bubble $path/$filename
   java -cp $DAIKONDIR/daikon.jar daikon.Daikon \ 
    --config_option daikon.derive.Derivation.disable_derived_variables=true \      daikon-output/$filename.decls daikon-output/$filename.dtrace
done
