#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h>
struct vect
{
    void* data;
    int size;
    int n;
    int bazis;
};
struct cmpx
{
    int re;
    int im;

};
/*--massiv--*/
void initInt(struct vect* arr)
{
    arr->size=sizeof(int);
    arr->data=(int*)malloc(arr->n*arr->bazis*arr->size);
}


void initFloat(struct vect* arr)
{
    arr->size=sizeof(float);
    arr->data=(float*)malloc(arr->n*arr->bazis*arr->size);

}
void initComplex(struct vect* arr)
{
    arr->size=sizeof(struct cmpx);
    arr->data=(struct cmpx*)malloc((arr->n)*arr->bazis*arr->size);
}

   /*--Ввод--*/
 void enter_int(struct vect* arr,int a,int b)
{
    printf("%d-ая координата %d вектора\n",b+1,a+1);
    scanf("%d",(int *)arr->data+a*arr->bazis+b);
}
   void enter_float(struct vect *arr,int a,int b)
{
    printf("%d-ая координата %d вектора\n",b+1,a+1);
    scanf("%f",(float *)arr->data+a*arr->bazis+b);
}

  void enter_complex(struct vect *arr,int a,int b)
{
    printf("Вещественная часть %d-ой координаты %d вектора Re=",b+1,a+1);
    scanf("%d",&(((struct cmpx*)arr->data+a*arr->bazis+b)->re));
    printf("Мнимая часть %d-ой координаты %d вектора Im=",b+1,a+1);
    scanf("%d",&(((struct cmpx*)arr->data+a*arr->bazis+b)->im));
}

 void enter(struct vect* arr,void (*func)(struct vect *arr,int a,int b))
{
     int i,j;
            for(i=0;i<arr->n;i++){
                for(j=0;j<arr->bazis;j++){
                (*func)(arr,i,j);
                }
            }
}
      /*--операции--*/
