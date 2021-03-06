/*En la regi�n de la sierra de los Cuchumatanes la compa��a Exterminio s.a., tiene las siguientes tarifas: 
Adem�s del area a fumigar es mayor a 500.00 hect�reas se tiene un descuento del 5%. Adicionalmente, si el total a pagar 
por el servicio es mayor a Q1500.00 se tiene un descuento adicional del 10% sobre el excedente. 
La compa��a necesita las estad�sticas de los servicios que ha ofrecido a un grupo de agricultores durante un periodo de tiempo. 
Por cada servicio debe ingresar los datos siguientes: 
Tipo de Fumigacion (1 a 4) y el n�mero de hect�reas, toda esta informaci�n deber� almacenarse en una base de datos (archivo plano).
Se le pide que realice un programa en C++ que solicite el ingreso de la informaci�n de cada servicio realizado a un grupo de agricultores. 
El programa deber� de leer los datos del archivo que tiene la informaci�n antes almacenada y mostrar la cantidad de servicios de 
cada tipo de fumigaci�n, determinar el tipo servicio con mayor demanda y el monto total pagado por los clientes.*/

include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include<ctime> 
#include <stdio.h>
#include <vector>
using namespace std;

struct servicios{
  int servicio;
  float tamanio;
  float total;
};

struct tipo {
  int servicio;
  string descripcion;
  int total;
};

void tabla(){
std::vector<tipo> fumigaciones;

float grantotal;

void inicio(){
  fumigaciones.clear();
  fumigaciones.push_back({1, "Mala hierba", 0});
  fumigaciones.push_back({2, "Langostas", 0});
  fumigaciones.push_back({3, "Gusanos", 0});
  fumigaciones.push_back({4, "Todo lo anterior", 0});
  grantotal=0;
};
cout << "Tipo" << "\t" << "Servicio" <<"\t" << "Costo x Hectaria" << endl;
cout << "1" << "\t \t" << "Mala Hierba" << "\t" << "10.00" << endl;
cout << "2" << "\t \t" << "Langostas" << "\t" << "20.00" << endl;
cout << "3" << "\t \t" << "Gusanos" << "\t \t" << "30.00" << endl;
cout << "4" << " " << "Todo lo anterior" << "\t" << "50.00" << endl;
cout << "=================================================" << endl;
};

float calculo (float servicio, int tamanio){
  float total, precio;
  if (servicio==1){
    precio=10*tamanio;
  }
  else if (servicio==2){
    precio=20*tamanio;
  }
  else if (servicio==3){
    precio=30*tamanio;
  }
  else if (servicio==4){
    precio=50*tamanio;
  }
  // obtengo el descuento si es mayor a 500 hectarias
  if (tamanio > 500) {
    precio=precio-(precio*0.5);
  }
  
  if (precio > 1500){
    // sacando el excdente para el descuento del 10%
    precio=(precio-1500)*0.10;
    // sumando el excdente mas 1500
    precio=precio+1500;
  }

  total=precio;

  return total;
};

void grabar(){
  servicios x;
  tabla();
  cout << "ingrese el tipo de servicio. "<< "\n";
  cin >> x.servicio;
  cout << "tamanio en hectarias. "<< "\n";
  cin >> x.tamanio;

  x.total = calculo(x.servicio, x.tamanio);
  // hacemos una pausa
  string empty;
  getchar();
  getline(cin, empty);
  
  // grabo al archivo
  ofstream miarchivo("servicios.txt", std::ios_base::app);
  miarchivo << x.servicio << "\t" << x.tamanio <<"\t"<< x.total<<endl;
  //Cerramos la escritura del archivo.
  miarchivo.close();
}
void leer_archivo(){
  // inicio los contadores de fumigaciones
  inicio();
  //declaro la variable para leer archivo
    ifstream miarchivo;
    
    servicios x;
    //std::vector<tipo> y;
    	
	  try{
      miarchivo.open("servicios.txt",ios::in);
		
  		while(miarchivo >> x.servicio >> x.tamanio >> x.total){
 
        fumigaciones[x.servicio-1].total=fumigaciones[x.servicio-1].total+1;
        grantotal=grantotal+x.total;
      }    
		  miarchivo.close();
      // Muestro los reportes
      cout << "Mala Hierba: " << fumigaciones[0].total << endl;
      cout << "Langosta: " << fumigaciones[1].total << endl;
      cout << "Gusanos: " << fumigaciones[2].total << endl;
      cout << "Todo lo anterior: " << fumigaciones[3].total << endl;
      
      int a,b,c,yz;
      
      for (int y=0; y<fumigaciones.size(); y++){
        
        switch(y){
          case 0:
          a=1; b=2; c=3;
          case 1:
          a=2; b=3; c=0;
          case 2:
          a=3; b=0; c=1;

          if ((fumigaciones[y].total > fumigaciones[a].total) && (fumigaciones[y].total > fumigaciones[b].total) && (fumigaciones[y].total > fumigaciones[c].total)){
            yz=y;
          }
        }
     
      cout << "La mayor demanda de servicio es de: "<< fumigaciones[yz].descripcion << endl;
      cout << "El total vendido es de: Q." << grantotal << endl;

      // hago una pausa
      string empty;
      getchar();
      getline(cin, empty);
      return;
    }
	  catch (exception X){		
			cout<<"Error para abrir archivo"<<endl;			
			exit(1);
	  }
};
void menu(){
  char tecla;
  string empty;
  bool bandera=false;
  
  do
    {
        system("clear");
        cin.clear();
        cout << "Xterminio s.a" << endl;
        cout << "-----------" << endl << endl;
        cout << "\t1 .- Agregar Servicio" <<endl;
        cout << "\t2 .- Mostrar Reporte" <<endl;
        cout << "\t3 .- Salir" << endl << endl;
        cout << "Elije una opcion: ";
 
        cin >> tecla;
 
		switch(tecla)
    		{
		case '1':
		system("clear");
        grabar();
        break;
 
		case '2':
        system("clear");
        leer_archivo();
        break;      
      case '3':
	bandera=true;
	//exit(1);
	break;
 	default:
		system("clear");
		cout << "Opcion no valida.\a\n";
		getchar();
        getline(cin, empty);
	break;
		}
    }while(bandera!=true);
}

int main(){
  menu();
  return 0;
}


