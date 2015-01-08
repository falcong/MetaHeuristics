/*
<moOneMaxIncrEval.h>
Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

Sebastien Verel, Arnaud Liefooghe, Jeremie Humeau

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

#ifndef _moOneMaxIncrEval_H
#define _moOneMaxIncrEval_H

#include <eval/moEval.h>

/**
 * Incremental evaluation Function for the OneMax problem
 */
template< class Neighbor >
class moOneMaxIncrEval : public moEval<Neighbor>
{
public:
    typedef typename Neighbor::EOT EOT;

    /*
    * incremental evaluation of the neighbor for the oneMax problem
    * @param _solution the solution to move (bit string)
    * @param _neighbor the neighbor to consider (of type moBitNeigbor)
    */
    virtual void operator()(EOT & _solution, Neighbor & _neighbor) {
        if (_solution[_neighbor.index()] == 0)
            _neighbor.fitness(_solution.fitness() + 1);
        else
            _neighbor.fitness(_solution.fitness() - 1);
        
        cout << _solution << endl;
    }

};


template< class Neighbor >
class moOneMaxIncrEvalCustom : public moEval<Neighbor> {
    
    private :
      int almacenes, clientes, pmediana, pcentro;
      vector< vector< float > > distancias;
      vector< int > almacen_cap;
      vector< int > almacen_cost;
      vector< int > demanda_clientes;
        
public:
    typedef typename Neighbor::EOT EOT;   
    
    int getPmediana () {return pmediana;}
    void setPmediana (int p) {pmediana = p;}
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
    /*
    * incremental evaluation of the neighbor for the oneMax problem
    * @param _solution the solution to move (bit string)
    * @param _neighbor the neighbor to consider (of type moBitNeigbor)
    */
    virtual void operator()(EOT & _solution, Neighbor & _neighbor) {
        /*if (_solution[_neighbor.index()] == 0)
            _neighbor.fitness(_solution.fitness() + 1);
        else
            _neighbor.fitness(_solution.fitness() - 1);*/
        
        if (pAlmacenes(_solution)) {
            _neighbor.fitness(_solution.fitness() + 1);
            cout << "entro bien"<< endl;
        } else {
            _neighbor.fitness(_solution.fitness() - 1);
            
        }
        cout << _solution << endl;
    }
};

#endif

