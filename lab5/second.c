//
// Created by queens_gambit on 13.12.2021.
//
int gcd(int A, int B) {
    int res = 1;
    for (int i = A; i > 1; --i) {
        if ((A % i == 0) && (B % i == 0)) {
            res = i;
            break;
        }
    }
    return res;
}

float countPi(int k) {
    float res = 1;
    for (int i = 1; i <= k - 1; ++i) {
        res *= (2.0 * i) * (2.0 * i) / ((2.0 * i - 1.0) * (2.0 * i + 1.0));
    }
    res *= ((2.0 * k / (2.0 * k - 1)) *
            ((2.0 * k) / (2.0 * k + 1) * (1.0 / 4.0) + 1) +
            3.0 / 4.0);
}