#!/bin/bash
while read FILM
do
    echo "yes! $FILM is a good file"
done
i=1
while (( $i<=5 ))
do
    echo $i
    let "i++"
done
