/**
 * @file diccionario.h
 * @author Profesores de ED y Salvador Romero Cortés
 */
#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <string>
#include <list>
#include <cassert>

using namespace std;

/**
 * @brief Tipo elemento que define el diccionario. 
 * @e T es el tipo de dato asociado a una clave que no se repite (DNI p.ej.) 
 * @e list<U> es una lista de datos (string p.ej) asociados a la clave de tipo T. El diccionario está ordenado de menor a mayor clave.
*/
template <class T, class U>
struct data
{
	T clave;
	list<U> info_asoci;
};

/**
 * @brief Comparador de datos. Ordena 2 registros de acuerdo a la clave de tipo T. Puede usarse como un funtor.
 * @param d1 uno de los diccionarios que se comparan
 * @param d2 el otro diccionario con el que se compara
 */
template <class T, class U>
bool operator<(const data<T, U> &d1, const data<T, U> &d2)
{
	if (d1.clave < d2.clave)
		return true;
	return false;
}

/**
 * @brief funcion para saber si un elemento está dentro de una lista
 * @param lista la lista donde se busca
 * @param elemento el elemento a buscar
 * @return true si se encuentra
 * 		   false si no se encuentra
 */
template <typename U>
bool esta_dentro(const list<U> &lista, const U &elemento)
{
	typename list<U>::const_iterator it;
	bool encontrado = false;
	for (it = lista.cbegin(); it != lista.cend() && !encontrado; ++it)
	{
		if ((*it) == elemento)
			encontrado = true;
	}
	return encontrado;
}

/**
 * @brief Un diccionario es una lista de datos de los definidos anteriormente.  Se añaden 2 funciones privadas que hacen más facil la implementación de algunos operadores o funciones de la parte pública. 
 * Copiar copia un diccioario en otro y borrar elimina todos los elementos de un diccionario. La implementación de copiar puede hacerse usando iteradores o directamente usando la función assign.
* @warning Cuidado porque se manejan listas de listas.
*/
template <class T, class U>
class Diccionario
{
private:
	list<data<T, U>> datos;

	/**
	 * @brief metodo para copiar un diccionario @e D en @e this
	 * @param D el diccionario que se copia
	 */
	void Copiar(const Diccionario<T, U> &D)
	{
		/*typename list<data<T,U> >::const_iterator it_d;
			   typename list<data<T,U> >::iterator it=this->datos.begin();*/

		datos.assign(D.datos.begin(), D.datos.end());
		/*for (it_d=D.datos.begin(); it_d!=D.datos.end();++it_d,++it){
				     this->datos.insert(it,*it_d);
				     
			   }*/
	}

	/**
	 * @brief metodo para borrar los elementos del diccionario
	 */
	void Borrar()
	{

		this->datos.erase(datos.begin(), datos.end());
	}

public:
	/**
	 * @brief Constructor por defecto
	 */
	Diccionario() : datos(list<data<T, U>>()) {}

	/**
	 * @brief Constructor de copias
	 * @param D el diccionario que se copia
	 * */
	Diccionario(const Diccionario &D)
	{
		Copiar(D);
	}

	/**
	 * @brief  Destructor
	 **/
	~Diccionario() {}

	/**
	 * @brief Operador de asignación
	 * @param D el diccionario que se asigna a @e this
	 * @return una referencia al objeto
	 * */
	Diccionario<T, U> &operator=(const Diccionario<T, U> &D)
	{
		if (this != &D)
		{
			Borrar();
			Copiar(D);
		}
		return *this;
	}

	/**
	 * @brief Busca la clave p en el diccionario. 
	 * @return Si está devuelve un iterador a dónde está clave. Si no está, devuelve end() y deja el iterador de salida apuntando al sitio dónde debería estar la clave
	*/
	bool Esta_Clave(const T &p, typename list<data<T, U>>::iterator &it_out)
	{

		if (datos.size() > 0)
		{

			typename list<data<T, U>>::iterator it;

			for (it = datos.begin(); it != datos.end(); ++it)
			{
				if ((*it).clave == p)
				{
					it_out = it;
					return true;
				}
				else if ((*it).clave > p)
				{
					it_out = it;
					return false;
				}
			}

			it_out = it;
			return false;
		}
		else
		{
			it_out = datos.end();
			return false;
		}
	}

	/**
	 * @brief Inserta un nuevo registro en el diccionario. Lo hace a través de la clave e inserta la lista con toda la información asociada a esa clave. 
	 * @warning Si el diccionario no estuviera ordenado habría que usar la función sort() 
	 * @param clave la clave de la nueva entrada
	 * @param info la lista de definiciones asocida a la @e clave
	 */
	void Insertar(const T &clave, const list<U> &info)
	{

		typename list<data<T, U>>::iterator it;

		if (!Esta_Clave(clave, it))
		{
			data<T, U> p;
			p.clave = clave;
			p.info_asoci = info;

			datos.insert(it, p);
		}
	}

