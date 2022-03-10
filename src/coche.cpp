#include "../include/coche.hpp"
#include "../include/tablero.hpp"
#include "../include/celda.hpp"

coche::coche(int fila, int columna)
{
    pos.first = fila;
    pos.second = columna;
}

coche::~coche(){}

std::pair<int,int> coche::get_pos()
{
    return pos;
}

std::pair<int,int> coche::set_pos(int fila, int columna)
{
    this->pos.first = fila;
    this->pos.second = columna;
    return pos;
}

void coche::UpdateSensor(tablero& malla, int x, int y)
{
        if(x != 0) //Norte
        {
            if(malla.tablero_[x - 1][y].isObstacle()) sensor[0] = 1;
            else sensor[0] = 0;
        }
        else sensor[0] = 1;

        if(x != (malla.nfilas_ - 1)) //Sur
        {
            if(malla.tablero_[x + 1][y].isObstacle()) sensor[2] = 1;
            else sensor[2] = 0;
        }
        else sensor[2] = 1;

        if(y != 0) //Oeste
        {
            if(malla.tablero_[x][y - 1].isObstacle()) sensor[1] = 1;
            else sensor[1] = 0;
        }
        else sensor[1] = 1;

        if(y != (malla.ncolumnas_ - 1)) //Este
        {
            if(malla.tablero_[x][y + 1].isObstacle()) sensor[3] = 1;
            else sensor[3] = 0;
        }
        else sensor[3] = 1;
}

void coche::set_Destino(int destino_x, int destino_y)
{
    destino.first = destino_x;
    destino.second = destino_y;
}

bool coche::vectorCheck(std::vector<celda> v, int x, int y)
{
    for(int i = 0; i < v.size(); i++)
    {
        if((v[i].pos.first == x) && (v[i].pos.second == y))
            return true;
    }
    return false;
}

void coche::vectorErase(std::vector<celda>& v, int x, int y)
{
    for(int i = 0; i < v.size(); i++)
    {
        if((v[i].pos.first == x) && (v[i].pos.second == y)){
            v.erase(v.begin() + i);
        }
    }
}

int coche::selectFromVector(std::vector<celda>& v)
{
    int aux = 0;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].get_f() <= v[aux].get_f())
            aux = i;
    }
    return aux;
}

int coche::definePath(tablero& malla)
{
    int contador_camino = 0;
    int i = destino.first;
    int j = destino.second;
    int aux;

    while((malla.tablero_[i][j].x_parent != -1)||(malla.tablero_[i][j].y_parent != -1))
    {
        malla.tablero_[i][j].optimal = true;
        aux = i;
        i = malla.tablero_[aux][j].x_parent;
        j = malla.tablero_[aux][j].y_parent;
        contador_camino++;
    }
    return contador_camino;
}

