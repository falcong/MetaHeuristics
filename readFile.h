#include <vector>


using namespace std;

//Creo mi clase para mantener datos del fichero
class datosFichero {
private:
  
     int almacenes, clientes;
     vector< vector< float > > distancias;
     vector< int > almacen_cap;
     vector< int > almacen_cost;
     vector< int > demanda_clientes;
  
    char* substr(char* cadena, int comienzo, int longitud=0)
    {
	if (longitud == 0) 
	    longitud = strlen(cadena)-comienzo;
    
	char *nuevo = (char*)malloc(sizeof(char) * (longitud+1));
	nuevo[longitud] = '\0';
	strncpy(nuevo, cadena + comienzo, longitud);
    
	return nuevo;
    }
    
    
    
public:
  
  
     inline int getAlmacenes() {return almacenes;}
     inline int getClientes() {return clientes;}
     inline vector< vector < float > > getDistancias() {return distancias;}   
     inline vector<int> getAlmacen_cap() {return almacen_cap;}
     inline vector<int> getAlmacen_cost() {return almacen_cost;}
     inline vector<int> getDemanda_clientes() {return demanda_clientes;}
 
    
    void readData (char **argv) {
      
      char c;
      const int buf = 1024;
	
	FILE *fichero = fopen(argv[1], "r");
	if (fichero == NULL) {
		perror ("Error al abrir el fichero");
		exit(-1);
	} else {
		fscanf(fichero, "%d", &almacenes);
		fscanf(fichero, "%d\n", &clientes);		


		char cadena[buf];
		int index_cost, index_cap;
		for (int i=0; i<almacenes; i++) {
			fgets(cadena, buf, fichero);				
			int index_cap = 0, index_cost = 0;
			bool primerEspacio = true;
			for (int j=0; j<strlen(cadena); j++) {
			  
				if ((cadena[j] == ' ') && primerEspacio ){	  
					index_cap = j;
					primerEspacio = false;
				}
				if (cadena[j] == '.'){
					index_cost = j;
				}
					
			}
			
			almacen_cap.push_back(atoi(substr(cadena, 0, index_cap)));
			//cout <<"Hasta aqui llego " << almacenes << clientes <<atoi(substr(cadena, 0, index_cap)) << endl;
			almacen_cost.push_back(atoi(substr(cadena, index_cap+1, index_cost)));	
			//fscanf(fichero, "%c\n", &c); //Leo caracter final de línea
			
			
		}
		
		for (int i=0; i<clientes;i++) {	  
		  
		  int aux = 0;
		  float aux2 = 0;
		  fscanf(fichero, "%d\n", &aux);
		  demanda_clientes.push_back(aux);
		  
		  vector <float> filas;
		  for (int j=0; j<almacenes; j++) {
		    fscanf(fichero, "%f", &aux2);
		    filas.push_back(aux2);
		    //cout <<"Hasta aqui llego " << almacenes << clientes << endl;
		  }
		  distancias.push_back(filas);
		  fscanf(fichero, "%c\n", &c); //Leo caracter final de línea
		}
	}
	fclose(fichero);

	printf ("%i ", almacenes);
	printf ("%i\n",clientes);
	for (int i=0; i<almacenes; i++) {
		printf("%d ", almacen_cap[i]);
		printf("%d", almacen_cost[i]);
		printf("\n");
	}
	for (int i=0;i<clientes;i++){  
	  printf ("%d\n", demanda_clientes[i]);
	  for (int j=0; j<almacenes; j++) {
	     printf("%f ", distancias[i][j]);
	  }
	  printf("\n");
	}
	
	printf ("\n\n");
     
      }	

};
