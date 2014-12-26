/*
<oneMaxEval.h>
Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  ue,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.
The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.

ParadisEO WebSite : http://paradiseo.gforge.inria.fr
Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef _oneMaxEval_h
#define _oneMaxEval_h

#include <eoEvalFunc.h>
#include <limits.h>

/**
 * Full evaluation Function for OneMax problem
 */
/*template< class EOT >
class oneMaxEval : public eoEvalFunc<EOT>
{
public:

};*/

/**
 * Full evaluation Function for OneMax problem
 */



template< class EOT >
class oneMaxEvalPmediana : public eoEvalFunc<EOT> {
    private:
  
     int almacenes, clientes, pmediana;
     vector< vector< float > > distancias;
     vector< int > almacen_cap;
     vector< int > almacen_cost;
     vector< int > demanda_clientes; 
  
public:
  
  
    void getPmediana (int p) {pmediana = p;}
     void operator<< (datosFichero dF) {
       
       almacenes = dF.getAlmacenes();
       clientes = dF.getClientes();
       
       distancias = dF.getDistancias();
       almacen_cap = dF.getAlmacen_cap();
       almacen_cost = dF.getAlmacen_cost();
       demanda_clientes = dF.getDemanda_clientes();
       
     }
     
     bool countAlmacenes (EOT& _sol) {
         int contador = 0;
         for (int i=0; i<almacenes;i++) {
             if (_sol[i] == 1) {
                 contador++;
             }
         }
         if (contador == pmediana) {
             return true;
         } else {
             return false;
         }
     }
     
     void operator() (EOT& _sol) { 

      /*//FUNCION OBJETIVO --REVISAR
      int valor = 0, minValor = 999999999, minDistancia = 0;
      for (int i= 0;i<almacenes;i++) {
	if (_sol[i] == 1) {
	  valor = valor + almacen_cost[i];
	  for (int j=0; j<clientes;j++) {
	    valor = valor + distancias[i][j];
	      if ()
	    }
	  }
	}
      }*/
      
      float valorT = 0,  minDistancia = UINT_MAX;
      int index_i = 0, index_j = 0;
      //bool existeValor = false;
      
      for (int i=0; i<clientes;i++) {
	for (int j=0;j<almacenes;j++) {
	  if ((_sol[j] == 1) && (countAlmacenes(_sol))) {
	    if (distancias[i][j] <= minDistancia) {
	      //cout <<"Entro porque soy menor"<< endl;
              //existeValor = true;
	      minDistancia = distancias[i][j];
	      index_i = i;
	      index_j = j;
	    }
	  }
	}
	minDistancia = UINT_MAX;
        //if (existeValor) {
        valorT += distancias[index_i][index_j];
           // existeValor = false;
       // }
	
	//cout << "Este es mi valor actual: " << valorT << " Relativo: " << distancias[index_i][index_j]<<endl;
      }
      
      /*for (int i=0;i<almacenes;i++) {
	     if (_sol[i] == 1) {
	        valorT += almacen_cost[i];
	       //cout << "Este es mi valor actual en almacenes: " << valorT << " Añadido: " << almacen_cost[i] << " en indice: "<< i <<endl;
	     }
      }*/
    
      //cout << "Vamos niñoooo " << valorT << endl;
      
      //cout << "hola " << valorT*-1 << endl;
      _sol.fitness(valorT); //SOLUCIONADO**//El hill Climbing esta máximizando y yo lo que necesito es minimizar los costos, por lo tanto, multiplico por -1
      cout << _sol << endl;
      

  
    }    
};



template< class EOT >
class oneMaxEval : public eoEvalFunc<EOT>
{
  
private:
  
     int almacenes, clientes;
     vector< vector< float > > distancias;
     vector< int > almacen_cap;
     vector< int > almacen_cost;
     vector< int > demanda_clientes; 
  
public:
  
  
     void operator<< (datosFichero dF) {
       
       almacenes = dF.getAlmacenes();
       clientes = dF.getClientes();
       
       distancias = dF.getDistancias();
       almacen_cap = dF.getAlmacen_cap();
       almacen_cost = dF.getAlmacen_cost();
       demanda_clientes = dF.getDemanda_clientes();
       
     }

	
      void operator() (EOT& _sol) { 

      /*//FUNCION OBJETIVO --REVISAR
      int valor = 0, minValor = 999999999, minDistancia = 0;
      for (int i= 0;i<almacenes;i++) {
	if (_sol[i] == 1) {
	  valor = valor + almacen_cost[i];
	  for (int j=0; j<clientes;j++) {
	    valor = valor + distancias[i][j];
	      if ()
	    }
	  }
	}
      }*/
      
      float valorT = 0,  minDistancia = UINT_MAX, index_i = 0, index_j = 0;
      for (int i=0; i<clientes;i++) {
	for (int j=0;j<almacenes;j++) {
	  if (_sol[j] == 1) {
	    if (distancias[i][j] <= minDistancia) {
	      //cout <<"Entro porque soy menor"<< endl;
	      minDistancia = distancias[i][j];
	      index_i = i;
	      index_j = j;
	    }
	  }
	}
	minDistancia = UINT_MAX;
	valorT += distancias[index_i][index_j];
	//cout << "Este es mi valor actual: " << valorT << " Relativo: " << distancias[index_i][index_j]<<endl;
      }
      
      for (int i=0;i<almacenes;i++) {
	     if (_sol[i] == 1) {
	        valorT += almacen_cost[i];
	       //cout << "Este es mi valor actual en almacenes: " << valorT << " Añadido: " << almacen_cost[i] << " en indice: "<< i <<endl;
	     }
      }
    
      //cout << "Vamos niñoooo " << valorT << endl;
      
      //cout << "hola " << valorT*-1 << endl;
      _sol.fitness(valorT); //SOLUCIONADO**//El hill Climbing esta máximizando y yo lo que necesito es minimizar los costos, por lo tanto, multiplico por -1
      cout << _sol << endl;
      

  
    }    
    /**
    * Count the number of 1 in a bitString
    * @param _sol the solution to evaluate
    */
    /*void operator() (EOT& _sol) {
        unsigned int sum = 0;
        for (unsigned int i = 0; i < _sol.size(); i++)
            sum += _sol[i];
        _sol.fitness(sum);
    }*/
 

};


#endif
