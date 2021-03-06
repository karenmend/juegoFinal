#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

#pragma region Declaración de variables.
GLFWwindow *window;

GLdouble xMarcos = -0.8f;
GLdouble yMarcos = -0.1f;
GLdouble velocidadMarcos = 1.0f;

GLdouble velocidad = 2.0f;
GLfloat velocidadActual = -0.6f;

float xSol = -0.7f;
float ySol = 0.6f;

GLdouble tiempoAnterior = 0.0;
GLdouble tiempoActual = 0.0;
GLdouble tiempoDiferencial = 0.0;
GLdouble tiempoCambioEscenario = 0.0;

GLdouble elementoXmov = 2.5f;
GLdouble elementoYmov = -0.6f;
GLdouble velocidadElementos = 0.8f;

GLdouble xTronco = 0.8f;
GLdouble yTronco = -0.1f;

GLdouble xTroncoDecierto = 12.0f;
GLdouble yTroncoDecierto = -0.47f;

GLdouble xTroncoInvierno = 0.5f;
GLdouble yTroncoInvierno = 0.6f;

GLfloat rEnemigo = 1.0f;
GLfloat gEnemigo = 1.0f;
GLfloat bEnemigo = 1.0f;

GLfloat aceleracion = 0.9f;
GLfloat desaceleracion = 0.5f;

GLdouble velocidadEnemigo = 0.8f;

GLdouble xEnemigoArbol = 1.0f;
GLdouble yEnemigoArbol = 0;

GLdouble xEnemigoArbusto = 5.0f;
GLdouble yEnemigoArbusto = -0.87f;

GLdouble xEnemigoCactus = 50.0f;
GLdouble yEnemigoCactus = -0.47f;

GLdouble xEnemigoMonoNieve = 100.0f;
GLdouble yEnemigoMonoNieve = -0.47f;

GLdouble xEnemigoAguaRio = 112.0f;
GLdouble yEnemigoAguaRio = -0.7f;

bool reinicio = false;
int contadorbrincos = 0;

enum Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion direccionBolita = Direccion::Izquierda;
Direccion direccionBolita2 = Direccion::Arriba;
#pragma endregion

void arbusto() {
	//ARBUSTO
	glPushMatrix();
	glTranslatef(xEnemigoArbusto, yEnemigoArbusto, 0.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.35, 0.17);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.15*cos((double)i*3.14159 / 180.0) - 0.8, 0.1* sin((double)i*3.14159 / 180.0) + 0.4, 0);
	}
	glEnd();
	glPopMatrix();

}

void arbolDia() {
	glPushMatrix();
	glTranslatef(xEnemigoArbol, yEnemigoArbol, 0.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.06, 0.05);
	glVertex3f(0.1f, -0.6f, 0.0f);
	glVertex3f(0.1f, -0.4f, 0.0f);
	glVertex3f(0.05f, -0.4f, 0.0f);
	glVertex3f(0.05f, -0.6f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.035, 0.57, 0.26);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.1*cos((double)i*3.14159 / 180.0) + 0.07, 0.15* sin((double)i*3.14159 / 180.0) - 0.33, 0);
	}
	glEnd();
	glPopMatrix();
}

void rio() {
	glPushMatrix();
	glTranslatef(xEnemigoAguaRio, yEnemigoAguaRio, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.07, 0.66, 0.89);
	glVertex3f(-0.15f, 0.2f, 0.0f);
	glVertex3f(-0.15f, -0.2f, 0.0f);
	glVertex3f(0.15f, -0.2f, 0.0f);
	glVertex3f(0.15f, 0.2f, 0.0f);
	glEnd();
	glPopMatrix();
}

void monoDeNieve() {
	//MONODENIEVE
	//cuerpo
	glPushMatrix();
	glTranslatef(xEnemigoMonoNieve, yEnemigoMonoNieve, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.68, 0.9, 0.94);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.09*cos((double)i*3.14159 / 180.0) + 0.0, 0.09* sin((double)i*3.14159 / 180.0) + -0.2, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.68, 0.9, 0.94);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.07*cos((double)i*3.14159 / 180.0) + 0.0, 0.07* sin((double)i*3.14159 / 180.0) + -0.1, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.68, 0.9, 0.94);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.05*cos((double)i*3.14159 / 180.0) + 0.0, 0.05* sin((double)i*3.14159 / 180.0) + 0.0, 0);
	}
	glEnd();

	//Botones
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.01*cos((double)i*3.14159 / 180.0) + 0.0, 0.01* sin((double)i*3.14159 / 180.0) + -0.2, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.01*cos((double)i*3.14159 / 180.0) + 0.0, 0.01* sin((double)i*3.14159 / 180.0) + -0.1, 0);
	}
	glEnd();

	//Ojos
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.007*cos((double)i*3.14159 / 180.0) - 0.02, 0.007* sin((double)i*3.14159 / 180.0) + -0.0, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.007*cos((double)i*3.14159 / 180.0) + 0.02, 0.007* sin((double)i*3.14159 / 180.0) + -0.0, 0);
	}
	glEnd();


	glPopMatrix();
}

