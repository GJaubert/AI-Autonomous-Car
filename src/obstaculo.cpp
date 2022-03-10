#include "../include/obstaculo.hpp"

obstaculo::obstaculo(int fila, int columna)
{
    pos.first = fila;
    pos.second = columna;
}

obstaculo::obstaculo()
{}

obstaculo::~obstaculo(){
}

std::pair<int,int> obstaculo::get_pos()
{
    return pos;
}

std::pair<int,int> obstaculo::set_pos(int fila, int columna)
{
    pos.first = fila;
    pos.second = columna;
    return pos;
}

void obstaculo::Create_Random(int max_filas, int max_columnas)
{
    srand(time(NULL));
    this->pos.first = rand() % max_filas;
    this->pos.second = rand() % max_columnas;
}

std::ostream& operator<<(std::ostream& os, const obstaculo& coche_)
{
    os << "X";
    return os;
}