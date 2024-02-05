//params07_exer1.c
//Exercise: Fill-in the blanks to make this program work like params07.c
#include<stdio.h>

void input(char *name) {
	printf("What is your name? ");
	scanf("%s",name);
	
}

void output(char *name){
	printf("Your name is %s.\n",name);
}
	

int main(){
	char name[20]; //can store up to 19 input chars
	
	//#1 do this in the input function
	//printf("What is your name? ");
	//scanf("%s",name);
	
	input(name); 

	
	
	//#2 do this in the output function
	//printf("Your name is %s.\n",name);
	
	output(name);
	
}

