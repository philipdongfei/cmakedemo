#!/bin/bash
num1=100
num2=100
if test $[num1] -eq $[num2]
then
    echo "two num eq"
else
    echo "two num not eq"
fi
str1="W3Cschool"
str2="W3Cschool"
if test str1=str2
then
    echo 'two strings eq'
else
    echo 'two strings not eq'
fi

cd /bin
if test -e ./bash
then
    echo 'file exist'
else
    echo 'file not exist'
fi
if test -e ./notFile -o -e ./bash
then
    echo 'one file exist'
else
    echo 'tow files all not exist'
fi
num1=$[2*3]
num2=$[1+5]
if test $[num1] -eq $[num2]
then
    echo 'two num eq'
else
    echo 'two num not eq'
fi
for loop in 1 2 3 4 5
do
    echo "The value is: $loop"
done
for str in 'This is a string'
do
    echo $str
done

