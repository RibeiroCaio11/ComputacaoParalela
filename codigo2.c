#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#define NUM_THREADS 4
#define N 10000000
int *v;

//long long total = 0;
long long parcial[NUM_THREADS];

void *soma_trecho(void *arg) {
    long tid = (long) arg;
    long ini = tid * (N / NUM_THREADS);
    long fim = (tid + 1) * (N / NUM_THREADS);
    long long soma_local = 0;
    for (long i = ini; i < fim; i++){
        soma_local += v[i]; // <<< CONDICAO DE CORRIDA
     }
     parcial[tid] = soma_local;
return NULL;
}


int main(void){
    v = malloc(N*sizeof(int));
    pthread_t threads[NUM_THREADS];
    for(int i = 0; i<N; i++){
        v[i] = 10;

    }
    for( long t = 0; t<NUM_THREADS;t++){
    
    pthread_create(&threads[t], NULL, soma_trecho, (void *)t);
    }
    for( long t = 0; t<NUM_THREADS;t++){
        pthread_join(threads[t],NULL);
    }
    long long total = 0;
    for(int t=0;t<NUM_THREADS;t++){
        total += parcial[t];
    }
    printf("soma esperada:%lld\n",(long long) N*10);
    printf("soma calculada:%lld\n",total);
}