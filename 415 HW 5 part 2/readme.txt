Name  :XiaoQian Huang
Date  :4/25/2018
Class :CSC415

Compile Instructions:This project is to implement consumer producer problem which based on Programming
Project 6.40 in silbershatz. It is the same to bounded buffer. For this project, we should discuss the 
suitation which is non-divisable. After finishing the programming, I complie it under the Linux 
environment. Then, I would see the output after running. 


Run Instructions:For this coding assginment, I used the CodeBlock to finish it. Then, I ran it under the Linux
environment. Thus, type:
gcc pandc.c -pthread
./a.out
the output should be as following:
xhuang@xhuang-VirtualBox:~/Desktop$ ./a.out 7 3 2 5 1 1
N = 7 P = 3 C = 2 X = 5 Ptime = 1 Ctime = 1
Current time: Fri Apr 20 02:39:59 2018

 1  was produced by producer->	3
 1  was consumed by consumer->	2
 2  was produced by producer->	2
 2  was consumed by consumer->	1
 3  was produced by producer->	1
 3  was consumed by consumer->	2
 4  was produced by producer->	3
 4  was consumed by consumer->	1
 5  was produced by producer->	2
 6  was produced by producer->	1
 5  was consumed by consumer->	2
 6  was consumed by consumer->	1
 7  was produced by producer->	3
 8  was produced by producer->	2
 9  was produced by producer->	1
 7  was consumed by consumer->	2
 8  was consumed by consumer->	1
10  was produced by producer->	3
11  was produced by producer->	2
12  was produced by producer->	1
 9  was consumed by consumer->	2
10  was consumed by consumer->	1
13  was produced by producer->	3
14  was produced by producer->	2
15  was produced by producer->	1
11  was consumed by consumer->	2
12  was consumed by consumer->	1
Producer Thread joined:   1
Producer Thread joined:   2
Producer Thread joined:   3
13  was consumed by consumer->	2
14  was consumed by consumer->	1
15  was consumed by consumer->	1
Consumer Thread joined:   1
Consumer Thread joined:   2
Current time: Fri Apr 20 02:40:07 2018

Producer Array 	| Consumer Array
1		| 1
2		| 2
3		| 3
4		| 4
5		| 5
6		| 6
7		| 7
8		| 8
9		| 9
10		| 10
11		| 11
12		| 12
13		| 13
14		| 14
15		| 15

Consume and Produce Arrays Match!

Total Runtime: 8 secs


Project Description: In this project, we need to solve the consumer producer problem. We have 6
arguments to do the command line. Also, we need to use the semaphoras to solve the consumer 
producer problem. At the same time, we should avoid some lock and unlock, printint disorder, and
changing the array problem. Finally, we got the output in the last question. 
