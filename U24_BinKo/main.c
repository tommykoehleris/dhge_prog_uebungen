#include <stdio.h>
#include <stdlib.h>

int fac(int n);
int binom(int n, int k);

int main(int argc, const char *argv[])
{
    if (argc != 2) {
    printf("%s: Fehlerhafter Aufruf!", argv[0]);
    return 1;
    }

    int zeilen = atoi(argv[1]);

    for (int i = 0; i < zeilen; i++) {

        int text = 80 / 2 - ((i + 1) * 5 + i) / 2;

        for (int j = 1; j < text; ++j) {
            putchar(' ');
        }

        for (int j = 0; j <= i; ++j) {
            printf("%5d ", binom(i, j));
        }

        putchar('\n');
    }

    return 0;
}

int binom(int n, int k)
{
    if ((n < 0) || (n > 12)) return -1;
    if ((k > n) || (k < 0)) return 0;

    return fac(n) / (fac(k) * fac((n-k)));
}

int fac(int n)
{
  if (n < 0) {
    return -1;
  }

  int f = 1;

  for (int i = 2; i <= n; ++i) {
    f *= i;
  }
  return f;
}
