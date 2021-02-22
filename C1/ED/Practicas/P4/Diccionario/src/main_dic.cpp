/**
 * @file main_dic.cpp
 * @author Salvador Romero Cortés
 */
#include <iostream>
#include <diccionario.h>
#include <list>

using namespace std;
/**
 * @brief sobrecarga del operador >> para leer datos de un flujo @e is
 * @param is el flujo de donde se lee
 * @param D el diccionario que se lee
 * @return una referencia al flujo
 */
istream & operator >>(istream & is,Diccionario<string,string> &D){
	  int np;
	  is>>np;
	  is.ignore();//quitamos \n
	  Diccionario<string,string> Daux;
	  for (int i=0;i<np; i++){
		    string clave;

		    getline(is,clave); 
		    
		    int ns;
		    is>>ns; 
		    is.ignore();//quitamos \n
		    list<string>laux;
		    for (int j=0;j<ns; j++){
			      string s;
			      getline(is,s);
			      
			      // cout<<"Significado leido "<<s<<endl;
			      laux.insert(laux.end(),s);
		    }
		    Daux.Insertar(clave,laux);		      
		    
	  }
	  D=Daux;
	  return is;
}
/**
 * @brief sobrecarga del operador << para escribir datos en un flujo @e os
 * @param os el flujo de donde se escribe
 * @param D el diccionario que se escribe
 * @return una referencia al flujo
 */
ostream & operator<<(ostream & os, Diccionario<string,string> D){
	typename Diccionario<string,string>::const_iterator it;
	string clave;
	int cont;
	for (it = D.cbegin(); it != D.cend(); ++it){
		clave = D.getClave(it);
		list<string> definiciones= D.getInfo_Asoc(clave);
		cont = 1;
		os << "Palabra: " << clave << endl;
		for (typename list<string>::const_iterator it_def = definiciones.cbegin(); it_def != definiciones.cend();++it_def){
			os << "Def. " << cont++ << " --> " << (*it_def) << endl;
		}
		os << "******************************" << endl;
	}


	  return os;
}

int main(){
    Diccionario<string,string> dic1, dic2, dic_union, sub_dic, dic_difer;
    list<string> definiciones;
    string palabra, borrado, definicion;
    cin >> dic1;

    // cout << "******************** DICCIONARIO 1 ************************" << endl;
    // cout << dic1;

    cin >> dic2;
    // cout << "******************** DICCIONARIO 2 ************************" << endl;
    // cout << dic2;

    dic_union = dic1.union_dic(dic2);

	sub_dic = dic_union.subdiccionario_entre("Feo","Libro");
    cout << "******************** DICCIONARIO UNION ************************" << endl;
    cout << dic_union;
	cout << "******************** SUBDICCIONARIO ************************" << endl;
    cout << sub_dic;
	dic_difer = dic_union.diferencia(sub_dic);
	cout << "******************** DIFERENCIA ************************" << endl;
    cout << dic_difer;
    // cout << "Introduce el elemento que quieras borrar: " << endl;
    // getline(cin,borrado);
    // dic1.borrar_por_clave(borrado);
    // cout << dic1;

}