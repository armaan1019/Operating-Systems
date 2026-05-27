#!/bin/bash

make

echo "Running step 1"
sh step1.sh

echo "Running step 2"
sh runStep1.sh

echo "Running step 3"
sh runStep3.sh

echo "Running step 4"
sh runStep4.sh

echo "Running step 5"
sh runStep5.sh