void cactus() {
	glPushMatrix();
	glTranslatef(xEnemigoCactus, yEnemigoCactus, 0.0f);

	//Sahuaro1
	glBegin(GL_POLYGON);
	glColor3f(0.03f, 0.5f, 0.05f);
	//base
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);
	//izquierda-bajo
	glVertex3f(0.05f, -0.05f, 0.0f);
	//brazo-izquierdo
	glVertex3f(0.1f, -0.05f, 0.0f);
	glVertex3f(0.1f, -0.0f, 0.0f);
	glVertex3f(0.07f, -0.0f, 0.0f);
	glVertex3f(0.07f, -0.05f, 0.0f);
	//termina-brazo
	glVertex3f(0.05f, -0.05f, 0.0f);
	glVertex3f(0.05f, 0.15f, 0.0f);
	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(0.0f, -0.05f, 0.0f);
	//brazo-derecho
	glVertex3f(-0.02f, -0.05f, 0.0f);
	glVertex3f(-0.02f, -0.0f, 0.0f);
	glVertex3f(-0.02f, -0.0f, 0.0f);
	glVertex3f(-0.05f, -0.05f, 0.0f);
	glEnd();
	glPopMatrix();
}	

void dibujarTroncoDecierto() {
	glPushMatrix();
	glTranslatef(xTroncoDecierto, yTroncoDecierto, 0);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.1, 0.05);
	glVertex2f(0.1, -0.2);
	glVertex2f(-0.1, -0.2);
	glVertex2f(-0.1, 0.05);
	glEnd();


	glPopMatrix();
}

void checarColision() {

	if (xEnemigoCactus < xMarcos + 0.1 &&
		xEnemigoCactus > xMarcos - 0.1 &&
		yEnemigoCactus < yMarcos + 0.3 &&
		yEnemigoCactus > yMarcos - 0.1) {

		gEnemigo = 0.0;
		bEnemigo = 0.0;
		exit(EXIT_SUCCESS);
	}

	if ( xEnemigoMonoNieve< xMarcos + 0.1 &&
		xEnemigoMonoNieve > xMarcos - 0.1 &&
		yEnemigoMonoNieve < yMarcos + 0.3 &&
		yEnemigoMonoNieve > yMarcos - 0.1) {

		
		exit(EXIT_SUCCESS);
	}

	if (xEnemigoAguaRio< xMarcos + 0.1 &&
		xEnemigoAguaRio > xMarcos - 0.1 &&
		yEnemigoAguaRio < yMarcos + 0.3 &&
		yEnemigoAguaRio > yMarcos - 0.1) {


		exit(EXIT_SUCCESS);
	}

	if (xEnemigoArbol< xMarcos + 0.1 &&
		xEnemigoArbol > xMarcos - 0.1 &&
		yEnemigoArbol < yMarcos + 0.3 &&
		yEnemigoArbol > yMarcos - 0.1) {


		exit(EXIT_SUCCESS);
	}

	if (xEnemigoArbusto< xMarcos + 0.1 &&
		xEnemigoArbusto > xMarcos - 0.1 &&
		yEnemigoArbusto < yMarcos + 0.3 &&
		yEnemigoArbusto > yMarcos - 0.1) {


		exit(EXIT_SUCCESS);
	}
}

void moverCuadros() {
	
	if (xEnemigoCactus > -1.2) {
		xEnemigoCactus -= (velocidadEnemigo * tiempoDiferencial)*1.5;
	}

	if (xEnemigoMonoNieve > -1.2) {
		xEnemigoMonoNieve -= (velocidadEnemigo * tiempoDiferencial)*2;
	}

	if (xEnemigoAguaRio > -1.2) {
		xEnemigoAguaRio -= velocidadEnemigo * tiempoDiferencial;
	}

	if (xEnemigoArbol > -1.2) {
		xEnemigoArbol -= velocidadEnemigo * tiempoDiferencial;
	}

	if (xEnemigoArbusto > -1.2) {
		xEnemigoArbusto -= velocidadEnemigo * tiempoDiferencial;
	}


	if (tiempoActual < 60)
	{
		if (xEnemigoArbol > 1.1f) {
			xEnemigoArbol -= 4;
		}

		else if (xEnemigoArbol < -1.1f) {
			xEnemigoArbol += 4;
		}

	}
	
	else if (tiempoActual < 120)
	{
		if (xEnemigoCactus > 1.1f) {
			xEnemigoCactus -= 3;
		}

		else if (xEnemigoCactus < -1.1f) {
			xEnemigoCactus += 3;
		}

	}

	else if (tiempoActual < 180)
	{
		if (xEnemigoMonoNieve > 1.1f) {
			xEnemigoMonoNieve -= 3;
		}

		else if (xEnemigoMonoNieve < -1.1f) {
			xEnemigoMonoNieve += 3;
		}

	}

}

#pragma region Escenario.
void sol()
{
	//sol
	glBegin(GL_POLYGON);
	glColor3f(1, .8, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + xSol, 0.3* sin((double)i*3.14159 / 180.0) + ySol, 0.3);
	}
	glEnd();
}

void sueloVerde() {
	glBegin(GL_POLYGON);
	glColor3f(0.035, 0.57, 0.26);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void sueloDesierto() {
	glBegin(GL_POLYGON);

	glColor3f(0.82, 0.58, 0.17);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void sueloNevado() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, 0.0f);
	glEnd();
}

