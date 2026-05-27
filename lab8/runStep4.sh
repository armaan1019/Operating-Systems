#!/bin/bash

for file in file1.txt file2.txt file3.txt file4.txt; do
  for buffer in 100 1000 10000 100000; do
    echo "Step2 $file $buffer copy_$file"
    time ./step4 $file $buffer copy_$file
    echo " "
  done
done
