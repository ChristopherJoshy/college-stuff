#include <stdio.h>
int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    int bt[n],p[n],wt[n],tat[n],pri[n],totalWT=0,totalTAT=0;

    for(int i=0;i<n;i++){
        printf("Enter Burst Time and Priority of P%d: ",i+1);
        scanf("%d%d",&bt[i],&pri[i]);
        p[i]=i+1;
    }

    // Sorting by Priority (lower value = higher priority)
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(pri[i]>pri[j]){
                int t=pri[i]; pri[i]=pri[j]; pri[j]=t;
                t=bt[i]; bt[i]=bt[j]; bt[j]=t;
                t=p[i]; p[i]=p[j]; p[j]=t;
            }
        }
    }

    wt[0]=0;
    for(int i=1;i<n;i++)
        wt[i]=wt[i-1]+bt[i-1];

    for(int i=0;i<n;i++)
        tat[i]=wt[i]+bt[i];

    for(int i=0;i<n;i++){
        totalWT+=wt[i];
        totalTAT+=tat[i];
    }

    printf("\nPID\tBT\tPR\tWT\tTAT\n");
    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\n",p[i],bt[i],pri[i],wt[i],tat[i]);

    printf("\nAvg WT=%.2f\nAvg TAT=%.2f\n",(float)totalWT/n,(float)totalTAT/n);
    return 0;
}

