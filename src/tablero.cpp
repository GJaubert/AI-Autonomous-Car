#include "../include/tablero.hpp"

tablero::tablero(int filas, int columnas) : nfilas_(filas), ncolumnas_(columnas)
{
    

   for(int i = 0; i < nfilas_; i++)
   {
       std::vector<celda> temp;
       for(int j = 0; j < ncolumnas_; j++)
       {
        celda celda_tmp(0,i,j);
        temp.push_back(celda_tmp);
       }
       tablero_.push_back(temp);
   }
}

tablero::~tablero(){}

int tablero::set_Cell(int type_, int fila, int columna)
{
    if((fila >= nfilas_)||(columna >= ncolumnas_))
    {
        std::cout << "Coordenada no valida para el tamaño de la tabla\n";
        return 0;
    }
    celda cell;
    tablero_[fila][columna].setType(type_);
    if(type_ == 2)
    {
        pos_coche.first = fila;
        pos_coche.second = columna;
    }
    if(type_ == 3)
    {
        pos_destino.first = fila;
        pos_destino.second = columna;
        tablero_[pos_coche.first][pos_coche.second].coche_->set_Destino(fila,columna);
    }
    return type_;
}

void tablero::print(int contador)
{
    system("clear");
    std::cout << "\n";
    std::cout << "\u250F"; //"┏"
    for(int i = 0; i < ncolumnas_ * 2; i++) std::cout << "\u2501"; //"━"
    std::cout << "\u2513" << "\n";
    for(int i = 0; i < nfilas_; i++)
    {
        std::cout << "\u2503"; //"┃"
        for(int j = 0; j < ncolumnas_; j++)
            tablero_[i][j].printCell();
        std::cout << "\u2503";  //"┃"
        std::cout << "\n";
    }
    std::cout << "\u2517"; //"┗"
    for(int i = 0; i < ncolumnas_ * 2; i++) std::cout << "\u2501"; //"━"
    std::cout << "\u251B" << "\n"; //"┛"
}

bool tablero::RandomObstacle(int porcentaje)
{
    if((porcentaje > 100)||(porcentaje < 0))
    {
        std::cout << "Porcentaje incorrecto\n";
        return false;
    }
    int quantity = (porcentaje * nfilas_ * ncolumnas_) / 100;
    if((nfilas_ * ncolumnas_) < quantity)
    {
        std::cout << "Numero superior de obstaculos que de casillas en la tabla\n";
        return false;
    }
    srand(time(NULL));
    for(int i = 0; i < quantity; i++)
    {
        int x = rand() % nfilas_;
        int y = rand() % ncolumnas_;
        if(tablero_[x][y].isObstacle()||(tablero_[x][y].isDestiny())||(tablero_[x][y].isCar()))
            i--;
        else
            set_Cell(1,x,y);
    }
    return true;
}

void tablero::Search(int functiontype, int& contador)
{
    tablero_[pos_coche.first][pos_coche.second].coche_->A_Star(*this, functiontype, contador);
}