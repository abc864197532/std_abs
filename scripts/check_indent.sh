#!/usr/bin/env bash

PATTERN='.*.cpp'
exitcode=0

while IFS= read -r file; do
	python3 scripts/check_indent.py "$file"
	if [[ $? -ne 0 ]]; then
		exitcode=1
	fi
done < <(find . -regextype posix-egrep -regex "$PATTERN")

exit $exitcode