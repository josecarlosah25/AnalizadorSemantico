#include <stdio.h>

FILE* origen;
TablaSimbolos* simb;
Temp* temporalInt;
char c;
int nError=0;
int auxSincronia=0;

void asignaArchivoAtomos(FILE *dir,TablaSimbolos* tablasimb,Temp* integers);
char getC();
void error();
void errorSemantico();
void P();
void YP();
void DP();
void Y();
void VP();
void D();
void L();
void C();
int V();
void G();
void S();
void U();
void W();
void H();
void X();
void O();
void B();
void I();
void J();
void N();
void R();
void K();
void E();
void EP();
void T();
void TP();
void F();
void A();
void CP();
void ZP();
void SP();

int obtenerTipoActual(int p1);
int obtenerP();
int VAT(int p1, int t1);

char getC(){
	
	char car=fgetc(origen);
	printf("%c",car);
	return car;
}

void asignaArchivoAtomos(FILE *dir,TablaSimbolos* tablasimb,Temp* integers){
	origen=dir;
	simb=tablasimb;
	temporalInt=integers;
	printf("\n--Cadena de atomos leida:\n");
	c=getC();
	
}

void P(){
	if(c=='b' || c=='c' || c=='f' || c=='n' ||
		c=='g' || c=='['){

		DP();
		Y();
		YP();
		return;
	}else{
		error(" b c f n g [ ");
	}
}

void YP(){
	if(c=='['){
		Y();
		YP();
		return;

	}else if(c==126){
		return;
	}else{
		error(" [ (fin de cadena)");
	}
}

void Y(){
	if(c=='['){
		c=getC();
		VP();
		
		if(c=='a'){
			c=getC();
		}else{
			error("a");
		}

		if(c=='('){
			c=getC();
		}else{
			error("(");
		}
		if(c==')'){
			c=getC();
		}else{
			error(")");
		}

		if(c=='{'){
			c=getC();
		}else{
			error("{");
		}

		DP();
		B();

		if(c=='}'){
			c=getC();
		}else{
			error("}");
		}

		if(c==']'){
			c=getC();
		}else{
			error("]");
		}
		return;
	}else{
		error("[");
	}
}

void VP(){
	if(c=='b' || c=='c' || c=='f' || c=='n' || c=='g'){
		V();
		return;
	}else if(c=='o'){
		c=getC();
		return;
	}else{
		error("b c f n g o ");
	}
}

void DP(){
	if(c=='b' || c=='c' || c=='f' || c=='n' ||
		c=='g'){
		D();
		DP();
		return;
	}else if(c=='a' || c=='x' || c=='i' || c=='w' ||
		c=='h'|| c=='p' || c=='u' || c=='t' || c=='[' ||
		c=='}'){
		return;
	}else{
		error("b c f n g a x i w h p u t [ }");
	}
}

void D(){
	int t;
	if(c=='b' || c=='c' || c=='f' || c=='n' ||
		c=='g'){
		t=V();
		if(t==-1){
			errorSemantico("Tipo de dato invalido");
			return;
		}
		L(t);
		return;
	}else{
		error("b c f n g");
	}
}

//nos va a ayudar a determinar el type que tiene el simbolo en la posicion "p1" 
int obtenerTipoActual(int p1){
	int type=buscarPosTablaSimbolos(simb,p1);
	return type;
}

//obtiene la posicion de la tabla de simbolos del identificador actual
int obtenerP(){
	int p=buscarValor(temporalInt,auxSincronia);
	auxSincronia++;
	return p;
}

//Verifica tipo y lo asigna
int VAT(int p1, int t1){
	int typeActual=obtenerTipoActual(p1);
	if(typeActual==-1){
		
		asignarTipo(simb,p1,t1);

		//printf("\n valor: %d\n",t1);
		return 0;
	}else{
		printf("\n id=%d : tipo actual:%d tipo a poner:%d\n",p1,typeActual,t1);
		errorSemantico("Se declaro previamente identificador ya que ya tenia el tipo asignado, revisar declaraciones");
		return -1;
	}
}

void L(int t){
	int p;
	if(c=='a'){
		p=obtenerP();
		VAT(p,t);
		c=getC();
		G();
		C(t);
		return;
	}else{
		error("a");
	}
}


void C(int t2){
	if(c==','){
		c=getC();
		L(t2);
		return;
	}else if(c==':'){
		c=getC();
		return;
	}else{
		error(", :");
	}
}

int V(){
	if(c=='b'){
		c=getC();
		return 0;
	}else if(c=='c'){
		c=getC();
		return 3;
	}else if(c=='f'){
		c=getC();
		return 8;
	}else if(c=='n'){
		c=getC();
		return 11;
	}else if(c=='g'){
		c=getC();
		return 13;
	}else{
		error("b c f n g");
		return -1;
	}	
}

