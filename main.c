
//LIBRERIAS
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

//PROTOTIPOS DE LAS FUNCIONES
void gotoxy(int x, int y);
void ocultarCursor();
void cuadro();
void guardar_posicion();
void dibujar_cuerpo();
void borrar_cuerpo();
void teclear();
void comida();
bool perder();

//DECLARACION GLOBAL DE VARIABLES
int cuerpo[200][2];
int n = 1, tam = 10, dir = 3;
int x = 10, y = 12;
int xc = 30, yc = 15;
int velocidad = 60;
int puntos=0;
char tecla;


//FUNCION PRINCIPAL MAIN
int main(){
	system("mode con cols=80 lines=25");
 	gotoxy (35,1); printf("JUEGO SNAKE");
 	printf("\n\n");
	ocultarCursor();
 	cuadro();
 	gotoxy(xc, yc); printf("%c", 4);
 
 	while(tecla != ESC && perder()){
 		gotoxy (3,2); printf("PUNTUACION: %i",puntos);
		borrar_cuerpo();
		guardar_posicion();
		dibujar_cuerpo();
		comida();
		teclear();
		teclear();
 
		if(dir == 1) y--;
		if(dir == 2) y++;
		if(dir == 3) x++;
		if(dir == 4) x--;
 
		Sleep(velocidad);
 	}
 	
 	system("cls");
 	gotoxy (35,1); printf("JUEGO SNAKE");
 	cuadro();
 	gotoxy (22,12); printf("OBTUVISTE UNA PUNTUACION DE: %i",puntos);
 	gotoxy (22,14); printf("Presione una tecla para continuar..");
 	getch();
	return 0;
}
 


//FUNCION QUE REALIZA EL RECUADRO DEL JUEGO
void cuadro(){ 
	int i,v;
	
	for(i=2; i < 78; i++){
		gotoxy (i, 4); printf ("%c", 205);
 		gotoxy(i, 23); printf ("%c", 205); 
	}

	for(v=4; v < 23; v++){
 		gotoxy (2,v); printf ("%c", 186);
 		gotoxy(77,v); printf ("%c", 186); 
	}
	
 	gotoxy (2,4); printf ("%c", 201);
 	gotoxy (2,23); printf ("%c", 200);
 	gotoxy (77,4); printf ("%c", 187);
 	gotoxy(77,23); printf ("%c", 188); 
}

 
//FUNCION QUE GUARDA LA POSICION EN LA QUE SE ENCUENTRA LA SERPIENTE
void guardar_posicion(){
	cuerpo[n][0] = x;
 	cuerpo[n][1] = y;
 	n++;
 
 	if(n == tam) n = 1;
}

//FUNCION QUE DIBUJA EL CUERPO DE LA SERPIENTE
void dibujar_cuerpo(){
	int i;
	for(i = 1; i < tam; i++){
 		gotoxy(cuerpo[i][0] , cuerpo[i][1]); printf("*");
	}
}

//FUNCION QUE BORRA EL CUERPO DE LA SERPIENTE (SE BORRA LA ULTIMA PARTE DEL CUERPO)
void borrar_cuerpo(){
	gotoxy(cuerpo[n][0] , cuerpo[n][1]); printf(" ");
}
 

//FUNCION QUE DETECTA QUE TECLA SE ESTA PRESIONANDO
void teclear(){
	if(kbhit()){
		tecla = getch();
	 	switch(tecla){
	 		
			case ARRIBA : if(dir != 2) dir = 1; break;
	 		case ABAJO : if(dir != 1) dir = 2; break;
	 		case DERECHA : if(dir != 4) dir = 3; break;
	 		case IZQUIERDA : if(dir != 3) dir = 4; break;
		}
 	}
}

//FUNCION QUE MUESTRA LA COMIDA DE FORMA ALEATORIA EN ALGUNA ZONA DE LA PANTALLA 
void comida(){
	if(x == xc && y == yc){
		xc = (rand() % 73) + 4;
 		yc = (rand() % 18) + 5;
 		tam++;
 		puntos+=100;
 		gotoxy(xc, yc); printf("%c", 4);
	}
}

//FUNCION QUE VERIFICA SI SE TOPADO EL RECUADRO O SE HA CHOCADO CON EL MISMO CUERPO
bool perder(){
	int j;
	
	if(y == 4 || y == 23 || x == 2 || x == 77) 
		return false;
		
 	for(j = tam - 1; j > 0; j--){
	 	if(cuerpo[j][0] == x && cuerpo[j][1] == y)
	 	return false;
	}
	
	return true;
}


//FUNCION GOTOXY, SE ENVIAN COORDENADAS PARA X / Y, CON ESTO SE LOGRA POSICIONAR ALGUN MENSAJE EN UNA ZONA DETERMINADA DE LA PANTALLA
void gotoxy(int x, int y) 
{ 
 	HANDLE hCon; 
 	COORD dwPos; 
 
 	dwPos.X = x; 
 	dwPos.Y = y; 
 	hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
 	SetConsoleCursorPosition(hCon,dwPos); 
}

//FUNCION QUE OCULTA EL CURSOR
void ocultarCursor() {
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}



