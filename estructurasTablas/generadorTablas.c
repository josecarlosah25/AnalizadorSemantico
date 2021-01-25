#include <stdio.h>
#include <stdlib.h>
#include "catalogos.h"
#include "tablaLiterales.h"
#include "tablaCaracteres.h"
#include "tablaOpAritmeticos.h"
#include "tablaSimbolos.h"

Catalogo generarTabPalabrasRes(){
	Catalogo palReserv = crearCatalogo();

	insertarCatalogo(&palReserv, "bool", 'b');
	insertarCatalogo(&palReserv, "break", 'q');
	insertarCatalogo(&palReserv, "case", 'k');
	insertarCatalogo(&palReserv, "char", 'c');
	insertarCatalogo(&palReserv, "continue", 't');
	insertarCatalogo(&palReserv, "default", 'd');
	insertarCatalogo(&palReserv, "do", 'h');
	insertarCatalogo(&palReserv, "else", 'l');
	insertarCatalogo(&palReserv, "float", 'f');
	insertarCatalogo(&palReserv, "for", 'p');
	insertarCatalogo(&palReserv, "if", 'i');
	insertarCatalogo(&palReserv, "int", 'n');
	insertarCatalogo(&palReserv, "return", 'u');
	insertarCatalogo(&palReserv, "string", 'g');
	insertarCatalogo(&palReserv, "switch", 'x');
	insertarCatalogo(&palReserv, "while", 'w');
	insertarCatalogo(&palReserv, "void", 'o');

	return palReserv;
}

Catalogo generarTabOpRelacionales(){
	Catalogo tabOpRel = crearCatalogo();

	insertarCatalogo(&tabOpRel, "!=", '!');
	insertarCatalogo(&tabOpRel, "==", '?');
	insertarCatalogo(&tabOpRel, ">", '>');
	insertarCatalogo(&tabOpRel, "<", '<');
	insertarCatalogo(&tabOpRel, ">=", 'y');
	insertarCatalogo(&tabOpRel, "<=", 'm');

	return tabOpRel;
}

TablaCaracteres generarTabSimbEspecial(){
	TablaCaracteres tabSimbEsp = crearTablaCaracteres();

	//Recordar que el símbolo insertado es también el átomo
	insertarTablaCaracteres(&tabSimbEsp, '{');
	insertarTablaCaracteres(&tabSimbEsp, '}');
	insertarTablaCaracteres(&tabSimbEsp, ',');
	insertarTablaCaracteres(&tabSimbEsp, ':');
	insertarTablaCaracteres(&tabSimbEsp, '(');
	insertarTablaCaracteres(&tabSimbEsp, ')');
	insertarTablaCaracteres(&tabSimbEsp, '[');
	insertarTablaCaracteres(&tabSimbEsp, ']');

	return tabSimbEsp;
}

TablaCaracteres generarTabOpAsignacion(){
	TablaCaracteres tabOpAsig = crearTablaCaracteres();

	//Recordar que el símbolo insertado es también el átomo
	insertarTablaCaracteres(&tabOpAsig, '=');

	return tabOpAsig;
}

TablaOperadores generarTabOpAritmeticos(){
	TablaOperadores tabOpArit = crearTablaOperadores();

	insertarTablaOperadores(&tabOpArit, "+", '+');
	insertarTablaOperadores(&tabOpArit, "-", '-');
	insertarTablaOperadores(&tabOpArit, "*", '*');
	insertarTablaOperadores(&tabOpArit, "/", '/');
	insertarTablaOperadores(&tabOpArit, "%", '%');
	insertarTablaOperadores(&tabOpArit, "**", '#');

	return tabOpArit;
}


