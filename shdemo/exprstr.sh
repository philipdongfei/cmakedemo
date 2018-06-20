#!/bin/bash

a="abc"
b="efg"

if [ $a = $b ]
then
    echo "$a = $b : a eq b"
else
    echo "$a = $b : a no eq b"
fi

if [ $a != $b ]
then
    echo "$a != $b : a no eq b"
else
    echo "$a != $b: a eq b"
fi
if [ -z $a ]
then
    echo "-z $a : str len is 0"
else
    echo "-z $a : str len is not 0"
fi
if [ -n $a ]
then
    echo "-n $a : str len is not 0"
else
    echo "-n $a : str len is 0"
fi
if [ $a ]
then
    echo "$a : str is not null"
else
    echo "$a : str is null"
fi

