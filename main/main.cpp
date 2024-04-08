#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "../Funciones/Funciones.h"

using namespace std;

int main()
{
    string entrada;
    bool t = true;
    int cantidad = 1;
    int contador= 0;
    string numeroStr;
    int *clave = nullptr;
    //FALTA VERIFICAR QUE NO ME INGRESEN UN 0 EN FILA O COLUMNA, Y QUE SOLO ME INGRESEN 1 -1 0 DESPUES DE FILA Y COLUMNA

    //Validemos la información
    while(t)
    {
        cout << "Ingrese la clave de esta manera: (fila,columna,comparacion1,comparacion2,...,comparacionN).";
        cout << endl << "Ingrese la clave por favor: ";
        cin >> entrada;

        //Contemos la cantidad de , o ; que hay, para así crear un arreglo con la cantidad necesaria
        for(int x = 0 ; x < (entrada.size()-1) ; x++)
        {
            if((entrada[x] == ',') || (entrada[x] == ';'))
            {
                cantidad++;
            }
        }

        //Liberamos el espacio en memoria anterior
        delete[] clave;

        //Creamos el lugar donde se va a guardar la clave
        clave = new int [cantidad];
        contador = cantidad;


        numeroStr = "";
        cantidad = 0;

        //Miremos si la clave ingresada está escrita con () [] {}
        if((entrada[0] == '(') && (entrada[entrada.size()-1] == ')') || (entrada[0] == '[') && (entrada[entrada.size()-1] == ']') || (entrada[0] == '{') && (entrada[entrada.size()-1] == '}'))
        {
            //Miramos que hayan solo números y , o ;
            for(int i = 1 ; i < (entrada.size() - 1) ; i++)
            {
                if((entrada[i] != '1') && (entrada[i] != '2') && (entrada[i] != '3') && (entrada[i] != '4') && (entrada[i] != '5') && (entrada[i] != '6') && (entrada[i] != '7') && (entrada[i] != '8') && (entrada[i] != '9') && (entrada[i] != '0') && (entrada[i] != '-'))
                {
                    //Cuando encontremos un ; o , guardamos lo que teníamos
                    if((entrada[i] == ';' ) || (entrada[i] == ','))
                    {
                        //Antes de guardar, verifiquemos que sí haya algo que guardar
                        if(numeroStr == "")
                        {
                            cout << "La clave ingresada es invalida. Ya que ha ingresado dos , seguidas." << endl;
                            break;
                        }

                        //Convertimos de string a int y lo guardamos
                        stringstream(numeroStr) >> clave[cantidad];
                        cantidad++;

                        numeroStr = "";
                    }
                    else
                    {
                        cout << "La clave ingresada es invalida. Ya que ha ingresado: " << entrada[i] << endl;
                        break;
                    }
                }

                //Verifiquemos que si hay un -, este acompañado por SOLAMENTE 1 y nada mas
                else if((entrada[i] == '-'))
                {
                    //Si el numero siguiente es 1
                    if(entrada[i+1] == '1')
                    {
                        //Para que sea valido lo ingresado, el numero siguiente al 1 (o lo que llevamos -1) debe ser una , ; o ) } ]
                        if((entrada[i+2] == ';' ) || (entrada[i+2] == ',') || (entrada[i +2] == entrada[entrada.size()-1]))
                        {
                            //Miremos si el -1 esta en la fila o columna
                            if((entrada[1] == '-') || (entrada[4] == '-'))
                            {
                                cout << "La clave ingresada es invalida. Ya que una fila o columna negativa no existe" << endl;
                                break;
                            }

                            //Si llegamos a este punto significa que hay un -1 pero este no esta en las filas o columnas, por lo cual es valido y podemos guardar el -
                            else
                            {
                                numeroStr+=entrada[i];
                            }
                        }

                        //Si llegamos a este punto tenemos un numero negativo, que empieza por -1..., el cual es diferente a -1
                        else
                        {
                            cout << "La clave ingresada es invalida. Ya que ha ingresado un numero negativo diferente a -1";
                            break;
                        }
                    }

                    //Si llegamos a este punto tenemos un numero negativo diferente a -1
                    else
                    {
                        cout << "La clave ingresada es invalida. Ya que ha ingresado un numero negativo diferente a -1";
                        break;
                    }
                }

                //Si lo anterior no se cumple(o sea que es un numero positivo, o si es negativo, es unicamente -1)
                else
                {
                    numeroStr+=entrada[i];
                }

                //Verificar si estamos al final de lo ingresado para así salirnos de la validacion
                if(i == (entrada.size() -2))
                {
                    t = false;

                    //Convertimos de string a int y lo guardamos
                    stringstream(numeroStr) >> clave[cantidad];
                }
            }
        }
        else
        {
            cout << "La clave ingresada es invalida. Por favor utilice los parentesis () al iniciar y finalizar la clave." << endl;
        }
    }

    //x y son las posiciones donde se desea que el candado esté "calibrado"
    int x1,y1,x2,y2;

    int diferencia = 0;
    int fila = clave[0];
    int columna = clave[1];
    int cantidadDeMatrices = contador-1;
    int candado [contador - 1];
    //llenemos el candado de matrices 3*3
    for(short int i = 0 ; i < (contador-1) ; i++)
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

    unsigned short int rotar;
    int p = 0;
    char sali = 'n';
    int nada;
    bool q = true;


    while(q)
    {
        crearA=candado[0];
        crearB=candado[1];
        matrizA = crearMatriz(crearA);

        x1=clave[0]-1;
        y1=clave[1]-1;

        for(int p = 0 ; p < (contador-2) ; p++)
        {

            x2=-1;
            y2=-1;

            //Si A > B (1)
            if(clave[p + 2] == 1)
            {
                //Si la matrizA llega al limite
                while(crearA < limite)
                {
                    diferencia = ((crearB - crearA)/2);
                    x2 = x1 + diferencia;
                    y2 = y1 + diferencia;

                    //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                    while(!(!((x2 < 0) || (x2 >= crearB)) && (!((y2 < 0) || (y2 >= crearB)))))
                    {
                        //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                        crearB+=2;

                        //Posicion de crearB respecto a crearA
                        diferencia = ((crearB - crearA)/2);
                        x2 = x1 + diferencia;
                        y2 = y1 + diferencia;
                    }


                    //Si la matrizB llega al limite(99)
                    while(crearB < limite)
                    {

                        diferencia = (crearB-crearA)/2;
                        x2=x1 + diferencia;
                        y2=y1 + diferencia;

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

                        //rotamos a matrizB y comparamos si A>B
                        rotar = 0;
                        for(int i = 0 ; i < 3 ; i++)
                        {
                            if(matrizA[x1][y1] > matrizB[x2][y2])
                            {
                                break;
                            }
                            rotarMatriz(matrizB,crearB);
                            rotar++;
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

                        crearB+=2;
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
                        matrizA = crearMatriz(crearB);

                        //rotamos a matrizA tanto como rotamos a matrizB
                        for(int i = 0 ; i < rotar ; i++)
                        {
                            rotarMatriz(matrizA,crearB);
                        }
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
                        //Si en verdad crearB == limite -1 significa que con matrizA no se encontró que A>B, por lo cual cambiemos el tamaño a la matrizA

                        //liberamos el espacio de la matrizA
                        for(int f = 0 ; f < crearA ; f++)
                        {
                            delete[] matrizA[f];
                        }
                        delete[] matrizA;

                        //Verificar que si antes habia un 0(igual) debemos aumentar a la matriz anterior
                        if(clave[p] == 0)
                        {
                            candado[p-2]+=2;
                        }

                        //Aumento +2 a matrizA
                        crearA+=2;

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

                    sali = 'n';

                    break;
                }
                if(crearA >= (limite-1))
                {
                    cout << "No se pudo encontrar un candado para esta clave.";
                    q=false;
                    break;
                }
            }
            //Si A < B (-1)
            if(clave[p + 2] == -1)
            {

                //Si la matrizA llega al limite
                while(crearA < limite)
                {
                    diferencia = ((crearB - crearA)/2);
                    x2 = x1 + diferencia;
                    y2 = y1 + diferencia;

                    //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                    while(!(!((x2 < 0) || (x2 >= crearB)) && (!((y2 < 0) || (y2 >= crearB)))))
                    {
                        //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                        crearB+=2;

                        //Posicion de crearB respecto a crearA
                        diferencia = ((crearB - crearA)/2);
                        x2 = x1 + diferencia;
                        y2 = y1 + diferencia;
                    }


                    //Si la matrizB llega al limite(99)
                    while(crearB < limite)
                    {

                        diferencia = (crearB-crearA)/2;
                        x2=x1 + diferencia;
                        y2=y1 + diferencia;

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

                        //rotamos a matrizB y comparamos si A<B
                        rotar = 0;
                        for(int i = 0 ; i < 3 ; i++)
                        {
                            if(matrizA[x1][y1] < matrizB[x2][y2])
                            {
                                break;
                            }
                            rotarMatriz(matrizB,crearB);
                            rotar++;
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

                        crearB+=2;

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

                        matrizA = crearMatriz(crearB);
                        //rotamos a matrizA tanto como rotamos a matrizB
                        for(int i = 0 ; i < rotar ; i++)
                        {
                            rotarMatriz(matrizA,crearB);
                        }

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

                        //Verificar que si antes habia un 0(igual) debemos aumentar a la matriz anterior
                        if(clave[p+1] == 0)
                        {
                            candado[p]+=2;
                        }

                        crearA+=2;

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

                    sali = 'n';

                    break;
                }
                if(crearA >= (limite-1))
                {
                    cout << "No se pudo encontrar un candado para esta clave.";
                    q=false;
                    break;
                }
            }
            //Si A = B (0)
            if(clave[p + 2] == 0)
            {
                crearB = crearA;
                x2=x1;
                y2=y1;
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
            crearA = crearB;
            if(p < (contador - 1))
            {
                crearB=candado[p+2];
            }


            //CAMBIEMOS LOS x1 y1 POR x2 y2
            x1 = x2;
            y1 = y2;

            if(p == (contador-3))
            {
                q = false;
            }
        }
    }

/*
    while(q)
    {
        crearA=candado[0];
        crearB=candado[1];
        matrizA = crearMatriz(crearA);

        x1=clave[0]-1;
        y1=clave[1]-1;

        cout << endl << "CREAR A = "<<crearA << " x1 " << x1 << " y1 " << y1;
        cout << endl << "CREAR B= " << crearB;

        cout << endl <<"El candado para la clave ingresadad seria:" << endl;
        for(int i = 0 ; i < (contador-1) ; i++)
        {
            cout << candado[i] << " ";
        }

        cin >> nada;

        for(int p = 0 ; p < (contador-2) ; p++)
        {

            x2=-1;
            y2=-1;
            cout << endl<<"PPPPPPPPPPPP= "<< p << endl;
            //Si A > B (1)
            if(clave[p + 2] == 1)
            {
                //Si la matrizA llega al limite
                while(crearA < limite)
                {
                    diferencia = ((crearB - crearA)/2);
                    x2 = x1 + diferencia;
                    y2 = y1 + diferencia;

                    //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                    while(!(!((x2 < 0) || (x2 >= crearB)) && (!((y2 < 0) || (y2 >= crearB)))))
                    {
                        //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                        crearB+=2;

                        //Posicion de crearB respecto a crearA
                        diferencia = ((crearB - crearA)/2);
                        x2 = x1 + diferencia;
                        y2 = y1 + diferencia;
                    }


                    //Si la matrizB llega al limite(99)
                    while(crearB < limite)
                    {

                        diferencia = (crearB-crearA)/2;
                        x2=x1 + diferencia;
                        y2=y1 + diferencia;

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
                        cout << endl <<"a "<<crearA << " b "<<crearB << " x1 "<<x1<<" y1 " <<y1 <<" x2 "<<x2<<" y2 "<<y2<< endl;

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
                        rotar = 0;
                        for(int i = 0 ; i < 3 ; i++)
                        {
                            if(matrizA[x1][y1] > matrizB[x2][y2])
                            {
                                break;
                            }
                            rotarMatriz(matrizB,crearB);
                            rotar++;
                        }

                        //Verificamos si matrizA > matrizB en sus respectivas posiciones
                        if(matrizA[x1][y1] > matrizB[x2][y2])
                        {
                            cout << endl << "ROTAN" <<endl;
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
                            break;
                        }

                        //liberamos el espacio de la matrizB
                        for(int f = 0 ; f < crearB ; f++)
                        {
                            delete[] matrizB[f];
                        }
                        delete[] matrizB;

                        crearB+=2;
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
                        matrizA = crearMatriz(crearB);

                        //rotamos a matrizA tanto como rotamos a matrizB
                        for(int i = 0 ; i < rotar ; i++)
                        {
                            rotarMatriz(matrizA,crearB);
                        }
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
                        //Si en verdad crearB == limite -1 significa que con matrizA no se encontró que A>B, por lo cual cambiemos el tamaño a la matrizA

                        //liberamos el espacio de la matrizA
                        for(int f = 0 ; f < crearA ; f++)
                        {
                            delete[] matrizA[f];
                        }
                        delete[] matrizA;

                        cout << " sumo 2 a crearA = " << crearA+2 << "candado p = " << p;

                        //Verificar que si antes habia un 0(igual) debemos aumentar a la matriz anterior
                        cout << "P ES CANDADO EN= " << p;
                        if(clave[p] == 0)
                        {
                            candado[p-2]+=2;
                        }

                        //Aumento +2 a matrizA
                        crearA+=2;

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

                    sali = 'n';

                    break;
                }
                if(crearA >= (limite-1))
                {
                    cout << "No se pudo encontrar un candado para esta clave.";
                    q=false;
                    break;
                }
            }
            //Si A < B (-1)
            if(clave[p + 2] == -1)
            {

                //Si la matrizA llega al limite
                while(crearA < limite)
                {
                    diferencia = ((crearB - crearA)/2);
                    x2 = x1 + diferencia;
                    y2 = y1 + diferencia;

                    //Nos libramos de posiciones negativas y de las que superan a la longitud de la matriz
                    while(!(!((x2 < 0) || (x2 >= crearB)) && (!((y2 < 0) || (y2 >= crearB)))))
                    {
                        //Nos aseguramos que crearB sea impar (ya que empieza en 1)
                        crearB+=2;

                        //Posicion de crearB respecto a crearA
                        diferencia = ((crearB - crearA)/2);
                        x2 = x1 + diferencia;
                        y2 = y1 + diferencia;
                    }


                    //Si la matrizB llega al limite(99)
                    while(crearB < limite)
                    {

                        diferencia = (crearB-crearA)/2;
                        x2=x1 + diferencia;
                        y2=y1 + diferencia;

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
                        cout << endl <<"a "<<crearA << " b "<<crearB << " x1 "<<x1<<" y1 " <<y1 <<" x2 "<<x2<<" y2 "<<y2<<endl;
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
                        cout << endl << "x2: " << x2 << " y2: " << y2 << endl<< "x1: " << x1 << " y2: " << y2<< endl;
                        cout << endl << " posicionA "<<matrizA[x1][y1];
                        cout <<endl << " posicionB "<<matrizB[x2][y2];
                        //rotamos a matrizB y comparamos si A<B
                        rotar = 0;
                        for(int i = 0 ; i < 3 ; i++)
                        {
                            if(matrizA[x1][y1] < matrizB[x2][y2])
                            {
                                break;
                            }
                            rotarMatriz(matrizB,crearB);
                            rotar++;
                        }

                        //Verificamos si matrizA < matrizB en sus respectivas posiciones
                        if(matrizA[x1][y1] < matrizB[x2][y2])
                        {
                            cout << endl << "ROTAN" <<endl;
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
                            break;
                        }

                        //liberamos el espacio de la matrizB
                        for(int f = 0 ; f < crearB ; f++)
                        {
                            delete[] matrizB[f];
                        }
                        delete[] matrizB;

                        crearB+=2;

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

                        matrizA = crearMatriz(crearB);
                        //rotamos a matrizA tanto como rotamos a matrizB
                        for(int i = 0 ; i < rotar ; i++)
                        {
                            rotarMatriz(matrizA,crearB);
                        }

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

                        cout << " sumo 2 a crearA = " << crearA+2 << "candado p = " << p;
                        //Verificar que si antes habia un 0(igual) debemos aumentar a la matriz anterior
                        if(clave[p+1] == 0)
                        {
                            candado[p]+=2;
                        }

                        crearA+=2;

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

                    sali = 'n';

                    break;
                }
                if(crearA >= (limite-1))
                {
                    cout << "No se pudo encontrar un candado para esta clave.";
                    q=false;
                    break;
                }
            }
            //Si A = B (0)
            if(clave[p + 2] == 0)
            {
                crearB = crearA;
                x2=x1;
                y2=y1;
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
            crearA = crearB;
            if(p < (contador - 1))
            {
                cout << endl << "crearB ahora es = " << candado[p+2];
                crearB=candado[p+2];
            }


            cout << "CrearA ahora es: " << crearA << endl;
            //CAMBIEMOS LOS x1 y1 POR x2 y2
            x1 = x2;
            y1 = y2;
            cout <<  endl <<"------------------------"<< endl;

            if(p == (contador-3))
            {
                q = false;
            }
        }
    }
*/

    if(crearA < (limite-1))
    {
        cout << "El candado para la clave ingresadad seria:" << endl;
        for(int i = 0 ; i < (contador-1) ; i++)
        {
            cout << candado[i] << " ";
        }
    }
    cout << endl;

    if(crearA < (limite-1))
    {
        comprobar(clave, candado, (contador-1));
    }

    return 0;
}