void dibujarEscenarioDia() {
	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.05f, 0.88f, 0.92f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();

	//Nubes
	glBegin(GL_POLYGON);
	glColor3f(.85, .82, .82);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.15, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.2, 0.1* sin((double)i*3.14159 / 180.0) + 0.5, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.2, 0.1* sin((double)i*3.14159 / 180.0) + 0.7, 0);
	}
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.2*cos((double)i*3.14159 / 180.0) + 0.4, 0.1* sin((double)i*3.14159 / 180.0) + 0.6, 0);
	}
	glEnd();

}

void dibujarEscenarioTarde() {
	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.92f, 0.49f, 0.11f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();
}

void dibujarEscenarioNoche() {

	//Cielo
	glBegin(GL_POLYGON);
	glColor3f(0.04f, 0.08f, 0.15f);
	glVertex3f(-1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, -0.51, 1.0f);
	glVertex3f(1.0f, 1.0, 1.0f);
	glVertex3f(-1.0f, 1.0, 1.0f);
	glEnd();

	//Luna
	glBegin(GL_POLYGON);
	glColor3f(0.89f, .90f, 0.92f);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.25*cos((double)i*3.14159 / 180.0) - 0.7, 0.3* sin((double)i*3.14159 / 180.0) + 0.6, 0.3);
	}
	glEnd();

	//Estrellas
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.3f, 0.7f, 0.0f);
	glVertex3f(-0.3f, 0.68f, 0.0f);
	glVertex3f(-0.32f, 0.68f, 0.0f);
	glVertex3f(-0.32f, 0.7f, 0.0f);
	glVertex3f(-0.3f, 0.7f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.2f, 0.75f, 0.0f);
	glVertex3f(0.2f, 0.73f, 0.0f);
	glVertex3f(0.22f, 0.73f, 0.0f);
	glVertex3f(0.22f, 0.75f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.8f, 0.75f, 1.0f);
	glVertex3f(0.8f, 0.73f, 1.0f);
	glVertex3f(0.78f, 0.73f, 1.0f);
	glVertex3f(0.78f, 0.75f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.3f, 1.0f);
	glVertex3f(0.0f, 0.28f, 1.0f);
	glVertex3f(0.02f, 0.28f, 1.0f);
	glVertex3f(0.02f, 0.3f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.3f, 1.0f);
	glVertex3f(0.5f, 0.28f, 1.0f);
	glVertex3f(0.48f, 0.28f, 1.0f);
	glVertex3f(0.48f, 0.3f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.8f, 0.0f, 1.0f);
	glVertex3f(-0.8f, -0.02f, 1.0f);
	glVertex3f(-0.78f, -0.02f, 1.0f);
	glVertex3f(-0.78f, 0.0f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.4f, -0.05f, 1.0f);
	glVertex3f(-0.4f, -0.03f, 1.0f);
	glVertex3f(-0.38f, -0.03f, 1.0f);
	glVertex3f(-0.38f, -0.05f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.2f, -0.07f, 1.0f);
	glVertex3f(0.2f, -0.09f, 1.0f);
	glVertex3f(0.22f, -0.09f, 1.0f);
	glVertex3f(0.22f, -0.07f, 1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.7f, -0.05f, 1.0f);
	glVertex3f(0.7f, -0.07f, 1.0f);
	glVertex3f(0.72f, -0.07f, 1.0f);
	glVertex3f(0.72f, -0.05f, 1.0f);
	glEnd();
}
#pragma endregion

