#!/bin/bash

val=`expr 2 + 2`
echo "sum: ${val}"

a=10
b=20

val=`expr $a + $b`
echo "a + b = $val"

val=`expr $a - $b`
echo "a - b = $val"

val=`expr $a \* $b`
echo "a * b = $val"

val=`expr $b / $a`
echo "b / a = $val"

val=`expr $b / $a`
echo "b / a = $val"

val=`expr $b % $a`
echo "b % a = $val"

if [ $a == $b ]
then
    echo "a == b"
fi
if [ $a != $b ]
then
    echo "a != b"
fi

if [ $a != $b ]
then
    echo "$a != $b : a not eq b"
else
    echo "$a != $b: a eq b"
fi
if [ $a -lt 100 -a $b -gt 15 ]
then
    echo "$a -lt 100 -a $b -gt 15: return true"
else
    echo "$a -lt 100 -a $b -gt 15: return false"
fi
if [ $a -lt 100 -o $b -gt 100 ]
then
    echo "$a -lt 100 -o $b -gt 100: return true"
else
    echo "$a -lt 100 -o $b -gt 100: return false"
fi

if [ $a -lt 5 -o $b -gt 100 ]
then
    echo "$a -lt 5 -o $b -gt 100: return true"
else
    echo "$a -lt 5 -o $b -gt 100: return false"
fi

if [[ $a -lt 100 && $b -gt 100 ]]
then
    echo "return true"
else
    echo "return false"
fi

if [[ $a -lt 100 || $b -gt 100 ]]
then
    echo "return true"
else
    echo "return false"
fi

