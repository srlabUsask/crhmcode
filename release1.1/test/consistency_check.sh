#!/bin/bash

#Function to print a fraction indicating progress
# $1 int numerator
# $2 int denominator
progress() {
    printf "\r Run: $1/$2"
}

echo "Running consistancy tests..."
#Create directories for output if they don't already exist.
mkdir -p ./testing_output/test_suite_1/badlake
mkdir -p ./testing_output/test_suite_1/smithcreek
mkdir -p ./testing_output/test_suite_1/SmokyRiver

echo "================badlake_old consistancy test================"
cd ..
printf "Running badlake_old.prj 10 times \n"
for ((i=1; i<=10; i++)); do
    progress $i 10
    ./crhm ./prj/badlake_old.prj >/dev/null
     mv ./CRHM_output_1.obs ./test/testing_output/test_suite_1/badlake/bl$i.obs
done
cd test/
printf "\n"
echo "-------------------- consistancy check --------------------"
python ./check_consistency.py ./testing_output/test_suite_1/badlake/


echo "================smithcreek consistancy test================"
cd ..
printf "Running smithcreek_2014.prj 10 times \n"
for ((i=1; i<=10; i++)); do
    progress $i 10
    ./crhm ./prj/smithcreek_2014.prj >/dev/null
    mv ./CRHM_output_1.obs ./test/testing_output/test_suite_1/smithcreek/sc$i.obs
done
printf "\n"
cd test/
echo "-------------------- consistancy check --------------------"
python ./check_consistency.py ./testing_output/test_suite_1/smithcreek/


echo "================Smoky River consistancy test================"
cd ..
printf "Running SmokyRiverModel_Forecasts.prj 10 times \n"
for ((i=1; i<=10; i++)); do
    progress $i 10
    ./crhm ./prj/SmokyRiverModel_Forecasts.prj >/dev/null
    mv ./CRHM_output_1.obs ./test/testing_output/test_suite_1/SmokyRiver/sr$i.obs
done
printf "\n"
cd test/
echo "-------------------- consistancy check --------------------"
python ./check_consistency.py./testing_output/test_suite_1/SmokyRiver/
