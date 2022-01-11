//
// Created by queens_gambit on 13.12.2021.
//
#include <stdio.h>

int gcd(int A, int B);
float countPi(int k);

int main() {
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
    return 0;
}
