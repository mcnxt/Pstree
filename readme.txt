Marcus Cureton
Corey Shafer
07/30/2022


How to compile and run this program:
1.Run the "gcc mypstree.c" command to complie the program
2.Run the "./a.out 'pid number'" command to run the program(ex. "./a.out 1")
3.(Optional) To output to a text file run the command "./a.out 1 > out.txt"


Program Limitatons:
This program correctly takes in a pid and outputs a hierarchy of all the processes in the system in a tree-like format.
Rather than outputting the names of processes, this program only lists the pids.
If the user enters a non-exsisting pid, an error message will be shown.
To produce the output, the program traverses through the proc file system and track the parent and child processes.
