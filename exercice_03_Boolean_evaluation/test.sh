#!/bin/bash

ret=0;
i=0;
# command="valgrind --leak-check=full  --show-leak-kinds=all -s ./eval_formula";
command="./eval_formula";
tab=(   [0]="$command 0"\
        [1]="$command 1"\
        [2]="$command 0!"\
        [3]="$command 010|&!"\
        [4]="$command 01|01&!!!0&"\
		[5]="$command 10&"\
		[6]="$command 10|"\
		[7]="$command 10|1&"\
		[8]="$command 101|&"\
		[9]="$command 11>"\
		[9]="$command 10="\
		[10]="$command 1011||="\
);

#		10& 	<===>	1 & 0 				<===> false
#		10| 	<===>	1 | 0 				<===> true
#		10|1&	<===>	(1 | 0) & 1			<===> true
#		101|& 	<===>	1 & (0 | 1)			<===> true
#		11>		<===>	1 => 1 				<===> true
#		1011||= <===>	((1 | 1) | 0) == 1	<===> true

echo "build binary..."
make > /dev/null

while [ $ret -eq "0" ] && [ $i -ne ${#tab[*]} ]
do
    printf  "\n\nTest $i: ${tab[i]}\n";
    ${tab[i]}

    ((i=i+1))
done;