void dibujarMarco() {
	glPushMatrix();
	glTranslatef(xMarcos, yMarcos, 0.0f);
	glScalef(0.6f, 0.6f, 0.0f);
	glPointSize(10.5);
	glBegin(GL_POINTS);
	//Pierna izquierda
	glColor3f(1.0f, 0.8f, 0.6f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.02f, 0.0f);
	glVertex2f(0.02f, 0.0f);
	glVertex2f(0.02f, 0.02f);
	glVertex2f(0.04f, 0.02f);
	glVertex2f(0.04f, 0.00f);
	glVertex2f(0.00f, 0.02f);
	glVertex2f(0.00f, 0.04f);
	glVertex2f(0.02f, 0.04f);

	//Patineta
	glColor3f(0.0f, 0.53f, 1.0f);
	glVertex2f(-0.08f, 0.0f);
	glVertex2f(-0.06f, -0.02f);
	glVertex2f(-0.04f, -0.02f);
	glVertex2f(-0.02f, -0.02f);
	glVertex2f(0.0f, -0.02f);
	glVertex2f(0.02f, -0.02f);
	glVertex2f(0.04f, -0.02f);
	glVertex2f(0.06f, -0.02f);
	glVertex2f(0.08f, -0.02f);
	glVertex2f(0.1f, -0.02f);
	glVertex2f(0.12f, -0.02f);
	glVertex2f(0.14f, -0.02f);
	glVertex2f(0.16f, -0.02f);
	glVertex2f(0.18f, -0.02f);
	glVertex2f(0.2f, -0.02f);
	glVertex2f(0.22f, -0.02f);
	glVertex2f(0.24f, -0.02f);
	glVertex2f(0.26f, -0.02f);
	glVertex2f(0.28f, -0.02f);
	glVertex2f(0.3f, 0.0f);
	//Ruedas
	glColor3f(0.20f, 0.7f, 0.85f);
	glVertex2f(0.18f, -0.04f);
	glVertex2f(0.2f, -0.04f);
	glVertex2f(0.2f, -0.06f);
	glVertex2f(0.18f, -0.06f);

	glVertex2f(0.0f, -0.04f);
	glVertex2f(0.02f, -0.04f);
	glVertex2f(0.02f, -0.06f);
	glVertex2f(0.0f, -0.06f);

	//Pantalon
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.04f, 0.04f);
	glVertex2f(0.04f, 0.06f);
	glVertex2f(0.02f, 0.06f);
	glVertex2f(0.00f, 0.06f);
	glVertex2f(0.00f, 0.08f);
	glVertex2f(0.02f, 0.08f);
	glVertex2f(0.04f, 0.08f);
	glVertex2f(0.02f, 0.1f);
	glVertex2f(0.04f, 0.1f);

	glVertex2f(0.06f, 0.1f);
	glVertex2f(0.08f, 0.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.1f, 0.08f);
	glVertex2f(0.12f, 0.08f);
	glVertex2f(0.14f, 0.08f);
	glVertex2f(0.16f, 0.1f);
	glVertex2f(0.18f, 0.12f);
	glVertex2f(0.2f, 0.12f);
	glVertex2f(0.22f, 0.1f);
	glVertex2f(0.24f, 0.08f);
	glVertex2f(0.22f, 0.12f);
	glVertex2f(0.22f, 0.14f);
	glVertex2f(0.2f, 0.14f);
	glVertex2f(0.18f, 0.14f);
	glVertex2f(0.16f, 0.14f);
	glVertex2f(0.16f, 0.12f);
	glVertex2f(0.14f, 0.1f);
	glVertex2f(0.12f, 0.1f);
	glVertex2f(0.14f, 0.12f);
	glVertex2f(0.12f, 0.12f);
	glVertex2f(0.1f, 0.12f);
	glVertex2f(0.08f, 0.12f);
	glVertex2f(0.06f, 0.12f);
	glVertex2f(0.04f, 0.12f);
	glVertex2f(0.02f, 0.12f);
	glVertex2f(0.02f, 0.14f);
	glVertex2f(0.04f, 0.14f);
	glVertex2f(0.06f, 0.14f);
	glVertex2f(0.08f, 0.14f);
	glVertex2f(0.1f, 0.14f);
	glVertex2f(0.12f, 0.14f);
	glVertex2f(0.14f, 0.14f);
	glVertex2f(0.1f, 0.16f);
	glVertex2f(0.08f, 0.16f);
	glVertex2f(0.06f, 0.16f);
	glVertex2f(0.04f, 0.16f);
	glVertex2f(0.22f, 0.08f);
	glVertex2f(0.2f, 0.08f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.18f, 0.1f);
	glVertex2f(0.18f, 0.1f);
	glVertex2f(0.18f, 0.08f);
	glVertex2f(0.16f, 0.08f);
	glVertex2f(0.16f, 0.06f);
	glVertex2f(0.18f, 0.06f);
	glVertex2f(0.2f, 0.06f);
	glVertex2f(0.22f, 0.06f);
	glVertex2f(0.22f, 0.04f);
	glVertex2f(0.2f, 0.04f);
	glVertex2f(0.18f, 0.04f);
	glVertex2f(0.16f, 0.04f);
	glVertex2f(0.16f, 0.02f);

	glColor3f(1.0f, 0.8f, 0.7f);
	glVertex2f(0.18f, 0.02f);
	glVertex2f(0.2f, 0.02f);
	glVertex2f(0.22f, 0.02f);
	glVertex2f(0.24f, 0.02f);
	glVertex2f(0.24f, 0.00f);
	glVertex2f(0.22f, 0.00f);
	glVertex2f(0.2f, 0.00f);
	glVertex2f(0.18f, 0.00f);
	glVertex2f(0.16f, 0.00f);

	glVertex2f(0.04f, 0.18f);
	glVertex2f(0.06f, 0.18f);
	glVertex2f(0.08f, 0.18f);
	glVertex2f(0.1f, 0.18f);
	glVertex2f(0.12f, 0.18f);
	glVertex2f(0.12f, 0.16f);
	glVertex2f(0.14f, 0.16f);
	glVertex2f(0.16f, 0.16f);
	glVertex2f(0.18f, 0.16f);
	glVertex2f(0.2f, 0.16f);
	glVertex2f(0.2f, 0.18f);
	glVertex2f(0.18f, 0.18f);
	glVertex2f(0.16f, 0.18f);
	glVertex2f(0.14f, 0.18f);
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.18f, 0.2f);
	glVertex2f(0.16f, 0.2f);
	glVertex2f(0.14f, 0.2f);
	glVertex2f(0.12f, 0.2f);
	glVertex2f(0.1f, 0.2f);
	glVertex2f(0.08f, 0.2f);
	glVertex2f(0.06f, 0.2f);
	glVertex2f(0.04f, 0.2f);
	glVertex2f(0.04f, 0.22f);
	glVertex2f(0.06f, 0.22f);
	glVertex2f(0.08f, 0.22f);
	glVertex2f(0.1f, 0.22f);
	glVertex2f(0.12f, 0.22f);
	glVertex2f(0.14f, 0.22f);
	glVertex2f(0.16f, 0.22f);
	glVertex2f(0.18f, 0.22f);
	glVertex2f(0.2f, 0.22f);
	glVertex2f(0.22f, 0.22f);
	glVertex2f(0.24f, 0.22f);
	glVertex2f(0.26f, 0.2f);
	glVertex2f(0.28f, 0.2f);
	glVertex2f(0.3f, 0.18f);
	glVertex2f(0.3f, 0.2f);
	glVertex2f(0.3f, 0.22f);
	glVertex2f(0.32f, 0.22f);
	glVertex2f(0.28f, 0.22f);
	glVertex2f(0.26f, 0.22f);
	glVertex2f(0.3f, 0.24f);
	glVertex2f(0.28f, 0.24f);
	glVertex2f(0.26f, 0.24f);
	glVertex2f(0.24f, 0.24f);
	glVertex2f(0.22f, 0.24f);
	glVertex2f(0.2f, 0.24f);
	glVertex2f(0.2f, 0.26f);
	glVertex2f(0.22f, 0.26f);
	glVertex2f(0.24f, 0.26f);
	glVertex2f(0.26f, 0.26f);
	glVertex2f(0.32f, 0.2f);
	glVertex2f(0.32f, 0.22f);

	glVertex2f(0.24f, 0.26f);
	glVertex2f(0.24f, 0.24f);
	glVertex2f(0.22f, 0.24f);
	glVertex2f(0.2f, 0.24f);
	glVertex2f(0.18f, 0.24f);
	glVertex2f(0.16f, 0.24f);
	glVertex2f(0.14f, 0.24f);
	glVertex2f(0.12f, 0.24f);
	glVertex2f(0.1f, 0.24f);
	glVertex2f(0.08f, 0.24f);
	glVertex2f(0.06f, 0.24f);
	glVertex2f(0.04f, 0.24f);
	glVertex2f(0.18f, 0.26f);
	glVertex2f(0.16f, 0.26f);
	glVertex2f(0.14f, 0.26f);
	glVertex2f(0.12f, 0.26f);
	glVertex2f(0.1f, 0.26f);
	glVertex2f(0.08f, 0.26f);
	glVertex2f(0.06f, 0.26f);
	glVertex2f(0.04f, 0.26f);

	glVertex2f(0.02f, 0.26f);
	glVertex2f(0.00f, 0.26f);
	glVertex2f(-0.02f, 0.24f);
	glVertex2f(-0.04f, 0.24f);
	glVertex2f(-0.04f, 0.22f);
	glVertex2f(-0.04f, 0.2f);
	glVertex2f(-0.06f, 0.2f);
	glVertex2f(-0.04f, 0.18f);
	glVertex2f(-0.06f, 0.18f);
	glVertex2f(-0.08f, 0.18f);
	glVertex2f(-0.08f, 0.2f);
	glVertex2f(-0.06f, 0.22f);
	glVertex2f(-0.06f, 0.24f);
	glVertex2f(-0.06f, 0.26f);
	glVertex2f(-0.04f, 0.26f);
	glVertex2f(-0.02f, 0.26f);
	glVertex2f(-0.04f, 0.28f);
	glVertex2f(-0.02f, 0.28f);
	glVertex2f(0.0f, 0.28f);
	glVertex2f(-0.02f, 0.2f);

	glVertex2f(0.02f, 0.28f);
	glVertex2f(0.04f, 0.28f);
	glVertex2f(0.06f, 0.28f);
	glVertex2f(0.08f, 0.28f);
	glVertex2f(0.1f, 0.28f);
	glVertex2f(0.12f, 0.28f);
	glVertex2f(0.14f, 0.28f);
	glVertex2f(0.16f, 0.28f);
	glVertex2f(0.18f, 0.28f);
	glVertex2f(0.2f, 0.28f);
	glVertex2f(0.22f, 0.28f);

	glVertex2f(0.16f, 0.3f);
	glVertex2f(0.14f, 0.3f);
	glVertex2f(0.12f, 0.3f);
	glVertex2f(0.1f, 0.3f);
	glVertex2f(0.08f, 0.3f);

	glVertex2f(0.06f, 0.32f);
	glVertex2f(0.04f, 0.34f);
	glVertex2f(0.02f, 0.36f);
	glVertex2f(0.02f, 0.38f);
	glVertex2f(0.02f, 0.4f);
	glVertex2f(0.02f, 0.42f);
	glVertex2f(0.04f, 0.44f);
	glVertex2f(0.06f, 0.46f);
	glVertex2f(0.08f, 0.48f);
	glVertex2f(0.1f, 0.48f);
	glVertex2f(0.12f, 0.48f);
	glVertex2f(0.14f, 0.48f);
	glVertex2f(0.16f, 0.48f);
	glVertex2f(0.18f, 0.46f);
	glVertex2f(0.2f, 0.44f);
	glVertex2f(0.22f, 0.42f);
	glVertex2f(0.22f, 0.4f);
	glVertex2f(0.22f, 0.38f);
	glVertex2f(0.22f, 0.36f);
	glVertex2f(0.2f, 0.34f);
	glVertex2f(0.18f, 0.32f);

	glVertex2f(0.16f, 0.32f);
	glVertex2f(0.14f, 0.32f);
	glVertex2f(0.12f, 0.32f);
	glVertex2f(0.1f, 0.32f);
	glVertex2f(0.08f, 0.32f);
	glVertex2f(0.06f, 0.34f);
	glVertex2f(0.08f, 0.34f);
	glVertex2f(0.1f, 0.34f);
	glVertex2f(0.12f, 0.34f);
	glVertex2f(0.14f, 0.34f);
	glVertex2f(0.16f, 0.34f);
	glVertex2f(0.18f, 0.34f);
	glVertex2f(0.04f, 0.36f);
	glVertex2f(0.06f, 0.36f);
	glVertex2f(0.08f, 0.36f);
	glVertex2f(0.1f, 0.36f);
	glVertex2f(0.12f, 0.36f);
	glVertex2f(0.14f, 0.36f);
	glVertex2f(0.16f, 0.36f);
	glVertex2f(0.18f, 0.36f);
	glVertex2f(0.2f, 0.36f);
	glVertex2f(0.04f, 0.38f);
	glVertex2f(0.06f, 0.38f);
	glVertex2f(0.08f, 0.38f);
	glVertex2f(0.1f, 0.38f);
	glVertex2f(0.12f, 0.38f);
	glVertex2f(0.14f, 0.38f);
	glVertex2f(0.16f, 0.38f);
	glVertex2f(0.18f, 0.38f);
	glVertex2f(0.2f, 0.38f);
	glVertex2f(0.04f, 0.4f);
	glVertex2f(0.06f, 0.4f);
	glVertex2f(0.08f, 0.4f);
	glVertex2f(0.1f, 0.4f);
	glVertex2f(0.12f, 0.4f);
	glVertex2f(0.14f, 0.4f);
	glVertex2f(0.16f, 0.4f);
	glVertex2f(0.18f, 0.4f);
	glVertex2f(0.2f, 0.4f);
	glVertex2f(0.04f, 0.42f);
	glVertex2f(0.06f, 0.42f);
	glVertex2f(0.08f, 0.42f);
	glVertex2f(0.1f, 0.42f);
	glVertex2f(0.12f, 0.42f);
	glVertex2f(0.14f, 0.42f);
	glVertex2f(0.16f, 0.42f);
	glVertex2f(0.18f, 0.42f);
	glVertex2f(0.2f, 0.42f);

	glVertex2f(0.06f, 0.44f);
	glVertex2f(0.08f, 0.44f);
	glVertex2f(0.1f, 0.44f);
	glVertex2f(0.12f, 0.44f);
	glVertex2f(0.14f, 0.44f);
	glVertex2f(0.16f, 0.44f);
	glVertex2f(0.18f, 0.44f);
	glVertex2f(0.16f, 0.46f);
	glVertex2f(0.14f, 0.46f);
	glVertex2f(0.12f, 0.46f);
	glVertex2f(0.1f, 0.46f);
	glVertex2f(0.08f, 0.46f);

	glEnd();

	glPopMatrix();
}

