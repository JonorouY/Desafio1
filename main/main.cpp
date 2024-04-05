#include <string>
#include <iostream>
#include <cmath>
#include "../Funciones/Funciones.h"

using namespace std;

int main()
{

    //x y son las posiciones donde se desea que el candado esté "calibrado"
    int x1,y1,x2,y2;

    int contador = 7;
    int diferencia = 0;
    int clave [7] = {5,7,1,-1,1,-1,-1};
    int fila = clave[0];
    int columna = clave[1];
    int cantidadDeMatrices = 6;
    int candado [contador - 1];
    //llenemos el candado de matrices 3*3
    for(int i = 0 ; i < (contador-1) ; i++)
    {
        candado[i] = 1;
    }
    x1 = clave[0] -1; //Le restamos la parte fisica, o sea que en el mundo fisico la matriz tiene 5, pero en la programacion tiene 4
    y1 = clave[1] -1; // * lo mismo de arriba *
    x2 = -1;
    y2 = -1;

    int crearA;
    int crearB = 1;

    if(fila > columna)
    {
        if((fila % 2) == 0)
        {
            crearA = fila + 1;
        }
        else
        {
            crearA = fila;
        }
    }
    else if(fila == columna)
    {
        //Si fila es 2 y columna es 2, debemos de crear una 5*5, ya que en una 3*3 la fila 2 y columna 2 es el centro
        if((fila == 2) && (columna == 2))
        {
            crearA = 5;
        }

        else
        {
            crearA = fila;
        }
    }
    else
    {
        if((columna % 2) == 0)
        {
            crearA = columna + 1;
        }
        else
        {
            crearA = columna;
        }
    }
    candado[0] = crearA;
    unsigned int **matrizA = nullptr;
    unsigned int **matrizB = nullptr;
    int crearAA = crearA;



    //Límite de hasta que matriz va a buscar, si llega a este limite entonces se dira que no se encontro una solucion
    int limite = 20; //DEBE SER PAR
/*
    //Ciclo principal
    for(int p = 0 ; p < cantidadDeMatrices ; p++)
    {

        cout << endl<<"PPPPPPPPPPPP= "<< p << endl;
        //Si A > B (1)
        if(clave[p + 2] == 1)
        {
            //Si la matrizA llega al limite
            while(crearA < limite)
            {
                //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                while(!(!((x2 < 0) || (x2 > crearB)) && (!((y2 < 0) || (y2 > crearB)))))
                {
                    //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                    crearB+=2;

                    //Posicion de crearB respecto a crearA
                    diferencia = ((crearB - crearA)/2);
                    x2 = x1 + diferencia;
                    y2 = y1 + diferencia;
                }
                crearB-=2;

                //Si la matrizB llega al limite(99)
                while(crearB < limite)
                {
                    crearB+=2;
                    diferencia = (crearB-crearA)/2;
                    x2=x1 + diferencia;
                    y2=y1 + diferencia;

                    //Que no sean iguales
                    if(crearB == crearA)
                    {
                        crearB+=2;
                    }

                    //Nos aseguramos de que no se pueda crear una matriz 3*3 con cordenadas 2 2, ya que quedaríamos en el centro
                    if((crearB == 3) && (x2 == 1) && (y2 == 1))
                    {
                        crearB+=2;
                    }

                    //Si crearB es == limite -1 debemos de salir del while, ya que llegamos al limite
                    if(crearB >= (limite-1))
                    {
                        break;
                    }
                    //Creamos a matrizB
                    matrizB = crearMatriz(crearB);
                    cout << endl <<"a "<<crearA << " b "<<crearB << " x1 "<<x1<<" y1 " <<y1 <<" x2 "<<x2<<" y2 "<<y2;

                    cout << endl << "11111111111111" <<endl;
                    for(int i = 0 ; i < crearA ; i++)
                    {
                        for(int x = 0; x < crearA ; x++)
                        {
                            cout << matrizA[i][x] << " ";
                        }
                        cout << endl;
                    }
                    for(int i = 0 ; i < crearB ; i++)
                    {
                        for(int x = 0; x < crearB ; x++)
                        {
                            cout << matrizB[i][x] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl << "x2: " << x2 << " y2: " << y2 << endl<< "x1: " << x1 << " y2: " << y2;
                    cout << endl <<"A: " << matrizA[x1][y1];
                    cout <<endl <<"B: "<< matrizB[x2][y2];
                    //rotamos a matrizB y comparamos si A>B
                    for(int i = 0 ; i < 3 ; i++)
                    {
                        if(matrizA[x1][y1] > matrizB[x2][y2])
                        {
                            break;
                        }
                        rotarMatriz(matrizB,crearB);
                    }

                    //Verificamos si matrizA > matrizB en sus respectivas posiciones
                    if(matrizA[x1][y1] > matrizB[x2][y2])
                    {
                        break;
                    }

                    //liberamos el espacio de la matrizB
                    for(int f = 0 ; f < crearB ; f++)
                    {
                        delete[] matrizB[f];
                    }
                    delete[] matrizB;

                }
                //Verificamos si matrizA > matrizB en sus respectivas posiciones
                if(matrizA[x1][y1] > matrizB[x2][y2])
                {
                    //liberamos el espacio de la matrizA
                    for(int f = 0 ; f < crearA ; f++)
                    {
                        delete[] matrizA[f];
                    }
                    delete[] matrizA;
                    //liberamos el espacio de la matrizB
                    for(int f = 0 ; f < crearB ; f++)
                    {
                        delete[] matrizB[f];
                    }
                    delete[] matrizB;
                    cout << " sali ";
                    break;
                }
                if(crearB >= (limite -1))
                {
                    //Si en verdad crearB == limite -1 significa que con matrizA no se encontró que A>B, por lo cual cambiemos el tamaño a la matrizA

                    //liberamos el espacio de la matrizA
                    for(int f = 0 ; f < crearA ; f++)
                    {
                        delete[] matrizA[f];
                    }
                    delete[] matrizA;

                    cout << " sumo 2 a " << crearA+2;
                    //Aumento +2 a matrizA
                    crearA+=2;
                    x1+=1;
                    y1+=1;

                    //Creamos la matrizA con un tamaño +2 respecto a la anterior
                    matrizA = crearMatriz(crearA);

                    crearB = 1;
                    x2=-1;
                    y2=-1;
                }
            }
            if(crearA >= limite)
            {
                cout << "No se pudo encontrar un candado para esta clave.";
                break;
            }
        }
        //Si A < B (-1)
        if(clave[p + 2] == -1)
        {

            //Si la matrizA llega al limite
            while(crearA < limite)
            {
                //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                while(!(!((x2 < 0) || (x2 > crearB)) && (!((y2 < 0) || (y2 > crearB)))))
                {
                    //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                    crearB+=2;

                    //Posicion de crearB respecto a crearA
                    diferencia = ((crearB - crearA)/2);
                    x2 = x1 + diferencia;
                    y2 = y1 + diferencia;
                }
                crearB-=2;

                //Si la matrizB llega al limite(99)
                while(crearB < limite)
                {

                    crearB+=2;
                    diferencia = (crearB-crearA)/2;
                    x2=x1 + diferencia;
                    y2=y1 + diferencia;

                    //Que no sean iguales
                    if(crearB == crearA)
                    {
                        crearB+=2;
                    }

                    //Nos aseguramos de que no se pueda crear una matriz 3*3 con cordenadas 2 2, ya que quedaríamos en el centro
                    if((crearB == 3) && (x2 == 1) && (y2 == 1))
                    {
                        crearB+=2;
                    }

                    //Si crearB es == limite -1 debemos de salir del while, ya que llegamos al limite
                    if(crearB >= (limite-1))
                    {
                        break;
                    }

                    //Creamos a matrizB
                    matrizB = crearMatriz(crearB);
                    cout<< endl << "-11111111111111" << endl;
                    for(int i = 0 ; i < crearA ; i++)
                    {
                        for(int x = 0; x < crearA ; x++)
                        {
                            cout << matrizA[i][x] << " ";
                        }
                        cout << endl;
                    }
                    for(int i = 0 ; i < crearB ; i++)
                    {
                        for(int x = 0; x < crearB ; x++)
                        {
                            cout << matrizB[i][x] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl << "x2: " << x2 << " y2: " << y2 << endl<< "x1: " << x1 << " y2: " << y2;
                    cout << endl << "posicionA "<<matrizA[x1][y1];
                    cout <<endl << "posicionB"<<matrizB[x2][y2];
                    //rotamos a matrizB y comparamos si A<B
                    for(int i = 0 ; i < 3 ; i++)
                    {
                        if(matrizA[x1][y1] < matrizB[x2][y2])
                        {
                            break;
                        }
                        rotarMatriz(matrizB,crearB);
                    }

                    //Verificamos si matrizA < matrizB en sus respectivas posiciones
                    if(matrizA[x1][y1] < matrizB[x2][y2])
                    {
                        break;
                    }

                    //liberamos el espacio de la matrizB
                    for(int f = 0 ; f < crearB ; f++)
                    {
                        delete[] matrizB[f];
                    }
                    delete[] matrizB;

                }
                //Verificamos si matrizA > matrizB en sus respectivas posiciones
                if(matrizA[x1][y1] < matrizB[x2][y2])
                {
                    //liberamos el espacio de la matrizA
                    for(int f = 0 ; f < crearA ; f++)
                    {
                        delete[] matrizA[f];
                    }
                    delete[] matrizA;

                    //liberamos el espacio de la matrizB
                    for(int f = 0 ; f < crearB ; f++)
                    {
                        delete[] matrizB[f];
                    }
                    delete[] matrizB;
                    break;
                }
                if(crearB >= (limite -1))
                {
                    //Si en verdad crearB == limite -1 significa que con matrizA no se encontró que A<B, por lo cual cambiemos el tamaño a la matrizA

                    //liberamos el espacio de la matrizA
                    for(int f = 0 ; f < crearA ; f++)
                    {
                        delete[] matrizA[f];
                    }
                    delete[] matrizA;

                    crearA+=2;
                    x1+=1;
                    y1+=1;

                    //Creamos la matrizA con un tamaño +2 respecto a la anterior
                    matrizA = crearMatriz(crearA);

                    crearB = 1;
                    x2=-1;
                    y2=-1;
                }
            }
            if(crearA >= limite)
            {
                cout << "No se pudo encontrar un candado para esta clave.";
                break;
            }
        }
        //Si A = B (0)
        if(clave[p + 2] == 0)
        {
            crearB = crearA;
        }

        //Guardamos el crearB, que es el tamaño de la matriz que cumple los requerimientos
        candado[p+1] = crearB;

        if(p == 0)
        {
            candado[0] = crearA;
        }

        //CAMBIEMOS EL crearA POR crearB
        crearA = crearB;
        crearB = 1;

        //Creamos matrizA
        matrizA = crearMatriz(crearA);

        cout << "CrearA ahora es: " << crearA << endl;
        //CAMBIEMOS LOS x1 y1 POR x2 y2
        x1 = x2;
        y1 = y2;
        cout <<  endl <<"------------------------"<< endl;
    }
*/
    int p = 0;
    char sali = 'n';
    int nada;
    int error=0;
    bool q = true;

    while(q)
    {
        crearA=candado[0];
        crearB=candado[1];
        matrizA = crearMatriz(crearA);

        //Posicion de crearA respecto a crearAA
        diferencia = ((crearA - crearAA)/2);
        x1 = (clave[0] + diferencia) - 1;
        y1 = (clave[1] + diferencia) - 1;



        cout << endl << "CREAR A = "<<crearA;
        cout << endl << "CREAR B= " << crearB;

        cout << "El candado para la clave ingresadad seria:" << endl;
        for(int i = 0 ; i < (contador-1) ; i++)
        {
            cout << candado[i] << " ";
        }

        cin >> nada;

        for(int p = 0 ; p < (contador-1) ; p++)
        {

            cout << endl<<"PPPPPPPPPPPP= "<< p << endl;
            //Si A > B (1)
            if(clave[p + 2] == 1)
            {
                //Si la matrizA llega al limite
                while(crearA < limite)
                {
                    //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                    while(!(!((x2 < 0) || (x2 > crearB)) && (!((y2 < 0) || (y2 > crearB)))))
                    {
                        //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                        crearB+=2;

                        //Posicion de crearB respecto a crearA
                        diferencia = ((crearB - crearA)/2);
                        x2 = x1 + diferencia;
                        y2 = y1 + diferencia;
                    }
                    crearB-=2;

                    //Si la matrizB llega al limite(99)
                    while(crearB < limite)
                    {
                        crearB+=2;
                        diferencia = (crearB-crearA)/2;
                        x2=x1 + diferencia;
                        y2=y1 + diferencia;

                        /*
                        //Que no sean iguales
                        if(crearB == crearA)
                        {
                            crearB+=2;
                            x2+=1;
                            y2+=1;
                        }
*/

                        //Nos aseguramos de que no se pueda crear una matriz 3*3 con cordenadas 2 2, ya que quedaríamos en el centro
                        if((crearB == 3) && (x2 == 1) && (y2 == 1))
                        {
                            crearB+=2;
                        }

                        //Si crearB es == limite -1 debemos de salir del while, ya que llegamos al limite
                        if(crearB >= (limite-1))
                        {
                            break;
                        }
                        //Creamos a matrizB

                        matrizB = crearMatriz(crearB);
                        cout << endl <<"a "<<crearA << " b "<<crearB << " x1 "<<x1<<" y1 " <<y1 <<" x2 "<<x2<<" y2 "<<y2;

                        cout << endl << "11111111111111" <<endl;
                        for(int i = 0 ; i < crearA ; i++)
                        {
                            for(int x = 0; x < crearA ; x++)
                            {
                                cout << matrizA[i][x] << " ";
                            }
                            cout << endl;
                        }
                        for(int i = 0 ; i < crearB ; i++)
                        {
                            for(int x = 0; x < crearB ; x++)
                            {
                                cout << matrizB[i][x] << " ";
                            }
                            cout << endl;
                        }
                        cout << endl << "x2: " << x2 << " y2: " << y2 << endl<< "x1: " << x1 << " y2: " << y2 << endl;
                        cout << endl <<"A: " << matrizA[x1][y1];
                        cout <<endl <<"B: "<< matrizB[x2][y2];
                        //rotamos a matrizB y comparamos si A>B
                        for(int i = 0 ; i < 3 ; i++)
                        {
                            if(matrizA[x1][y1] > matrizB[x2][y2])
                            {
                                break;
                            }
                            rotarMatriz(matrizB,crearB);
                        }

                        //Verificamos si matrizA > matrizB en sus respectivas posiciones
                        if(matrizA[x1][y1] > matrizB[x2][y2])
                        {
                            break;
                        }

                        //liberamos el espacio de la matrizB
                        for(int f = 0 ; f < crearB ; f++)
                        {
                            delete[] matrizB[f];
                        }
                        delete[] matrizB;


                    }
                    //Verificamos si matrizA > matrizB en sus respectivas posiciones
                    if(matrizA[x1][y1] > matrizB[x2][y2])
                    {
                        //liberamos el espacio de la matrizA
                        for(int f = 0 ; f < crearA ; f++)
                        {
                            delete[] matrizA[f];
                        }
                        delete[] matrizA;
                        //liberamos el espacio de la matrizB
                        for(int f = 0 ; f < crearB ; f++)
                        {
                            delete[] matrizB[f];
                        }
                        delete[] matrizB;
                        cout << " sali ";
                        break;
                    }
                    if(crearB >= (limite -1))
                    {
                        //Si en verdad crearB == limite -1 significa que con matrizA no se encontró que A>B, por lo cual cambiemos el tamaño a la matrizA

                        //liberamos el espacio de la matrizA
                        for(int f = 0 ; f < crearA ; f++)
                        {
                            delete[] matrizA[f];
                        }
                        delete[] matrizA;

                        cout << " sumo 2 a " << crearA+2;
                        //Aumento +2 a matrizA
                        crearA+=2;
                        x1+=1;
                        y1+=1;

                        //Creamos la matrizA con un tamaño +2 respecto a la anterior
                        matrizA = crearMatriz(crearA);

                        crearB = 1;
                        x2=-1;
                        y2=-1;

                        candado[p+1] = crearB;

                        sali='s';

                        break;
                    }
                    if(sali=='s')
                    {
                        sali='s';
                        break;
                    }
                }
                if(sali=='s')
                {
                    candado[p] = crearA;

                    error+=2;

                    sali = 'n';

                    break;
                }
                if(crearA >= limite)
                {
                    cout << "No se pudo encontrar un candado para esta clave.";
                    break;
                }
            }
            //Si A < B (-1)
            if(clave[p + 2] == -1)
            {

                //Si la matrizA llega al limite
                while(crearA < limite)
                {
                    //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                    while(!(!((x2 < 0) || (x2 > crearB)) && (!((y2 < 0) || (y2 > crearB)))))
                    {
                        //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                        crearB+=2;

                        //Posicion de crearB respecto a crearA
                        diferencia = ((crearB - crearA)/2);
                        x2 = x1 + diferencia;
                        y2 = y1 + diferencia;
                    }
                    crearB-=2;

                    //Si la matrizB llega al limite(99)
                    while(crearB < limite)
                    {

                        crearB+=2;
                        diferencia = (crearB-crearA)/2;
                        x2=x1 + diferencia;
                        y2=y1 + diferencia;
/*
                        //Que no sean iguales
                        if(crearB == crearA)
                        {
                            crearB+=2;
                            x2+=1;
                            y2+=1;
                        }
*/

                        //Nos aseguramos de que no se pueda crear una matriz 3*3 con cordenadas 2 2, ya que quedaríamos en el centro
                        if((crearB == 3) && (x2 == 1) && (y2 == 1))
                        {
                            crearB+=2;
                        }

                        //Si crearB es == limite -1 debemos de salir del while, ya que llegamos al limite
                        if(crearB >= (limite-1))
                        {
                            break;
                        }

                        //Creamos a matrizB
                        matrizB = crearMatriz(crearB);
                        cout<< endl << "-11111111111111" << endl;
                        cout << endl <<"a "<<crearA << " b "<<crearB << " x1 "<<x1<<" y1 " <<y1 <<" x2 "<<x2<<" y2 "<<y2;
                        for(int i = 0 ; i < crearA ; i++)
                        {
                            for(int x = 0; x < crearA ; x++)
                            {
                                cout << matrizA[i][x] << " ";
                            }
                            cout << endl;
                        }
                        for(int i = 0 ; i < crearB ; i++)
                        {
                            for(int x = 0; x < crearB ; x++)
                            {
                                cout << matrizB[i][x] << " ";
                            }
                            cout << endl;
                        }
                        cout << endl << "x2: " << x2 << " y2: " << y2 << endl<< "x1: " << x1 << " y2: " << y2;
                        cout << endl << "posicionA "<<matrizA[x1][y1];
                        cout <<endl << "posicionB"<<matrizB[x2][y2];
                        //rotamos a matrizB y comparamos si A<B
                        for(int i = 0 ; i < 3 ; i++)
                        {
                            if(matrizA[x1][y1] < matrizB[x2][y2])
                            {
                                break;
                            }
                            rotarMatriz(matrizB,crearB);
                        }

                        //Verificamos si matrizA < matrizB en sus respectivas posiciones
                        if(matrizA[x1][y1] < matrizB[x2][y2])
                        {
                            break;
                        }

                        //liberamos el espacio de la matrizB
                        for(int f = 0 ; f < crearB ; f++)
                        {
                            delete[] matrizB[f];
                        }
                        delete[] matrizB;

                    }
                    //Verificamos si matrizA > matrizB en sus respectivas posiciones
                    if(matrizA[x1][y1] < matrizB[x2][y2])
                    {
                        //liberamos el espacio de la matrizA
                        for(int f = 0 ; f < crearA ; f++)
                        {
                            delete[] matrizA[f];
                        }
                        delete[] matrizA;

                        //liberamos el espacio de la matrizB
                        for(int f = 0 ; f < crearB ; f++)
                        {
                            delete[] matrizB[f];
                        }
                        delete[] matrizB;
                        break;
                    }
                    if(crearB >= (limite -1))
                    {
                        //Si en verdad crearB == limite -1 significa que con matrizA no se encontró que A<B, por lo cual cambiemos el tamaño a la matrizA

                        //liberamos el espacio de la matrizA
                        for(int f = 0 ; f < crearA ; f++)
                        {
                            delete[] matrizA[f];
                        }
                        delete[] matrizA;

                        crearA+=2;
                        x1+=1;
                        y1+=1;

                        //Creamos la matrizA con un tamaño +2 respecto a la anterior
                        matrizA = crearMatriz(crearA);

                        crearB = 1;
                        x2=-1;
                        y2=-1;

                        candado[p+1] = crearB;

                        sali='s';
                        break;
                    }
                    if(sali=='s')
                    {
                        sali='s';
                        break;
                    }
                }
                if(sali=='s')
                {
                    candado[p] = crearA;

                    error+=2;
                    sali = 'n';

                    break;
                }
                if(crearA >= limite)
                {
                    cout << "No se pudo encontrar un candado para esta clave.";
                    break;
                }
            }
            //Si A = B (0)
            if(clave[p + 2] == 0)
            {
                crearB = crearA;
            }




            //Guardamos el crearB, que es el tamaño de la matriz que cumple los requerimientos
            if(sali != 's')
            {
                candado[p+1] = crearB;
            }
            sali = 'no';

            candado[p] = crearA;

            //CAMBIEMOS EL crearA POR crearB
            crearA = crearB;
            crearB = 1;

            //Creamos matrizA
            matrizA = crearMatriz(crearA);

            cout << "CrearA ahora es: " << crearA << endl;
            //CAMBIEMOS LOS x1 y1 POR x2 y2
            x1 = x2;
            y1 = y2;
            cout <<  endl <<"------------------------"<< endl;

            if(p == (contador-2))
            {
                q = false;
            }
        }
    }


    if(crearA < limite)
    {
        cout << "El candado para la clave ingresadad seria:" << endl;
        for(int i = 0 ; i < (contador-1) ; i++)
        {
            cout << candado[i] << " ";
        }
    }

    comprobar(clave, candado, (contador-1));

    return 0;
}
