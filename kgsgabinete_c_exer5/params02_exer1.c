//params02_exer1.c Passing two integers as parameters
//Exercise: fill in the blanks to make this work like params02.c

#include<stdio.h>

void input(int *a , int *b){ 
	
	printf("Enter two integers (e.g. 21 123): ");
	scanf("%i %i",a,b);
}


void output(int a, int b){	
	printf("a==%i b==%i\n",a,b); 
}

int main(){
	int a=21, b=123;
	
	input(&a,&b); //should ask for user input for a and b, respectively

	
	output(a,b); //should print the values of a and b, respectively

}
					