void saltoMarcos() {
	int estadoTeclaArribaMarco = glfwGetKey(window, GLFW_KEY_UP);

	if ((estadoTeclaArribaMarco == GLFW_PRESS || estadoTeclaArribaMarco == GLFW_REPEAT) && contadorbrincos == 0 && (yMarcos >= -0.6f && yMarcos <= 0.5f))
	{
		if (yMarcos <= 0.5f)
		{
			yMarcos += (velocidadMarcos * tiempoDiferencial) * 2;
		}
		if (yMarcos >= 0.5f)
		{
			yMarcos = 0.5f;
			contadorbrincos = 1;
		}

	}
	else
		if (estadoTeclaArribaMarco == GLFW_RELEASE)
		{
			contadorbrincos = 1;
		}
	if (contadorbrincos == 1)
	{
		if (yMarcos >= -0.6f)
		{
			yMarcos -= velocidad * tiempoDiferencial;
		}
		if (yMarcos <= -0.6f)
		{
			yMarcos = -0.6f;
			contadorbrincos = 0;
		}
	}
}

void elementosVerde()
{
	//AGUA
	glBegin(GL_POLYGON);
	glColor3f(0.07, 0.66, 0.89);
	glVertex3f(-0.35f, -0.5f, 0.0f);
	glVertex3f(-0.35f, -1.0f, 0.0f);
	glVertex3f(-0.15f, -1.0f, 0.0f);
	glVertex3f(-0.15f, -0.5f, 0.0f);
	glEnd();

	//ARBUSTO
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.35, 0.17);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.15*cos((double)i*3.14159 / 180.0) - 0.7, 0.1* sin((double)i*3.14159 / 180.0) + -0.5, 0);
	}
	glEnd();

	//PIEDRA
	glBegin(GL_POLYGON);
	glColor3f(0.37, 0.39, 0.39);
	glVertex3f(0.75f, -0.6f, 0.0f);
	glVertex3f(0.73f, -0.5f, 0.0f);
	glVertex3f(0.75f, -0.45f, 0.0f);
	glVertex3f(0.85f, -0.45f, 0.0f);
	glVertex3f(0.88f, -0.5f, 0.0f);
	glVertex3f(0.85f, -0.6f, 0.0f);
	glEnd();

	//PINO
	//Tronco
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.06, 0.05);
	glVertex3f(0.4f, -0.6f, 0.0f);
	glVertex3f(0.4f, -0.4f, 0.0f);
	glVertex3f(0.45f, -0.4f, 0.0f);
	glVertex3f(0.45f, -0.6f, 0.0f);
	glEnd();
	//Hojas
	glBegin(GL_POLYGON);
	glColor3f(0.035, 0.57, 0.26);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.1*cos((double)i*3.14159 / 180.0) + 0.425, 0.15* sin((double)i*3.14159 / 180.0) + -0.33, 0);
	}
	glEnd();

	//Tronco
	glBegin(GL_POLYGON);
	glColor3f(0.69, 0.31, 0.07);
	glVertex3f(0.1f, -0.6f, 0.0f);
	glVertex3f(0.1f, -0.4f, 0.0f);
	glVertex3f(0.05f, -0.4f, 0.0f);
	glVertex3f(0.05f, -0.6f, 0.0f);
	glEnd();
}

