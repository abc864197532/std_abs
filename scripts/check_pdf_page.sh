#!/usr/bin/env bash

page=$(exiftool "codebook.pdf" | awk -F": " '/Page Count/{print $2}')

echo "Page count: ${page}"

if [[ ${page} -gt 25 ]]; then
	echo "Too many pages!"
	exit 1
fi