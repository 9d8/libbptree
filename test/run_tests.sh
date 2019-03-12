#!/bin/sh

cd "$(dirname "$0")" || exit 1

find . -maxdepth 1 -executable -type f -not -name "$(basename "$0")" | while read -r file; do
	printf "Running test %s: " "$file"
	if TEST_OUTPUT="$($file)"; then
		printf "\033[0;32mpass\n\033[0m"
	else
		printf "\033[0;31mfail\n\033[0m"
		printf "\nPrinting test output...\n\n%s\n" "$TEST_OUTPUT"
	fi
done

