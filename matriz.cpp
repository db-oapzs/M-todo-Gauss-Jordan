#include "matriz.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

Matriz::Matriz()
{
    this->filas = 1;
    this->columnas = 1;
    this->filasAux = 0;
    this->columnasAux = 0;
    this->inicializarMatrices();
    this->entrada = true;
}

Matriz::~Matriz()
{
    this->liberarRecursos();
}

void Matriz::inicializarMatrices()
{
    this->matriz = new double *[this->filas];
    this->matrizId = new double *[this->filas];
    this->matrizInv = new double *[this->filas];

    for (int i = 0; i < this->filas; i++)
    {
        this->matriz[i] = new double[this->columnas]{};
        this->matrizId[i] = new double[this->columnas]{};
        this->matrizInv[i] = new double[this->columnas]{};
    }

    this->vectorRt = new double[this->filas]{};
    this->vectorInv = new double[this->filas]{};
}

void Matriz::liberarRecursos()
{
    if (this->matriz)
    {
        for (int i = 0; i < this->filas; i++)
        {
            delete[] this->matriz[i];
        }
        delete[] this->matriz;
        this->matriz = nullptr;
    }

    if (this->matrizId)
    {
        for (int i = 0; i < this->filas; i++)
        {
            delete[] this->matrizId[i];
        }
        delete[] this->matrizId;
        this->matrizId = nullptr;
    }

    if (this->matrizInv)
    {
        for (int i = 0; i < this->filas; i++)
        {
            delete[] this->matrizInv[i];
        }
        delete[] this->matrizInv;
        this->matrizInv = nullptr;
    }

    delete[] this->vectorRt;
    this->vectorRt = nullptr;
    delete[] this->vectorInv;
    this->vectorInv = nullptr;
}

void Matriz::setDatos()
{
    cout << "\n¿Su matriz es cuadrada? (S/n): ";
    char dt;
    cin >> dt;

    if (dt == 'S' || dt == 's')
    {
        cout << "Ingrese el tamaño de la matriz cuadrada (n x n): ";
        cin >> this->filas;
        this->columnas = this->filas;
    }
    else if (dt == 'N' || dt == 'n')
    {
        cout << "Ingrese el número de filas: ";
        cin >> this->filas;
        cout << "Ingrese el número de columnas: ";
        cin >> this->columnas;
    }
    else
    {
        cout << "\nOpción no válida. Usando matriz 1x1 por defecto.\n";
        this->filas = 1;
        this->columnas = 1;
    }

    if (this->filas <= 0 || this->columnas <= 0)
    {
        cout << "\nDimensiones no válidas. Usando matriz 1x1 por defecto.\n";
        this->filas = 1;
        this->columnas = 1;
    }

    this->filasAux = this->filas;
    this->columnasAux = this->columnas;

    if (this->filas > this->columnas)
    {
        cout << "\n filas mayores datos \n";
        this->columnas = this->filas;
    }
    else if (this->columnas > this->filas)
    {
        cout << "\n columnas mayores datos \n";
        this->filas = this->columnas;
    }
    else if (this->filas == this->columnas)
    {
        cout << "\n cuadrada datos \n";
    }
}

