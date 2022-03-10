#include <iostream>
#include <vector>
#include <unistd.h>
#include "./celda.hpp"

#ifndef TABLERO
#define TABLERO
class tablero
{   
    private:
        
        std::vector<std::vector<celda>> tablero_;
        int nfilas_;
        int ncolumnas_;
        std::pair<int,int> pos_coche;
        std::pair<int,int> pos_destino;

    public:

        tablero(int nfilas, int ncolumnas);
        ~tablero();
        int get_filas();
        int get_columnas();
        int set_Cell(int type_, int fila, int columna);
        bool RandomObstacle(int porcentaje);
        void Search(int functiontype, int& contador);
        void print(int contador);
        void printPath();
    friend class coche;
};
#endif