//params02_exer2.c 
//Exercise: Fill the blanks to make the swap function work
#include<stdio.h>

void input(int *a, int *b){ //ask user input for a and b, respectively
	printf("Enter two integers (e.g. 21 123): ");
	scanf("%i %i",a,b);  
}

void output(int a, int b){	//prints the values of a and b
	printf("a==%i b==%i\n",a,b); 
}

void swap(int *a,int *b){ //swaps values of "a and b in main"
	int temp = *a;
	*a = *b;
	*b = temp;

	//fill the missing codes to swap the values of "a and b in main"
}


int main(){
	int a=1, b=2;
	
	input(&a, &b); 	
	output(a,b);
	swap(&a,&b); //should swap the values of and b using pass-by-reference
	output(a,b);
}