void elementosDesierto()
{
	//Sahuaro1
	glBegin(GL_POLYGON);
	glColor3f(0.03f, 0.5f, 0.05f);
	//base
	glVertex3f(-0.5f, -0.6f, 0.0f);
	glVertex3f(-0.55f, -0.6f, 0.0f);
	//izquierda-bajo
	glVertex3f(-0.55f, -0.45f, 0.0f);
	//brazo-izquierdo
	glVertex3f(-0.6f, -0.45f, 0.0f);
	glVertex3f(-0.6f, -0.4f, 0.0f);
	glVertex3f(-0.57f, -0.4f, 0.0f);
	glVertex3f(-0.57f, -0.45f, 0.0f);
	//termina-brazo
	glVertex3f(-0.55f, -0.45f, 0.0f);
	glVertex3f(-0.55f, -0.25f, 0.0f);
	glVertex3f(-0.5f, -0.25f, 0.0f);
	glVertex3f(-0.5f, -0.45f, 0.0f);
	//brazo-derecho
	glVertex3f(-0.48f, -0.45f, 0.0f);
	glVertex3f(-0.48f, -0.4f, 0.0f);
	glVertex3f(-0.45f, -0.4f, 0.0f);
	glVertex3f(-0.45f, -0.45f, 0.0f);
	glEnd();

	//Sahuaro2
	glBegin(GL_POLYGON);
	glColor3f(0.03f, 0.5f, 0.05f);
	//base
	glVertex3f(0.5f, -0.6f, 0.0f);
	glVertex3f(0.55f, -0.6f, 0.0f);
	//izquierda-bajo
	glVertex3f(0.55f, -0.45f, 0.0f);
	//brazo-izquierdo
	glVertex3f(0.6f, -0.45f, 0.0f);
	glVertex3f(0.6f, -0.4f, 0.0f);
	glVertex3f(0.57f, -0.4f, 0.0f);
	glVertex3f(0.57f, -0.45f, 0.0f);
	//termina-brazo
	glVertex3f(0.55f, -0.45f, 0.0f);
	glVertex3f(0.55f, -0.25f, 0.0f);
	glVertex3f(0.5f, -0.25f, 0.0f);
	glVertex3f(0.5f, -0.45f, 0.0f);
	//brazo-derecho
	glVertex3f(0.48f, -0.45f, 0.0f);
	glVertex3f(0.48f, -0.4f, 0.0f);
	glVertex3f(0.45f, -0.4f, 0.0f);
	glVertex3f(0.45f, -0.45f, 0.0f);
	glEnd();

	//AGUA
	glBegin(GL_POLYGON);
	glColor3f(0.07, 0.66, 0.89);
	glVertex3f(-0.15f, -0.5f, 0.0f);
	glVertex3f(-0.1f, -0.57f, 0.0f);
	glVertex3f(0.0f, -0.6f, 0.0f);
	glVertex3f(0.1f, -0.6f, 0.0f);
	glVertex3f(0.12f, -0.5f, 0.0f);
	glEnd();

	//PIEDRA
	glBegin(GL_POLYGON);
	glColor3f(0.37, 0.39, 0.39);
	glVertex3f(0.75f, -0.6f, 0.0f);
	glVertex3f(0.73f, -0.5f, 0.0f);
	glVertex3f(0.75f, -0.45f, 0.0f);
	glVertex3f(0.85f, -0.45f, 0.0f);
	glVertex3f(0.88f, -0.5f, 0.0f);
	glVertex3f(0.85f, -0.6f, 0.0f);
	glEnd();
}

