#include<iostream>
#include<conio.h>
#include<cstdlib>
#include <algorithm>
#include<math.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#define MaxBase 30
#define MAxAleat 35

using namespace std;


long VectorBase[MaxBase];       /// contiene los numeros que son raicez cuadradas del numero
long VectorX[MAxAleat * 2];     /// contiene el vector de numeros (X+M)
long fx[MAxAleat * 2];          /// contiene el vector de numeros f(x)=(X+M)^2 - n
long Matriz[MAxAleat][MaxBase]; ///contiene la matriz binaria de numeros lisos (suaves)

long tamBase = 0,tamX = 0, tamfact = 0;
long n;
long *Sol;
long **MatrizT;

bool esPrimo(long);
long jacobi(long ,long );
long func_exp(long );
long *HallarBase(long );
void addMatriz(long ,long );
void CalcularX();
long *factorizar(long );
void imprimirVector(long *, long );
void imprimirMatriz(long , long );
long long mcd(long long  , long long  );
bool obtenerSolucion();
void LiberarMemoria();

/** Calcula el Maximo Comun Divisor **/
long long mcd(long long  a, long long b )
{
    if(b == 0) return a;
    else mcd(b, a % b);
}



/** Imprime la Matriz **/
void imprimirMatriz(long x, long y){

    for(long i=0; i < x; i++)
    {
        for(long j=0; j<y; j++)
            cout << Matriz[i][j] << " ";

        cout << endl;
    }
    cout << "\n\n";
}

/** Imprime un vector **/
void imprimirVector(long *V, long tam)
{
    for(long i = 0; i < tam; i++)
    {
        cout << V[i];
        if (i < tam - 1) cout << ", ";
    }
    cout << endl;
}


/** Calcula si es primo o no **/
bool esPrimo(long x)
{
     if (x <= 1) return false;

     for (long i = 2; i * i <= x; ++i)
          if (!(x % i)) return false;

     return true;
}