void Matriz::llenarMatrices()
{
    int dt1Aux = this->filas;
    int dt2Aux = this->columnas;

    this->inicializarMatrices();
    cout << "\n ¿Desea llenar la matriz manualmente?	(S/n): ";
    char opcllenado;
    cin >> opcllenado;
    if (opcllenado == 's' || opcllenado == 'S')
    {
        this->entrada = true;
    }
    else if (opcllenado == 'S' || opcllenado == 'N')
    {
        this->entrada = false;
    }
    else
    {
        this->entrada = false;
    }

    this->filas = this->filasAux;
    this->columnas = this->columnasAux;

    this->filasAux = dt1Aux;
    this->columnasAux = dt2Aux;

    if (this->entrada)
    {
        for (int i = 0; i < this->filas; i++)
        {
            for (int j = 0; j < this->columnas; j++)
            {
                cout << "\n Datos de x[" << i + 1 << "] ";
                cin >> this->matriz[i][j];
            }
            cout << "\n Datos del vector x[" << i + 1 << "] ";
            cin >> this->vectorRt[i];
        }

        for (int i = 0; i < this->filasAux; i++)
        {
            for (int j = 0; j < this->columnasAux; j++)
            {
                this->matrizId[i][j] = 0.0;
                this->matrizInv[i][j] = 1.0;
                if (i == j)
                {
                    this->matrizId[i][j] = 1.0;
                }
            }
            this->vectorInv[i] = 1;
        }
    }
    else
    {
        for (int i = 0; i < this->filas; i++)
        {
            for (int j = 0; j < this->columnas; j++)
            {
                this->matriz[i][j] = -50 + rand() % (50 - (-50) + 1);
            }
            this->vectorRt[i] = -50 + rand() % (100 - (-50) + 1);
        }

        for (int i = 0; i < this->filasAux; i++)
        {
            for (int j = 0; j < this->columnasAux; j++)
            {
                this->matrizId[i][j] = 0.0;
                this->matrizInv[i][j] = 1.0;
                if (i == j)
                {
                    this->matrizId[i][j] = 1.0;
                }
            }
            this->vectorInv[i] = 1;
        }
    }
}

void Matriz::imprimirMatriz()
{

    cout << "\n\n\n=================== Matriz Resultante ===================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            cout << setw(10) << fixed << setprecision(0) << abs(this->matriz[i][j]) ;
        }
        cout << " | " << setw(10) << fixed << setprecision(10) << this->vectorRt[i];
        cout << "\n";
    }

    cout << "\n\n\n=================== Matriz Pruebas A[1] ===================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            cout << setw(10) << fixed << setprecision(5) << this->matrizInv[i][j];
        }
        cout << "\n";
    }

    cout << "\n\n\n=================== Matriz Inverza =================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            cout << setw(10) << fixed << setprecision(5) << this->matrizId[i][j];
        }
	    cout << " | " << setw(10) << fixed << setprecision(10) << this->vectorInv[i];
        cout << "\n";
    }
    cout << "\n\n\n=================== Matriz Completa ==================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            cout << setw(10) << fixed << setprecision(0) << abs(this->matriz[i][j]);
        }
        cout << " | ";
        for (int j = 0; j < this->columnasAux; j++)
        {
            cout << setw(10) << fixed << setprecision(5) << this->matrizId[i][j];
        }
        cout << " | " << setw(10) << fixed << setprecision(10) << this->vectorRt[i];
        cout << " | " << setw(10) << fixed << setprecision(10) << this->vectorInv[i];
        cout << "\n";
    }

    cout << "\n\n\n=====================================================\n\n";
}

void Matriz::imprimirMatrizArchivo()
{
    std::ofstream archivo("matriz_resultado.txt");
    if (!archivo)
    {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    archivo << "\n\n\n=================== Matriz Resultante ===================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            archivo << std::setw(10) << std::fixed << std::setprecision(0) << std::abs(this->matriz[i][j]);
        }
        archivo << " | " << std::setw(10) << std::fixed << std::setprecision(10) << this->vectorRt[i] << "\n";
    }

    archivo << "\n\n\n=================== Matriz Pruebas A[1] ===================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            archivo << std::setw(10) << std::fixed << std::setprecision(5) << this->matrizInv[i][j];
        }
        archivo << "\n";
    }

    archivo << "\n\n\n=================== Matriz Inversa =================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            archivo << std::setw(10) << std::fixed << std::setprecision(5) << this->matrizId[i][j];
        }
        archivo << " | " << std::setw(10) << std::fixed << std::setprecision(10) << this->vectorInv[i] << "\n";
    }

    archivo << "\n\n\n=================== Matriz Completa ==================\n\n";
    for (int i = 0; i < this->filasAux; i++)
    {
        for (int j = 0; j < this->columnasAux; j++)
        {
            archivo << std::setw(10) << std::fixed << std::setprecision(0) << std::abs(this->matriz[i][j]);
        }
        archivo << " | ";
        for (int j = 0; j < this->columnasAux; j++)
        {
            archivo << std::setw(10) << std::fixed << std::setprecision(5) << this->matrizId[i][j];
        }
        archivo << " | " << std::setw(10) << std::fixed << std::setprecision(10) << this->vectorRt[i];
        archivo << " | " << std::setw(10) << std::fixed << std::setprecision(10) << this->vectorInv[i] << "\n";
    }

    archivo << "\n\n\n=====================================================\n\n";
    archivo.close();
}

