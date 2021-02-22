/**
 * @file guiatlf.h 
 * @brief Archivo con las declaraciones y las definiciones de los métodos de la guía telefónica
 * @author Profesores de ED y Salvador Romero Cortés
 */
#ifndef _GUIA_TLF_H
#define _GUIA_TLF_H
#include <map>
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief sobrecarga del operador >> para poder leer una lista
 * @param is el flujo de donde se lee
 * @param d la lista donde se guarda lo leído
 * @return una referencia al flujo
 */
istream &operator>>(istream &is, pair<string, string> &d)
{

	getline(is, d.first, '\t');
	getline(is, d.second);
	return is;
}

/**
 * @brief clase Guía telefónica, representa una guia de teléfonos. Se implementa a través de un map
 */
class Guia_Tlf
{
private:
	map<string, string> datos; //si admites que haya nombres repetidos tendr�as que usar un
							   //multimap
	
public:
	Guia_Tlf() = default;
	Guia_Tlf(const Guia_Tlf & gt):datos(gt.datos){}
	~Guia_Tlf() = default;
	Guia_Tlf & operator=(const Guia_Tlf & gt) = default;
	/**
	 @brief Acceso a un elemento
	@param nombre: nombre del elemento  elemento acceder
	@return devuelve el valor asociado a un nombre, es decir el teléfono
*/
	string &operator[](const string &nombre)
	{
		return datos[nombre];
	}

	/**
	 * @brief Acceso al teléfono
	 * @param nombre el nombre del cual hay que buscar su número
	 * @return el teléfono asociado a @e nombre
	 */
	string gettelefono(const string &nombre)
	{
		map<string, string>::iterator it = datos.find(nombre);
		if (it == datos.end())
			return string("");
		else
			return it->second;
	}

	/**
	 @brief Insert un nuevo telefono 
		@param nombre: nombre clave del nuevo telefono
		@param tlf: numero de telefono
		@return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o false en caso contrario
	*/
	pair<map<string, string>::iterator, bool> insert(string nombre, string tlf)
	{
		pair<string, string> p(nombre, tlf);
		pair<map<string, string>::iterator, bool> ret;

		ret = datos.insert(p);
		return ret;
	}

	/**
	 @brief Insert un nuevo telefono 
	@param p: pair con el nombre y el telefono asociado		
	@return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o false en caso contrario
	*/
	pair<map<string, string>::iterator, bool> insert(pair<string, string> p)
	{

		pair<map<string, string>::iterator, bool> ret;

		ret = datos.insert(p);
		return ret;
	}

	/**
	 @brief Borrar un telefono
	@param nombre: nombre que se quiere borrar
	@note: en caso de que fuese un multimap borraria todos con ese nombre
*/
	void borrar(const string &nombre)
	{
		map<string, string>::iterator itlow = datos.lower_bound(nombre);   //el primero que tiene dicho nombre
		map<string, string>::iterator itupper = datos.upper_bound(nombre); //el primero que ya no tiene dicho nombre
		datos.erase(itlow, itupper);									   //borramos todos aquellos que tiene dicho nombre
	}

	/**
	 @brief Borrar un telefono
	@param nombre: nombre que se quiere borrar y telefono asociado
	@note: esta funcion nos permite borrar solamente aquel que coincida en nombre y tlf
*/
	//con map siempre hay uno con multimap puede existir mas de uno
	void borrar(const string &nombre, const string &tlf)
	{
		map<string, string>::iterator itlow = datos.lower_bound(nombre);   //el primero que tiene dicho nombre
		map<string, string>::iterator itupper = datos.upper_bound(nombre); //el primero que ya no tiene dicho nombre
		map<string, string>::iterator it;
		bool salir = false;
		for (it = itlow; it != itupper && !salir; ++it)
		{
			if (it->second == tlf)
			{
				datos.erase(it);
				salir = true;
			}
		}
	}
	/**
	 @brief  Numero de telefonos 
	@return el numero de telefonos asociados
	*/
	int size() const
	{
		return datos.size();
	}
	/**
	 @brief Contabiliza cuantos telefonos tenemos asociados a un nombre
	@param nombre: nombre sobre el que queremos consultar
	@return numero de telefonos asociados a un nombre
	
	*/
	//al ser un map debe de ser 0 o 1. Si fuese un multimap podr�amos tener mas de uno
	unsigned int contabiliza(const string &nombre)
	{
		return datos.count(nombre);
	}

