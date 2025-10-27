#include <stdio.h>

int main() {
    int p, c, i, j, count = 0, terminate = 0;
    printf("Enter the no of processes and resoures: ");
    scanf("%d %d", &p, &c);

    int alloc[p][c], max[p][c], need[p][c], avail[c], safe[p], finish[p];

    printf("Enter the allocation of resource of all process %dx%d matrix:\nallocation:\n", p, c);
    for (i = 0; i < p; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter the max resoure of all process %dx%d matrix:\n", p, c);
    for (i = 0; i < p; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter the available resource: ");
    for (i = 0; i < c; i++)
        scanf("%d", &avail[i]);

    printf("\nThe need matrix is:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
        finish[i] = 0;
    }

    while (count < p) {
        int progress = 0;
        for (i = 0; i < p; i++) {
            if (!finish[i]) {
                for (j = 0; j < c; j++)
                    if (need[i][j] > avail[j]) break;

                if (j == c) {
                    safe[count++] = i;
                    finish[i] = 1;
                    for (j = 0; j < c; j++)
                        avail[j] += alloc[i][j];
                    progress = 1;
                }
            }
        }
        if (!progress) {
            printf("\nSafe sequence does not exist\n");
            return 0;
        }
    }

    printf("\nAvailable resource after completion: ");
    for (i = 0; i < c; i++)
        printf("%d ", avail[i]);

    printf("\nSystem is in safe state:\nThe safe sequence is:\n<");
    for (i = 0; i < p; i++)
        printf("P%d ", safe[i] + 1);
    printf(">\n");

    return 0;
}

