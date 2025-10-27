#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
  char label[20],opcode[20],operand[20],optcode[20],optvalue[20];
  int locctr=0,startaddr=0,proglen=0;
  FILE *input,*optab,*symtab,*intermediate;
  input= fopen("input.txt","r");
  optab = fopen("optab.txt", "r");
  symtab = fopen("symtab.txt", "w");
  intermediate = fopen("intermediate.txt", "w");

  if(!input||!optab||!symtab||!intermediate){
    printf("Files Not found !!!!\n");
    return 1;
  }
 fscanf(input,"%s %s %s",label,opcode,operand);
   if(strcmp(opcode,"START")==0) {
    startaddr = (int)strtol(operand,NULL,16);
    locctr = startaddr;
    fprintf(intermediate,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fscanf(input,"%s %s %s",label,opcode,operand);
  }
  while(strcmp(opcode,"END")!=0){
    fprintf(intermediate,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    if(strcmp(label,"**")!=0){
      fprintf(symtab,"%s\t%04X\n",label,locctr);
    }
    int found = 0;
    rewind(optab);
    while(fscanf(optab,"%s %s",optcode,optvalue)!=EOF){
      if(strcmp(opcode,optcode)==0){
        locctr+=3;
        found=1;
        break;
      }
      }
    if(!found){
      if(strcmp(opcode,"WORD")==0){
        locctr+=3;}
      else if(strcmp(opcode,"RESW")==0){
           locctr+=3*atoi(operand);
      }
      else if(strcmp(opcode,"RESB")==0){
           locctr+=atoi(operand);
      }
      else if(strcmp(opcode,"BYTE")==0){
           if(operand[0]=='C'){locctr+=strlen(operand)-3;}
              else if(operand[0]=='X'){locctr+=(strlen(operand)-3)/2;}
      }
      else {printf("Invalid operand %s\n",opcode);}
    }
    fscanf(input,"%s %s %s",label,opcode,operand);}
    fprintf(intermediate,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
  printf("The pass1 completed succesfully ;)  size:= %x",locctr-startaddr);
  fclose(input);
  fclose(optab);
  fclose(symtab);
  fclose(intermediate);
  return 0;
}
