#!/bin/bash

ret=0;
i=0;
c="valgrind --leak-check=full  --show-leak-kinds=all -s ./eval_formula";
tab=(   [0]="$c 0"\
        [1]="$c 1"\
        [2]="$c '!0'"\
        [3]="$c '01|&!'"\
        [4]="$c '01|&!01|!!!0&'");

make

while [ $ret -eq "0" ] && [ $i -ne ${#tab[*]} ]
do
    printf  "\n\n${tab[i]}\n\n";
    ${tab[i]} 2> stderr.log;
    ret=$?;

    if [ $ret -ne "0" ]
    then
        echo -e "\e[1;5;4;91m **** ERROR **** \e[0m";
    fi

    ((i=i+1))
    printf "\n\n";

done;


