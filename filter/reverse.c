#include <stdio.h>

int main (void)
{
  int temp;
  int n = 5;
  int a[5] = {0, 1, 2, 3, 4};

  for (int c = 0; c < n/2; c++)
  {
    temp = a[c];                  // Swapping
    a[c] = a[n - c - 1];
    a[n - c - 1] = temp;
  }

  for (int i = 0; i < n; i++)
  {
    printf("%i ", a[i]);
    printf("\n");
  }

}
