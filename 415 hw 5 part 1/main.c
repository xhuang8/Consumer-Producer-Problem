#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define NUM_THREADS 10


/**
 * Can use the following struct for
 * the nanosleep function.
 * the first value is sleep time in seconds
 * the second vaue is sleep time in nanoseconds.
 *
 * struct timespec ts = {2, 0 };
 *
 * you can call nano sleep as nanosleep(&ts, NULL);
*/
pthread_mutex_t m;
struct timespec ts ={2,0};
int static globalCounter=0;
void* printscreen(void* loca)
{
    pthread_mutex_lock(&m);
    int localVariable = globalCounter;
    //nanosleep(&localVariable, NULL);
    fprintf(stderr,"Hello, I am thread #%d\n",(int)loca);
    nanosleep(&ts,NULL);

    localVariable=globalCounter;
    fprintf(stderr,"I am thread #%d   read value            : %d\n",(int)loca,localVariable);
    nanosleep(&ts,NULL);

    localVariable=localVariable+10;
    fprintf(stderr,"I am thread #%d   added 10 value is now : %d\n",(int)loca,localVariable);
    nanosleep(&ts,NULL);

    globalCounter=localVariable;
    pthread_mutex_unlock(&m);
    return NULL;
}

void threadFunction()
{
    pthread_t my_thread[NUM_THREADS];
    pthread_mutex_init(&m,NULL);
    long i;
    //int threadRace;
    int threadStatus[NUM_THREADS];
    for(i=1;i<=NUM_THREADS;i++)
    {
        //int *p=(int*)malloc(sizeof(int));
        //*p=i;
       pthread_create(&my_thread[i],NULL,&printscreen,(void *)i);
       //pthread_create(&my_thread[i],NULL,&printscreen,void(*)(void *)i);
    }
    for(i=1;i<=NUM_THREADS;i++){
        pthread_join(my_thread[i],(void*)&threadStatus[i]);
    }
    printf("Final Global Value : %d\n",globalCounter);
    //exit(EXIT_SUCCESS);
}

int main()
{
     threadFunction();
    //printf("Hello world!\n");
    return 0;
}