void G(){
	if(c=='['){
		c=getC();
		if(c=='e'){
			c=getC();
		}else{
			error("e");
		}
		if(c==']'){
			c=getC();
		}else{
			error("]");
		}
		return;
	}else if(c==',' || c=='='|| c==':'|| c=='*'|| c=='/'
		|| c=='%'|| c=='#'|| c=='+'|| c=='-'|| c=='!'
		|| c=='?'|| c=='>'|| c=='<'|| c=='y'|| c=='m' || c==')'){
		return;
	}else{
		error("[ , = : * / % # + - ! ? > < y m )");
	}
}

void S(){
	if(c=='a'){
		A();
		return;
	}else if(c=='x'){
		X();
		return;
	}else if(c=='i'){
		I();
		return;
	}else if(c=='w'){
		W();
		return;
	}else if(c=='h'){
		H();
		return;
	}else if(c=='p'){
		N();
		return;
	}else if(c=='u'){
		c=getC();
		U();
		if(c==':'){
			c=getC();
		}else{
			error(":");
		}
		return;
	}else if(c=='t'){
		c=getC();
		if(c==':'){
			c=getC();
		}else{
			error(":");
		}
		return;
	}else if(c=='['){
		c=getC();
		if(c=='a'){
			c=getC();
		}else{
			error("a");
		}
		if(c=='('){
			c=getC();
		}else{
			error("(");
		}
		if(c==')'){
			c=getC();
		}else{
			error(")");
		}
		if(c==']'){
			c=getC();
		}else{
			error("]");
		}
		if(c==':'){
			c=getC();
		}else{
			error(":");
		}
		return;
	}else{
		error("a x i w h p u t [");
	}
}

void U(){
	if(c=='('){
		c=getC();
		F();
		if(c==')'){
			c=getC();
		}else{
			error(")");
		}
		return;
	}else if(c==':'){
		return;
	}else{
		error("( :");
	}
}

void W(){
	if(c=='w'){
		c=getC();
		if('('){
			c=getC();
		}else{
			error("(");
		}
		R();
		if(')'){
			c=getC();
		}else{
			error(")");
		}

		if('{'){
			c=getC();
		}else{
			error("{");
		}

		B();

		if('}'){
			c=getC();
		}else{
			error("}");
		}
		return;

	}else{
		error("w");
	}
}

void H(){
	if(c=='h'){
		c=getC();
		if(c=='{'){
			c=getC();
		}else{
			error("{");
		}
		B();
		if(c=='}'){
			c=getC();
		}else{
			error("}");
		}
		if(c=='w'){
			c=getC();
		}else{
			error("w");
		}
		if(c=='('){
			c=getC();
		}else{
			error("(");
		}
		R();
		if(c==')'){
			c=getC();
		}else{
			error(")");
		}
		if(c==':'){
			c=getC();
		}else{
			error(":");
		}
		return;
	}else{
		error("h");
	}
}

void X(){
	if(c=='x'){
		c=getC();
		if(c=='('){
			c=getC();
		}else{
			error("(");
		}

		if(c=='a'){
			c=getC();
		}else{
			error("a");
		}

		if(c==')'){
			c=getC();
		}else{
			error(")");
		}

		if(c=='{'){
			c=getC();
		}else{
			error("{");
		}

		O();

		if(c=='d'){
			c=getC();
		}else{
			error("d");
		}

		if(c=='['){
			c=getC();
		}else{
			error("[");
		}

		B();

		if(c==']'){
			c=getC();
		}else{
			error("]");
		}

		if(c=='}'){
			c=getC();
		}else{
			error("}");
		}
		return;

	}else{
		error("x");
	}
}

void O(){
	if(c=='k'){
		c=getC();
		if(c=='e'){
			c=getC();
		}else{
			error("e");
		}

		if(c=='['){
			c=getC();
		}else{
			error("[");
		}

		B();

		if(c==']'){
			c=getC();
		}else{
			error("]");
		}

		if(c=='q'){
			c=getC();
		}else{
			error("q");
		}

		if(c==':'){
			c=getC();
		}else{
			error(":");
		}

		O();
		return;

	}else if(c=='d'){
		return;
	}else{
		error("k d");
	}
}

void B(){
	if(c=='a' || c=='x' || c=='i' || c=='w' || c=='h' ||
		c=='p'|| c=='u' || c=='t' ||c=='['){
		S();
		B();
		return;
	}else if(c==']' || c=='}'){
		return;
	}else{
		error("a x i w h p u t [ ] }");
	}
}

void I(){
	if(c=='i'){
		c=getC();
		if(c=='('){
			c=getC();
		}else{
			error("(");
		}
		R();
		if(c==')'){
			c=getC();
		}else{
			error(")");
		}
		if(c=='{'){
			c=getC();
		}else{
			error("{");
		}
		B();
		if(c=='}'){
			c=getC();
		}else{
			error("}");
		}
		J();
		if(c==':'){
			c=getC();
		}else{
			error(":");
		}
		return;
	}else{
		error("i");
	}
}