void elementosNieve()
{
	//AGUA
	glBegin(GL_POLYGON);
	glColor3f(0.07, 0.66, 0.89);
	glVertex3f(-0.15f, -0.5f, 0.0f);
	glVertex3f(-0.1f, -0.57f, 0.0f);
	glVertex3f(0.0f, -0.6f, 0.0f);
	glVertex3f(0.1f, -0.57f, 0.0f);
	glVertex3f(0.15f, -0.5f, 0.0f);
	glEnd();

	//PIEDRA
	glBegin(GL_POLYGON);
	glColor3f(0.37, 0.39, 0.39);
	glVertex3f(-0.75f, -0.6f, 0.0f);
	glVertex3f(-0.73f, -0.5f, 0.0f);
	glVertex3f(-0.75f, -0.45f, 0.0f);
	glVertex3f(-0.85f, -0.45f, 0.0f);
	glVertex3f(-0.88f, -0.5f, 0.0f);
	glVertex3f(-0.85f, -0.6f, 0.0f);
	glEnd();

	//PINO
	//Tronco
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.06, 0.05);
	glVertex3f(-0.4f, -0.6f, 0.0f);
	glVertex3f(-0.4f, -0.55f, 0.0f);
	glVertex3f(-0.45f, -0.55f, 0.0f);
	glVertex3f(-0.45f, -0.6f, 0.0f);
	glEnd();
	//Hojas
	glBegin(GL_TRIANGLES);
	glColor3f(0.1f, 0.45f, 0.16f);
	glVertex3f(-0.5f, -0.55f, 0.0f);
	glVertex3f(-0.425f, -0.3f, 0.0f);
	glVertex3f(-0.35f, -0.55f, 0.0f);
	glEnd();

	//MONODENIEVE
	//cuerpo
	glBegin(GL_POLYGON);
	glColor3f(0.68, 0.9, 0.94);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.09*cos((double)i*3.14159 / 180.0) + 0.7, 0.09* sin((double)i*3.14159 / 180.0) + -0.6, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.68, 0.9, 0.94);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.07*cos((double)i*3.14159 / 180.0) + 0.7, 0.07* sin((double)i*3.14159 / 180.0) + -0.5, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.68, 0.9, 0.94);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.05*cos((double)i*3.14159 / 180.0) + 0.7, 0.05* sin((double)i*3.14159 / 180.0) + -0.4, 0);
	}
	glEnd();

	//Sombrero
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.51, 0.01);
	glVertex3f(0.67f, -0.36, 0.0);
	glVertex3f(0.67f, -0.26, 0.0);
	glVertex3f(0.73f, -0.26, 0.0);
	glVertex3f(0.73f, -0.36, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.51, 0.0);
	glVertex3f(0.65f, -0.37, 0.0);
	glVertex3f(0.65f, -0.35, 0.0);
	glVertex3f(0.75f, -0.35, 0.0);
	glVertex3f(0.75f, -0.37, 0.0);
	glEnd();

	//Botones
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.01*cos((double)i*3.14159 / 180.0) + 0.7, 0.01* sin((double)i*3.14159 / 180.0) + -0.6, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.01*cos((double)i*3.14159 / 180.0) + 0.7, 0.01* sin((double)i*3.14159 / 180.0) + -0.5, 0);
	}
	glEnd();

	//Ojos
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.007*cos((double)i*3.14159 / 180.0) + 0.68, 0.007* sin((double)i*3.14159 / 180.0) + -0.39, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex3f(0.007*cos((double)i*3.14159 / 180.0) + 0.72, 0.007* sin((double)i*3.14159 / 180.0) + -0.39, 0);
	}
	glEnd();
}