	/**
		      @brief Limpia la guia
		     */
	void clear()
	{
		datos.clear();
	}
	/**
		      @brief Union de guias de telefonos
		      @param g: guia que se une
		      @return: una nueva guia resultado de unir el objeto al que apunta this y g
		    */
	Guia_Tlf operator+(const Guia_Tlf &g)
	{
		Guia_Tlf aux(*this);
		map<string, string>::const_iterator it;
		for (it = g.datos.begin(); it != g.datos.end(); ++it)
		{
			aux.insert(it->first, it->second);
		}
		return aux;
	}

	/**
		      @brief Diferencia de guias de telefonos
		      @param g: guia que se une
		      @return: una nueva guia resultado de la diferencia del objeto al que apunta this y g
		    */
	Guia_Tlf operator-(const Guia_Tlf &g)
	{
		Guia_Tlf aux(*this);
		map<string, string>::const_iterator it;
		for (it = g.datos.begin(); it != g.datos.end(); ++it)
		{
			aux.borrar(it->first, it->second);
		}
		return aux;
	}

	/**
		      @brief Escritura de la guia de telefonos
		      @param os: flujo de salida. Es MODIFICADO
		      @param g: guia de telefonos que se escribe
		      @return el flujo de salida
		     */

	friend ostream &operator<<(ostream &os, Guia_Tlf &g)
	{
		map<string, string>::iterator it;
		for (it = g.datos.begin(); it != g.datos.end(); ++it)
		{
			os << it->first << "\t" << it->second << endl;
		}
		return os;
	}

	/**
		      @brief Lectura de  la guia de telefonos
		      @param is: flujo de entrada. ES MODIFICADO
		      @param g: guia de telefonos. ES MODIFICADO
		      @return el flujo de entrada
		    */

	friend istream &operator>>(istream &is, Guia_Tlf &g)
	{
		pair<string, string> p;
		Guia_Tlf aux;

		while (is >> p)
		{
			aux.insert(p);
		}
		g = aux;
		return is;
	}

	/**
	 * @brief clase iteradora no constante de la guía telefónica
	 */
	class iterator
	{
	private:
		typename map<string, string>::iterator it;
		iterator(const typename map<string,string>::iterator otro):it(otro){}
	public:
		/**
		 * @brief constructor sin parametros por defecto
		 */
		iterator() = default;

		/**
		 * @brief constructor de copia por defecto
		 * @param otro el que se copia
		 */
		iterator(const iterator &otro) : it(otro.it) {}

		/**
		 * @brief operador de asignacion (se delega en el operador de asignacion de map)
		 * @param otro el que se asigna
		 * @return una referencia al objeto
		 */
		iterator &operator=(const iterator &otro)
		{
			this->it = otro.it;
			return *this;
		}

		/**
		 * @brief operador ++ pre incremento
		 * @return una referencia al objeto
		 */
		iterator &operator++()
		{
			it++;
			return *this;
		}
		/**
		 * @brief operador ++ post incremento
		 * @return una copia del objeto
		 */
		iterator operator++(int)
		{
			Guia_Tlf::iterator aux(*this);
			it++;
			return aux;
		}
		/**
		 * @brief operador de desigualdad
		 * @param otro el iterador con el que se compara
		 * @return true si son distintos
		 * 			false si son iguales
		 */
		bool operator!=(const Guia_Tlf::iterator &otro)
		{
			return this->it != otro.it;
		}
		/**
		 * @brief operador *
		 * @return la entrada de la guia a la que apunta el iterador
		 */
		pair<string, string> operator*()
		{
			return (*it);
		}
		friend class Guia_Tlf;
	};
	/**
	 * @brief clase iteradora constante de la guía telefónica
	 */
	class const_iterator
	{
		typename map<string, string>::const_iterator it;
		const_iterator(const typename map<string,string>::const_iterator otro):it(otro){}

	public:
		/**
		 * @brief constructor sin parametros por defecto
		 */
		const_iterator() = default;

		/**
		 * @brief constructor de copia por defecto
		 * @param otro el que se copia
		 */
		const_iterator(const const_iterator &otro) : it(otro.it) {}

