#include <iostream>
#include <utility>
#include <time.h>

#ifndef OBSTACULO
#define OBSTACULO
class obstaculo
{
    private:
    
        std::pair<int, int> pos;

    public:

        obstaculo();
        obstaculo(int fila, int columna);
        ~obstaculo();
        std::pair<int,int> get_pos();
        std::pair<int,int> set_pos(int fila, int columna);
        void Create_Random(int max_filas, int max_columnas);
        friend std::ostream& operator<<(std::ostream& os, const obstaculo& coche_);
};
#endif