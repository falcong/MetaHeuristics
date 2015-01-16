/*
 <moBitNeighbor.h>
 Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

 Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

 This software is governed by the CeCILL license under French law and
 abiding by the rules of distribution of free software.  You can  use,
 modify and/ or redistribute the software under the terms of the CeCILL
 license as circulated by CEA, CNRS and INRIA at the following URL
 "http://www.cecill.info".

 As a counterpart to the access to the source code and  rights to copy,
 modify and redistribute granted by the license, users are provided only
 with a limited warranty  and the software's author,  the holder of the
 economic rights,  and the successive licensors  have only  limited liability.

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

#ifndef _bitNeighbor_h
#define _bitNeighbor_h

#include <ga/eoBit.h>
#include <neighborhood/moBackableNeighbor.h>
#include <neighborhood/moIndexNeighbor.h>

/**
 * Neighbor related to a vector of Bit
 */
template< class Fitness >
class moBitNeighbor : public moBackableNeighbor<eoBit<Fitness> >, public moIndexNeighbor<eoBit<Fitness> >
{
    
public:
	typedef eoBit<Fitness> EOT;

	using moBackableNeighbor<EOT>::fitness;
	using moIndexNeighbor<EOT>::key;

        
	/**
	 * move the solution
	 * @param _solution the solution to move
	 */
	virtual void move(EOT & _solution) {

		_solution[key] = !_solution[key];
                cout << "Me muevo gente "<<key<<" "<<_solution<< endl;
		_solution.invalidate();   // only there for eoEvalFuncCounter !
  
	}

	/**
	 * move back the solution (useful for the evaluation by modif)
	 * @param _solution the solution to move back
	 */
	virtual void moveBack(EOT & _solution) {
		move(_solution);
	}

	/**
	 * return the class name
	 * @return the class name as a std::string
	 */
	virtual std::string className() const {
		return "moBitNeighbor";
	}

	/**
	 * Read object.\
     * Calls base class, just in case that one had something to do.
	 * The read and print methods should be compatible and have the same format.
	 * In principle, format is "plain": they just print a number
	 * @param _is a std::istream.
	 * @throw runtime_std::exception If a valid object can't be read.
	 */
	virtual void readFrom(std::istream& _is) {
		std::string fitness_str;
		int pos = _is.tellg();
		_is >> fitness_str;
		if (fitness_str == "INVALID") {
			throw std::runtime_error("invalid fitness");
		} else {
			Fitness repFit;
			_is.seekg(pos);
			_is >> repFit;
			_is >> key;
			fitness(repFit);
		}
	}

	/**
	 * Write object. Called printOn since it prints the object _on_ a stream.
	 * @param _os A std::ostream.
	 */
	virtual void printOn(std::ostream& _os) const {
		_os << fitness() << ' ' << key << std::endl;
	}
};

template< class Fitness >
class moPBitNeighbor : public moBackableNeighbor<eoBit<Fitness> >, public moIndexNeighbor<eoBit<Fitness> >
{
     
    
    private:
        int p;
public:
	typedef eoBit<Fitness> EOT;

	using moBackableNeighbor<EOT>::fitness;
	using moIndexNeighbor<EOT>::key;

        
        
        void setP(int _p) {
            p=_p;
        }
        
        
	/**
	 * move the solution
	 * @param _solution the solution to move
	 */       
        //setP(3);
	virtual void move(EOT & _solution) {

            int cont = 0;
            for (int i=0;i<_solution.size();i++) {
                if (_solution[i] == 1) {
                    cont++;
                }
            }
            
                                    cout << "contador "<< cont << endl;

              cin.get();                      
            bool completo = false;
            while (!completo) {
                bool paro = false;
                int i = 0;
                if (cont > p) {
                    while (!paro) {
                        srand(time(NULL));
                        int n = rand() % _solution.size();
                        cout << "valor del rand > "<< n <<"solucion n "<<_solution[n]<<" contador "<<cont<<" p "<<p<<endl;
                                                  
                        if (_solution[n] == 1) {
                            _solution[n] = 0;
                            cont--;
                        }
                        if (cont == p) {
                            paro = true;
                            completo = true;
                        }
                    }   
                }
                
                if (cont < p) {
                    while (!paro) {
                        srand(time(NULL));
                        int n = rand() % _solution.size();
                        cout << "valor del rand < "<< n << endl;
                        if (_solution[n] == 0) {
                            _solution[n] = 1;
                            cont++;
                        }
                        if (cont == p) {
                            paro = true;
                            completo = true;
                        }
                    }
                }
                
                if (cont == p) {
                    
                    completo = true;
                    /*while (!paro) {
                        srand(time(NULL));
                        int n = rand() % _solution.size();
                        if (_solution[n] == 0) {
                            _solution[n] = 1;
                            cont++;
                        } else {
                            _solution[n] = 0;
                            cont--;
                        }
                        
                    }*/
                }
            }
            
            cout << "Me muevo gente "<<key<<" "<<_solution<< endl;
            
	}

	/**
	 * move back the solution (useful for the evaluation by modif)
	 * @param _solution the solution to move back
	 */
	virtual void moveBack(EOT & _solution) {
		move(_solution);
	}

	/**
	 * return the class name
	 * @return the class name as a std::string
	 */
	virtual std::string className() const {
		return "moBitNeighbor";
	}

	/**
	 * Read object.\
     * Calls base class, just in case that one had something to do.
	 * The read and print methods should be compatible and have the same format.
	 * In principle, format is "plain": they just print a number
	 * @param _is a std::istream.
	 * @throw runtime_std::exception If a valid object can't be read.
	 */
	virtual void readFrom(std::istream& _is) {
		std::string fitness_str;
		int pos = _is.tellg();
		_is >> fitness_str;
		if (fitness_str == "INVALID") {
			throw std::runtime_error("invalid fitness");
		} else {
			Fitness repFit;
			_is.seekg(pos);
			_is >> repFit;
			_is >> key;
			fitness(repFit);
		}
	}

	/**
	 * Write object. Called printOn since it prints the object _on_ a stream.
	 * @param _os A std::ostream.
	 */
	virtual void printOn(std::ostream& _os) const {
		_os << fitness() << ' ' << key << std::endl;
	}
};


#endif
