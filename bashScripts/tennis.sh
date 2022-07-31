#! /bin/bash
#Tomer Hadar 207651027

game_on=true
playerOneAmount=50
playerTwoAmount=50
   echo " player 1: $playerOneAmount         player 2: $playerTwoAmount"
   echo " --------------------------------- "
   echo " |       |       #       |       | "
   echo " |       |       #       |       | "
   echo " |       |       O       |       | "
   echo " |       |       #       |       | "
   echo " |       |       #       |       | "
   echo " --------------------------------- "
ballPosition=null
currentBallPosition=0
playerOneNumber=null
playerTwoNumber=null
validMove=0
winString=""


printBored(){

   case "${currentBallPosition}" in
       -3)
           ballPosition="O|       |       #       |       | "
       ;;
       -2)
           ballPosition=" |   O   |       #       |       | "
       ;;
       -1)
           ballPosition=" |       |   O   #       |       | "
       ;;
       0)
           ballPosition=" |       |       O       |       | "
       ;;
       1)
           ballPosition=" |       |       #   O   |       | "
       ;;
       2)
           ballPosition=" |       |       #       |   O   | "
       ;;
       3)
           ballPosition=" |       |       #       |       |O"
       ;;
   esac
   
   echo " player 1: $playerOneAmount         player 2: $playerTwoAmount"
   echo " --------------------------------- "
   echo " |       |       #       |       | "
   echo " |       |       #       |       | "
   echo "$ballPosition"
   echo " |       |       #       |       | "
   echo " |       |       #       |       | "
   echo " --------------------------------- "
   echo -e "       Player 1 played: $playerOneNumber\n       Player 2 played: $playerTwoNumber\n\n"
}


checkInput(){
    if [[ ! $1 =~ ^[0-9]+$ ]] || [ $1 -gt $2 ]; then
        echo "NOT A VALID MOVE !"
        validMove=0
        return
    fi
    validMove=1
}



playersChooseNumber(){
   while [ $validMove -eq 0 ]
   do
   echo 'PLAYER 1 PICK A NUMBER:'
   read -s playerOneNumber
   checkInput "$playerOneNumber" "$playerOneAmount"
   done

   validMove=0

   while [ $validMove -eq 0 ]
   do
   echo 'PLAYER 2 PICK A NUMBER:'
   read -s playerTwoNumber
   checkInput "$playerTwoNumber" "$playerTwoAmount"
   done
   
   validMove=0
   changeBallPosition
   checkWinAndUpdateAmount
}

changeBallPosition(){
    if [ $playerOneNumber -gt $playerTwoNumber ]; then
        if [ $currentBallPosition -lt 0 ]; then
            currentBallPosition=1
        else
            currentBallPosition=$((currentBallPosition+1))
        fi
    elif [ $playerTwoNumber -gt $playerOneNumber ]; then
        if [ $currentBallPosition -gt 0 ]; then
            currentBallPosition=-1
        else
            currentBallPosition=$((currentBallPosition-1))
        fi
    fi
}

checkWinAndUpdateAmount(){
    if [ $currentBallPosition -eq 3 ]; then
        winString="PLAYER 1 WINS !"
        game_on=false
        return
    elif [ $currentBallPosition -eq -3 ]; then
        winString="PLAYER 2 WINS !"
        game_on=false
        return
    fi
    playerOneAmount=$((playerOneAmount-playerOneNumber))
    playerTwoAmount=$((playerTwoAmount-playerTwoNumber))

    if [ $playerOneAmount -eq 0 ] && [ $playerTwoAmount -eq 0 ]; then
        if [ $currentBallPosition -eq 0 ]; then
            winString="IT'S A DRAW !"
        elif [ $currentBallPosition -gt 0 ]; then
            winString="PLAYER 1 WINS !"
        else
            winString="PLAYER 2 WINS !"
        fi
        game_on=false
    elif [ $playerOneAmount -eq 0 ]; then
        winString="PLAYER 2 WINS !"
        game_on=false

    elif [ $playerTwoAmount -eq 0 ]; then
        winString="PLAYER 1 WINS !"
        game_on=false
    fi
}

while $game_on
do
playersChooseNumber
printBored
done
echo "$winString"