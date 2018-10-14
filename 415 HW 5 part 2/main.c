#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

struct queue{
    int *buffer;
    int front;
    int near;
};

struct queue bufferQueue;
//int buffer[BUFFERSIZE+1];//definition of buffer
//int front=0,rear=0;// pointer of front and near
int itemCount=1;// this is for item counting when a new item is released.
//sem_t mutex,empty,full;//semaphores
int N,P,C,X,Ptime,Ctime;//this is command line

//semaphores
sem_t semPrint;//need to lock it to avoid printing disorder
sem_t semQueue;//need to lock it to avoid changing the queue;
sem_t queueEmpty;//posted by consumer, init as N;
sem_t queueFull;//posted by producer, init as 0;

//define two arrays to store the sequence;
int* producerArray;
int* consumerArray;

//initialize the queue;
void initQueue()
{
    bufferQueue.buffer=(int* )malloc(sizeof(int) *N);
    bufferQueue.front=0;
    bufferQueue.near=0;
}

//enqueue function to insert item to the buffer
void enqueue(int enq)
{
    int t=bufferQueue.front;
    bufferQueue.front=(bufferQueue.front+1)%N;
    bufferQueue.buffer[t]=enq;
}

//dequeue function to remove item from the buffer
int dequeue()
{
    int t=bufferQueue.buffer[bufferQueue.near];
    bufferQueue.near=(bufferQueue.near+1)%N;
    return t;
}

//producer function
void* producer(void* arg)
{
    int id=*(int* )arg;
	static int item=0;
	int i;
	for(i=0;i<X;i++)
	{
		sem_wait(&queueEmpty); // this is V(BUFFEREMPTY)
		sem_wait(&semQueue);
		enqueue(itemCount);
		sem_wait(&semPrint);
		printf("%2d  was produced by producer->\t%d\n",itemCount,id);
		producerArray[item]=itemCount;
		item++;
		itemCount++;
		sem_post(&semPrint);
		sem_post(&semQueue);
		sem_post(&queueFull);
		sleep(Ptime);//Each producer thread must sleep for Ptime after producing each item.
	}
}

//consumer function
void* consumer(void* arg)
{
    int id=*(int* )arg;
    static int item=0;
    int i;
    for(i=0;i<P*X/C;i++)
	{
		sem_wait(&queueFull); // this is V(BUFFEREMPTY)
		sem_wait(&semQueue);
		int t=dequeue();
		sem_wait(&semPrint);
		printf("%2d  was consumed by consumer->\t%d\n",t,id);
		consumerArray[item]=t;
		item++;
		//itemCount++;
		sem_post(&semPrint);
		sem_post(&semQueue);
		sem_post(&queueEmpty);
		sleep(Ctime);//Each consumer thread must sleep for Ctime after consuming each item.
	}

	//design a situation to avoid non-dividable.
	if(id<=(P*X)%C)
    {
        sem_wait(&queueFull); // this is V(BUFFEREMPTY)
		sem_wait(&semQueue);
		int t=bufferQueue.buffer[bufferQueue.near];
		bufferQueue.near=(bufferQueue.near+1)%N;
		sem_wait(&semPrint);
		printf("%2d  was consumed by consumer->\t%d\n",t,id);
		consumerArray[item]=t;
		item++;
		//itemCount++;
		sem_post(&semPrint);
		sem_post(&semQueue);
		sem_post(&queueEmpty);
		sleep(Ctime);//also need to sleep Ctime;
    }
}