	/**
	 * @brief Añade una nueva informacion asocida a una clave que está en el diccionario la nueva información se inserta al final de la lista de información. Si no esta la clave la inserta y añade la informacion asociada. 
	*/
	void AddSignificado_Palabra(const U &s, const T &p)
	{
		typename list<data<T, U>>::iterator it;
		if (!Esta_Clave(p, it))
		{
			list<U> lista_temp;
			lista_temp.insert(lista_temp.begin(), s);
			data<T, U> nuevo = {p, lista_temp};
			datos.insert(it, nuevo);
		}

		//Insertamos el siginificado al final
		(*it).info_asoci.insert((*it).info_asoci.end(), s);
	}

	/**
	 * @brief Devuelve la información (una lista) asociada a una clave p. Podrían 
		 haberse definido operator[] como
		 data<T,U> & operator[](int pos){ return datos.at(pos);}
		 const data<T,U> & operator[](int pos)const { return datos.at(pos);}
	* @param p la clave del diccionario
	* @return una lista con las definiciones	
	*/
	list<U> getInfo_Asoc(const T &p)
	{
		typename list<data<T, U>>::iterator it;

		if (!Esta_Clave(p, it))
		{
			return list<U>();
		}
		else
		{
			return (*it).info_asoci;
		}
	}

	/**
	 * @brief metodo que devuelve el tamaño del diccionario
	 * @return el tamaño del diccionario
	 **/

	int size() const
	{
		return datos.size();
	}

	//CLASES ITERADORAS
	/**
	 * @brief clase iteradora que sirve para recorrer el diccionario, versión no constante
	 */
	class iterator
	{
	private:
		typename list<data<T, U>>::iterator it;
		/**
			 * @brief constructor privado del iterador
			 * @param otro un interador de la clase list de la stl
			 */
		iterator(typename list<data<T, U>>::iterator otro) : it(otro) {}

	public:
		/**
		 * @brief constructor por defecto
		 */
		iterator() = default;

		/**
		 * @brief constructor de copia
		 * @param otro el objeto que se copia
		 */
		iterator(const iterator &otro) : it(otro.it) {}

		/**
		 * @brief operador para continuar en la iteracion, es el operador prefijo
		 * @return una referencia al objeto
		 */

		iterator &operator++() { return ++it; }
		/**
		 * @brief operador para continuar en la iteracion, es el operador posfijo
		 * @return una copia del objeto
		 */
		iterator operator++(int) { return it++; }

		/**
		 * @brief operador de asignacion
		 * @param otro el que se le asigna
		 * @return una referencia al objeto actual
		 */
		iterator &operator=(const iterator &otro)
		{
			it = otro.it;
			return *this;
		}

		/**
		 * @brief operador de consulta
		 * @return el elemento de la posicion del iterador
		 */
		data<T, U> &operator*() { return (*it); }
		/**
		 * @brief operador de desigualdad de iteradores no constantes
		 * @param otro el segundo iterador con el que se compara
		 * @return true si uno != otro
		 * 		   false si uno == otro
		 */
		bool operator!=(const typename Diccionario<T, U>::iterator &otro)
		{
			return this->it != otro.it;
		}

		friend class Diccionario<T, U>;
	};

	/**
	 * @brief clase iteradora que sirve para recorrer el diccionario, versión constante
	 */
	class const_iterator
	{
	private:
		typename list<data<T, U>>::const_iterator it;
		/**
			 * @brief constructor privado del iterador
			 * @param otro un interador de la clase list de la stl
			 */
		const_iterator(typename list<data<T, U>>::const_iterator otro) : it(otro) {}

	public:
		/**
		 * @brief constructor por defecto
		 */
		const_iterator() = default;

		/**
		 * @brief constructor de copia
		 * @param otro el objeto que se copia
		 */
		const_iterator(const const_iterator &otro) : it(otro.it) {}

		/**
		 * @brief operador para continuar en la iteracion, es el operador prefijo
		 * @return una referencia al objeto
		 */

		const_iterator &operator++()
		{
			it++;
			return *this;
		}
		/**
		 * @brief operador para continuar en la iteracion, es el operador posfijo
		 * @return una copia del objeto
		 */
		const_iterator operator++(int) { return it++; }

		/**
		 * @brief operador de asignacion
		 * @param otro el que se le asigna
		 * @return una referencia al objeto actual
		 */
		const_iterator &operator=(const const_iterator &otro)
		{
			it = otro.it;
			return *this;
		}

		/**
		 * @brief operador de consulta
		 * @return el elemento de la posicion del iterador
		 */
		data<T, U> operator*() const { return (*it); };

		/**
		 * @brief operador de desigualdad de iteradores constantes
		 * @param otro el segundo iterador con el que se compara
		 * @return true si uno != otro
		 * 		   false si uno == otro
		 */
		bool operator!=(const typename Diccionario<T, U>::const_iterator &otro)
		{
			return this->it != otro.it;
		}
		friend class Diccionario<T, U>;
	};