		/**
		 * @brief operador de asignacion (se delega en el operador de asignacion de map)
		 * @param otro el que se asigna
		 * @return una referencia al objeto
		 */
		const_iterator &operator=(const const_iterator &otro)
		{
			this->it = otro.it;
			return *this;
		}
		/**
		 * @brief operador ++ pre incremento
		 * @return una referencia al objeto
		 */
		const_iterator &operator++()
		{
			it++;
			return *this;
		}
		/**
		 * @brief operador ++ post incremento
		 * @return una copia del objeto
		 */
		const_iterator operator++(int)
		{
			Guia_Tlf::const_iterator aux(*this);
			it++;
			return aux;
		}
		/**
		 * @brief operador de desigualdad
		 * @param otro el iterador con el que se compara
		 * @return true si son distintos
		 * 			false si son iguales
		 */
		bool operator!=(const Guia_Tlf::const_iterator &otro)
		{
			return this->it != otro.it;
		}
		/**
		 * @brief operador *
		 * @return la entrada de la guia a la que apunta el iterador
		 */
		pair<string, string> operator*()
		{
			return (*it);
		}
		friend class Guia_Tlf;
	};

	/**
	 * @brief método begin no constante
	 * @return un iterador diccionario que apunta al begin no constante de @e datos
	 */
	Guia_Tlf::iterator begin()
	{
		return Guia_Tlf::iterator(datos.begin());
	}
	/**
	 * @brief método end no constante
	 * @return un iterador diccionario que apunta al end no constante de @e datos
	 */
	Guia_Tlf::iterator end()
	{
		return Guia_Tlf::iterator(datos.end());
	}
	/**
	 * @brief método begin constante
	 * @return un iterador diccionario que apunta al begin  constante de @e datos
	 */
	Guia_Tlf::const_iterator cbegin() const
	{
		return Guia_Tlf::const_iterator(datos.cbegin());
	}
	/**
	 * @brief método end constante
	 * @return un iterador diccionario que apunta al end constante de @e datos
	 */
	Guia_Tlf::const_iterator cend() const
	{
		return Guia_Tlf::const_iterator(datos.cend());
	}

	/**
	 * @brief metodo para saber si una clave está en la guia
	 * @param nombre la clave que se busca
	 * @return true si está
	 * 			false si no está
	 */
	bool estaClave(const string &nombre) const{
		return (datos.find(nombre) != datos.end());
	}

	/**
	 * @brief metodo para realizar la interseccion con @e otra
	 * @param otra la guia de teléfono con la que se hace la interseccion
	 * @return la guia con la interseccion
	 */
	Guia_Tlf interseccion(const Guia_Tlf & otra){
		Guia_Tlf inters(*this);
		Guia_Tlf::iterator it_this;
		for (it_this = begin(); it_this != end(); ++it_this){
			pair<string,string> aux = (*it_this);
			if (!otra.estaClave(aux.first)){
				inters.borrar(aux.first);
			}
		}
	return inters;
	}

	/**
	 * @brief metodo para modificar el numero de telefono de una guia
	 * @param nombre el nombre de la persona que se cambia su telefono
	 * @param telefono el telefono nuevo
	 */
	void modificarTelefono(const string &nombre, const string &telefono){
		typename map<string,string>::iterator posicion = datos.find(nombre);
		if (posicion != datos.end()){
			datos[nombre] = telefono;
		}
	}

	/**
	 * @brief metodo para obtener los numeros de teléfono de la gente cuyo nombre empiece por @e letra
	 * @param letra el caracter por el que deben empezar los nombres 
	 * @return guia de telefono con esos nombres
	 */
	Guia_Tlf telefonosEmpiezanCon(char letra){
		Guia_Tlf salida;
		for (Guia_Tlf::iterator it = begin(); it != end(); ++it){
			if ((*it).first[0] == letra){
				salida.insert((*it));
			}
		}
		return salida;
	}

	/**
	* @brief metodo para obtener los numeros de teléfono entre @e nombre1 y @e nombre2
	* @pre @e nombre1 y @e nombre2 deben estar en la guia
	* @param nombre1 el primer elemento del subconjunto de numeros
	* @param nombre2 el final del subconjunto del numeros
	*/
	Guia_Tlf numerosEntre(string nombre1, string nombre2){
		Guia_Tlf salida;
		iterator it (datos.find(nombre1));
		iterator fin(datos.find(nombre2));
		for (; it != fin; ++it){
			salida.insert((*it));
		}
		salida.insert((*it));
		return salida;
	}

};

#endif