void int_sum (struct vect* arr,int a,int b)
{
    *((int*)arr->data+((arr->n-1)*arr->bazis+b))+=*((int*)arr->data+(a*(arr->bazis)+b));
}
void float_sum(struct vect* arr,int a,int b)
{
   *((float*)arr->data+((arr->n-1)*arr->bazis+b))+=*((float*)arr->data+(a*arr->bazis+b));
}
 void complex_sum(struct vect* arr,int a,int b)
{

    ((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->re+=((struct cmpx*)arr->data+(a*arr->bazis+b))->re;
    ((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->im+=((struct cmpx*)arr->data+(a*arr->bazis+b))->im;
}


void sum(struct vect* arr,void(*func)(struct vect* arr,int a,int b)) {
         int i,j;
         for(j=0;j<arr->bazis;j++){
            for(i=0;i<arr->n-1;i++){
                (*func)(arr,i,j);
            }
        }
}

void int_mult1(struct vect* arr,int a,int b)
{
   *((int*)arr->data+((arr->n-1)*arr->bazis+b))*= *((int*)arr->data+(a*arr->bazis+b));

}

void float_mult1(struct vect* arr,int a,int b)
{
   *((float*)arr->data+((arr->n-1)*arr->bazis+b))*= *((float*)arr->data+(a*arr->bazis+b));

}

void complex_mult1(struct vect* arr,int a,int b)
{

    ((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->re *= ((struct cmpx*)arr->data+(a*arr->bazis+b))->re;
    ((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->im *= ((struct cmpx*)arr->data+(a*arr->bazis+b))->im;
}

void mult1(struct vect* arr,void (*func)(struct vect *arr,int a,int b))
{
    int i,j;
     for(j=0;j<arr->bazis;j++){
     for(i=0;i<arr->n-1;i++)
            (*func)(arr,i,j);
        }
}
// -----//
void int_mult2(struct vect *arr,int b)
{
     *((int*)arr->data+((arr->n-1)*arr->bazis))+=*((int*)arr->data+((arr->n-1)*arr->bazis+b));
}
void float_mult2(struct vect *arr,int b)
{
     *((float*)arr->data+((arr->n-1)*arr->bazis))+=*((float*)arr->data+((arr->n-1)*arr->bazis+b));
}
void complex_mult2(struct vect *arr,int b)
{
   ((struct cmpx*)arr->data+((arr->n-1)*arr->bazis))->re+=((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->re;
    ((struct cmpx*)arr->data+((arr->n-1)*arr->bazis))->im+=((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->im;
}
void mult2(struct vect *arr,void(*funct)(struct vect *arr,int b))
{
    int j;
     for(j=1;j<arr->bazis;j++)
            (*funct)(arr,j);
}
void pr_multint(struct vect *arr)
{
    printf("Произведение=%d",*((int*)arr->data+((arr->n-1)*arr->bazis)));
}
    /*--вывод--*/
void pr_sumint(struct vect *arr,int b)
{
        printf("%d",*((int*)arr->data+(arr->n-1)*arr->bazis+b));
}

void pr_sumfloat (struct vect *arr,int b)
{
        printf("%f",*((float*)arr->data+(arr->n-1)*arr->bazis+b));
}

void  pr_sumcomplex (struct vect *arr,int b)
{
        printf("%d+%d*I",((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->re,((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+b))->im);
}

  void print (struct vect *arr,void(*func)(struct vect *arr,int b))
  {
           int j;
    for(j=0;j<arr->bazis;j++)
    {
        if(j==0)printf("(");
        if(j>0)printf(",");
        (*func)(arr,j);
        if(j==arr->bazis-1) printf(")");
    }
  }
                /*--тест--*/
void test_sum(struct vect* arr,void (*try)(struct vect *arr,int type), void (*fn)(struct vect* arr,void(*func)(struct vect *arr,int a,int b)),void(*func)(struct vect *arr,int a,int b))
{
    (*try)(arr,0);//Initialize vectors
    (*fn)(arr,(*func));
    (*try)(arr,1);//Compare vectors
}
void test_mult(struct vect* arr,void (*try)(struct vect *arr,int type), void (*fn)(struct vect* arr,void(*func)(struct vect *arr,int a,int b)),void(*func)(struct vect *arr,int a,int b),void (*pr)(struct vect *arr,void(*funct)(struct vect *arr,int b)),void (*funct)(struct vect *arr,int b))
{
    (*try)(arr,0);//Initialize vectors
    (*fn)(arr,(*func));
    (*pr)(arr,(*funct));
    (*try)(arr,1);//Compare vectors
}


void test_int_sum(struct vect* arr,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int in[4] = {2,6,5,8};
        arr->n = 2;
        arr->bazis = 2;
        arr->size = sizeof(int);
        arr->data = (int*)malloc((arr->n)*arr->bazis*arr->size);
        for(i=0;i<(arr->n)*arr->bazis;i++){
           *((int*)arr->data+i)=in[i];
            }
    }else{//Compare vectors
        int out[2] = {7,14},t=1;
        for(i=0;i<arr->bazis;i++){
            if(out[i]!=*((int*)arr->data+((arr->n-1)*arr->bazis+i))){
                printf("ОШИБКА при сложени %d-х координат",i+1);
                t=0;
                break;
            }
        }if(t)printf("ТЕСТ УСПЕШНО ПРОЙДЕН");
    }
}
void test_int_mult(struct vect* arr,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int in[4] = {2,6,5,8};
        arr->n = 2;
        arr->bazis = 2;
        arr->size = sizeof(int);
        arr->data = (int*)malloc(arr->n*arr->bazis*arr->size);
        for(i=0;i<arr->n*arr->bazis;i++){
            *((int*)arr->data+i)=in[i];
        }
    }else{//Compare vectors
        int t=1;
            if(58!=*((int*)arr->data+((arr->n-1)*arr->bazis))){
                printf("ОШИБКА при умножении");
                t=0;
            }
            if(t)printf("ТЕСТ УСПЕШНО ПРОЙДЕН");
        }
}
void test_float_sum(struct vect* arr,int type)
{
    int i;
    if(type==0){//Initialize vectors
        float in[4] = {3.5,7.2,2.1,3.5};
        arr->n = 2;
        arr->bazis = 2;
        arr->size = sizeof(float);
        arr->data = (float*)malloc(arr->n*arr->bazis*arr->size);
        for(i=0;i<arr->n*arr->bazis;i++){
           *((float*)arr->data+i)=in[i];

        }
    }else{//Compare vectors
        float out[2] = {5.6,10.7},t=1;
        for(i=0;i<arr->bazis;i++){
            if(out[i]!=*((float*)arr->data+((arr->n-1)*arr->bazis+i))){
                printf("ОШИБКА при сложени %d-х координат",i+1);
                t=0;
                break;
            }
        }if(t)printf("ТЕСТ УСПЕШНО ПРОЙДЕН");
    }
}
void test_float_mult(struct vect* arr,int type)
{
    int i;
    if(type==0){//Initialize vectors
        float in[4] = {3.5,7.2,2.1,3.5};
        arr->n = 2;
        arr->bazis = 2;
        arr->size = sizeof(float);
        arr->data = (float*)malloc(arr->n*arr->bazis*arr->size);
        for(i=0;i<arr->n*arr->bazis;i++){
           *((float*)arr->data+i)=in[i];
        }
    }else{//Compare vectors
        int t=1;
            if(fabs(32.55-*((float*)arr->data+((arr->n-1)*arr->bazis)))>0.00001){
                printf("ОШИБКА при умножении ");
                t=0;
            }
        if(t)printf("ТЕСТ УСПЕШНО ПРОЙДЕН");
    }
}
void test_complex_sum(struct vect* arr,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int re[4] = {3,2,4,1};
        int im[4] = {1,6,1,7};
        arr->n = 2;
        arr->bazis = 2;
        arr->size = sizeof(struct cmpx);
        arr->data = (struct cmpx*)malloc(arr->n*arr->bazis*arr->size);
        for(i=0;i<arr->n*arr->bazis;i++){
                ((struct cmpx*)arr->data+i)->re = re[i];
                ((struct cmpx*)arr->data+i)->im = im[i];
        }
    }else{//Compare vectors
        int re_out[2] = {7,3},t=1;
        int im_out[2] = {2,13};
        for(i=0;i<arr->bazis;i++){
            if(re_out[i]!=((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+i))->re || im_out[i]!=((struct cmpx*)arr->data+((arr->n-1)*arr->bazis+i))->im){
                printf("ОШИБКА при сложени %d-х координат",i+1);
                t=0;
                break;
            }
        }if(t)printf("ТЕСТ УСПЕШНО ПРОЙДЕН");
    }
}
void test_complex_mult(struct vect* arr,int type)
{
    int i;
    if(type==0){//Initialize vectors
        int re[4] = {3,2,4,1};
        int im[4] = {1,6,1,7};
        arr->n = 2;
        arr->bazis = 2;
        arr->size = sizeof(struct cmpx);
        arr->data = (struct cmpx*)malloc((arr->n+1)*arr->bazis*arr->size);
        for(i=0;i<(arr->n)*arr->bazis;i++){

                ((struct cmpx*)arr->data+i)->re = re[i];
                ((struct cmpx*)arr->data+i)->im = im[i];
        }
    }else{//Compare vectors
       int t=1;
            if(14!=((struct cmpx*)arr->data+((arr->n-1)*arr->bazis))->re || 43!=((struct cmpx*)arr->data+((arr->n-1)*arr->bazis))->im){
                printf("ОШИБКА при умножении ");
                t=0;
        }if(t)printf("ТЕСТ УСПЕШНО ПРОЙДЕН");
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    setlocale(LC_NUMERIC, "C");
    int type,fn,mode;
    struct vect arr;
    printf("Выберите действие:\n1-Тестировать программу\n2-Выполнить операцию\nрежим:");
    scanf("%d",&mode);
    printf("Выберите операцию:\n1-Суммировать вектора\n2-Скалярно умножить вектора\nоперация:");
    scanf("%d",&fn);
    printf("Выберите тип данных:\n1-Целые числа\n2-Вещественные числа\n3-Комплексные числа\nтип данных:");
    scanf("%d",&type);
     printf("Введите количество векторов(для теста оно равно 2-м)\nn=");
    scanf("%d",&arr.n);
    printf("Введите размерность пространства(для теста она равна 2-м)\nбазис=");
    scanf("%d",&arr.bazis);

    if(mode==1){//Test mode
        if(type==1){//Integer
            if(fn==1)test_sum(&arr,test_int_sum,sum,int_sum);
           else test_mult(&arr,test_int_mult,mult1,int_mult1,mult2,int_mult2);
        }else if(type==2){//Float
            if(fn==1)test_sum(&arr,test_float_sum,sum,float_sum);
            else test_mult(&arr,test_float_mult,mult1,float_mult1,mult2,float_mult2);

        }else{//Complex
            if(fn==1)test_sum(&arr,test_complex_sum,sum,complex_sum);
            else test_mult(&arr,test_complex_mult,mult1,complex_mult1,mult2,complex_mult2);
        }
    }
    if (mode==2){//Usual mode
        if(type==1){//Integer
            initInt(&arr);
           enter(&arr,enter_int);
            if(fn==1){
                sum(&arr,int_sum);
                print(&arr,pr_sumint);
             }else if (fn==2){
                  mult1(&arr,int_mult1);
                  mult2(&arr,int_mult2);
                printf("Произведение=%d",*((int*)arr.data+(arr.n-1)*arr.bazis));
                }
        }
    else if(type==2){//Float
            initFloat(&arr);
            enter(&arr,enter_float);
               if(fn==1){
                sum(&arr,float_sum);
                 print(&arr,pr_sumfloat);
                }else if(fn==2){
                     mult1(&arr,float_mult1);
                    mult2(&arr,float_mult2);
                        printf("Произведение=%f",*((float*)arr.data+(arr.n-1)*arr.bazis));
                        }
        }else if (type==3){//Complex
                initComplex(&arr);
                 enter(&arr,enter_complex);
                    if(fn==1){
                        sum(&arr,complex_sum);
                        print(&arr,pr_sumcomplex);
                        }else if(fn==2){
                                mult1(&arr,complex_mult1);
                                mult2(&arr,complex_mult2);
                            printf("Произведение=%d+%d*I",((struct cmpx*)arr.data+((arr.n-1)*arr.bazis))->re,((struct cmpx*)arr.data+((arr.n-1)*arr.bazis))->im);
                        }
            }
    }
  free(arr.data);
}
