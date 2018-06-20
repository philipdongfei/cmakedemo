echo 'input between 1 and 4 :'
echo 'input the num:'
read aNum
case $aNum in
    1) echo 'choice 1'
    ;;
    2) echo 'choice 2'
    ;;
    3) echo 'choice 3'
    ;;
    4) echo 'choice 4'
    ;;
    *) echo 'you do not input in between 1 and 4'
    ;;
esac

while :
do
    echo -n "input 1 - 5 num:"
    read aNum
    case $aNum in
        1|2|3|4|5) echo "you input the num $aNum!"
        ;;
        *) echo "you input the num not in 1 - 5! GO"
            break
        ;;
    esac
done
