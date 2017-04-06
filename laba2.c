#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

const int mode;

struct vectors
{
    void* V;
    int size;//size of coord
    int n;
    int bazis;
};
struct cmplx
{
    int re;
    int im;

};
/*--Usual mode--*/
void initInt(struct vectors* v)
{
    v->size=sizeof(int);
    v->V=(int*)malloc((v->n+1)*v->bazis*v->size);
    int i;
    printf("Enter coordinates:");
    for(i=0;i<v->n*v->bazis;i++)scanf("%d",((int *)v->V+i*v->size));
}
void initFloat(struct vectors* v)
{
    v->size=sizeof(float);
    v->V=(float*)malloc((v->n+2)*v->bazis*v->size);
    int i;
    printf("Enter coordinates:");
    for(i=0;i<v->n*v->bazis;i++)scanf("%f",((float* )v->V+i*v->size));
}
void initComplex(struct vectors* v)
{
    int i;
    v->size=sizeof(struct cmplx*);
    v->V=(struct cmplx*)malloc((v->n+1)*v->bazis*v->size);
    for(i=0;i<(v->n+1)*v->bazis;i++){
        if(i<(v->n)*v->bazis){
            printf("Re=");
            scanf("%d",&(((struct cmplx*)v->V+i*v->size)->re));
            printf("Im=");
            scanf("%d",&(((struct cmplx*)v->V+i*v->size)->im));
        }else{
            ((struct cmplx*)v->V+i*v->size)->re = 0;
            ((struct cmplx*)v->V+i*v->size)->im = 0;
        }
    }
}
void initVectors(struct vectors* v,void (*f)(struct vectors* v),void (*p)(struct vectors* v))
{
    printf("Number of vectors=");
    scanf("%d",&v->n);
    printf("Bazis of vectors=");
    scanf("%d",&v->bazis);
    (*f)(v);
    (*p)(v);
}
/*--Test mode--*/
void testVectors(struct vectors* v,void (*test)(struct vectors* v,int type),void (*fn)(struct vectors* v))
{
    (*test)(v,0);//Initialize vectors
    (*fn)(v);
    (*test)(v,1);//Compare vectors
}
void test_add_int(struct vectors* v,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int in[12] = {1,7,6,3,2,1,6,-2,17,21,42,29};
        v->n = 2;
        v->bazis = 6;
        v->size = sizeof(int);
        v->V = (int*)malloc((v->n+1)*v->bazis*v->size);
        for(i=0;i<(v->n+1)*v->bazis;i++){
            if(i<v->n*v->bazis)*((int*)v->V+i*v->size)=in[i];
            else *((int*)v->V+i*v->size)= 0;
        }
    }else{//Compare vectors
        int out[6] = {7,5,23,24,44,30},t=1;
        for(i=0;i<v->bazis;i++){
            if(out[i]!=*((int*)v->V+(v->n*v->bazis+i)*v->size)){
                printf("Error occured on %d coord",i);
                t=0;
                break;
            }
        }if(t)printf("OK");
    }
}
void test_mult_int(struct vectors* v,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int in[12] = {1,7,6,3,2,1,6,-2,17,21,42,29};
        v->n = 2;
        v->bazis = 6;
        v->size = sizeof(int);
        v->V = (int*)malloc((v->n+1)*v->bazis*v->size);
        for(i=0;i<(v->n+1)*v->bazis;i++){
            if(i<v->n*v->bazis)*((int*)v->V+i*v->size)=in[i];
            else *((int*)v->V+i*v->size)= 1;
        }
    }else{//Compare vectors
        int out[6]={6,-14,102,63,84,29},t=1;
        for(i=0;i<v->bazis;i++){
            if(out[i]!=*((int*)v->V+(v->n*v->bazis+i)*v->size)){
                printf("Error occured on %d coord",i);
                t=0;
                break;
            }
        }if(t)printf("OK");
    }
}
void test_add_float(struct vectors* v,int type)
{
    int i;
    if(type==0){//Initialize vectors
        float in[12] = {5.25,4.2,3.2,4.0,10.5,-5.4,4.0,5.5,3.125,-13.5,2.0,3.0};
        v->n = 2;
        v->bazis = 6;
        v->size = sizeof(float);
        v->V = (float*)malloc((v->n+1)*v->bazis*v->size);
        for(i=0;i<(v->n+1)*v->bazis;i++){
            if(i<(v->n)*v->bazis)*((float*)v->V+i*v->size)=in[i];
            else *((float*)v->V+i*v->size) = 0;
        }
    }else{//Compare vectors
        float out[12]={9.25,9.7,6.325,-9.5,12.5,-2.4},t=1;//out[1-6]-(addition),out[7-12]-(mult)
        for(i=0;i<v->bazis;i++){
            if(out[i]!=*((float*)v->V+(v->n*v->bazis+i)*v->size)){
                printf("Error occured on %d coord",i);
                t=0;
                break;
            }
        }if(t)printf("OK");
    }
}
void test_mult_float(struct vectors* v,int type)
{
    int i;
    if(type==0){//Initialize vectors
        float in[12] = {5.25,4.2,3.2,4.0,10.5,-5.4,4.0,5.5,3.125,-13.5,2.0,3.0};
        v->n = 2;
        v->bazis = 6;
        v->size = sizeof(float);
        v->V = (float*)malloc((v->n+1)*v->bazis*v->size);
        for(i=0;i<(v->n+1)*v->bazis;i++){
            if(i<v->n*v->bazis)*((float*)v->V+i*v->size)=in[i];
            else *((float*)v->V+i*v->size)= 1;
        }
    }else{//Compare vectors
        float out[6]={21.0,23.1,10.0,-54.0,21.0,-16.2},t=1;
        for(i=0;i<v->bazis;i++){
            if(fabs(out[i]-*((float*)v->V+(v->n*v->bazis+i)*v->size))>0.00001){
                printf("Error occured on %d coord",i);
                t=0;
                break;
            }
        }if(t)printf("OK");
    }
}
void test_add_complex(struct vectors* v,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int re[6] = {3,6,11,7,9,-2};
        int im[6] = {2,5,2,-13,-4,-3};
        v->n = 2;
        v->bazis = 3;
        v->size = sizeof(struct cmplx);
        v->V = (struct cmplx*)malloc((v->n+1)*v->bazis*v->size);
        for(i=0;i<(v->n+1)*v->bazis;i++){
            if(i<(v->n)*v->bazis){
                ((struct cmplx*)v->V+i*v->size)->re = re[i];
                ((struct cmplx*)v->V+i*v->size)->im = im[i];
            }else{
                ((struct cmplx*)v->V+i*v->size)->re = 0;
                ((struct cmplx*)v->V+i*v->size)->im = 0;
            }
        }
    }else{//Compare vectors
        int re_out[6] = {10,15,9,57,74,-16},t=1;//out[1-6]-(addition),out[7-12]-(mult)
        int im_out[6] = {-11,1,-1,-25,21,-37};
        for(i=0;i<v->bazis;i++){
            if(re_out[i]!=((struct cmplx*)v->V+(v->n*v->bazis+i)*v->size)->re || im_out[i]!=((struct cmplx*)v->V+(v->n*v->bazis+i)*v->size)->im){
                printf("Error occured on %d coord",i);
                t=0;
                break;
            }
        }if(t)printf("OK");
    }
}
void test_mult_complex(struct vectors* v,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int re[4] = {2,-2,1,7};
        int im[4] = {3,6,2,-3};
        v->n = 2;
        v->bazis = 2;
        v->size = sizeof(struct cmplx);
        v->V = (struct cmplx*)malloc((v->n+1)*v->bazis*v->size);
        for(i=0;i<(v->n+1)*v->bazis;i++){
            if(i<(v->n)*v->bazis){
                ((struct cmplx*)v->V+i*v->size)->re = re[i];
                ((struct cmplx*)v->V+i*v->size)->im = im[i];
            }else{
                ((struct cmplx*)v->V+i*v->size)->re = 1;
                ((struct cmplx*)v->V+i*v->size)->im = 1;
            }
        }
    }else{//Compare vectors
        int re_out[2] = {2,-14},t=1;//out[1-6]-(addition),out[7-12]-(mult)
        int im_out[2] = {6,-18};
        for(i=0;i<v->bazis;i++){
            if(re_out[i]!=((struct cmplx*)v->V+(v->n*v->bazis+i)*v->size)->re || im_out[i]!=((struct cmplx*)v->V+(v->n*v->bazis+i)*v->size)->im){
                printf("Error occured on %d coord",i);
                t=0;
                break;
            }
        }if(t)printf("OK");
    }
}
/*--Functions--*/
//int
void add_int(struct vectors* v)
{
    int i,j;
    for(i=0;i<v->n;i++){
        for(j=0;j<v->bazis;j++)*((int*)v->V+(v->n*v->bazis+j)*v->size)+=*((int*)v->V+(i*v->bazis+j)*v->size);
    }if(mode!=1){
        printf("Output:\n");
        for(j=0;j<v->bazis;j++)printf("%d ",*((int*)v->V+(v->n*v->bazis+j)*v->size));
    }
}
void mult_int(struct vectors* v)
{
    int i,j;
    for(j=0;j<v->bazis;j++)*((int*)v->V+(v->n*v->bazis+j)*v->size) = 1;
    for(i=0;i<v->n;i++){
        for(j=0;j<v->bazis;j++){
            *((int*)v->V+(v->n*v->bazis+j)*v->size)*= *((int*)v->V+(i*v->bazis+j)*v->size);
        }
    }if(mode!=1){
    printf("Output:\n");
    for(j=0;j<v->bazis;j++)printf("%d ",*((int*)v->V+(v->n*v->bazis+j)*v->size));
  }
}
//float
void add_float(struct vectors* v)
{
    int i,j;
    for(i=0;i<v->n;i++){
        for(j=0;j<v->bazis;j++){
            *((float*)v->V+(v->n*v->bazis+j)*v->size)+=*((float*)v->V+(i*v->bazis+j)*v->size);
        }
    }if(mode!=1){
        printf("Output:\n");
        for(j=0;j<v->bazis;j++)printf("%f ",*((float*)v->V+(v->n*v->bazis+j)*v->size));
    }
}
void mult_float(struct vectors* v)
{
    int i,j;
    for(j=0;j<v->bazis;j++)*((float*)v->V+(v->n*v->bazis+j)*v->size) = 1;
    for(i=0;i<v->n;i++){
        for(j=0;j<v->bazis;j++){
            *((float*)v->V+(v->n*v->bazis+j)*v->size)*= *((float*)v->V+(i*v->bazis+j)*v->size);
        }
    }if(mode!=1){
    printf("Output:\n");
    for(j=0;j<v->bazis;j++)printf("%f ",*((float*)v->V+(v->n*v->bazis+j)*v->size));
  }
}
//complex
void add_complex(struct vectors* v)
{
    int i,j;
    for(i=0;i<v->n;i++){
        for(j=0;j<v->bazis;j++){
            ((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->re+=((struct cmplx*)v->V+(i*v->bazis+j)*v->size)->re;
            ((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->im+=((struct cmplx*)v->V+(i*v->bazis+j)*v->size)->im;
        }
    }if(mode!=1){
        printf("Output:\n");
        for(j=0;j<v->bazis;j++){
            printf("Re=%d Im=%d\n",((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->re,((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->im);
        }
    }
}
void mult_complex(struct vectors* v)
{
    int i,j;
    for(j=0;j<v->bazis;j++){
        ((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->re = 1;
        ((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->im = 1;
    }
    for(i=0;i<v->n;i++){
        for(j=0;j<v->bazis;j++){
            ((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->re *= ((struct cmplx*)v->V+(i*v->bazis+j)*v->size)->re;
            ((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->im *= ((struct cmplx*)v->V+(i*v->bazis+j)*v->size)->im;    }
    }if(mode!=1){
        printf("Output:\n");
        for(j=0;j<v->bazis;j++){
            printf("Re=%d Im=%d\n",((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->re,((struct cmplx*)v->V+(v->n*v->bazis+j)*v->size)->im);
        }
    }
}
int main()
{
    int type,fn;
    void* fn_p;
    struct vectors v;
    printf("Choose the mode /1-Test/2-Usual mode/: ");
    scanf("%d",&mode);
    printf("Choose the function/1-Addition/2-Scalar mult/: ");
    scanf("%d",&fn);
    printf("Choose the datatype/1-Integer/2-Float/3-Complex/: ");
    scanf("%d",&type);
    if(mode==1){//Test mode
        if(type==1){//Integer
            if(fn==1)testVectors(&v,test_add_int,add_int);
            else testVectors(&v,test_mult_int,mult_int);
        }else if(type==2){//Float
            if(fn==1)testVectors(&v,test_add_float,add_float);
            else testVectors(&v,test_mult_float,mult_float);

        }else{//Complex
            if(fn==1)testVectors(&v,test_add_complex,add_complex);
            else testVectors(&v,test_mult_complex,mult_complex);
        }
    }else{//Usual mode
        if(type==1){//Integer
            if(fn==1)fn_p=add_int;
            else fn_p=mult_int;
            initVectors(&v,initInt,fn_p);
        }else if(type==2){//Float
            if(fn==1)fn_p=add_float;
            else fn_p=mult_float;
            initVectors(&v,initFloat,fn_p);
        }else{//Complex
            if(fn==1)fn_p=add_complex;
            else fn_p=mult_complex;
            initVectors(&v,initComplex,fn_p);
        }
    }
}









