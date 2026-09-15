#!/bin/sh
# print one case block from an extracted cases file
awk -v want="==== case $2 ====" '
  $0 ~ /^====/ { p = ($0 == want) }
  p { print }
' "$1"