void movimientosElementos() 
{
	if (elementoXmov > -2) {
		elementoXmov -= velocidadElementos * tiempoDiferencial;
	}

}

void dibujar() {
	if (tiempoCambioEscenario > 180) tiempoCambioEscenario = 0;

	if (tiempoCambioEscenario <= 40)
	{
		if (tiempoCambioEscenario <= 20) dibujarEscenarioDia();
		else if (tiempoCambioEscenario > 20 && tiempoCambioEscenario <= 40) dibujarEscenarioTarde();
		sol();
		xSol += 0.00003;
		ySol -= 0.00003;
	}
	else if (tiempoCambioEscenario > 40 && tiempoCambioEscenario <= 60)
	{
		dibujarEscenarioNoche();
		xSol = -0.7;
		ySol = 0.6;
	}

	if (tiempoCambioEscenario > 60 && tiempoCambioEscenario <= 100)
	{
		if (tiempoCambioEscenario > 60 && tiempoCambioEscenario <= 80) dibujarEscenarioDia();
		else if (tiempoCambioEscenario > 80 && tiempoCambioEscenario <= 100) dibujarEscenarioTarde();
		sol();
		xSol += 0.00003;
		ySol -= 0.00003;
	}
	else if (tiempoCambioEscenario > 100 && tiempoCambioEscenario <= 120)
	{
		dibujarEscenarioNoche();
		xSol = -0.7;
		ySol = 0.6;
	}

	if (tiempoCambioEscenario > 120 && tiempoCambioEscenario <= 160)
	{
		if (tiempoCambioEscenario > 120 && tiempoCambioEscenario <= 140) dibujarEscenarioDia();
		else if (tiempoCambioEscenario > 140 && tiempoCambioEscenario <= 160) dibujarEscenarioTarde();
		sol();
		xSol += 0.00003;
		ySol -= 0.00003;
	}
	else if (tiempoCambioEscenario > 160 && tiempoCambioEscenario <= 180)
	{
		dibujarEscenarioNoche();
		xSol = -0.7;
		ySol = 0.6;
	}

	if (tiempoCambioEscenario <= 60) sueloVerde();
	else if (tiempoCambioEscenario > 60 && tiempoCambioEscenario <= 120) sueloDesierto();
	else if (tiempoCambioEscenario > 120 && tiempoCambioEscenario <= 180) sueloNevado();

	dibujarMarco();
	cactus();
	monoDeNieve();
	//rio();
	arbolDia();
	//arbusto();
}

void actualizar() {
	tiempoCambioEscenario = glfwGetTime();
	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;
	tiempoAnterior = tiempoActual;

	saltoMarcos();
	moverCuadros();
	checarColision();
}

int main()
{
	//Si no se puede inicializar glfw
	//Iniciamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamosla ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	//Si nopodemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;
	

	//ciclode dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(1, 1, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rutina de dibujo.
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}