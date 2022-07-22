#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/Queue.h"
#include "header/Tree.h"
#include "header/pQueue.h"

#define TRUE 1
#define FALSE 0

typedef struct pkgdMsg{
  Tree tree;
  char* message;
} Msg;

Queue addChar(Queue, char*);
int repeatedChar(Queue, char);
Tree buildTree(QueueP);
QueueP fillQueueP(QueueP, List);
int* printTable(Tree, QueueP);
void printData(Tree, char, char*, int*);
char* printableChar(char);
void printDiv(char,char, char, char);
Msg encode(char*);
char* encodeChar(Tree,char, char*);
void decode(Msg);
int decodeChar(Tree, char*, int);
char* charArray(int);
char* addBit(char*, const char*);
Msg newPkgdMessage(Tree , char*);
char* getMessage(Msg);
Tree getTree(Msg);

int main(int argc, char *argv[]) {

  Msg pkgdMessage = encode(argv[1]);

  decode(pkgdMessage);

  return 0;
}

Msg encode(char* message){
  int * totals, i=0;
  QueueP p, q;
  char* codedMessage;

  Queue caracters = addChar(newQueue(), message); //Almacena y cuenta los caracteres en una lista
  p = fillQueueP(newQueueP(), toList(caracters)); //Encola los caracteres a una cola de prioridad
  q = fillQueueP(newQueueP(), toList(caracters)); //Auxiliar

  Tree t = buildTree(p); //Construye el arbol
  totals = printTable(t, q); //Imprime la tabla, y devuelvo los totales obtenidos
  codedMessage = charArray(totals[3]);//arreglo del numero total de bits

  while (message[i] != '\0') //Codifica cada caracter y lo concatena con los anteriores
    strcat(codedMessage, encodeChar(t,message[i++],charArray(1)));

  printf("\n\t+ Mensaje codificado:\n\n\t%s\n", codedMessage);

  return newPkgdMessage(t, codedMessage); //Devuelve el arbol y el mensage codificado
}
//Guarda el mensaje y el arbol en una estructura de datos
Msg newPkgdMessage(Tree t, char* s){
  Msg pM;
  pM.tree = t;
  pM.message = s;
  return pM;
}//Fin newPkgdMessage

char* getMessage(Msg pkm){
  return pkm.message;
}

Tree getTree(Msg pkm){
  return pkm.tree;
}
//Codifica el caracter dado, c
char* encodeChar(Tree t, char c , char* code){
  char* aux1, *aux2;
  if(isLeaf(t)){//Si llega a una hoja
    if(!(getCharT(t)==c)) //Y la hoja no es el caracter buscado
      strcpy(code,"");//Borra el codigo
    return code;
  }else{
    aux1 = strcpy(charArray(strlen(code)), code); //Copia el codigo que lleva
    aux2 = strcpy(charArray(strlen(code)), code);
    code = encodeChar(leftT(t),c,addBit(aux1,"0"));//Entra a la rama izq. y agrega el respectivo bit
    if(strlen(code) == 0) //Si no hallo el caracter en la izq.
      code = encodeChar(rightT(t),c,addBit(aux2,"1")); //Entra  la rama der.
    free(aux1);
    free(aux2);
    return code;
  }
}
//Imprime la tabla y devuelve los totales obtenidos
int* printTable(Tree t, QueueP p){
  int* totals = (int*)calloc(4,sizeof(int));
  NodeP q = getHead(p); //Obtiene el primer nodo de la cola
  printf("\n");
  printDiv(218,194,196,191); //Lienas de la tabla

  printf("\t%cCaracter%c Conteo %c   Codificacion   %c        Bits        %c\n"
  ,179,179,179,179, 179); //Encabezado de la tabla

  while (q!=NULL){ //Se recorre la cola, para imprimir los caracteres en orden
    printDiv(195,197,196,180);
    printData(t,getCharP(q), charArray(1), totals); //Imprime los datos del caracter
    q = getNextP(q);//Siguiente elemeto de la cola de prioridad
  }
  printDiv(195,197,196,180);
  printf("\t%c Total: %c %6d %c %16d %c %18d %c\n",
    179, //totals[0],
    179, totals[1],
    179, totals[2],
    179, totals[3], 179);//Totales al final de la tabla
  printDiv(192,193,196,217);

  printf("\n\tCodificacion de caracteres en ASCII: %d x 8 = %d bits",totals[0], totals[0]*8 );
  printf("\n\tCodificacion de caracteres: %d bits",totals[2]);
  printf("\n\tTotal de bits requerido: %d + %d + %d = %d bits\n",
    totals[3], totals[0]*8, totals[2], totals[3]+totals[0]*8+totals[2]);

  return totals;
}

