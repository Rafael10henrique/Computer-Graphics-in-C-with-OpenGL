/*
 * Main.c
 *
 *  Created on: 30 de mai de 2018
 *      Author: Rafael Vieira.
 */

#include  <GL/gl.h>
#include  <GL/glut.h>
#include  <stdio.h>
#include  <math.h>

typedef struct {
	int xy;
	int x;
	int y;
}status;

int main(int argc, char **argv){

	void Linha(void);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(283,84);
	glutCreateWindow("CG");
	glutDisplayFunc(Linha);
	glClearColor(0,0,0,0);
	glutMainLoop();

	return 0;
}

void Linha(void){

	//Choose your points here:
	int x0=-8, y0=-4,  x1=0, y1=0, tx;
	double m, ty,e;
	status Inversor(int *x0, int *y0, int *x1, int *y1, double *m);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-15,15,-15,15);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(20.0);

	glBegin(GL_POINTS);
		glVertex2d(x0,y0);
	glEnd();

		glBegin(GL_LINES);
		glVertex2d(0,-50);
		glVertex2d(0,50);
		glVertex2d(-50,0);
		glVertex2d(50,0);
	glEnd();

	status k = Inversor(&x0,&y0,&x1,&y1,&m);

	int x=x0;
	double y=y0;

	e=m-0.5;

	while(x<x1){
		if (e >= 0) {
			y++;
			e = e - 1;
		}
		x++;
		e = e + m;

		if (k.xy == 1) {
			ty = (double)x;
			tx = (int)y;
		}else{
			tx = x;
			ty = y;
		}
		if (k.x == 1)
			tx = tx * (-1);
		if (k.y == 1)
			ty = ty * (-1);

		printf("%i %lf\n",tx,ty);
		glBegin(GL_POINTS);
				glVertex2d(tx,round(ty));
		glEnd();
		//printf("%lf\n",e);
		}

	glFlush();
}

status Inversor(int *x0, int *y0, int *x1, int *y1, double *m) {

	status k;
	int temp;
	double CAngular(int x0, int y0, int x1, int y1);

	*m=CAngular(*x0, *y0, *x1, *y1);

	if (*m>1 || *m<(-1)) {
		k.xy = 1;
		temp = *x0;
		*x0 = *y0;
		*y0 = temp;
		temp = *x1;
		*x1 = *y1;
		*y1 = temp;
		*m=CAngular(*x0, *y0, *x1, *y1);
	}
	else
		k.xy = 0;

	if (*x0>*x1) {
		k.x = 1;
		*x0 = *x0*(-1);
		*x1 = *x1*(-1);
	}
	else
		k.x = 0;

	if (*y0>*y1) {
		k.y = 1;
		*y0 = *y0*(-1);
		*y1 = *y1*(-1);
	}
	else
		k.y = 0;

	return k;
}

double CAngular(int x0, int y0,int x1,int y1){

	double dy=(double)y0-y1;
	double dx=(double)x0-x1;
	double m=dy/dx;
	//printf("%lf\n",m);

	return m;
}
