#ifndef FUNCIONES_H
#define FUNCIONES_H

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
#endif
