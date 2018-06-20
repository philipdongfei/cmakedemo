#!/bin/bash
funWithParam(){
    echo "first param $1 !"
    echo "second param $2 !"
    echo "tenth param $10 !"
    echo "tenth param ${10} !"
    echo "eleventh param ${11} !"
    echo "param total num $# "
    echo "output string $* !"
}

funWithReturn(){
    echo "input the two nums and sum them in this fun"
    echo "input first num"
    read aNum
    echo "input second num"
    read anotherNum
    echo "two nums are $aNum and $anotherNum!"
    return $(($aNum+$anotherNum))
}
demoFun(){
    echo "This is my first function!"
}
echo "------fun begin------"
demoFun
echo "------fun end--------"
funWithReturn
echo "input the two nums' sum is $? !"
funWithParam 1 2 3 4 5 6 7 8 9 34 73

