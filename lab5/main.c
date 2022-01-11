#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("libfirst.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }
    int (*gcd)(int, int);
    float (*countPi)(int);
    gcd = dlsym(handle, "gcd");
    if(!gcd){
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }
    countPi = dlsym(handle, "countPi");
    if(!countPi){
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }
    int command = 0;
    while (scanf("%d", &command) != EOF) {
        switch (command) {
            case 1: {
                int A, B;
                scanf("%d %d", &A, &B);
                printf("%d\n", gcd(A, B));
            }
            break;
            case 2: {
                int kkk;
                scanf("%d", &kkk);
                printf("%f\n", countPi(kkk));
            }
            break;
            default: {
                printf("Wrong Command\n");
            }
        }
    }
    dlclose(handle);
    return 0;
}