bool coche::A_Star(tablero& malla, int function, int& contador)
{
    celda m;
    celda n;
    m = malla.tablero_[pos.first][pos.second];
    
    std::shared_ptr<coche> coche_ = malla.tablero_[pos.first][pos.second].coche_;
    coche::frontera.push_back(m);
    
    
    m.set_g(0);
    m.get_h(function, destino.first, destino.second);
    m.set_f(m.get_f());

    double cost = 0;
    int index = 0;

    while(!coche::frontera.empty())
    {
        usleep(50000);
        contador++;
        
        index = selectFromVector(coche::frontera);
        m = coche::frontera[index];
        malla.tablero_[m.pos.first][m.pos.second].visitado = true;

        malla.print(contador);

        if (m.isDestiny())
        {
            definePath(malla);
            malla.print(contador);
            std::cout << "Camino optimo: " << definePath(malla) << "\n";
            return true;
        }
        
        coche::closed_list.push_back(m);
        coche::frontera.erase(coche::frontera.begin() + index);

        UpdateSensor(malla,m.pos.first,m.pos.second);
        
        if(sensor[0] != 1) //n = celda[i - 1][j]
        {
            if(!vectorCheck(coche::closed_list, m.pos.first - 1, m.pos.second))
            {
                cost = m.get_g() + COSTE;
                if((vectorCheck(coche::frontera,m.pos.first -1, m.pos.second)) && (cost < malla.tablero_[m.pos.first -1][m.pos.second].get_g()))
                {
                    vectorErase(coche::frontera,m.pos.first - 1, m.pos.second);
                }
                if((vectorCheck(coche::closed_list,m.pos.first -1, m.pos.second)) && (cost < malla.tablero_[m.pos.first -1][m.pos.second].get_g()))
                    vectorErase(coche::closed_list,m.pos.first - 1, m.pos.second);
                if((!vectorCheck(coche::frontera,m.pos.first -1, m.pos.second)) && (!vectorCheck(coche::closed_list,m.pos.first -1, m.pos.second)))
                {
                    malla.tablero_[m.pos.first - 1][m.pos.second].set_x_parent(m.pos.first);
                    malla.tablero_[m.pos.first - 1][m.pos.second].set_y_parent(m.pos.second);
                    malla.tablero_[m.pos.first -1][m.pos.second].set_g(cost);
                    malla.tablero_[m.pos.first -1][m.pos.second].get_h(function, destino.first, destino.second);
                    malla.tablero_[m.pos.first -1][m.pos.second].set_f(malla.tablero_[m.pos.first -1][m.pos.second].get_f());
                    n = malla.tablero_[m.pos.first -1][m.pos.second];
                    coche::frontera.push_back(n);

                    
                }
            }
        }

        if(sensor[1] != 1) //n = celda[i][j - 1]
        {
            if(!coche_->vectorCheck(coche::closed_list, m.pos.first, m.pos.second - 1))
            {
                cost = m.get_g() + COSTE;
                if((vectorCheck(coche::frontera,m.pos.first, m.pos.second - 1)) && (cost < malla.tablero_[m.pos.first][m.pos.second - 1].get_g()))
                    vectorErase(coche::frontera,m.pos.first, m.pos.second - 1);
                if((vectorCheck(coche::closed_list,m.pos.first, m.pos.second - 1)) && (cost < malla.tablero_[m.pos.first][m.pos.second - 1].get_g()))
                    vectorErase(coche::closed_list,m.pos.first, m.pos.second - 1);
                if((!vectorCheck(coche::frontera,m.pos.first, m.pos.second - 1)) && (!coche_->vectorCheck(coche::closed_list,m.pos.first, m.pos.second - 1)))
                {
                    malla.tablero_[m.pos.first][m.pos.second - 1].set_x_parent(m.pos.first);
                    malla.tablero_[m.pos.first][m.pos.second - 1].set_y_parent(m.pos.second);
                    malla.tablero_[m.pos.first][m.pos.second - 1].set_g(cost);
                    malla.tablero_[m.pos.first][m.pos.second - 1].get_h(function, destino.first, destino.second);
                    malla.tablero_[m.pos.first][m.pos.second - 1].set_f(malla.tablero_[m.pos.first][m.pos.second - 1].get_f());
                    n = malla.tablero_[m.pos.first][m.pos.second - 1];
                    coche::frontera.push_back(n);
                }
            }
        }


        if(coche_->sensor[2] != 1) //n = celda[i + 1][j]
        {
            if(!vectorCheck(coche::closed_list, m.pos.first + 1, m.pos.second))
            {
                cost = m.get_g() + COSTE;

                if((vectorCheck(coche::frontera,m.pos.first +1, m.pos.second)) && (cost < malla.tablero_[m.pos.first +1][m.pos.second].get_g()))
                    vectorErase(coche::frontera,m.pos.first + 1, m.pos.second);
                if((vectorCheck(coche::closed_list,m.pos.first +1, m.pos.second)) && (cost < malla.tablero_[m.pos.first +1][m.pos.second].get_g()))
                    vectorErase(coche::closed_list,m.pos.first + 1, m.pos.second);
                if((!vectorCheck(coche::frontera,m.pos.first +1, m.pos.second)) && (!coche_->vectorCheck(coche::closed_list,m.pos.first +1, m.pos.second)))
                {
                    malla.tablero_[m.pos.first + 1][m.pos.second].set_x_parent(m.pos.first);
                    malla.tablero_[m.pos.first + 1][m.pos.second].set_y_parent(m.pos.second);
                    malla.tablero_[m.pos.first +1][m.pos.second].set_g(cost);
                    malla.tablero_[m.pos.first +1][m.pos.second].get_h(function, destino.first, destino.second);
                    malla.tablero_[m.pos.first +1][m.pos.second].set_f(malla.tablero_[m.pos.first +1][m.pos.second].get_f());
                    n = malla.tablero_[m.pos.first +1][m.pos.second];
                    coche::frontera.push_back(n);
                }
            }
        }


        if(sensor[3] != 1) //n = celda[i][j + 1]
        {
            if(!vectorCheck(coche::closed_list, m.pos.first, m.pos.second + 1))
            {
                cost = m.get_g() + COSTE;
                if((vectorCheck(coche::frontera,m.pos.first, m.pos.second + 1)) && (cost < malla.tablero_[m.pos.first][m.pos.second + 1].get_g()))
                    vectorErase(coche::frontera,m.pos.first, m.pos.second + 1);
                if((vectorCheck(coche::closed_list,m.pos.first, m.pos.second + 1)) && (cost < malla.tablero_[m.pos.first][m.pos.second + 1].get_g()))
                    vectorErase(coche::closed_list,m.pos.first, m.pos.second + 1);
                if((!vectorCheck(coche::frontera,m.pos.first, m.pos.second + 1)) && (!coche_->vectorCheck(coche::closed_list,m.pos.first, m.pos.second + 1)))
                {
                    malla.tablero_[m.pos.first][m.pos.second + 1].set_x_parent(m.pos.first);
                    malla.tablero_[m.pos.first][m.pos.second + 1].set_y_parent(m.pos.second);
                    malla.tablero_[m.pos.first][m.pos.second + 1].set_g(cost);
                    malla.tablero_[m.pos.first][m.pos.second + 1].get_h(function, destino.first, destino.second);
                    malla.tablero_[m.pos.first][m.pos.second + 1].set_f(malla.tablero_[m.pos.first][m.pos.second + 1].get_f());
                    n = malla.tablero_[m.pos.first][m.pos.second + 1];
                    coche::frontera.push_back(n);
                }
            }
        }
    }
    return false;
}