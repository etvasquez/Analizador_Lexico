//definicion de bibliotecas
#include <iostream>
#include <string.h>
#include <string> 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;

bool compararReservada(string lista[], string cadena, int longitud);
int buscarEstado(string listaSeparadores[],int listaEstados[], string cadena, int longitud,char simbolo);
bool VerificarSeparador(string listaSeparadores[], string cadena,  int longitud,char simbolo);

//programa principal
main (){
	//VARIABLES
	string reservadas[] = {"start", "finish", "set", "get", "int", "string","double","char", "boolean","while","endwhile","if","else","endif","and","or"};
	int long_reservadas = (sizeof(reservadas)/sizeof(*reservadas));
	//SEPARADORES PALABRA
	string Spalabra[] = {" ",";","(","=",">","<","!","+","-","/","*","\"",")",":","\n"};
	int long_separadoresP = (sizeof(Spalabra)/sizeof(*Spalabra));
	int estadoPalabra[] = {0,9,8,4,4,4,6,11,11,11,11,10,7,12,0};
	
	//SEPARADORES NUMEROS
	string SNumeros[] = {" ","=",">","<","!","+","-","/","*",";",")"};
	int long_Numeros = (sizeof(SNumeros)/sizeof(*SNumeros));
	int estadoNumero[] = {0,4,4,4,6,11,11,11,11,9,7};
	//SEPARADORES CARACTERES <,>,<=,>=,=,==,!=
	string SRelacional[] = {" ","(","\""};
	int long_Relacionales = (sizeof(SRelacional)/sizeof(*SRelacional));
	int estadoRelacional[] = {0,8,10};
	//SEPARADORES CARACTER )
	string SRelacional1[] = {" ",";",")",":"};
	int long_Relacionales1 = (sizeof(SRelacional1)/sizeof(*SRelacional1));
	int estadoRelacional1[] = {0,9,7,12};
	//SEPARADORES CARACTER (
	string SRelacional2[] = {" ","\"","("};
	int long_Relacionales2 = (sizeof(SRelacional2)/sizeof(*SRelacional2));
	int estadoRelacional2[] = {0,10,8};
	//SEPARADORES CARACTER ; y :
	string SRelacional3[] = {" ","\n"};
	int long_Relacionales3 = (sizeof(SRelacional3)/sizeof(*SRelacional3));
	int estadoRelacional3[] = {0,0};
	//SEPARADORES CARACTER "
	string SRelacional4[] = {" ",")",",","+","\"",";"};
	int long_Relacionales4 = (sizeof(SRelacional4)/sizeof(*SRelacional4));
	int estadoRelacional4[] = {0,7,3,11,10,9};
	//SEPARADORES ARITMETICOS
	string SAritmeticos[] = {" ",";","+","=","-"};
	int long_Aritmeticos = (sizeof(SAritmeticos)/sizeof(*SAritmeticos));
	int estadoAritmeticos[] = {0,9,11,4,11};
		
	string nfichero = "codigo.txt";
	char cadena[500];
	ifstream fichero;
	fichero.open(nfichero.c_str());
	bool bandera = false;
	
	FILE *archivo;
	if ((archivo = fopen("codigo.txt", "r")) == NULL){
		printf("\n el archivo no existe");
        exit(0);
    }else{
		string cadena ="";	//para guardar la cadena que se analizará
    	string simbolo;
    	char caracter;
    	int estado = 0;
    	int suma = 0;
    	cout<<"\t\t\t---------------------------------------------------------------------"<<endl;
    	cout<<"\t\t\t----------------      ANALIZADOR LEXICO             -----------------"<<endl;
    	cout<<"\t\t\t---------------------------------------------------------------------"<<endl;
    	cout<<"\t\t\t-------------               UTPL                          -----------"<<endl;
    	cout<<"\t\t\t------------- Estudiante: Erika Tatiana Vasquez Tapia     -----------"<<endl;
    	cout<<"\t\t\t-------------                                             -----------"<<endl;
    	cout<<"\t\t\t---------------------------------------------------------------------"<<endl;
    	printf("\t\t\t%5s%16s%16s%16s\n","NRO.","PALABRA", "TOKEN","TIPO");
    	cout<<"\t\t\t---------------------------------------------------------------------"<<endl;

		while (caracter!=EOF){
			caracter =  getc(archivo);
			simbolo = string(1, caracter);
			switch(estado) {
    			case 0:
    				// LETRA
    				if(isalpha(caracter)){
    					estado = 1;
    					cadena = cadena + caracter;
    					break;
    				// DIGITO
					}else if (isdigit(caracter)){
						estado = 2;
						cadena = cadena + caracter;
						break;
					//COMA DIGITO
					}else if(caracter == ','){
						estado = 3;
						cadena = cadena + caracter;
						break;
					//RELACIONALES
					}else if(caracter == '<' || caracter == '>' || caracter =='='){
						estado = 4;
						cadena = cadena + caracter;
						break;
					//RELACIONALES
					}else if(caracter == '!'){
						estado = 5;
						cadena = cadena + caracter;
						break;
					//ESPECIALESx
					}else if(caracter == ')'){
						estado = 7;
						cadena = cadena + caracter;
						break;
					//ESPECIALES
					}else if(caracter == '('){
						estado = 8;
						cadena = cadena + caracter;
						break;
					//ESPECIALES
					}else if(caracter == ';'){
						estado = 9;
						cadena = cadena + caracter;
						break;
					//ARITMETICOS
					}else if(caracter == '"'){
						estado = 10;
						cadena = cadena + caracter;
						break;
					}else if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/'){
						estado = 11;
						cadena = cadena + caracter;
						break;
					}else if(caracter == ':'){
						estado = 12;
						cadena = cadena + caracter;
						break;
					}
				break;
				
				case 1:
					if(isalpha(caracter) or isdigit(caracter)){
    					estado = 1;
    					cadena = cadena + caracter;	
    				}else{
						if(compararReservada(reservadas, cadena, long_reservadas)){
							suma = suma + 1 ;
							cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena +"\t\tpalabra\t\tPalabra Reservada\n";
							cadena = "";
						}else{
							suma = suma + 1 ;
							cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena +"\t\tpalabra\t\tIdentificador\n";
							cadena = "";
						}
						if(VerificarSeparador(Spalabra,simbolo,long_separadoresP,caracter)){
							estado = buscarEstado(Spalabra,estadoPalabra,simbolo,long_separadoresP,caracter);
							if(estado!=0){
								cadena = cadena + caracter;
							}	
						}else{
							cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
							estado=0;
						}								
    				}
    			break;
    			
				case 2:
					if(isdigit(caracter)){
    					estado = 2;
    					cadena = cadena + caracter;	
    				}else{
						if(caracter==','){
							estado=3;
							cadena = cadena + caracter;
						}else{
							if(isalpha(caracter)==false){
								suma = suma + 1 ;
								cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena +"\t\tnumero\t\tValor Entero\n";
								cadena="";
							}
							if(VerificarSeparador(SNumeros,simbolo,long_Numeros,caracter)){
								estado = buscarEstado(SNumeros,estadoNumero,simbolo,long_Numeros,caracter);
								if(estado==1){
									estado = 2;
									bandera=true;
								}else{
									if(bandera){
										cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
										cadena += caracter;
									}else{	
										cout<<"\t\t\t- "<<suma<<"\t\t"+simbolo+"\t\t"+simbolo+"\t\tCaracter Especial\n";
										estado=0;
									}
								}
							}else{
								cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
								estado=0;
							}		
						}
					}
    			break;
				
				case 3:
					if(isdigit(caracter)){
						estado = 13;
				     	cadena = cadena + caracter;
					}else{
						suma = suma + 1 ;
						cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tCaracter Especial\n";
						cadena="";
						if(VerificarSeparador(SRelacional3,simbolo,long_Relacionales3,caracter)){
							estado = buscarEstado(SRelacional3,estadoRelacional3,simbolo,long_Relacionales3,caracter);
							if(estado!=0){
								cadena = cadena + caracter;
							}
						}else{
							cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
							estado=0;
						}
					}
				break;
				
				case 4:
					if(caracter=='='){
						estado = 5;
						cadena = cadena + caracter;
					}else{
						suma = suma + 1 ;
						if(caracter=='>'|| caracter=='<'){
							cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tOperador Relacional\n";
						}else{
							cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tAsignacion\n";
						}
						cadena="";
						if(VerificarSeparador(SRelacional,simbolo,long_Relacionales,caracter)){
							estado = buscarEstado(SRelacional,estadoRelacional,simbolo,long_Relacionales,caracter);
							if(estado!=0){
								cadena = cadena + caracter;
							}
						}else{
							cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
							estado=0;
						}
					}
				break;
				
				case 5:
					suma = suma + 1 ;
					cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tOperador Relacional\n";
					cadena="";
					if(VerificarSeparador(SRelacional,simbolo,long_Relacionales,caracter)){
						estado = buscarEstado(SRelacional,estadoRelacional,simbolo,long_Relacionales,caracter);
						if(estado!=0){
							cadena = cadena + caracter;
						}
					}else{
						cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
						estado=0;
					}
				break;
				
				case 6:
					if(caracter=='='){
						estado = 5;
						cadena = cadena + caracter;	
					}else{
						cadena="";
						if(VerificarSeparador(SRelacional,simbolo,long_Relacionales,caracter)){
							estado = buscarEstado(SRelacional,estadoRelacional,simbolo,long_Relacionales,caracter);
							if(estado!=0){
								cadena = cadena + caracter;
							}
						}else{
							cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
							estado=0;
						}
					}
				break;	
				
				case 7:
					suma = suma + 1 ;
					cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tCaracter Especial\n";
					cadena="";
					if(VerificarSeparador(SRelacional1,simbolo,long_Relacionales1,caracter)){
						estado = buscarEstado(SRelacional1,estadoRelacional1,simbolo,long_Relacionales1,caracter);
						if(estado!=0){
							cadena = cadena + caracter;
						}
					}else{
						cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
						estado=0;
					}
						
				break;
				case 8:
					suma = suma + 1 ;
					cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tCaracter Especial\n";
					cadena="";
					if(VerificarSeparador(SRelacional2,simbolo,long_Relacionales2,caracter)){
						estado = buscarEstado(SRelacional2,estadoRelacional2,simbolo,long_Relacionales2,caracter);
						if(estado!=0){
							cadena = cadena + caracter;
						}
					}else{
						cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
						estado=0;
					}
				break;
				case 9:
					suma = suma + 1 ;
					cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tCaracter Especial\n";
					cadena="";
					if(VerificarSeparador(SRelacional3,simbolo,long_Relacionales3,caracter)){
						estado = buscarEstado(SRelacional3,estadoRelacional3,simbolo,long_Relacionales3,caracter);
						if(estado!=0){
							cadena = cadena + caracter;
						}
					}else{
						cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
						estado=0;
					}
				break;
				case 10:
					suma = suma + 1 ;
					cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tCaracter Especial\n";
					cadena="";
					if(VerificarSeparador(SRelacional4,simbolo,long_Relacionales4,caracter)){
						estado = buscarEstado(SRelacional4,estadoRelacional4,simbolo,long_Relacionales4,caracter);
						if(estado!=0){
							cadena = cadena + caracter;
						}
					}else{
						cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
						estado=0;
					}
				break;
				
				case 11:
					suma = suma + 1 ;
					cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tOperadores Aritmeticos\n";
					cadena="";
					if(VerificarSeparador(SAritmeticos,simbolo,long_Aritmeticos,caracter)){
						estado = buscarEstado(SAritmeticos,estadoAritmeticos,simbolo,long_Aritmeticos,caracter);
						if(estado!=0){
							cadena = cadena + caracter;
						}
					}else{
						cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
						estado=0;
					}		
				break;
				
				case 12:
					suma = suma + 1 ;
					cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena + "\t\t"+cadena+"\t\tCaracter Especial\n";
					cadena="";
					if(VerificarSeparador(SRelacional3,simbolo,long_Relacionales3,caracter)){
						estado = buscarEstado(SRelacional3,estadoRelacional3,simbolo,long_Relacionales3,caracter);
						if(estado!=0){
							cadena = cadena + caracter;
						}
					}else{
						cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
						estado=0;
					}
				break;
				
				case 13:
					if(isdigit(caracter)){
						estado=13;
						cadena = cadena + caracter;
					}else{
						if(isalpha(caracter)==false){
							suma = suma + 1 ;
							cout<<"\t\t\t- "<<suma<<"\t\t"+ cadena +"\t\tnumero\t\tValor Decimal\n";
							cadena="";
						}
						if(VerificarSeparador(SNumeros,simbolo,long_Numeros,caracter)){
							estado = buscarEstado(SNumeros,estadoNumero,simbolo,long_Numeros,caracter);
							if(estado==1){
								estado = 13;
								bandera=true;
							}else{
								if(bandera){
									cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
									cadena += caracter;
								}else{	
									cout<<"\t\t\t- "<<suma<<"\t\t"+simbolo+"\t\t"+simbolo+"\t\tCaracter Especial\n";
									estado=0;
								}
							}
						}else{
							cout<<"\t\t\tERROR, VERIFIQUE EL CODIGO\n";
							estado=0;
						}		
					}
				break;
				default:
				break;	
			}	
    	}
		cout<<"\t\t\t---------------------------------------------------------------------"<<endl;				
	}
	fclose(archivo);
    return 0;	
}
//METODOS
bool compararReservada(string lista[], string cadena, int longitud){
	bool a= false;
	for ( int i = 0; cadena [i]; i++) {
		cadena [i] = tolower(cadena [i]) ;
	}
	for (int i=0; i< longitud; i++){
		if((cadena.compare(lista[i]) == 0)){
			a= true;
			break;	
		}
	}
	return a;
}
int buscarEstado(string listaSeparadores[],int listaEstados[], string cadena, int longitud, char simbolo){
	int a = 0;
	for (int i=0; i< longitud; i++){
		if((cadena.compare(listaSeparadores[i]) == 0)){
			a= listaEstados[i];
			break;	
		}
		if(isdigit(simbolo)){
			a = 2;
		}else if(isalpha(simbolo)){
			a = 1;
		}
	}
	return a;
}
bool VerificarSeparador(string listaSeparadores[], string cadena,int longitud, char simbolo){
	bool b = 0;
	for (int i=0; i< longitud; i++){
		if((cadena.compare(listaSeparadores[i]) == 0)|| isdigit(simbolo)|| isalpha(simbolo)){
			b=true;
			break;	
		}
	}
	return b;
}
