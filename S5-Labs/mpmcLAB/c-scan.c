#include<stdio.h>
#include<stdlib.h>
int main() {
    int head, a[20], n, distance, seektime=0, temp;
    printf("Enter head position: "); scanf("%d",&head);
    printf("Enter number of requests: "); scanf("%d",&n);
    printf("Enter requests: ");
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    a[n] = head;

    // Sort requests
    for(int i=0;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(a[i]>a[j]) { temp=a[i]; a[i]=a[j]; a[j]=temp; }

    int index;
    for(index=0;index<=n;index++) if(a[index]>=head) break;

    printf("C-SCAN Disk Scheduling\n");
    // Move towards higher end
    for(int i=index;i<n+1;i++){
        distance = a[i]- (i==index ? head : a[i-1]);
        printf("Move from %d to %d : %d\n", i==index? head:a[i-1], a[i], distance);
        seektime += distance;
    }
    // Jump to start (0)
    distance = a[n]-a[0];
    printf("Move from %d to %d : %d\n", a[n], a[0], distance);
    seektime += distance;
    // Move from start to just before original head
    for(int i=0;i<index;i++){
        distance = a[i+1]-a[i];
        printf("Move from %d to %d : %d\n", a[i], a[i+1], distance);
        seektime += distance;
    }
    printf("Total Seek Time: %d\n",seektime);
    return 0;
}

