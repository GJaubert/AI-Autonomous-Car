#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>


#ifndef COCHE
#define COCHE

#define COSTE 1
#define CLEARSCREEN system("CLS")

class tablero;
class celda;
class coche
{
    private:
    
        std::pair<int, int> pos;
        int sensor[4]; //Norte,Oeste,Sur,Este
        static std::vector<celda> frontera;
        static std::vector<celda> closed_list;
        std::pair<int,int> destino;

    public:

        coche(int filas, int columna);
        ~coche();
        std::pair<int,int> get_pos();
        std::pair<int,int> set_pos(int fila, int columna);
        bool A_Star(tablero& malla, int function, int& contador);
        int definePath(tablero& malla);
        void set_Destino(int destino_x, int destino_y);
        void UpdateSensor(tablero&, int x, int y);
        bool vectorCheck(std::vector<celda> v, int x, int y);
        void vectorErase(std::vector<celda>& v,int x, int y);
        int selectFromVector(std::vector<celda>& v);
};
#endif
