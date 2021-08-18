#!/usr/bin/env bash

run_test () {
    let "$3"="$3"+1

    echo "----------"
    echo -e $1" test"

    time ./crhm system_regression_test/projects/"$1".prj -o $TEMP_DIR/"$1"_output.txt &> /dev/null
    echo " "

    TEST=$(diff system_regression_test/expected_output/"$1"_output.txt $TEMP_DIR/"$1"_output.txt)

    if test -z "$TEST"
        then
            let "$2"="$2"+1
            echo -e "$1: \e[1;32m Pass \e[0m"
        else
            echo -e "$1: \e[1;31m Fail \e[0m"
    fi

    echo " "
}

#Make directory to put testing results in if it does not exist.
TEMP_DIR=$(dirname "$(readlink -f "$0")")
TEMP_DIR+="/system_regression_test/tmp_test_output"
mkdir -p $TEMP_DIR

let total=0
let passed=0

run_test badlake passed total
run_test Brandon_all_wetland_hru_0_pct passed total
run_test smithcreek passed total


echo "Tests passed: $passed/$total"

rm -r "$TEMP_DIR"
