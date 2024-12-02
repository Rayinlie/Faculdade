#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5  // Número de cadeiras de espera

sem_t cliente;
sem_t barbeiro;
sem_t mutex;
int clientes_esperando = 0;

void* barber(void* arg) {
    while (1) {
        sem_wait(&cliente);           // Espera por um cliente
        sem_wait(&mutex);             // Entra na seção crítica
        clientes_esperando--;
        sem_post(&barbeiro);          // Acorda o barbeiro
        sem_post(&mutex);             // Sai da seção crítica
        printf("Cortando cabelo...\n");
    }
}

void* customer(void* arg) {
    while (1) {
        sem_wait(&mutex);             // Entra na seção crítica
        if (clientes_esperando < N) { // Se há cadeiras de espera disponíveis
            clientes_esperando++;
            sem_post(&cliente);       // Cliente entra na fila
            sem_post(&mutex);         // Sai da seção crítica
            sem_wait(&barbeiro);      // Espera o barbeiro cortar o cabelo
            printf("Cliente cortou o cabelo.\n");
        } else {
            sem_post(&mutex);         // Sai da seção crítica
            printf("Cliente foi embora sem cortar o cabelo.\n");
        }
    }
}

int main() {
    pthread_t b, c[10];

    sem_init(&cliente, 0, 0);
    sem_init(&barbeiro, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&b, NULL, barber, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_create(&c[i], NULL, customer, NULL);
    }

    pthread_join(b, NULL);
    for (int i = 0; i < 10; i++) {
        pthread_join(c[i], NULL);
    }

    sem_destroy(&cliente);
    sem_destroy(&barbeiro);
    sem_destroy(&mutex);

    return 0;
}
