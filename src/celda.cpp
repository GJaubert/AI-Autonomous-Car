#include "../include/celda.hpp"

celda::celda()
{
    type = 0;
    f = 0;
    g = 0;
    h = 0;
    x_parent = -1;
    y_parent = -1;
    optimal = false;
    visitado = false;

}

celda::~celda(){}

celda::celda(int type_, int fila, int columna) : pos(std::pair<int,int>(fila,columna))
{
    f = 0;
    g = 0;
    h = 0;
    x_parent = -1;
    y_parent = -1;
    optimal = false;
    visitado = false;
    switch(type_)
    {
        case 0:
            type = type_;
            break;
        case 1:
            type = type_;
            obstaculo_ = std::make_shared<obstaculo>(pos.first,pos.second);
            break;
        case 2:
            type = type_;
            coche_ = std::make_shared<coche>(pos.first,pos.second);
            break;
        default: 
            std::cout << "\nEstado no valido\n";
            break;
    }
}

int celda::get_y_parent()
{
    return y_parent;
}

int celda::get_x_parent()
{
    return x_parent;
}

double celda::get_f()
{
    return g + h;
}

double celda::get_g()
{
    return g;
}

double celda::get_h(int function, int destino_x,int destino_y)
{
    switch(function)
    {
    case 0:
        h = Manhattan(destino_x,destino_y);
        break;
    case 1:
        h = Euclidea(destino_x,destino_y);
    break;
    }
    return h;
}

void celda::set_f(double input)
{
    f = input;
}
void celda::set_g(double input)
{
    g = input;
}

void celda::set_x_parent(int value)
{
    x_parent = value;
}

void celda::set_y_parent(int value)
{
    y_parent = value;
}

celda& celda::operator=(celda other)
{
    type = other.type;
    pos = other.pos;
    f = other.f;
    g = other.g;
    h = other.h;
    x_parent = other.x_parent;
    y_parent = other.y_parent;
    optimal = other.optimal;
    visitado = other.visitado;
    return *this;
}

bool celda::isObstacle()
{
    if(type == 1)
        return true;
    else
        return false;
}

bool celda::isCar()
{
    if(type == 2)
        return true;
    else
        return false;
}

bool celda::isDestiny()
{
    if(type == 3)
        return true;
    else
        return false;
}

int celda::setType(int type_)
{
    switch(type_){
        case 0:
            type = type_;
            break;
        case 1:
            type = type_;
            obstaculo_ = std::make_shared<obstaculo>(pos.first,pos.second);
            break;
        case 2:
            type = type_;
            coche_ = std::make_shared<coche>(pos.first,pos.second);
            break;
        case 3:
            type = type_;
            break;
        case 4:
            type = type_;
            break;
        default: 
            std::cout << "\nEstado no valido\n";
            break;
    }
    return type;
}

void celda::printCell()
{
    switch(type)
    {
        case 0: 
        {
            if(optimal)
                std::cout << PURPLE << "\u2588" << "\u2588" << RESET;
            else if (visitado)
                std::cout << GREY << "\u2588" << "\u2588" << RESET;
            else
                std::cout << "  ";
        }
        break;
        case 1:
        {
            std::cout << "\u2588" << "\u2588"; //"█"
        }
        break;
        case 2:
        {
            std::cout << RED << "\u2588" << "\u2588" << RESET;
        }
        break;
        case 3:
        {
            std::cout << GREEN << "\u2588" << "\u2588" << RESET;
        }
        break;
    }
}

int celda::Manhattan(int destino_x, int destino_y)
{
    return abs(pos.first - destino_x) + abs(pos.second - destino_y);
}

double celda::Euclidea(int destino_x, int destino_y)
{
    return sqrt(pow(pos.first - destino_x, 2) + pow(pos.second - destino_y, 2));
}