	/*Funciones begin y end asociadas al diccionario*/
	/**
	 * @brief método begin no constante
	 * @return una referencia al begin no constante de @e datos
	 */
	typename Diccionario<T, U>::iterator &begin()
	{
		return Diccionario<T, U>::iterator(datos.begin());
	}
	/**
	 * @brief método end no constante
	 * @return una referencia al end no constante de @e datos
	 */
	typename Diccionario<T, U>::iterator &end()
	{
		return Diccionario<T, U>::iterator(datos.end());
	}
	/**
	 * @brief método begin constante
	 * @return un iterador diccionario que apunta al begin constante de @e datos
	 */
	typename Diccionario<T, U>::const_iterator cbegin() const
	{
		return Diccionario<T, U>::const_iterator(datos.cbegin());
	}
	/**
	 * @brief método end constante
	 * @return un iterador diccionario que apunta al end constante de @e datos
	 */
	typename Diccionario<T, U>::const_iterator cend() const
	{
		return Diccionario<T, U>::const_iterator(datos.cend());
	}

	/**
	 * @brief metodo para eliminar un elemento del diccionario por su clave
	 * @param clave la clave del elemento que se borra
	 * @return true si se ha podido eliminar
	 * 		   false si no esta en el diccionario y no se ha podido eliminar
	 */
	bool borrar_por_clave(const T &clave)
	{
		//primero comprobamos que realmente esté la clave en el diccionario
		typename list<data<T, U>>::iterator posicion;
		bool esta_clave = Esta_Clave(clave, posicion);
		if (esta_clave)
		{
			datos.erase(posicion);
		}
		return esta_clave;
	}

	/**
	 * @brief metodo para unir dos diccionarios, el objeto llamador no se modifica
	 * @param nuevo el diccionario que se une al objeto que llama al metodo
	 * @return la union de diccionarios
	 */
	Diccionario<T, U> union_dic(Diccionario<T, U> nuevo)
	{
		Diccionario<T, U> aux(*this);
		typename list<data<U, T>>::iterator it_aux;
		for (auto it = nuevo.cbegin(); it != nuevo.cend(); ++it)
		{
			typename Diccionario<T, U>::const_iterator it_dic(it);
			T clave = nuevo.getClave(it_dic);
			list<U> definiciones(nuevo.getInfo_Asoc(clave));
			if (aux.Esta_Clave(clave, it_aux))
			{
				for (typename list<U>::const_iterator iterador_def = definiciones.cbegin(); iterador_def != definiciones.cend(); ++iterador_def)
				{
					if (!esta_dentro((*it_aux).info_asoci, (*iterador_def)))
						aux.AddSignificado_Palabra((*iterador_def), clave);
				}
			}
			else
			{
				aux.Insertar(clave, nuevo.getInfo_Asoc(clave));
			}
		}
		return aux;
	}

	/**
	 * @brief metodo que devuelve los elementos dentro de un rango de claves
	 * @param inicio clave desde la que se empieza
	 * @param fin ultima clave del rango
	 * @return subdiccionario de las claves entre @e inicio y @e fin
	 */
	Diccionario<T, U> subdiccionario_entre(const T &inicio, const T &fin)
	{
		typename list<data<T, U>>::iterator inicio_it;
		typename list<data<T, U>>::iterator fin_it;
		assert(Esta_Clave(inicio, inicio_it));
		assert(Esta_Clave(fin, fin_it));
		Diccionario<T, U> nuevo;
		for (typename list<data<T, U>>::iterator it = inicio_it; it != fin_it; ++it)
		{
			nuevo.Insertar((*it).clave, (*it).info_asoci);
		}
		nuevo.Insertar((*fin_it).clave, (*fin_it).info_asoci);
		return nuevo;
	}

	/**
	 * @brief metodo para hacer la diferencia de diccionarios, el diccionario llamador no se modifica
	 * @param otro diccionario que se le resta al actual
	 * @return diccionario diferencia
	 */
	Diccionario<T, U> diferencia(const Diccionario<T, U> &otro)
	{
		Diccionario<T, U> resultado(*this);
		for (typename Diccionario<T, U>::const_iterator it_dic = otro.cbegin(); it_dic != otro.cend(); ++it_dic)
		{
			typename list<data<T, U>>::iterator it_basura;
			T clave = otro.getClave(it_dic);
			if (Esta_Clave(clave, it_basura))
			{
				resultado.borrar_por_clave(clave);
			}
		}
		return resultado;
	}

	/**
	 * @brief metodo que devuelve la clave en la posicion del iterador del diccionario
	 * @param it posicion de la clave
	 * @return la clave
	 */
	T getClave(const iterator &it) const { return (*it).clave; }

	/**
	 * @brief metodo que devuelve la clave en la posicion del iterador del diccionario (version it constante)
	 * @param it posicion de la clave (constante)
	 * @return la clave
	 */
	T getClave(const const_iterator &it) const { return (*it).clave; }
};

#endif
