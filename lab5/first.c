//
// Created by queens_gambit on 13.12.2021.
//

int gcd(int A, int B) {
    while (A != B) {
        if (A > B) {
            A -= B;
        } else {
            B -= A;
        }
    }
    return A;
}

float countPi(int k) {
    float res = 0.0;
    for (int i = 0; i < k; ++i)  {
        float temp = 1 / (2.0 * i + 1);
        res += (i % 2 == 0)? temp : -temp;
    }
    return 4 * res;
}
