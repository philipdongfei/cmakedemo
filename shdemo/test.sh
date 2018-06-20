#!/bin/bash
echo "Hello World!"
for file in `ls ~`
do
    echo ${file}
done

your_name="qinjx"
echo $your_name
echo ${your_name}
for skill in Ada Coffe Action Java
do
    echo "I am good at ${skill}Script"
done
str="Hello, I know your are \"${your_name}\"! \n"
echo ${str}
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo ${greeting} ${greeting_1}
string="abcd"
echo ${#string} #out 4
string="alibaba is a great company"
echo ${string:1:4}
echo `expr index "$string" is`
array_name=(value0 value1 value2 value3)
value1=${array_name[1]}
echo ${value1}
echo ${array_name[@]}

length=${#array_name[@]}
echo ${length}
length=${#array_name[*]}
echo ${length}
length2=${#array_name[2]}
echo ${length2}

