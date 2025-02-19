#include <stdio.h>
#include <stdlib.h>




void printRecC1(char word[],int n){

if(n==0)
return;

printf("%c",word[n-1]);
 printRecC1(word,n-1); 

}

void printRecC2(char word[],int n){

    if(!(n==0))
    {
    
    printf("%c",word[n-1]);
     printRecC2(word,n-1); 
    
    }
}

//putting the print statement AFTER the recurrsive call allows to hold the value but not print it yet 
void printRevV2(char word[],int k){

    if(word[k]=='\0')
    return;
        
        printRevV2(word,k+1);
        printf("%c",word[k]);
    
}

void rec2(int x)
{
if (x==0)
return;
rec2(x-1);
printf("%d ", x);
}

int multiply(int first,int second){
//base case
if(first==0||second==0)
return 0;
//else return 
return (first+multiply(first,second-1));


}


//Write a recursive function that calculates the sum 1^1 + 2^2 +3^3 +...+n^n, given an integer value of n
//in between 1 and 9. You can write a separate power function in this process and call that power
//function as needed:

int power(int n,int pow){

    if (pow==0)
    return 1;

return (n*power(n,pow-1));
}

int crazySum(int n){
//base case 
if (n==0)
return 0;
return (power(n,n)+crazySum(n-1));


}
void convert(int num) {
    if (num == 0)  // Base case: stop when the quotient is 0
        return;

    convert(num / 8);  // Process higher digits first
    printf("%d", num % 8);    // Print current digit
}
int main(){

    //printRecC1("hello",5);
    //printRevV2("hello",0);
    //rec2(5);
    //printf("%d",crazySum(5));
    //printf("\n");
    convert(83);
    return 0;
}