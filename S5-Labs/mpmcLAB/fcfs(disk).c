#include<stdio.h>
int main() {
    int head, a[20], n, distance, seektime=0;
    printf("Enter head position: ");
    scanf("%d",&head);
    printf("Enter number of requests: ");
    scanf("%d",&n);
    printf("Enter requests: ");
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    a[0]=head;

    printf("FCFS Disk Scheduling\n");
    for(int i=0;i<n;i++){
        distance = (a[i]>a[i+1]) ? a[i]-a[i+1] : a[i+1]-a[i];
        printf("Move from %d to %d : %d\n",a[i],a[i+1],distance);
        seektime += distance;
    }
    printf("Total Seek Time: %d\n",seektime);
    return 0;
}

