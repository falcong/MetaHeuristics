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

/*Next class have necessary code for algorithm HC y SA. It have p-median evaluation function*/
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
         float valorT = 0,  minDistancia = UINT_MAX;
         int index_i = 0, index_j = 0;
         if (pAlmacenes(_sol)) { 
            for (int i=0; i<clientes;i++) {
               for (int j=0;j<almacenes;j++) {
                  if (_sol[j] == 1) {
                     if (distancias[i][j] <= minDistancia) {
                        minDistancia = distancias[i][j];
                        index_i = i;
                        index_j = j;
                     }
                  }
               }
               minDistancia = UINT_MAX;
               valorT += distancias[index_i][index_j];
            }
         } else {
         valorT = UINT_MAX;
      }
      _sol.fitness(valorT); 
      //cout << _sol << endl;
  
     }    
};

/*Next class have necessary code for algorithm HC y SA. It have SPLP/UFLP evaluation function*/
template< class EOT >
class oneMaxEval : public eoEvalFunc<EOT> {
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
         float valorT = 0,  minDistancia = UINT_MAX, index_i = 0, index_j = 0;
         for (int i=0; i<clientes;i++) {
	    for (int j=0;j<almacenes;j++) {
	       if (_sol[j] == 1) {
	          if (distancias[i][j] <= minDistancia) {
	             minDistancia = distancias[i][j];
	             index_i = i;
	             index_j = j;
	          }
	       }
	    }
	    minDistancia = UINT_MAX;
	    valorT += distancias[index_i][index_j];
         }
         for (int i=0;i<almacenes;i++) {
	    if (_sol[i] == 1) {
	       valorT += almacen_cost[i];
	    }
         }
         _sol.fitness(valorT);
         //cout << _sol << endl;
      }
};

/*Next class have necessary code for algorithm HC y SA. It have p-center evaluation function*/
template< class EOT >
class oneMaxEvalPcentro : public eoEvalFunc<EOT> {
   private:
      int almacenes, clientes, pcentro;
      vector< vector< float > > distancias;
      vector< int > almacen_cap;
      vector< int > almacen_cost;
      vector< int > demanda_clientes; 
  
   public:
       
       int getAlmacenes () {return almacenes;}
       int getPcentro () {return pcentro;} 
      void setPcentro (int p) {pcentro = p;}
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
         if (contador == pcentro) {
             return true;
         } else {
             return false;
         }
      }
     
      void operator() (EOT& _sol) { 
         float valorT = 0,  minDistancia = UINT_MAX, maxDistancia = 0;
         int index_i = 0, index_j = 0;
         
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
            
            if (distancias[index_i][index_j] > maxDistancia) {
                maxDistancia = distancias[index_i][index_j];
            }
            //maxDistancia = 0;
            valorT = maxDistancia;

         }
         maxDistancia = 0;
        
        } else {
          valorT = UINT_MAX;
      }
      _sol.fitness(valorT); 
      //cout << _sol << endl;    
    }    
};

#endif
