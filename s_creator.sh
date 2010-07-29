#!/bin/bash

echo "Filename: "
read inputLine
filename="$inputLine"

python s_creator.py $filename
echo "Add to repository (y/n)?"
read inputLine
op="$inputLine"

if [ $op = "y" ] 
then
git add "$filename"
fi
