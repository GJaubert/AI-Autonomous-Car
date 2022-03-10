/*NOMBRE: GABRIEL GARCÍA JAUBERT
PE102
UNIVERSIDAD DE LA LAGUNA
INTELIGENCIA ARTIFICIAL(2020-2021)
15/11/2020*/

#include "../include/tablero.hpp"

std::vector<celda> coche::frontera;
std::vector<celda> coche::closed_list;


int main(int argc, char* argv[])
{
  std::cout << "\nPractica 1. Estrategias de búsqueda.\n";
  std::cout << "------------------------------------\n\n";

  int n,m = 0;
  int x,y = 0;
  char randomobs;
  int filerandomobs;
  int cantidadobs, functiontype;
  char c;
  int contador = 0;

  if(argc == 2)
  {
    std::fstream file_(argv[1]);
    if(!file_.is_open())
      std::cout << "Error al abrir el fichero\n\n";
    else
    {
      file_ >> n;
      file_ >> m;
      file_ >> functiontype;
      
      tablero tablero1(n,m);
      
      file_ >> x >> c >> y;

      if(tablero1.set_Cell(2,x,y) == 0)
        return 0;

      file_ >> x >> c >> y;
      
      if(tablero1.set_Cell(3,x,y) == 0)
        return 0;

      file_ >> filerandomobs;
      if(filerandomobs == -1)
      {
          file_ >> cantidadobs;
          tablero1.RandomObstacle(cantidadobs);
      }
      else if(filerandomobs >= 0)
      {
        for(int i = 0; i < filerandomobs; i++)
        {
          file_ >> x >> c >> y;
          if (tablero1.set_Cell(1,x,y) == 0) i--;
        }
      }
      else
      {
        std::cout << "Error, opcion de obstaculos no valida\n";
        return 0;
      }
      
        tablero1.Search(functiontype, contador);
        std::cout << "Numero de nodos expandidos: " << contador << "\n";
    }
  }
  else
  {

    std::cout << "Introduzca el numero de filas: ";
    std::cin >> n;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }
    std::cout << "Introduzca el numero de columnas: ";
    std::cin >> m;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }

    std::cout << "Introduzca el tipo de funcion heuristica(0: Manhattan, 1: Euclidea): ";
    std::cin >> functiontype;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }

    tablero tablero1(n,m);

    std::cout << RED << "\nPara introducir las coordenadas, recuerde que comienzan a contar desde [0,1,2...n]\n" << RESET;
    std::cout << "\nIntroduzca la coordenada x para la posicion inicial del coche: ";
    std::cin >> x;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }
    std::cout << "Introduzca la coordenada y para la posicion inicial del coche: ";
    std::cin >> y;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }
    
    if(tablero1.set_Cell(2,x,y) == 0)
      return 0;

    std::cout << "\nIntroduzca la coordenada x para la posicion del destino del coche: ";
    std::cin >> x;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }
    std::cout << "Introduzca la coordenada y para la posicion del destino del coche: ";
    std::cin >> y;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }

    if(tablero1.set_Cell(3,x,y) == 0)
        return 0;

    std::cout << "\n¿Desea generar los obstaculos automaticamente? [s/n]: ";
    std::cin >> randomobs;
    if(std::cin.fail())
    {
      std::cout <<  RED << "No es un numero\n" << RESET;
      return 0;
    }

    if(randomobs == 's')
    {
      std::cout << "Introduzca el porcentaje de obstaculos a generar: ";
      std::cin >> cantidadobs;
      if(std::cin.fail())
      {
        std::cout <<  RED << "No es un numero\n" << RESET;
        return 0;
      }
      if (!tablero1.RandomObstacle(cantidadobs))
          return 0;
    }
    else if(randomobs == 'n')
    {
      std::cout << "Introduzca el numero de obstaculos a generar: ";
      std::cin >> cantidadobs;
      if(std::cin.fail())
      {
        std::cout <<  RED << "No es un numero\n" << RESET;
        return 0;
      }
      
      for(int i = 0; i < cantidadobs; i++)
      {
        std::cout << "\nIntroduzca la coordenada x para la posicion del obstaculo: ";
        std::cin >> x;
        if(std::cin.fail())
        {
          std::cout <<  RED << "No es un numero\n" << RESET;
          return 0;
        }
        std::cout << "Introduzca la coordenada y para la posicion del obstaculo: ";
        std::cin >> y;
        if(std::cin.fail())
        {
          std::cout <<  RED << "No es un numero\n" << RESET;
          return 0;
        }
        if (tablero1.set_Cell(1,x,y) == 0) i--;
      }
    }
    else
    {
      std::cout << "Respuesta no valida\n";
      return 0;
    }
    tablero1.Search(functiontype, contador);
    std::cout << "Numero de nodos expandidos: " << contador << "\n";
  }
}