#include <stdio.h>
void cheak(int a, int b, int c, int R, int* steps)
{
    *steps += 1;
    //printf("Cheak!\n");
    if (a == R || b == R || c == R)
    {
        printf("(%d, %d, %d)\n", a, b, c);
        printf("Target was find\n");
        printf("Steps: %d\n", *steps);
        exit();
    }
}
void pour_water(int a, int b, int c, int R, int* steps) {
    int x = a, y = 0, z = 0;

    if (a*b*c % R != 0) 
    {
        printf("No solution found\n");
        return;
    }
    while (x != R && y != R && z != R) {
        while (b != y )
        {
            printf("(%d, %d, %d)\n", x, y, z);
            printf("Refill water from first to third\n"); //1-3
            int pour = c - z;
            if (pour > x) {
                pour = x;
            }
            x -= pour;
            z += pour;
            cheak(x, y, z, R, steps);
            printf("(%d, %d, %d)\n", x, y, z);
            printf("Refill water from third to second\n"); //3-2
            int pour1 = b - y;
            if (pour1 > z) {
                pour1 = z;
            }
            z -= pour1;
            y += pour1;
            cheak(x, y, z, R, steps);
        }
        printf("(%d, %d, %d)\n", x, y, z);
        printf("Refill water from second to first\n");//2-1
        int pour2 = a - x;
        if (pour2 > y) {
            pour2 = y;
        }
        y -= pour2;
        x += pour2;
        cheak(x, y, z, R,steps);
        printf("(%d, %d, %d)\n", x, y, z);
        printf("Refill water from third to second\n"); //3-2
        int pour = b - y;
        if (pour > z) {
            pour = z;
        }
        z -= pour;
        y += pour;
        cheak(x, y, z, R, steps);

    }
}

int main() {
    int a, b, c, R;
    int n = 0;
    printf("Vassel's volumes a, b, c: ");
    scanf_s("%d %d %d", &a, &b, &c);
    printf("Target R: ");
    scanf_s("%d", &R);

    pour_water(a, b, c, R, &n);

    return 0;
}
