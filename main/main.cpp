#include <string>
#include <iostream>
#include <cmath>

using namespace std;

int rotarMatriz(unsigned int **matriz,int longitud)
{
    int **matrizNueva = new int *[longitud];
    for(int i=0;i<longitud;i++)
    {
        matrizNueva[i] = new int [longitud];
    }
    int a=0;
    int p=0;
    //copiemos lo que hay en matriz a matrizNueva
    for(int i=0;i<longitud;i++)
    {
        for(int j=0;j<longitud;j++)
        {
            matrizNueva[i][j]=matriz[i][j];
        }
    }

    //Rotemos matrizNueva y lo guardamos en matriz
    for(int i=0;i<longitud;i++)
    {
        p=0;
        for(int j=(longitud-1);j>=0;j--)
        {
            matriz[j][i]=matrizNueva[a][p];
            p++;
        }
        a++;
    }

    for(int i=0;i<longitud;i++)
    {
        delete[] matrizNueva[i];
    }
    delete[] matrizNueva;
    return 0;
}
int main()
{

    //x y son las posiciones donde se desea que el candado esté "calibrado"
    int x1,y1,x2,y2;


    int dif = 0;

    int clave [5] = {4,3,1,-1,1};
    int fila = clave[0];
    int columna = clave[1];
    int filaB;
    int contador = 4;
    int candado [contador];
    x1 = clave[0];
    y1 = clave[1];


    if(fila >= columna)
    {
        if((fila % 2) == 1)
        {
            fila++;
        }
    }
    else
    {
        if((columna % 2) == 1)
        {
            columna++;
        }
        fila = columna;
    }
    filaB = fila;
    candado[0] = fila;

    unsigned int **matriz = new unsigned int *[fila];
    for (int i = 0; i < fila; i++)
    {
        matriz[i] = new unsigned int[fila];
    }
    llenarMatriz(fila,matriz);

    return 0;
}
