/**
 * @file main_dic.cpp
 * @author Salvador Romero Cortés
 */
#include <iostream>
#include "diccionario.h"
#include <list>

using namespace std;

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

ostream & operator<<(ostream & os, const Diccionario<string,string> & D){
	  
	  list<data<string,string> >::const_iterator it;
	  
	  for (it=D.cbegin(); it!=D.cend(); ++it){
	  
		    list<string>::const_iterator it_s;
		    
		    os<<endl<<(*it).clave<<endl<<" informacion asociada:"<<endl;
		    for (it_s=(*it).info_asoci.begin();it_s!=(*it).info_asoci.end();++it_s){
			      os<<(*it_s)<<endl;
		    }
		    os<<"**************************************"<<endl;
	  }
	  
	  return os;
}

int main(){
    Diccionario<string,string> dic1, dic2, dic_union, sub_dic, dic_difer;
    list<string> definiciones;
    int np,nd; 
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