/** funcion para determinar si a es raiz cuadrada de n **/
long jacobi(long a, long n)
{
   long a1 = 1, b = 2, n1 = 0, s, j, sj, e ,p;

   if(a == 0 || a == 1)
        return a;

   else
   {
       e  = func_exp(a);
       p  = (long)pow(2, e);
       a1 = (long)(a / p);

       if(!(e % 2))
            s = 1;

       else
       {
            if( ( !((n-1) % 8) ) || ( !((n-7) % 8) ) )
                s = 1;

            else
            {
                if( ( !((n-3) % 8) ) || ( !((n-5) % 8) ) )
                    s = -1;
            }
       }

       if( (!((n-3) % 4) && !((a1-3) % 4) )
            s = -s;

       n1 = (n % a1);
       if(a1 == 1)
            return s;

       else
            return s*jacobi(n1,a1);

    }
}

/* Funcion para Encotrar la Base de primos */

long* HallarBase(long n)
{
    long i,j;
    VectorBase[0] = -1;
    VectorBase[1] = 2;
    for(i=3,j=2;i<MaxBase;i++)
    {
        if(esPrimo(i)==true)
        {
            if(jacobi(n,i)==1)//hallamos el jacobi para filtrar los primos que pertenecen a la base
            {
                VectorBase[j++]=i;
            }
        }
    }
    tamBase=j;
}

/* agrega un vector de binarios a matriz*/
void addMatriz(long fact[], long inicio,long h)
{
    for(long i=inicio;i<tamfact;i++)
    {
        Matriz[h][i-1]=fact[i];
    }
}


/*calcula los x+m */
void CalcularX()
{

    long raiz=(long)sqrt(n);
    long i=raiz-MAxAleat;// i es el rango menor de la criba
    long j=raiz+MAxAleat;// j es el rango mayor de la criba
    long h=0,w=0,y;

    while(i!=j)
    {
        long *factores = new long[tamBase+1];
        y=(i*i)-n;// (x+m)^2 - n
        if(y!=0)
        {
            factores = factorizar(y);
            if(factores[0]==1)
            {
                VectorX[h]=i;
                fx[h]=y;
                addMatriz(factores,1,h);
                h++;
            }
        }
        i++;
    }

    tamX = h;
}

/* factoriza a x+m en los primos de la base y devuelve en vector binario*/
long *factorizar(long x)
{
    long *Vf = new long[tamBase+1];
    Vf[0]=0;
    long cont=0,j=2,i=1;

    (x < 0) ? Vf[1] = 1 : Vf[1] = 0;

    for(;i<tamBase;)
    {
        if(x%VectorBase[i]==0)//hallamos los exponentes de cada vector
        {
            cont++;
            x=x/VectorBase[i];
            continue;
        }
        Vf[j++]=cont%2;
        cont=0;
        i++;
    }
    tamfact = j;
    if(x==1 || x==-1)
    {
        Vf[0] = 1;
    }
    return Vf;
}
/*se utiliza en jacobi para obtener el contador del exponente*/
long func_exp(long a)
{
   long e=0;
   while(a%2==0)
   {
        a=a/2;
        e++;
   }
   return e;
}



/*liberamos memoria de la matriz transpuesta*/
void LiberarMemoria(){

   for(long i = 0; i < tamX; i++) delete[] MatrizT[i];
   delete[] MatrizT;
}


/*Obtenemos una solucion */
bool obtenerSolucion(){
    int q=0;
    bool band=false;
    Sol=new long[tamX];
    long *aux2=new long[tamBase];
    int cont;

    MatrizT = new long*[tamBase];
    for(int i = 0; i < tamBase; i++)
      MatrizT[i] = new long[tamX];

    /*obtenemos la transpuesta*/
    for(long i=0; i<tamBase; i++){
        for(long j=0; j<tamX; j++){

            MatrizT[i][j]=Matriz[j][i];
        }

    }

    while(band==false||q!=100000){

            /*generar matriz aleatoria*/

            for(int i=0;i<tamX;i++){

                Sol[i]=rand()%(2);
            }
            //cout<<endl;
            //for(int i=0;i<tamX;i++)cout<<Sol[i];

            int aux=0;
            for(long i=0; i<tamBase; i++){
                for(long j=0; j<tamX; j++){

                    aux+=MatrizT[i][j]*Sol[j];
                }
                aux2[i]=aux%2;

            }
            cont=0;

            /*verificamos que el vector final sea cero*/
            for(int i=0;i<tamBase;i++){
                if(aux2[i]!=0){
                   cont++;
                }
            }

            if(cont==0){
               band =true;
               return true;
             }

            q++;
    }

    if(q<=100000){// si no se encuentra soluciones luego de 10000 numeros aleatorios retorna no hay solucion
        return false;
    }

}

/**    Funcion principal    **/
int main(void)
{
    system("color 0a");

    cout<<"Ingrese  N: "; cin>>n;

    HallarBase(n);

    cout<<"\nLos Factores Base: \n\n";
    imprimirVector(VectorBase,tamBase);
    cout<<"\n";


    CalcularX();///calcula los x+m

    cout<<"Los Valores de X son: \n\n";
    imprimirVector(VectorX,tamX);
    cout<<"\n\n";

    cout<<"Los Valores y = F(x) son: \n\n";
    imprimirVector(fx,tamX);
    cout<<"\n\n";

    cout<<"La matriz de Factores es: \n\n";
    imprimirMatriz(tamX,tamBase);
    cout<<"\n\n";



    long long x=1,y2=1;

    cout<<"\n\nProcesando ";

    if(obtenerSolucion()==true)
    {
        cout<<"\n\nUna solucion posible es :"<<endl;

        for(int i=0;i<tamX;i++)
        {
            cout<<Sol[i]<<"  ";
            if(Sol[i]==1)
            {
                x=x*VectorX[i];
                y2=y2*fx[i];
            }
        }

        x=x%n;
        cout<<"\n X = "<<x<<endl;
        long long y=sqrt(y2);
        y=y%n;
        cout<<"\n Y = "<<y<<endl;

        if( (x - y) > n ) cout<<"\nmcd(x-y,n)="<<mcd(n,x-y)<<endl;
        else cout<<"\nmcd(x-y,n)="<<mcd(n,x-y)<<endl;

        if( (x + y) > n ) cout<<"\nmcd(x+y,n)="<<mcd(x+y,n)<<endl;
        else cout<<"\nmcd(x+y,n)="<<mcd(n,x+y)<<endl;

    }

    else cout<<"\nLa solucion no tuvo exito"<<endl;

    LiberarMemoria();
}

