#include<stdio.h>
int main(){
 int n;
 int avgwt=0,avgtat=0,totalTAT=0,totalWT=0;
 printf("Enter the total number of process\n");
 scanf("%d",&n);
  int tat[n],wt[n],bt[n];
 for(int i=1;i<=n;i++){
  printf("Enter The Burst time of Process %d\n",i);
    scanf("%d",&bt[i]);
}
  wt[1]=0;
  for(int i=2;i<=n;i++){
    wt[i]=wt[i-1]+bt[i-1];
  }
  for(int i=1;i<=n;i++){
    tat[i]=wt[i]+bt[i];
  }
  for(int i=1;i<=n;i++){
    totalTAT = tat[i]+totalTAT;
    totalWT =wt[i]+totalWT;
  }
  avgwt= totalWT/n;
  avgtat= totalTAT/n;
  printf("ProcessID\tBurstTime\t watingTime\tTurnAroundTime\n");
	for(int i=1;i<=n;i++){
		printf("P%d: ",i);
		printf("\t\t%d",bt[i]);
		printf("\t\t\t%d",wt[i]);
		printf("\t\t%d",tat[i]);
		printf("\n");
	}
  printf("average Turn around time: %d",avgtat);
	printf("\naverage waiting time: %d\n",avgwt);
  printf("Gantt Chart------->\n");
  for(int i=1;i<=n;i++){
		printf("|  P%d   ",i);
	}
  printf("\n");
	
  for(int i=1;i<=n;i++){
		printf("%d\t",wt[i]);
	}
  printf("%d: ",tat[n]);
  return 0;
} 
