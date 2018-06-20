#!/bin/bash

file="./test.sh"
if [ -r $file ]
then
    echo "file is able reading"
else
    echo "file is not able reading"
fi
if [ -w $file ]
then
    echo "file is able writing"
else
    echo "file is not able writing"
fi
if [ -x $file ]
then
    echo "file is able processing"
else
    echo "file is not able processing"
fi
if [ -f $file ]
then
    echo "file is normal"
else
    echo "file is special"
fi
if [ -d $file ]
then
    echo "file is dir"
else
    echo "file is not dir"
fi
if [ -s $file ]
then
    echo "file is not null"
else
    echo "file is null"
fi
if [ -e $file ]
then
    echo "file is exist"
else
    echo "file is not exist"
fi

