#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
int SharedVariable = 0;
pthread_mutex_t mutex  =PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

void *SimpleThread(void *id){
	int num, val;
	int which = *((int*)id);
	for(num = 0; num < 20; num++){
	pthread_mutex_lock(&mutex);
                if(random()>RAND_MAX/2)
                        usleep(500);

                val = SharedVariable;
                printf("***thread %d sees value %d\n", which, val);
                SharedVariable = val + 1;
        pthread_mutex_unlock(&mutex);
	usleep(500);
        }
        pthread_barrier_wait(&barrier);
	 val = SharedVariable;
        printf("Tread %d sees final value %d\n", which, val);

}

int main(int argc, char *args[]){
/*-----------first is to validate command line parameter--*/
	int m;
	if(argc != 2 ){		
		printf("Please input a non-zero number\n");
		return 0;
	}
	for(m = 0;m<strlen(args[1]) ;m++){
		if(args[1][m] < '1' || args[1][m] > '9')
	{		printf("Please input a non-zero number\n");
			return 0;
		}
	}

	int ania = atoi(args[1]);
	pthread_t t[ania];
	int i,r;
	int flag[ania];
	pthread_barrier_init(&barrier, 0, ania);
	for( i = 0; i < ania; i++){
		flag[i] = i;	
		r = pthread_create(&t[i],NULL,SimpleThread,(void *)&(flag[i]));
	}
	pthread_exit(NULL);
	return 0;
}