void Matriz::metodo()
{
    for (int i = 0; i < this->filasAux; i++){
        if (this->matriz[i][i] == 0) {
            cout << "Error: Pivote en posición [" << i << "][" << i << "] es 0. No se puede dividir." << endl;
            return;
        }

        // Pivoteo
        this->pivote = this->matriz[i][i];
        for(int k = 0 ; k < this->columnasAux ; k++){
            this->matriz[i][k] /= this->pivote;
            this->matrizId[i][k] /= this->pivote;
            this->matrizInv[i][k] /= this->pivote;
        }
        this->vectorRt[i] /= this->pivote;
        this->vectorInv[i] /= this->pivote;
        
        // Eliminación de la diagonal inferior
        for(int j = i + 1; j < this->filasAux; j++){
            this->pivote = this->matriz[j][i];  
            for(int k = 0 ; k < this->columnasAux ; k++){
                this->matriz[j][k] -= this->pivote * this->matriz[i][k];
                this->matrizId[j][k] -= this->pivote * this->matrizId[i][k];
                this->matrizInv[j][k] -= this->pivote * this->matrizInv[i][k];
            }
            this->vectorRt[j] -= this->pivote * this->vectorRt[i];
            this->vectorInv[j] -= this->pivote * this->vectorInv[i];
        }
    }

    // Eliminación de la diagonal superior
    for (int i = this->filasAux - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            this->pivote = this->matriz[j][i];
            for (int k = 0; k < this->columnasAux; k++) {
                this->matriz[j][k] -= this->pivote * this->matriz[i][k];
                this->matrizId[j][k] -= this->pivote * this->matrizId[i][k];
                this->matrizInv[j][k] -= this->pivote * this->matrizInv[i][k];
            }
            this->vectorRt[j] -= this->pivote * this->vectorRt[i];
            this->vectorInv[j] -= this->pivote * this->vectorInv[i];
        }
    }
}



void Matriz::proceso()
{
    char dt;
    do
    {
        this->setDatos();
        this->llenarMatrices();
        cout << "\n\n\n=================== Matriz Ingresada ===================\n\n";
        for (int i = 0; i < this->filasAux; i++)
        {
            for (int j = 0; j < this->columnasAux; j++)
            {
                cout << setw(10) << fixed << setprecision(2) << this->matriz[i][j];
            }
            cout << " | " << setw(10) << fixed << setprecision(2) << this->vectorRt[i];
            cout << "\n";
        }
        this->metodo();
        this->imprimirMatriz();
        this->imprimirMatrizArchivo();

        cout << "\n¿Desea realizar un nuevo ejercicio? (S/n): ";
        cin >> dt;
        if (dt != 'S' && dt != 's' && dt != 'N' && dt != 'n')
        {
            cout << "\nEntrada no válida. Por favor, intente de nuevo.\n";
        }
        if (dt == 'S' || dt == 's')
        {
            system("cls");
        }
        this->liberarRecursos();
    } while (dt == 'S' || dt == 's');
}
