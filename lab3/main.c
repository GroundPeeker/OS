#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int nums[131072];
int len = 131072;
int threads = 2;
pthread_mutex_t mutex;

void exchange(int i, int j) {
    int t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}

void compare(int i, int j) {
    if (nums[i]  > nums[j])
        exchange(i, j);
}

void* oddEvenMerge(void* args) {
    int* ar = (int*) args;
    int lo = ar[0];
    int n = ar[1];
    int r = ar[2];
    int m = r * 2;
    if (m < n) {
        int properties1[3] = {lo, n, m};
        int properties2[3] = {lo+r, n, m};
        int create_threads = 0;
        pthread_mutex_lock(&mutex);
        if (threads >= 2) {
            threads -= 2;
            create_threads = 1;
        }
        pthread_mutex_unlock(&mutex);
        if (create_threads) {
            pthread_t t1;
            pthread_create(&t1, NULL, &oddEvenMerge, properties1);
            pthread_t t2;
            pthread_create(&t2, NULL, &oddEvenMerge, properties2);
            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
        } else {
            oddEvenMerge(properties1);
            oddEvenMerge(properties2);
        }
        for (int i = lo + r; i + r < lo + n; i += m) {
            compare(i, i + r);
        }
    }
    else {
        compare(lo, lo+r);
    }
}


void* oddEvenMergeSort(void* args) {
    int* ar = (int*) args;
    int lo = ar[0];
    int n = ar[1];
    if (n > 1) {
        int create_threads = 0;
        int m = n/2;
        int properties1[2] = {lo, m};
        int properties2[2] = {lo+m, m};
        pthread_mutex_lock(&mutex);
        if (threads >= 2) {
            threads -= 2;
            create_threads = 1;
        }
        pthread_mutex_unlock(&mutex);
        if (create_threads) {
            pthread_t t1;
            pthread_create(&t1, NULL, &oddEvenMergeSort, properties1);
            pthread_t t2;
            pthread_create(&t2, NULL, &oddEvenMergeSort, properties2);
            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
        } else {
            oddEvenMergeSort(properties1);
            oddEvenMergeSort(properties2);
        }
        int properties3[3] = {lo, n, 1};
        oddEvenMerge((void**) properties3);
    }
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    struct timespec start, stop;
    long int tt;
    if ((threads < 0) && (threads % 2 == 1)) {
        printf("Incorrect number of threads\n");
    }
    if ((len==0) && (len % 2 == 1)) {
        printf("Not even or zero length\n");
        return 1;
    }
    for (int i = 1; i <= len; i++) {
        nums[len - i] = i;
    }
    clock_gettime(CLOCK_REALTIME, &start);

    int properties[2] = {0, len};
    oddEvenMergeSort((void**)properties);
    pthread_mutex_destroy(&mutex);
    clock_gettime(CLOCK_REALTIME, &stop);
    tt = 100000000*(stop.tv_sec - start.tv_sec)+(stop.tv_nsec - start.tv_nsec);
    printf("Time estimated: %ld ns\n", tt);
}
