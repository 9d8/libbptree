#!/bin/sh

FORCE_PRINT=0

schelp="Usage: run_tests [OPTIONS]

Run all test ececutables located in this script's directory. An executable is 
considered a test if the first 5 characters of its name are 'test_'. If a test
fails, the stdout of that test will be printed. 

Do not rename this script to test_[something] since it will cause it
to run recursively.

Options:
 -p	Print all test output (regardless of pass or fail)
 -h	Print out this help text"

while getopts "hp" flag; do
	case "${flag}" in
		h) printf "%s\\n" "$schelp" && exit 0;;
		p) FORCE_PRINT=1;;
		*) printf "Invalid argument %s\\n" "${flag}" && exit 1;;
	esac
done

cd "$(dirname "$0")" || exit 1

find . -maxdepth 1 -executable -type f -name 'test_*' | while read -r file; do
	printf "Running test %s: " "$file"
	if TEST_OUTPUT="$($file)"; then
		printf "\033[0;32mpass\n\033[0m"
		if [ "$FORCE_PRINT" -eq 1 ]; then
			printf "\n%s\n\n" "$TEST_OUTPUT"
		fi
	else
		printf "\033[0;31mfail\n\033[0m"
		printf "\n%s\n\n" "$TEST_OUTPUT"
	fi
done

