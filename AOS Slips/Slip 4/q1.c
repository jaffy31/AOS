/*write a c program to find whether a given file is persent in current directory or not*/

#include<stdio.h>
#include<unistd.h>

int main(){
char filename[256];

printf("enter ther file name");
scanf("%s",filename);

if(access(filename, F_OK)==0){
printf("The file %s is present in the current directory",filename);
}else{
printf("The file %s is not present in the current directory",filename);
}
return 0;
}
