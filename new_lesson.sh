#!/bin/bash

#Get the last lesson number.
LAST=`find . -type d | grep 'lesson' | grep -o '[0-9]*' | sort -Vu | tail -n 1`;
let NEXT=LAST+1;

echo "Creating directory for lesson $NEXT.";

mkdir "lesson$NEXT";

cp -r "./lesson$LAST/"* "./lesson$NEXT/";

sed -i "s/$LAST/$NEXT/g" lesson$NEXT/makefile
mv "lesson$NEXT/lesson$LAST.cpp" "lesson$NEXT/lesson$NEXT.cpp"
