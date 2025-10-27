#include <stdio.h>
int main(){
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    int bt[n], rem[n], wt[n], tat[n];
    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    for(int i=0;i<n;i++){
        printf("Enter Burst Time of P%d: ",i+1);
        scanf("%d",&bt[i]);
        rem[i]=bt[i];
        wt[i]=tat[i]=0;
    }

    int t=0, done;
    do{
        done=1;
        for(int i=0;i<n;i++){
            if(rem[i]>0){
                done=0;
                if(rem[i]>tq){
                    t+=tq;
                    rem[i]-=tq;
                }else{
                    t+=rem[i];
                    wt[i]=t-bt[i];
                    rem[i]=0;
                }
            }
        }
    }while(!done);

    for(int i=0;i<n;i++)
        tat[i]=bt[i]+wt[i];

    float totalWT=0,totalTAT=0;
    printf("\nPID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\n",i+1,bt[i],wt[i],tat[i]);
        totalWT+=wt[i];
        totalTAT+=tat[i];
    }

    printf("\nAvg WT=%.2f\nAvg TAT=%.2f\n",totalWT/n,totalTAT/n);
    return 0;
}

