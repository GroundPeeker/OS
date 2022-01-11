#include <iostream>
#include <ostream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fstream>

int main() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    int N=4;
    int *ptr = static_cast<int*>(mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0,
                                       0));
    sem_t* osem = static_cast<sem_t*>(mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0));
    sem_t* isem = static_cast<sem_t*>(mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0));
    if ((ptr == MAP_FAILED)||(isem == MAP_FAILED)||(osem == MAP_FAILED)){
        printf("Mapping Failed\n");
        return 1;
    }
    for(int i = 0; i < N; i++) {
        ptr[i] = 0;
    }
    sem_init(osem, true, 0);
    sem_init(isem, true, 1);
    int pid = fork();
    if (pid == 0) {
        std::ofstream outputFile;
        outputFile.open(filename, std::ios::out);
        while (true) {
            sem_wait(osem);
            if (ptr[3] == -1) {
                break;
            }
            if ((ptr[1] == 0) || (ptr[2] == 0)) {
                std::cout << "One of Divisors is zero!!!" << std::endl;
                ptr[3] = -1;
            } else {
                outputFile << (ptr[0] / ptr[1] / ptr[2]) << std::endl;
            }
            sem_post(isem);
            if (ptr[3] == -1) {
                break;
            }
        }
        outputFile.close();
    } else {
        while (true) {
            sem_wait(isem);
            if (ptr[3] == -1) {
                break;
            }
            int a1, a2, a3;
            std::cout << "Enter numbers: ";
            if (std::cin >> a1 >> a2 >> a3) {
                ptr[0] = a1;
                ptr[1] = a2;
                ptr[2] = a3;
            } else {
                ptr[3] = -1;
            }
            sem_post(osem);
            if (ptr[3] == -1) {
                break;
            }
        }
    }
    int err = munmap(ptr, N * sizeof(int)) + munmap(isem, sizeof(sem_t)) + munmap(osem, sizeof(sem_t));
    if (err != 0) {
        printf("UnMapping Failed\n");
        return 1;
    }
    sem_destroy(isem);
    sem_destroy(osem);
    return 0;
}
