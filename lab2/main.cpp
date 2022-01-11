#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main() {
    char name[30];
    scanf("%s", name);
    FILE *fd = fopen(name, "w");
    int pipe1[2];
    if (pipe(pipe1) == -1) {
        printf("Error piping");
        return 1;
    }
    int pid = fork();
    if (pid == -1) {
        printf("Error forking");
        return 2;
    }
    if (pid != 0) {
        close(pipe1[0]);
        float a1 = 0;
        float a2 = 0;
        float a3 = 0;
        scanf("%f %f %f", a1, a2, a3);
        write(pipe1[1], (const void) a1, sizeof(float));
        w
    }
    return 0;
}