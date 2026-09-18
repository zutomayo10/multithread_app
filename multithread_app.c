#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

void* cpu_bound_worker(void* arg) {
    long id = (long) arg;
    volatile unsigned long long counter = 0;
    unsigned long long i;

    printf("Hilo CPU-bound %ld: iniciando calculo intensivo\n", id);

    for (i = 0; i < 3000000000ULL; i++) {
        counter += i % 7;
    }

    printf("Hilo CPU-bound %ld: termino (counter=%llu)\n", id, counter);
    return NULL;
}

void* io_bound_worker(void* arg) {
    long id = (long) arg;
    int j;

    printf("Hilo I/O-bound %ld: iniciando ciclo con sleep\n", id);

    for (j = 0; j < 20; j++) {
        printf("Hilo I/O-bound %ld: iteracion %d\n", id, j);
        usleep(200000);
    }

    printf("Hilo I/O-bound %ld: termino\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    long i;

    printf("PID del proceso principal: %d\n", getpid());

    pthread_create(&threads[0], NULL, cpu_bound_worker, (void*) 0);
    pthread_create(&threads[1], NULL, cpu_bound_worker, (void*) 1);

    pthread_create(&threads[2], NULL, io_bound_worker, (void*) 2);
    pthread_create(&threads[3], NULL, io_bound_worker, (void*) 3);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Todos los hilos terminaron.\n");
    return 0;
}
