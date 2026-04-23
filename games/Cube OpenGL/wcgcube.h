/***************************************************************************
                          wcgcube.h  -  description
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

#ifndef WCGCUBE_H
#define WCGCUBE_H


/**
  *@author wguzgg
  */
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

#include <iostream.h>

#define X 1
#define Y 2
#define Z 3

class WcgCube {
public:
	WcgCube();	
	~WcgCube();
	
	void turnByXShun(int x);
	void turnByXNi(int x);
	void turnByYShun(int y);
	void turnByYNi(int y);
	void turnByZShun(int z);
	void turnByZNi(int z);
	void output(int sign);
	void output();
	void draw(GLfloat x0,GLfloat y0,GLfloat z0);
	
private:
	int direct[6];
	GLfloat sideColor[6][3];
	
	void turnByX(int x,int sign);
	void turnByY(int y,int sign);
	void turnByZ(int z,int sign);
};

#endif
