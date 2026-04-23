/***************************************************************************
                          cubemanage.cpp  -  description
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

#include "cubemanage.h"

CubeManage::CubeManage(){
	for (int i=0;i<CUBE_SIZE;i++) {
		for (int j=0;j<CUBE_SIZE;j++) {
			for (int k=0;k<CUBE_SIZE;k++) {
				cubes[i][j][k]=new WcgCube();
			}
		}
	}
}

CubeManage::~CubeManage(){
	for (int i=0;i<CUBE_SIZE;i++) {
		for (int j=0;j<CUBE_SIZE;j++) {
			for (int k=0;k<CUBE_SIZE;k++) {
				delete cubes[i][j][k];
			}
		}
	}
}

void CubeManage::turn(int rotateType) {	
	if (rotateType==1) {
		turnByZShun(2);
	}
	else
	if (rotateType==2) {
		turnByXShun(2);
	}
	else
	if (rotateType==3) {
		turnByZNi(0);
	}
	else
	if (rotateType==4) {
		turnByXNi(0);
	}
	else
	if (rotateType==5) {
		turnByYShun(2);
	}
	else
	if (rotateType==6) {
		turnByYNi(0);
	}
	else
	if (rotateType==7) {
		turnByZNi(2);
	}
	else
	if (rotateType==8) {
		turnByXNi(2);
	}
	else
	if (rotateType==9) {
		turnByZShun(0);
	}
	else
	if (rotateType==10) {
		turnByXShun(0);
	}
	else
	if (rotateType==11) {
		turnByYNi(2);
	}
	else
	if (rotateType==12) {
		turnByYShun(0);
	}
}

void CubeManage::draw(int rotateType,GLfloat rotate) {
	GLfloat PI=3.1415f;
	GLfloat cubeRadium=10.0f;
	GLfloat cubeSpace=2.0f;
	GLfloat x,y,z;
	int i,j,k;

	x=ORIENTX-(CUBE_SIZE/2)*(cubeRadium*2+cubeSpace);
	y=ORIENTZ-(CUBE_SIZE/2)*(cubeRadium*2+cubeSpace);
	z=ORIENTZ-(CUBE_SIZE/2)*(cubeRadium*2+cubeSpace);
	
	if (rotateType==0) {
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==1) {
  	glPushMatrix();
  	glRotatef(360-180*rotate/PI,0.0f,0.0f,1.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][j][CUBE_SIZE-1])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*(CUBE_SIZE-1));
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE-1;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==2) {
  	glPushMatrix();
  	glRotatef(360-180*rotate/PI,1.0f,0.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[CUBE_SIZE-1][i][j])->draw(x+(cubeRadium*2+cubeSpace)*(CUBE_SIZE-1),y+(cubeRadium*2+cubeSpace)*i,z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE-1;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==3) {
  	glPushMatrix();
  	glRotatef(360-180*rotate/PI,0.0f,0.0f,-1.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][j][0])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=1;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==4) {
  	glPushMatrix();
  	glRotatef(360-180*rotate/PI,-1.0f,0.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[0][i][j])->draw(x,y+(cubeRadium*2+cubeSpace)*i,z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=1;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==5) {
  	glPushMatrix();
  	glRotatef(360-180*rotate/PI,0.0f,1.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][CUBE_SIZE-1][j])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*(CUBE_SIZE-1),z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE-1;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==6) {
  	glPushMatrix();
  	glRotatef(360-180*rotate/PI,0.0f,-1.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][0][j])->draw(x+(cubeRadium*2+cubeSpace)*i,y,z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=1;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==7) {
  	glPushMatrix();
  	glRotatef(180*rotate/PI,0.0f,0.0f,1.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][j][CUBE_SIZE-1])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*(CUBE_SIZE-1));
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE-1;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==8) {
  	glPushMatrix();
  	glRotatef(180*rotate/PI,1.0f,0.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[CUBE_SIZE-1][i][j])->draw(x+(cubeRadium*2+cubeSpace)*(CUBE_SIZE-1),y+(cubeRadium*2+cubeSpace)*i,z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE-1;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==9) {
  	glPushMatrix();
  	glRotatef(180*rotate/PI,0.0f,0.0f,-1.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][j][0])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=1;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==10) {
  	glPushMatrix();
  	glRotatef(180*rotate/PI,-1.0f,0.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[0][i][j])->draw(x,y+(cubeRadium*2+cubeSpace)*i,z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=1;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==11) {
  	glPushMatrix();
  	glRotatef(180*rotate/PI,0.0f,1.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][CUBE_SIZE-1][j])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*(CUBE_SIZE-1),z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE-1;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
	else
	if (rotateType==12) {
  	glPushMatrix();
  	glRotatef(180*rotate/PI,0.0f,-1.0f,0.0f);
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=0;j<CUBE_SIZE;j++) {
				(cubes[i][0][j])->draw(x+(cubeRadium*2+cubeSpace)*i,y,z+(cubeRadium*2+cubeSpace)*j);
			}
		}
  	glPopMatrix();
		for (i=0;i<CUBE_SIZE;i++) {
			for (j=1;j<CUBE_SIZE;j++) {
				for (k=0;k<CUBE_SIZE;k++) {
					(cubes[i][j][k])->draw(x+(cubeRadium*2+cubeSpace)*i,y+(cubeRadium*2+cubeSpace)*j,z+(cubeRadium*2+cubeSpace)*k);
				}
			}
		}
	}
}

void CubeManage::output() {
	for (int i=0;i<CUBE_SIZE;i++) {
		for (int j=0;j<CUBE_SIZE;j++) {
			cubes[0][i][j]->output();
		}
	}
}

void CubeManage::output(int scr,int site){
	int sign;
	int i,j;

	if (site==1) {
		cout << "site=1,nonsense!" << endl;
		return;
	}
	
	switch (scr) {
		case 1:
			if (site==0)
				sign=-X;
			else
				sign=X;
			cout << "scr=" << scr << " sign=" << sign << endl;
			for (i=0;i<CUBE_SIZE;i++) {
				for (j=0;j<CUBE_SIZE;j++) {
					cout << i << "," << j << "=";
					cubes[site][i][j]->output(sign);
					cout << endl;
				}
			}
			break;
		case 2:
			if (site==0)
				sign=-Y;
			else
				sign=Y;
			for (i=0;i<CUBE_SIZE;i++) {
				for (j=0;j<CUBE_SIZE;j++) {
					cout << i << "," << j << "=";
					cubes[i][site][j]->output(sign);
					cout << endl;
				}
			}
			break;
		case 3:
			if (site==0)
				sign=-Z;
			else
				sign=Z;
			for (i=0;i<CUBE_SIZE;i++) {
				for (j=0;j<CUBE_SIZE;j++) {
					cout << i << "," << j << "=";
					cubes[i][j][site]->output(sign);
					cout << endl;
				}
			}
			break;
	}
}

void CubeManage::goStep(int *leftLeg,int *rightLeg,int *goDirection,int step,int leftEdge,int rightEdge) {
	for (int i=0;i<step;i++) {
		switch (*goDirection) {
			case 0:
				*leftLeg=*leftLeg-1;
				if (*leftLeg<leftEdge) {
					*leftLeg=*leftLeg+1;
					*goDirection=3;
					*rightLeg=*rightLeg+1;
				}
				break;
			case 1:
				*rightLeg=*rightLeg-1;
				if (*rightLeg<leftEdge) {
					*rightLeg=*rightLeg+1;
					*goDirection=0;
					*leftLeg=*leftLeg-1;
				}
				break;
			case 2:
				*leftLeg=*leftLeg+1;
				if (*leftLeg>=rightEdge) {
					*leftLeg=*leftLeg-1;
					*goDirection=1;
					*rightLeg=*rightLeg-1;
				}
				break;
			case 3:
				*rightLeg=*rightLeg+1;
				if (*rightLeg>=rightEdge) {
					*rightLeg=*rightLeg-1;
					*goDirection=2;
					*leftLeg=*leftLeg+1;
				}
				break;
		}
	}
}

void CubeManage::turnByXShun(int x) {
	int step=CUBE_SIZE-1;
	int leftEdge=0;
	int rightEdge=CUBE_SIZE;
	int goDirection0=3;
	int goDirection1=3;
	int y0=0;
	int z0=0;
	int y1=0;
	int z1=0;
	WcgCube *tempcubes[CUBE_SIZE][CUBE_SIZE];
	
	tempcubes[CUBE_SIZE/2][CUBE_SIZE/2]=cubes[x][CUBE_SIZE/2][CUBE_SIZE/2];
	cubes[x][CUBE_SIZE/2][CUBE_SIZE/2]->turnByXShun(x);
	for (int i=0;i<CUBE_SIZE/2;i++) {
		step=CUBE_SIZE-i*2-1;
		goDirection0=3;
		goDirection1=3;
		leftEdge=i;
		rightEdge=CUBE_SIZE-i;
		y0=leftEdge;
		z0=leftEdge;
		y1=leftEdge;
		z1=leftEdge;
		goStep(&y1,&z1,&goDirection1,step,leftEdge,rightEdge);
		for (int j=0;j<step*4;j++) {
			tempcubes[y1][z1]=cubes[x][y0][z0];
			cubes[x][y0][z0]->turnByXShun(x);
			goStep(&y0,&z0,&goDirection0,1,leftEdge,rightEdge);
			goStep(&y1,&z1,&goDirection1,1,leftEdge,rightEdge);
		}
		for (int m=0;m<CUBE_SIZE;m++) {
			for (int n=0;n<CUBE_SIZE;n++) {
				cubes[x][m][n]=tempcubes[m][n];
			}
		}
	}
}

void CubeManage::turnByXNi(int x) {
	turnByXShun(x);
	turnByXShun(x);
	turnByXShun(x);
}

void CubeManage::turnByYShun(int y) {
	int step=CUBE_SIZE-1;
	int leftEdge=0;
	int rightEdge=CUBE_SIZE;
	int goDirection0=3;
	int goDirection1=3;
	int x0=0;
	int z0=0;
	int x1=0;
	int z1=0;
	WcgCube *tempcubes[CUBE_SIZE][CUBE_SIZE];
	
	tempcubes[CUBE_SIZE/2][CUBE_SIZE/2]=cubes[CUBE_SIZE/2][y][CUBE_SIZE/2];
	cubes[CUBE_SIZE/2][y][CUBE_SIZE/2]->turnByYShun(y);
	for (int i=0;i<CUBE_SIZE/2;i++) {
		step=CUBE_SIZE-i*2-1;
		goDirection0=3;
		goDirection1=3;
		leftEdge=i;
		rightEdge=CUBE_SIZE-i;
		x0=leftEdge;
		z0=leftEdge;
		x1=leftEdge;
		z1=leftEdge;
		goStep(&z1,&x1,&goDirection1,step,leftEdge,rightEdge);
		for (int j=0;j<step*4;j++) {
			tempcubes[x1][z1]=cubes[x0][y][z0];
			cubes[x0][y][z0]->turnByYShun(y);
			goStep(&z0,&x0,&goDirection0,1,leftEdge,rightEdge);
			goStep(&z1,&x1,&goDirection1,1,leftEdge,rightEdge);
		}
		for (int m=0;m<CUBE_SIZE;m++) {
			for (int n=0;n<CUBE_SIZE;n++) {
				cubes[m][y][n]=tempcubes[m][n];
			}
		}
	}
}

void CubeManage::turnByYNi(int y) {
	turnByYShun(y);
	turnByYShun(y);
	turnByYShun(y);
}

void CubeManage::turnByZShun(int z) {
	int step=CUBE_SIZE-1;
	int leftEdge=0;
	int rightEdge=CUBE_SIZE;
	int goDirection0=3;
	int goDirection1=3;
	int x0=0;
	int y0=0;
	int x1=0;
	int y1=0;
	WcgCube *tempcubes[CUBE_SIZE][CUBE_SIZE];
	
	tempcubes[CUBE_SIZE/2][CUBE_SIZE/2]=cubes[CUBE_SIZE/2][CUBE_SIZE/2][z];
	cubes[CUBE_SIZE/2][CUBE_SIZE/2][z]->turnByZShun(z);
	for (int i=0;i<CUBE_SIZE/2;i++) {
		step=CUBE_SIZE-i*2-1;
		goDirection0=3;
		goDirection1=3;
		leftEdge=i;
		rightEdge=CUBE_SIZE-i;
		x0=leftEdge;
		y0=leftEdge;
		x1=leftEdge;
		y1=leftEdge;
		goStep(&x1,&y1,&goDirection1,step,leftEdge,rightEdge);
		for (int j=0;j<step*4;j++) {
			tempcubes[x1][y1]=cubes[x0][y0][z];
			cubes[x0][y0][z]->turnByZShun(z);
			goStep(&x0,&y0,&goDirection0,1,leftEdge,rightEdge);
			goStep(&x1,&y1,&goDirection1,1,leftEdge,rightEdge);
		}
		for (int m=0;m<CUBE_SIZE;m++) {
			for (int n=0;n<CUBE_SIZE;n++) {
				cubes[m][n][z]=tempcubes[m][n];
			}
		}
	}
}

void CubeManage::turnByZNi(int z) {
	turnByZShun(z);
	turnByZShun(z);
	turnByZShun(z);
}