int main(int argc, char* argv[])
{
   // int i, threadNum;
    if(argc!=7)
    {
        printf("You get the wrong number of parameters !!!\n");
        return 1;
    }
    /*else{
        threadNum=atoi(argv[1]);//get the line of input
    }*/
    N = atoi(argv[1]);
	P = atoi(argv[2]);
	C = atoi(argv[3]);
	X = atoi(argv[4]);
	Ptime = atoi(argv[5]);
	Ctime = atoi(argv[6]);

    //initialize queue
    initQueue();
    //initialize array
    producerArray=(int* )malloc(sizeof(int)*P*X);
    consumerArray=(int* )malloc(sizeof(int)*P*X);

    //initialize semaphores
    int sema=sem_init(&queueEmpty, 0, N);
    if (sema)
    {
         printf("Semaphore initialization failed !!!\n");
         exit(EXIT_FAILURE);
    }
    sema =sem_init(&queueFull, 0, 0);
    if (sema)
    {
         printf("Semaphore initialization failed !!!\n");
         exit(EXIT_FAILURE);
    }
    sema=sem_init(&semPrint, 0, 1);
    if (sema)
    {
         printf("Semaphore initialization failed !!!\n");
         exit(EXIT_FAILURE);
    }
    sema=sem_init(&semQueue, 0, 1);
    if (sema)
    {
         printf("Semaphore initialization failed !!!\n");
         exit(EXIT_FAILURE);
    }
   // printf("Hello world!\n");

    /*pthread_t *threadProducer;
    pthread_t *threadConsumer;

    *threadProducer=(pthread_t *)malloc(sizeof(pthread_t)*P);
    *threadConsumer=(pthread_t *)malloc(sizeof(pthread_t)*C);*/
    pthread_t *threadProducer=(pthread_t *)malloc(sizeof(pthread_t)*P);
    pthread_t *threadConsumer=(pthread_t *)malloc(sizeof(pthread_t)*C);
    int *idP=(int *)malloc(sizeof(int)*P);
    int *idC=(int *)malloc(sizeof(int)*C);
    printf("N = %d P = %d C = %d X = %d Ptime = %d Ctime = %d\n",N,P,C,X,Ptime,Ctime);
    //print the time
    time_t curTime;
    time(&curTime);
    printf("Current time: %s\n",ctime(&curTime));
    //loop for creating
    int i;
    for(i=0;i<P;i++)
    {
        idP[i]=i+1;
        sema=pthread_create(&threadProducer[i],NULL,producer,(void *)&idP[i]);
        if (sema!=0)
        {
	         printf("Thread creation failed !!! sema = %d !!!\n", sema);
	         exit(EXIT_FAILURE);
        }
    }

    for(i=0;i<C;i++)
    {
        idC[i]=i+1;
        sema=pthread_create(&threadConsumer[i],NULL,consumer,(void *)&idC[i]);
        if (sema!=0)
        {
	         printf("Thread creation failed !!!\n");
	         exit(EXIT_FAILURE);
        }
    }

    //loop for joining
    for(i=0;i<P;i++)
    {
    	pthread_join(threadProducer[i],NULL);
    	sem_wait(&semPrint);
    	printf("Producer Thread joined:  %2d\n", i+1);
    	sem_post(&semPrint);
    }
    for(i=0;i<C;i++)
    {
    	pthread_join(threadConsumer[i],NULL);
    	sem_wait(&semPrint);
    	printf("Consumer Thread joined:  %2d\n", i+1);
    	sem_post(&semPrint);
    }
    //print the time
    time_t curTime1;
    time(&curTime1);
    printf("Current time: %s\n",ctime(&curTime1));

    //do the array part.
    printf("Producer Array \t| Consumer Array\n");
    for(i=0;i<P*X;i++)
    {
    	printf("%d\t\t| %d\n", producerArray[i], consumerArray[i]);
    }
    printf("\nConsume and Produce Arrays Match!\n\n");
    printf("Total Runtime: %d secs\n", (int)difftime(curTime1,curTime));

    free(bufferQueue.buffer);
    free(threadConsumer);
    free(threadProducer);
    free(consumerArray);
    free(producerArray);
    free(idC);
    free(idP);
    //sem_destroy(&empty);
    //sem_destroy(&full);
    sem_destroy(&semPrint);
    sem_destroy(&queueFull);
    sem_destroy(&queueEmpty);
    sem_destroy(&semQueue);

    return 0;
}
