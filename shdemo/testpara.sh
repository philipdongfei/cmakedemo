#!/bin/bash

echo "Shell pass the parameter demo!";
echo "process file name: $0";
echo "first para: $1";
echo "second para: $2";
echo "third para: $3";

echo "para count: $#";
echo "para string: $*";
echo "-- \$* show ---"
for i in "$*";
do
    echo $i
done

echo "-- \$@ show ---"
for i in "$@";
do
    echo $i
done

