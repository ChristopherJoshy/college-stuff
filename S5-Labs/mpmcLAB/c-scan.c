#include<stdio.h>
#include<stdlib.h>

int main() {
    int head, a[30], n, distance, seektime = 0, temp, max;
    printf("Enter disk size: "); scanf("%d", &max);
    printf("Enter head position: "); scanf("%d", &head);
    printf("Enter number of requests: "); scanf("%d", &n);
    printf("Enter requests: ");
    for(int i=0; i<n; i++) scanf("%d", &a[i]);

    a[n] = head;
    a[n+1] = 0;
    a[n+2] = max - 1;

    for(int i=0; i<=n+2; i++)
        for(int j=i+1; j<=n+2; j++)
            if(a[i] > a[j]) { temp = a[i]; a[i] = a[j]; a[j] = temp; }

    int index;
    for(index=0; index<=n+2; index++)
        if(a[index] == head) break;

    printf("C-SCAN Disk Scheduling\n");

    for(int i=index; i<n+2; i++) {
        distance = abs(a[i+1] - a[i]);
        printf("Move from %d to %d : %d\n", a[i], a[i+1], distance);
        seektime += distance;
    }

    distance = abs((max - 1) - 0);
    printf("Move from %d to %d : %d\n", max - 1, 0, distance);
    seektime += distance;

    for(int i=0; i<index; i++) {
        distance = abs(a[i+1] - a[i]);
        printf("Move from %d to %d : %d\n", a[i], a[i+1], distance);
        seektime += distance;
    }

    printf("Total Seek Time: %d\n", seektime);
    return 0;
}