void printData(Tree t, char c, char* code, int* totals){
  if(isLeaf(t)){ //Si es hoja
    if(getCharT(t)==c){ //Y es el caracter buscado
      totals[0] ++; // Caracteres diferentes
      totals[1] += getValue(t); //Letras en la frase
      totals[2] += strlen(code); //Longitudes de las codificaciones
      totals[3] += getValue(t)*strlen(code); //Bits totales
      printf("\t%c  %2s    %c %6d %c %16s %c %4d x %2d = %6d %c\n",
        179, printableChar(getCharT(t)),
        179, getValue(t),
        179, code,
        179, getValue(t), strlen(code),
             getValue(t)*strlen(code), 179);//Imprime los datos del caracter
    }
    return;
  }else{
    char* aux1 = strcpy(charArray(strlen(code)), code);//Copia el codigo conseguido
    char* aux2 = strcpy(charArray(strlen(code)), code);//hasta el momento
    printData(leftT(t),c, addBit(aux1,"0"), totals); //Ingresa a la rama izq.
    printData(rightT(t),c,addBit(aux2,"1"), totals); //Ingresa a la rama der.
    free(aux1);
    free(aux2);
  }
}
//Imprime el simbolo correspondiente a una secuencia de escape
char* printableChar(char c){
  char* s = charArray(2);
  switch (c) {
    case ' ':
      strcpy(s,"\\s");
    break;
    case '\a':
      strcpy(s,"\\a");
    break;
    case '\b':
      strcpy(s,"\\b");
    break;
    case '\f':
      strcpy(s,"\\f");
    break;
    case '\n':
      strcpy(s,"\\n");
    break;
    case '\r':
      strcpy(s,"\\r");
    break;
    case '\t':
      strcpy(s,"\\t");
    break;
    case '\v':
      strcpy(s,"\\v");
    break;
    case '\\':
      strcpy(s,"\\\\");
    break;
    case '\'':
      strcpy(s,"\\\'");
    break;
    case '\"':
      strcpy(s,"\\\"");
    break;
    case '\?':
      strcpy(s,"\\?");
    break;
    default:
      sprintf(s,"%c",c);
  }
  return s;
}
//Imprime el marco para la tabla
void printDiv(char inicio,char medio, char linea, char fin){
  int i, m=2; //m: margen
	printf("\t%c",inicio);
	for(i=0; i<6+m; i++)//Caracteres
		printf("%c",linea);
	printf("%c",medio);
	for(i=0; i<6+m; i++)//Conteo
		printf("%c",linea);
  printf("%c",medio);
	for(i=0; i<16+m;i++)//Codificacion
    printf("%c",linea);
  printf("%c",medio);
	for(i=0; i<18+m; i++)//Bits
		printf("%c",linea);
	printf("%c\n",fin);
	return;
}
//Reserva memoria para un arregle de caracteres de tamano n (mas fin de cadena)
char* charArray(int n){
  return (char*)calloc(n+1,sizeof(char));
}
//Añade un bit a la cadena del codigo
char* addBit(char* code, const char* c){
    code = (char*)realloc(code, strlen(code)+1); //Redimenciona el arreglo
    return strcat(code,c); //Agrega el bit al final de la cadena
}
//Costruye el arbol de la codificación
Tree buildTree(QueueP p){
  NodeT LNode, RNode;
  int n;

  if(getHead(p)==getTail(p))//[CASO BASE] Si solo queda un nodo en la cola
    return first(p);// Devuelve ese nodo (aka Tree)
  LNode = first(p); //Tomamos el primer nodo de la cola
  p = deQueueP(p);  //Desencolamos ese nodo
  RNode = first(p); //Tomamos el nuevo primer nodo
  p = deQueueP(p);  //Desencolamos ese nodo
  n = getValue(LNode)+getValue(RNode); //Suma de los pesos de los nodos
  p = enQueueP(p,newNodeT(LNode,RNode,n,'\0'), n); //Crea y agrega el nodo a la cola de prioridad
  return buildTree(p); //Llamada recursiva
}
//Agrega y cuenta los caracteres del mensaje una la lista
Queue addChar(Queue caracters, char* message){
  int i=0;
  while (message[i]!='\0'){
    if(!repeatedChar(caracters, message[i])) //Si no está repetido
      caracters = enQueue(caracters, message[i]); //Agregamos a la lista el caracter
    i++;
  }
  return caracters;
}
//Revisa si el caracter ya esta en la lista
int repeatedChar(Queue caracters, char c){
  List first = toList(caracters);
    while (first!=NULL){
      if(getChar(first) == c){//Si encuentra el caracter repetido
        setCounter(first, getCounter(first)+1);//Aumenta el contador
        return TRUE;
      }
      first = getNext(first);
    }
  return FALSE; //Devuelve si encontró o no elcaracter repetido
}
//Llena la cola de prioridad con los elemetos de la lista
QueueP fillQueueP(QueueP p, List l){
  while (l!=NULL){//Crea y agrega un nodo de arbol y su respectivo peso
    p = enQueueP(p, newNodeT(newTree(),newTree(), getCounter(l), getChar(l)), getCounter(l));
    l = getNext(l);
  }
  return p;
}

void decode(Msg pkgdMsg){
  int i=0;
  Tree tree = getTree(pkgdMsg); //Recupera el arbol para la decodificación
  char* codedMessage = getMessage(pkgdMsg); //Recupera el mensaje codificado
  printf("\n\t+ Mensaje decodificado:\n\n\t");
  while(codedMessage[i]!='\0'){//Recorre el mensaje codificado
    i = decodeChar(tree, codedMessage, i); //Decodifica cada caracter
  }
  printf("\n");
}

int decodeChar(Tree t, char*messege,int i){
  if(isLeaf(t)){//Si es hoja
    printf("%c",getCharT(t)); //Imprime el caracter correspondiente
    return i; //Contador para recordar la posicion en la cadena
  }else{
    if(messege[i] == '0'){ //dependido del caracter en la cadena codificada
      return decodeChar(leftT(t), messege,++i); //Entramos a la rama izq.
    }else{
      return decodeChar(rightT(t), messege,++i);//Entramos a la rama der.
    }
  }
}
