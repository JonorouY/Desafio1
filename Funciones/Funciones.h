#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>

using namespace std;

unsigned int** crearMatriz(int k) {
    unsigned int centro, valores;
    valores = 1;
    centro = ((k + 1)/2) - 1;

    unsigned int **matriz = new unsigned int *[k];
    for (int i = 0; i < k; i++) {
        matriz[i] = new unsigned int[k];
    }

    for(int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (i == centro && j == centro) {
                matriz[i][j] = 0;
            }
            else {
                matriz[i][j] = valores;
                valores++;
            }
        }
    }
    return matriz;
}

int rotarMatriz(unsigned int **matriz,int longitud){
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
int ubicacion(int principal, int secundario){
    int diferencia = (secundario - principal)/2;
    return diferencia;
}
int comprobar(int *clave, int *candado,int longitud){
    int columna, fila, columna1, fila1, num, diferencia, variable, rotar;
    columna= clave[1]-1;
    fila = clave[0]-1;
    columna1 = clave[1]-1;
    fila1 = clave[0]-1;
    variable = 2;
    rotar = 0;

    for(int i=0; i<longitud-1; i++){
        int valor = candado[i+1];
        int valor0 = candado[i];

        unsigned int **matriz_a = crearMatriz(valor0);
        for (int i = 0; i < rotar; ++i) {
            rotarMatriz(matriz_a,valor0);
        }
        rotar = 0;
        unsigned int **matriz_b = crearMatriz(valor);

        int num = clave[variable];
        diferencia = ubicacion(candado[0],candado[i+1]);

        columna1 += diferencia;
        fila1 += diferencia;

        if(num == 1){
            for (int m=0; m < 2; m++ ){
                if (matriz_a[fila][columna] <= matriz_b[fila1][columna1]){
                    rotarMatriz(matriz_b,valor);
                    rotar++;
                }
                else{
                    break;
                }
            }
            if (matriz_a[fila][columna] <= matriz_b[fila1][columna1]){
                cout << "La contraseña no concuerda con la cerradura, en 1. ";
                return 0;
            }
        }
        if(num == -1 ){
            for (int m=0; m < 2; m++ ){
                if (matriz_a[fila][columna] >= matriz_b[fila1][columna1]){
                    rotarMatriz(matriz_b, valor);
                    rotar++;
                }
                else{
                    break;
                }
            }
            if (matriz_a[fila][columna] >= matriz_b[fila1][columna1]){
                cout << "La contrasena no concuerda con la cerradura, en -1. ";
                return 0;
            }
        }
        if(num == 0 ){
            for (int m=0; m < 2; m++ ){
                if (!(matriz_a[fila][columna] == matriz_b[fila1][columna1])){
                    rotarMatriz(matriz_b, valor);
                    rotar++;
                }
                else{
                    break;
                }
            }
            if (!(matriz_a[fila][columna] == matriz_b[fila1][columna1])){
                cout << "La contrasena no concuerda con la cerradura, en 0 ";
                return 0;
            }
        }

        delete[] matriz_a;
        delete[] matriz_b;

        columna = columna1;
        fila = fila1;
        columna1 = clave[1]-1;
        fila1 = clave[0]-1;
        variable++;
    }
    cout << "La contrasena concuerda con la cerradura. ";
    return 0;
}

#endif
