/*
<queenEval.h>
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

#ifndef _queenEval_h
#define _queenEval_h

#include <eoEvalFunc.h>
#include <limits.h>
#include </home/fizco/git/MetaHeuristics/readFile.h>


//class dataFile;

/**
 * Full evaluation function for QUEEN problem
 */

template< class EOT >
class queenEvalPmediana : public eoEvalFunc<EOT> {
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
     
     bool pAlmacenes (EOT& _sol) {
         int contador = 0;
         for (int i=0; i<almacenes;i++) {
             if (_sol[i] != 0) {
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
      
      if (pAlmacenes(_sol)) {
          
        for (int i=0; i<clientes;i++) {
            for (int j=0;j<almacenes;j++) {
                if (_sol[j] == 1) {
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
      } else {
          //cout <<"Entro aqui por"<<endl;
          valorT = UINT_MAX;
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
class queenEval : public eoEvalFunc<EOT>
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

      _sol.fitness(valorT); //El hill Climbing esta máximizando y yo lo que necesito es minimizar los costos, por lo tanto, multiplico por -1
      //cout << _sol << endl;



    }
/*public:

	/**
	 * Count number of threat
	 * @param _queen a solution
	 */
    /*void operator()(EOT& _queen){
    	  unsigned int fit=0;
    	  for(unsigned int i=0; i<_queen.size()-1; i++)
    		  for(unsigned int j=i+1; j< _queen.size(); j++)
    			  if(((unsigned int)_queen[i]+j-i == (unsigned int)_queen[j]) || ((unsigned int)_queen[i]+i-j == (unsigned int)_queen[j]))
    				  fit++;
    	  _queen.fitness(fit);*/
   /* }*/
};

#endif
