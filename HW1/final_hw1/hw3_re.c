#include<stdio.h>
#define MAX 100
typedef struct{
    int r;
    int c;
    int d;
}Matrix;

void fast(Matrix* m);

int main(){
    int r,c,d;
    scanf("%d%d%d", &r,&c,&d);
    Matrix m[d+1];
    for(int i=0;i<d;i++){
        if(i=0){
            m[i].r=r;
            m[i].c=c;
            m[i].d=d;
            continue;
        }
        scanf("%d%d%d",&m[i].r,&m[i].c,&m[i].d);
    }
    

    return 0;
}
typedef struct{
    int rowTerm;//to calculate starpt of row
    int starting;
}FTterm;

void fast(Matrix* m){
    int row= m->r,col=m->c,num=m->d;
    Matrix trans[num+1];
    FTterm record[num+1];

    trans[0].r=row;
    trans[0].c=col;
    trans[0].d=num;
    if(num>0){
        for( int i=0;i<col;i++)
            record[i].rowTerm=0;

        for( int i=1;i<num+1;i++)
            record[(m+i)->c].rowTerm++;
        record[0].starting=1;

        for(int i=1;i<num+1;i++){
            record[i].starting=record[i-1].starting+record[i-1].rowTerm;
        }
        int j;
        for(int i=1;i<num+1;i++){
            j=record[(m+i)->c].starting++;
            trans[j].r=(m+i)->c;
            trans[j].c=(m+i)->r;
            trans[j].d=(m+i)->d;
        }   

    }    
    for(int i=0;i<num+1;i++){
        printf("%d %d %d\n",trans[i].r,trans[i].c,trans[i].d);
    }

}
