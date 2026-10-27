
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int fcfs(int a[], int n, int head) {
    int total = 0, cur = head;
    for (int i = 0; i < n; i++) {
        total += abs(cur - a[i]);
        cur = a[i];
    }
    return total;
}

int sstf(int a[], int n, int head) {
    int used[100] = {0}, total = 0, cur = head;

    for (int i = 0; i < n; i++) {
        int min = 100000, pos = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && abs(cur - a[j]) < min) {
                min = abs(cur - a[j]);
                pos = j;
            }
        }
        used[pos] = 1;
        total += abs(cur - a[pos]);
        cur = a[pos];
    }
    return total;
}

int scan(int a[], int n, int head, int size) {
    int b[100], total = 0, cur = head;

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    qsort(b, n, sizeof(int), cmp);

    int i = 0;
    while (i < n && b[i] < head)
        i++;

    for (int j = i; j < n; j++) {
        total += abs(cur - b[j]);
        cur = b[j];
    }

    if (cur != size - 1) {
        total += abs(cur - (size - 1));
        cur = size - 1;
    }

    for (int j = i - 1; j >= 0; j--) {
        total += abs(cur - b[j]);
        cur = b[j];
    }

    return total;
}

int main() {
    int n, a[100], head, size;

    printf("Enter disk size: ");
    scanf("%d", &size);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    if (n < 1 || n > 100 || size < 1 ||
        head < 0 || head >= size) {
        printf("Invalid input!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < 0 || a[i] >= size) {
            printf("Invalid request!\n");
            return 1;
        }
    }

    int f = fcfs(a, n, head);
    int s = sstf(a, n, head);
    int sc = scan(a, n, head, size);

    printf("\n--- Disk Scheduling Results ---\n");
    printf("FCFS Head Movement: %d\n", f);
    printf("SSTF Head Movement: %d\n", s);
    printf("SCAN Head Movement: %d\n", sc);

    if (f <= s && f <= sc)
        printf("Least movement: FCFS\n");
    else if (s <= sc)
        printf("Least movement: SSTF\n");
    else
        printf("Least movement: SCAN\n");

    return 0;
}
