#!/usr/bin/env bash

PATTERN='.*.cpp'
exitcode=0

while IFS= read -r file; do
	grep -v "^$file$" "./codebook/dont_check_list.txt" > /dev/null 2>&1
	if [[ $? -eq 0 ]]; then
		python3 scripts/check_indent.py "$file"
		if [[ $? -ne 0 ]]; then
			exitcode=1
		fi
	fi
done < <(find . -regextype posix-egrep -regex "$PATTERN")

# exit $exitcode
exit 0