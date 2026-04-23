/***************************************************************************
                          cubemanage.h  -  description
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

#ifndef CUBEMANAGE_H
#define CUBEMANAGE_H


/**
  *@author wguzgg
  */
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

#include "wcgcube.h"

#define CUBE_SIZE  3
#define ORIENTX 0
#define ORIENTY 0
#define ORIENTZ 0

class CubeManage {
public: 
	CubeManage();
	~CubeManage();
	
	void turn(int rotateType);
	void turnByXShun(int x);
	void turnByXNi(int x);
	void turnByYShun(int y);
	void turnByYNi(int y);
	void turnByZShun(int z);
	void turnByZNi(int z);
	void output(int scr,int site);
	void output();
	void draw(int rotateType,GLfloat rotate);
	
private:
	WcgCube *cubes[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
	
	void goStep(int *leftLeg,int *rightLeg,int *goDirection,int step,int leftEdge,int rightEdge);
};

#endif
