#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define MAX 50
char str_postpre[MAX],str_prepost[MAX],stack[MAX];
int top=-1;
void push(char c)
{
   stack[++top]=c;
}
char pop()
{
   return stack[top--];
}
void post_pre()
{
   int n,i,j=0; char c[MAX];
   char a,b,op;
   
   n=strlen(str_postpre);

   for(i=0;i<MAX;i++)
   stack[i]='\0';

   for(i=n-1;i>=0;i--)//scan form back to front: str
   {
      if(str_postpre[i]=='+'||str_postpre[i]=='-'||
         str_postpre[i]=='*'||str_postpre[i]=='/'||str_postpre[i]=='^')
      {
         push(str_postpre[i]);//store operator
      }
      else
      { 
        c[j++]=str_postpre[i];//store numbers

        while((top!=-1)&&(stack[top]=='@'))
        {
            a=pop(); //get rid of '@'
            c[j++]=pop();
        }
        push('@');
      }
   }
   c[j]='\0';//last entry of c

   for(int k=strlen(c)-1;k>=0;k--)
      printf("%c",c[k]);
}

int main()
{
   gets(str_postpre);
   gets(str_prepost);
   post_pre();
  return 0;
}