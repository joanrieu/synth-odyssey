#include <pthread.h>

void ui();
void* driver(void*);

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, driver, NULL);
    ui();
}
