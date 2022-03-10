#include "../include/tablero.hpp"

std::vector<celda> coche::frontera;
std::vector<celda> coche::closed_list;

int main()
{
    tablero tablero1(15,15);
    //tablero1.set_Cell(1,3,9);
    //tablero1.RandomObstacle(20);
     //tablero1.set_Cell(1,3,8);
    // tablero1.set_Cell(1,5,7);
    // tablero1.set_Cell(1,2,9);
    //tablero1.set_Cell(1,9,9);
    tablero1.set_Cell(2,1,3);
    tablero1.set_Cell(3,1,12);
    for(int i = 0; i < 10; i++)
       tablero1.set_Cell(1,i,8);
    tablero1.set_Cell(1,5,6);
    tablero1.set_Cell(1,6,4);
    tablero1.set_Cell(1,6,5);
    tablero1.set_Cell(1,7,3);
    tablero1.set_Cell(1,7,2);
    tablero1.set_Cell(1,8,3);
    tablero1.set_Cell(1,9,3);
    tablero1.set_Cell(1,9,5);
    tablero1.set_Cell(1,9,6);
    tablero1.set_Cell(1,9,7);
    tablero1.set_Cell(1,9,8);
    //tablero1.set_Cell(1,9,9);
    tablero1.set_Cell(1,10,6);
    tablero1.set_Cell(1,11,6);
    tablero1.set_Cell(1,14,6);
    //tablero1.set_Cell(1,10,6);
    tablero1.actualizar();
    //tablero1.print();
    
}