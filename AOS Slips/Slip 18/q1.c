/*5)write a c program to find whether a given file is persent in current directory or not*/

#include <stdio.h>
#include <unistd.h>

int main (){
char filename[256];

printf("enter the filename:");
scanf("%s",filename);
if (access(filename, F_OK)==0){
printf("The file '%s' is persent\n",filename);
}

else{
printf("The file '%s'is not persent in the current directory\n",filename);
}

return 0;

}