void J(){
	if(c=='l'){
		c=getC();
		if(c=='{'){
			c=getC();
		}else{
			error("{");
		}
		B();
		if(c=='}'){
			c=getC();
		}else{
			error("}");
		}

		return;
	}else if(c==':'){
		return;
	}else{
		error("l :");
	}
}

void N(){
	if(c=='p'){
		c=getC();
		if(c=='['){
			c=getC();
		}else{
			error("[");
		}
		if(c=='e'){
			c=getC();
		}else{
			error("e");
		}
		if(c==']'){
			c=getC();
		}else{
			error("]");
		}
		if(c=='{'){
			c=getC();
		}else{
			error("{");
		}
		B();
		if(c=='}'){
			c=getC();
		}else{
			error("}");
		}
		return;
	}else{
		error("p");
	}
}

void R(){
	if(c=='(' || c=='a' || c=='e' || c=='r' || c=='['){
		E();
		K();
		E();
		return;
	}else{
		error("( a e r [");
	}
}

void K(){
	if(c=='!' || c=='?' || c=='>' || c=='<' || c=='y'|| c=='m'){
		c=getC();
		return;
	}else{
		error("! ? > < y m");
	}
}

void E(){
	if(c=='(' || c=='a' || c=='e' || c=='r' || c=='[' ){
		T();
		EP();
		return;
	}else{
		error("( a e r [");
	}
}

void EP(){
	if (c == '+'){
		c = getC();
		T();
		EP();
		return;
	} else if (c == '-'){
		c = getC();
		T();
		EP();
		return;
	} else if (c == ')' || c == '}' || c == '!' || c == '?' || c == '>' || 
				c == '<' || c == 'y' || c == 'm' || c == ':'){
		return;
	} else {
		error(") } ! ? > < y m :");
	}
}

void T(){
	if (c == '(' || c == 'a' || c == 'e' || c== 'r' || c == '['){
		F();
		TP();
		return;
	} else {
		error("( a e r [");
	} 
	
}

void TP(){
	if (c == '*'){
		c = getC();
		F();
		TP();
		return;
	} else if (c == '/'){
		c = getC();
		F();
		TP();
		return;
	} else if (c == '%'){
		c = getC();
		F();
		TP();
		return; 
	} else if (c == '#'){
		c = getC();
		F();
		TP();
		return;
	} else if (c == '+' || c == '-' || c == '!' || c == '?' || c == '>' 
				|| c == '<' || c == 'y' || c == 'm' || c == ')' || c == ':'){
		return;
	} else {
		error("* / % # + - ! ? > < y m ) :");
	}
} 

void F(){
	if (c == '('){
		c = getC();
		E();
		if (c == ')')
			c = getC();
		else 
			error(")");
		return;

	} else if (c == 'a'){
		c = getC();
		G();
		return;

	} else if (c == 'e'){
		c = getC();
		return;

	} else if (c == 'r'){
		c = getC();
		return;

	} else if (c == '['){
		c = getC();
		if (c == 'a')
			c = getC();
		else
			error("a");

		if (c == '(')
			c = getC();
		else
			error("(");

		if (c == ')')
			c = getC();
		else
			error(")");
		
		if (c == ']')
			c = getC();
		else
			error("]");
		return;

	} else{
		error("( a e r [");
	}
}

void A(){
	if (c == 'a'){
		c = getC();
		G();
		if (c == '=')
			c = getC();
		else
			error("=");
		CP();
		if (c == ':')
			c = getC();
		else
			error(":");
		return;

	} else{
		error("a");
	}
}

void CP(){
	if (c == '+'){
		c = getC();
		ZP();
		if (c == ',')
			c = getC();
		else
			error(",");
		ZP();
		SP();
		return;

	} else if ( c == '(' || c == 'a' || c == 'e' || c == 'r' || c == '['){
		E();
		return;

	} else if (c == 's'){
		c = getC();
		return;

	} else {
		error("+ ( a e r [ s");
	}
}

void ZP(){
	if (c == 's'){
		c = getC();
		return;

	} else if (c == 'a'){
		c = getC();
		G();
		return;

	} else{
		error("s a");
	}
}

void SP(){
	if (c == ','){
		c = getC();
		ZP();
		SP();
		return;

	} else if (c == ':'){
		return;

	} else {
		error(", :");
	}
}

void error(char *charEsperado){
	nError++;
	printf("\n---Error sintactico: Se esperaba ->|| %s ||<-\tY se leyó ->|| %c ||<-\n\n----------Seguimos leyendo cadena de atomos --------\n",charEsperado,c);
}

void errorSemantico(char* charEsperado){
	nError++;
	printf("\n---Error semantico:%s \n\n----------Seguimos leyendo cadena de atomos --------\n",charEsperado);
}

void showNumErrores(){
	printf("Errores sintacticos: %d\n",nError);
}

