#include <iostream>
using namespace std;

int llenarMatriz(unsigned int k,unsigned int **matriz)
{

    unsigned int valores = 1;
    unsigned short int centro = ((k + 1)/2)- 1 ;

    for(int i=0; i<k; i++){
        for (int j=0; j<k; j++){
            if (i == centro && j == centro){
                matriz[i][j]=0;
            }
            else{
                matriz[i][j] = valores;
                valores++;
            }
        }

    }
}

int main()
{

    unsigned int **matriz = new unsigned int *[5];
    for (int i = 0; i < 5; i++){
        matriz[i] = new unsigned int[5];
    }
    llenarMatriz(5,matriz);

    for(int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            if (matriz[i][j] < 10){
                cout << matriz[i][j] << "   ";
            }
            else {
                cout << matriz[i][j] << "  ";
            }
        }
        cout <<endl;
    }

    return 0;
}
