%{
#include <string.h>
#include <stdlib.h>
#include "estructurasTablas/generadorTablas.c"
#include "estructurasTablas/linkedListInteger.h"
#include "anSintacRecursivo.h"


/*Programa que lee un programa y hace el reconocimiento del lenguaje
	definido por la clase, realiza analisis lexico y sintactico

Elaborado por : 
	-Alcántara Hoyos José Carlos
	-Vargas Guerrero Armando

Fecha de entrega : 3 de Diciembre de 2020
*/

FILE *archSal;
FILE *archAtomos;
FILE *openPrueba;
char* tmp;
int clase;
int valor;
char atomo;
Catalogo palReserv;
Catalogo opRel;
TablaCaracteres simbEsp;
TablaCaracteres opAsig;
TablaOperadores opArit;
TablaLiterales ctesReales;
TablaLiterales cadenas;
TablaLiterales ctesEnteras;
TablaSimbolos tabSimb;

Temp temporalIntegers;
%}

/*Expresiones regulares recurrentes*/
whatEver [^""]
dig [0-9]
letras [a-zA-Z]

/*Definimos las cosas que omitimos*/
tab \t
salto \n
spaceBar (\ )
comment @[^\n]*{salto}
omite {tab}|{salto}|{spaceBar}

/*Definimos las palabras reservadas*/
pR1 (bool)|(break)|(case)|(char)|(continue)|(default)
pR2 (else)|(float)|(for)|(if)|(int)|(return)|(string)|(switch)
pR3 (do)|(while)|(void)
palRes {pR1}|{pR2}|{pR3}

/*Definimos operadores relacionales*/
opRel (!=)|(==)|(>)|(<)|(>=)|(<=)

/*Definimos simbolos especiales*/
simbEsp (\{)|(\})|(,)|(:)|(\()|(\))|(\[)|(\])

/*Definimos el op de asignacion*/
asig =

/*Definimos op aritmeticos*/
opArit (\+)|(\-)|(\*)|(\/)|(\*\*)|(%)

/*Definimos las constantes numéricas enteras*/
cNumEnt {dig}{1,14}

/*Definimos las constantes numéricas reales*/
dot \.
notCien (E|e)((-?)|(\+?)){dig}{1,5}
cNumReal {dig}{1,10}{dot}({dig}{1,10}{notCien}?)

/*Definimos las cadenas*/
str \"{whatEver}*\"

/*Definimos los identificadores*/
ident {letras}({letras}|{dig}|_)*
%%
{palRes} {clase=1; valor=buscarCatalogo(&palReserv,yytext);
	atomo=devolverAtomoCat(&palReserv,valor);
	fprintf(archSal,"(%d,%d)\n",clase,valor);
	fprintf(archAtomos,"%c",atomo);}
{opRel} {clase=5; valor=buscarCatalogo(&opRel,yytext);
	atomo=devolverAtomoCat(&opRel,valor);
	fprintf(archSal,"(%d,%d)\n",clase,valor);
	fprintf(archAtomos,"%c",atomo);}
{simbEsp} {clase=2; valor=buscarTablaCaracteres(&simbEsp,yytext[0]);
	fprintf(archSal,"(%d,%d)\n",clase,valor);
	fprintf(archAtomos,"%c",valor);}
{asig} {clase=4; valor=buscarTablaCaracteres(&opAsig,yytext[0]);
	fprintf(archSal,"(%d,%d)\n",clase,valor);
	fprintf(archAtomos,"%c",valor);}
{opArit} {clase=8; atomo=devolverAtomoArit(&opArit,yytext);
	fprintf(archSal,"(%d,%c)\n",clase,buscarTablaOperadores(&opArit,yytext));
	fprintf(archAtomos,"%c",atomo);}
{cNumReal} {clase=0; 
	tmp=(char *)malloc(strlen(yytext)*sizeof(char));
	strcpy(tmp,yytext);
	valor=insertarTablaLiterales(&ctesReales,tmp, 'r');
	atomo=devolverAtomoLit(&ctesReales,valor);
	/*fprintf(archSal, "\n------TABLA DE CONSTANTES REALES-----\n");*/
	fprintf(archSal,"(%d,%d)\n",clase,valor);
	fprintf(archAtomos,"%c",atomo);}
{str} {clase=7; 
	tmp=(char *)malloc(strlen(yytext)*sizeof(char));
	strcpy(tmp,yytext);
	valor=insertarTablaLiterales(&cadenas,tmp, 's');
	atomo=devolverAtomoLit(&cadenas,valor);
	/*fprintf(archSal, "\n------TABLA DE CADENAS------\n");*/
	fprintf(archSal,"(%d,%d)\n",clase,valor);
	fprintf(archAtomos,"%c",atomo);}
{comment}|{omite} {}
{cNumEnt} {clase=6; atomo='e';
	fprintf(archSal,"(%d,%s)\n",clase,yytext);
	fprintf(archAtomos,"%c",atomo);}
{ident} {clase=3; 
	tmp=(char *)malloc(strlen(yytext)*sizeof(char));
	strcpy(tmp,yytext);
	if(buscarTablaSimbolos(&tabSimb,tmp)!=-1){
		valor=buscarTablaSimbolos(&tabSimb,tmp);
		atomo=devolverAtomoSimb(&tabSimb,valor);
	}else{
		valor=insertarTablaSimbolos(&tabSimb,tmp);
		atomo=devolverAtomoSimb(&tabSimb,valor);
	}
	insertarInt(&temporalIntegers,valor);
	fprintf(archSal,"(%d,%d)\n",clase,valor);
	fprintf(archAtomos,"%c",atomo);}
. {printf("======>ERROR: No se reconoció: %s Sigue el analisis\n",yytext);}
%%
int main(int argc,char *argv[])
{
	palReserv = generarTabPalabrasRes();
	opRel = generarTabOpRelacionales();
	simbEsp = generarTabSimbEspecial();
	opAsig = generarTabOpAsignacion();
	opArit = generarTabOpAritmeticos();

	/*imprimirCatalogo(palReserv);
	imprimirCatalogo(opRel);
	imprimirTablaCaracteres(simbEsp);
	imprimirTablaCaracteres(opAsig);
	imprimirTablaOperadores(opArit);*/
	
	temporalIntegers=crearTemp();
	
	ctesReales = crearTablaLiterales();
	cadenas = crearTablaLiterales();
	tabSimb = crearTablaSimbolos();

	yyin=fopen(argv[1],"r");
	archSal=fopen("tokens.txt","w");
	archAtomos=fopen("atomos.txt","w");
	fprintf(archSal, "-----TOKENS GENERADOS----\n");
	yylex();
	imprimirTablaLiterales(cadenas, archSal);
	imprimirTablaLiterales(ctesReales, archSal);
	

	fprintf(archAtomos,"%c", 126);

	
	fclose(archAtomos);
	
	//para probar el tmp: imprimirLinkedList(&temporalIntegers);

	openPrueba=fopen("atomos.txt", "r");
	asignaArchivoAtomos(openPrueba,&tabSimb,&temporalIntegers);
	P();
	printf("\n\n---------Analisis sintactico terminado---------\n");
	showNumErrores();

	imprimirTablaSimbolos(tabSimb, archSal);
	fclose(archSal);
}
