#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include "./obstaculo.hpp"
#include "./coche.hpp"

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define PURPLE "\033[35m"
#define GREY "\033[1;30m"

#ifndef CELDA
#define CELDA

class celda
{
    private:
    
        int type; //0 vacío, 1 obstaculo, 2 coche, 3 meta
        std::pair<int,int> pos;
        std::shared_ptr<coche> coche_;
        std::shared_ptr<obstaculo> obstaculo_;
        double f,g,h;
        int x_parent;
        int y_parent;
        bool optimal;
        bool visitado; 

    public:

        celda();
        ~celda();
        celda(int type_, int fila, int columna);
        celda& operator=(celda other);
        int setType(int type_);
        void printCell();
        double get_f();
        double get_g();
        double get_h(int function, int destino_x,int destino_y); //0: manhattan, 1: euclidea
        void set_f(double);
        void set_g(double);
        int get_y_parent();
        int get_x_parent();
        void set_x_parent(int value);
        void set_y_parent(int value);
        int Manhattan(int destino_x, int destino_y);
        double Euclidea(int destino, int destino_y);
         bool isObstacle();
        bool isCar();
        bool isDestiny();

    friend class coche;
    friend class tablero;
};
#endif