#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

#define n_clients 3
int client_count[n_clients + 1];

/* initialize mutex */
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

void *client(void *value) {
    int i;
    int num = (intptr_t) value;
    time_t start_t, end_t;
    int read = 100;
    start_t = clock();
    printf("Enters shop with basket nº.\n", num, client_count[num] + 1);
    pthread_mutex_lock( &my_mutex );
    client_count[num] = client_count[num] + 1;
    client_count[n_clients + 1] = client_count[n_clients + 1] + 1;
	pthread_mutex_unlock( &my_mutex );
    while (i < read) {
        i++;
    }
    end_t = clock();
    printf("Client leaves shop.");
    printf("Execution time: ", num, (double)(end_t - start_t) / CLOCKS_PER_SEC);
    return NULL;
}
int main(int argc, char **argv) {
    pthread_t thread[n_clients];
    srand(time(NULL));
    printf("Program starts: ");
    int i;
    while (1) {
        for (i = 0; i < n_clients; i++) {
            printf("Create the thread:  ");
            if (client_count[i] < 2) {
                pthread_create(&thread[i], NULL, client, (void*) (intptr_t) i);
            }else{
                (client_count[i] == 2){
                    pthread_create(&thread[i], NULL);
                }
            }
        }
        for (i = 0; i < n_clients; i++) {
            pthread_join(thread[i], NULL);
        }
        if (client_count[n_clients + 1] >= n_clients * 2) {
            break;
        }
    }
    return EXIT_SUCCESS;
}