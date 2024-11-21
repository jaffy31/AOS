/*Write a C Program that demonstrates redirection of standard output to a file.*/


#include <stdio.h>

int main() {

	freopen("output.txt", "w", stdout);

	printf("This is a example of standard output redirection.\n");
	printf("The output is redirected to the 'output.txt' file.\n");

	return 0;

}

