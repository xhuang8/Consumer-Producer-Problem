Name  :XiaoQian Huang
Date  :4/20/2018
Class : CSC 415 

Compile Instructions: This project lets us modify pthread_race.c. We need to add the necessary
mutex synchronization calls for Linux threads. After finish this project, I compile it under 
the Linux environment. However, it still has some warning in my project, and it doesn't affect
us to run it to get the results.


Run Instructions: This project requires us use the synchronization primitives of the programming
API you are working with (Posix). I use the CodeBlocks to finish it, adn then put then in the 
Linux environment. Type: gcc pthread_race.c -pthread and ./a.out
the ouput should be as following: 
xhuang@xhuang-VirtualBox:~/Desktop$ ./a.out
Hello, I am thread #6
I am thread #6   read value            : 0
I am thread #6   added 10 value is now : 10
Hello, I am thread #7
I am thread #7   read value            : 10
I am thread #7   added 10 value is now : 20
Hello, I am thread #8
I am thread #8   read value            : 20
I am thread #8   added 10 value is now : 30
Hello, I am thread #5
I am thread #5   read value            : 30
I am thread #5   added 10 value is now : 40
Hello, I am thread #9
I am thread #9   read value            : 40
I am thread #9   added 10 value is now : 50
Hello, I am thread #4
I am thread #4   read value            : 50
I am thread #4   added 10 value is now : 60
Hello, I am thread #3
I am thread #3   read value            : 60
I am thread #3   added 10 value is now : 70
Hello, I am thread #2
I am thread #2   read value            : 70
I am thread #2   added 10 value is now : 80
Hello, I am thread #1
I am thread #1   read value            : 80
I am thread #1   added 10 value is now : 90
Hello, I am thread #0
I am thread #0   read value            : 90
I am thread #0   added 10 value is now : 100
Final Global Value : 100

Project Description: In this project, we should add some code which based on the last project. The last
project we just have the output in race condition is fine. This time ,we should have the output with mutex 
avoiding race condition. Thus, only add pthread_mutex_t m, pthread_mutex_lock(&m)//mutex is locked by the 
thread to avoid race condition, pthread_mutex_unlock(&m)//when finish, thread will be unlocked.
and pthread_mutex_init(&m,NULL); We get the output in last question.
