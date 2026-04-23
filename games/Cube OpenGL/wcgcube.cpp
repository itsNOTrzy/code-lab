/***************************************************************************
                          wcgcube.cpp  -  description
                             -------------------
    begin                : Sat Nov 3 2001
    copyright            : (C) 2001 by wguzgg
    email                : wguzgg@263.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <iostream.h>

#include "wcgcube.h"

WcgCube::WcgCube(){
	direct[0]=Z;
	direct[1]=X;
	direct[2]=-Z;
	direct[3]=-X;
	direct[4]=Y;
	direct[5]=-Y;
	
	sideColor[0][0]=1.0f;
	sideColor[0][1]=1.0f;
	sideColor[0][2]=1.0f;
	
	sideColor[1][0]=1.0f;
	sideColor[1][1]=1.0f;
	sideColor[1][2]=0.0f;
	
	sideColor[2][0]=1.0f;
	sideColor[2][1]=0.0f;
	sideColor[2][2]=0.0f;
	
	sideColor[3][0]=1.0f;
	sideColor[3][1]=0.0f;
	sideColor[3][2]=1.0f;
	
	sideColor[4][0]=0.0f;
	sideColor[4][1]=1.0f;
	sideColor[4][2]=1.0f;
	
	sideColor[5][0]=0.0f;
	sideColor[5][1]=1.0f;
	sideColor[5][2]=0.0f;
}

WcgCube::~WcgCube(){
}

void WcgCube::draw(GLfloat orientX,GLfloat orientY,GLfloat orientZ) {
	GLfloat cubeRadium=10.0f;
	GLfloat cubeSpace=2.0f;
	for (int i=0;i<6;i++) {
		glColor3f(sideColor[i][0],sideColor[i][1],sideColor[i][2]);
		if (direct[i]==Z) {
			// Front face
			glBegin(GL_POLYGON);
				glVertex3f(orientX+cubeRadium,orientY+cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX+cubeRadium,orientY-cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY-cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY+cubeRadium,orientZ+cubeRadium);
			glEnd();
		}
		else
		if (direct[i]==-Z) {
			// Back Face
			glBegin(GL_POLYGON);
				glVertex3f(orientX+cubeRadium,orientY+cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX+cubeRadium,orientY-cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY-cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY+cubeRadium,orientZ-cubeRadium);
			glEnd();
		}
		else
		if (direct[i]==Y) {
			// Top Face
			glBegin(GL_POLYGON);
				glVertex3f(orientX+cubeRadium,orientY+cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX+cubeRadium,orientY+cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY+cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY+cubeRadium,orientZ-cubeRadium);
			glEnd();
		}
		else
		if (direct[i]==-Y) {
			// Bottom Face
			glBegin(GL_POLYGON);
				glVertex3f(orientX+cubeRadium,orientY-cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX+cubeRadium,orientY-cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY-cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY-cubeRadium,orientZ-cubeRadium);
			glEnd();
		}
		else
		if (direct[i]==X) {
			// Left face
			glBegin(GL_POLYGON);
				glVertex3f(orientX+cubeRadium,orientY+cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX+cubeRadium,orientY+cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX+cubeRadium,orientY-cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX+cubeRadium,orientY-cubeRadium,orientZ+cubeRadium);
			glEnd();
		}
		else
		if (direct[i]==-X) {
			// Right face
			glBegin(GL_POLYGON);
				glVertex3f(orientX-cubeRadium,orientY+cubeRadium,orientZ+cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY+cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY-cubeRadium,orientZ-cubeRadium);

				glVertex3f(orientX-cubeRadium,orientY-cubeRadium,orientZ+cubeRadium);
			glEnd();
		}
	}
}

void WcgCube::output() {
	for (int i=0;i<6;i++) {
		cout << "direct[" << i << "]=" << direct[i] << endl;
	}
}

void WcgCube::output(int sign) {
	for (int i=0;i<6;i++) {
		if (direct[i]==sign)
			cout <<  i;
	}
}

void WcgCube::turnByXShun(int x) {
	turnByX(x,-1);
}

void WcgCube::turnByXNi(int x) {
	turnByX(x,1);
}

void WcgCube::turnByX(int x,int sign) {
	for (int i=0;i<6;i++) {
		switch (direct[i]) {
			case Z:
				direct[i]=(-1)*sign*Y;
				break;
			case -Z:
				direct[i]=sign*Y;
				break;
			case Y:
				direct[i]=sign*Z;
				break;
			case -Y:
				direct[i]=(-1)*sign*Z;
				break;
		}
	}
}

void WcgCube::turnByYShun(int y) {
	turnByY(y,-1);
}

void WcgCube::turnByYNi(int y) {
	turnByY(y,1);
}

void WcgCube::turnByY(int y,int sign) {
	for (int i=0;i<6;i++) {
		switch (direct[i]) {
			case Z:
				direct[i]=sign*X;
				break;
			case -Z:
				direct[i]=(-1)*sign*X;
				break;
			case X:
				direct[i]=(-1)*sign*Z;
				break;
			case -X:
				direct[i]=sign*Z;
				break;
		}
	}
}

void WcgCube::turnByZShun(int z) {
	turnByZ(z,-1);
}

void WcgCube::turnByZNi(int z) {
	turnByZ(z,1);
}

void WcgCube::turnByZ(int z,int sign) {
	for (int i=0;i<6;i++) {
		switch (direct[i]) {
			case Y:
				direct[i]=(-1)*sign*X;
				break;
			case -Y:
				direct[i]=sign*X;
				break;
			case X:
				direct[i]=sign*Y;
				break;
			case -X:
				direct[i]=(-1)*sign*Y;
				break;
		}
	}
}
