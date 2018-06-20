#!/bin/sh
read name
echo "${name} It is a test"
echo -e "OK!\n" # -e
echo "It it a test"
echo -e "OK! \c"
echo "It is a test"
echo "It is a test" > myfile
echo '$name\"'
echo `date`

printf "%-10s %-8s %-4s\n" name sex weight
printf "%-10s %-8s %-4.2f\n" guojing m 66.1234
printf "%-10s %-8s %-4.2f\n" yangguo m 48.6543
printf "%-10s %-8s %-4.2f\n" guofu   w 47.9876

printf "%d %s\n" 1 "abc"
printf '%d %s\n' 1 "abc"

printf %s abcdef
printf %s abc def
printf "%s\n" abc def
printf "%s %s %s\n" a b c d e f g h i j
printf "%s and %d \n"

