#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define MIN(X,Y) (((X)<(Y)) ? (X) : (Y))
#define VMAX 50

typedef struct res{
    int dif;
    int tam;
    int *sol;
    int max;
}res;

int max;
long int bound;
int df;
res nl;

//entrada, tamanho, soma total, soma calculada
res recMin(int *ve, int tam, int tsum, int csum){++bound;
    if(max!=-1 && csum>max){
        //++bound;
        return nl;
    }
    if (tam==0){
        res s;
        s.tam=0;
        s.sol=malloc(VMAX*sizeof(int));
        if(s.sol==NULL){
            printf("Erro malloc...\n");
            exit(-1);
        }
        s.dif=abs((tsum-csum)-csum);
        if(max==-1){
            max = csum;
            df=s.dif;
        }
        else{
            if(s.dif<df)
                if((tsum-csum)-csum<0)
                    max=csum;
                else
                    max=tsum-csum;
        }
        return s;
    }

    res a,b;
    
    a=recMin(ve, tam-1, tsum, csum+ve[tam-1]);
    b=recMin(ve, tam-1, tsum, csum); 

    if(a.tam==-1)
        return b;
    if(b.tam==-1)
        return a;
    
    if(a.dif < b.dif){
        a.sol[a.tam]=ve[tam-1];
        a.tam++;
        free(b.sol);
        return a;
    }
    else{
        free(a.sol);
        return b;
    }
}

res achaMin(int *ve, int tam){
    int tsum=0;
    for(int i=0;i<tam;++i){
        tsum+=ve[i];
    }
    return (recMin(ve, tam, tsum, 0));
}

int cmpfunc(const void *a, const void *b){
    return(*(int*)a - *(int*)b);   
}

int main(int argc, char **argv){
    int k=0, v[VMAX];
    max=-1;
    bound=0;
    nl.tam=-1;
    df=0;
    do{
        scanf("%d", &v[k]);
        ++k;
    }while(getchar()!=EOF);
    
    int ini, fim;
    
    res s;

    ini = time(NULL);
    s=achaMin(v, k);
    fim = time(NULL);

    //printf("ini=%ld\n", ini);
    
    int f=0;
    
    for (int i=0;i<s.tam;++i){
        f=0;
        for(int j=0;j<k && f!=1; ++j){
            if(v[j]==s.sol[i]){
                f=1;
                v[j]=-1;
            }
        }
    }
    
    printf("1 subconjunto:");
    for(int i=0;i<s.tam;++i){
        printf("%d, ", s.sol[i]);
    }
    printf("\n2 subconjunto:");
    for(int i=0;i<k;++i){
        if(v[i]!=-1)
            printf("%d, ", v[i]);
    }
    
    double corte;
    corte = pow(2,(double)k+1);
    
    printf("\nCortou %d%% dos nos.\nTempo %ds\n", (int)((1-(bound/corte))*100), fim-ini);    
}