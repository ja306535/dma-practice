#include <stdio.h>
#include <stdlib.h>




//Towers of hanoi
void towerOfHanoi(int n, char from, char to, char aux){

//base case
if(n==1){
    printf("moving disk %d from %c to %c",n,from,to)
    return;
}
else{

    towerOfHanoi(n-1,from,aux,to);//move n-1 from the starting place to the aux position
    printf("moving disk %d from %c to %c",n,from,to);
    towerOfHanoi(n-1,aux,to,from);
}

}

void ExchangeCharacters(char str[], int i, int j);{

//create a temp variable
char temp=str[i]
//swap 
str[i]=str[j];
str[j]=temp;

}

void RecursivePermute(char str[], int k){
//if the index is the same as the string length print the string
if(k==strlen(str))
printf("%s",str)
return;

else{ //have a for loop for each character 
for(int j=k;j<strlen(str);j++){
//swap the positions at k with j
ExchangeCharacters(str,k,j);
//call recursion to to that with the rest of the string
RecursivePermute(str,k+1);
//swap back the characters to restore original order
ExchangeCharacters(str,j,k);

}


}

}