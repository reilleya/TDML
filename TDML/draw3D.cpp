//draw3D.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	void draw3D::setup()
	{
		//Cube Setup
		cubeVAO = requestBuffer(VAO);
		bindBuffer(VAO, cubeVAO);

		cubeVBO = requestBuffer(VBO);
		GLfloat *geometry;
		geometry = new GLfloat[72];
		geometry[0] = -0.5; geometry[1] = -0.5; geometry[2] = -0.5;
		geometry[3] = 0.5; geometry[4] = -0.5; geometry[5] = -0.5;

		geometry[6] = 0.5; geometry[7] = -0.5; geometry[8] = 0.5;
		geometry[9] = -0.5; geometry[10] = -0.5; geometry[11] = 0.5;

		geometry[12] = -0.5; geometry[13] = 0.5; geometry[14] = 0.5;
		geometry[15] = 0.5; geometry[16] = 0.5; geometry[17] = 0.5;

		geometry[18] = 0.5; geometry[19] = 0.5; geometry[20] = -0.5;
		geometry[21] = -0.5; geometry[22] = 0.5; geometry[23] = -0.5;

		geometry[24] = -0.5; geometry[25] = -0.5; geometry[26] = -0.5;
		geometry[27] = -0.5; geometry[28] = 0.5; geometry[29] = -0.5;

		geometry[30] = -0.5; geometry[31] = -0.5; geometry[32] = 0.5;
		geometry[33] = -0.5; geometry[34] = 0.5; geometry[35] = 0.5;

		geometry[36] = 0.5; geometry[37] = -0.5; geometry[38] = 0.5;
		geometry[39] = 0.5; geometry[40] = 0.5; geometry[41] = 0.5;

		geometry[42] = 0.5; geometry[43] = -0.5; geometry[44] = -0.5;
		geometry[45] = 0.5; geometry[46] = 0.5; geometry[47] = -0.5;

		geometry[48] = -0.5; geometry[49] = -0.5; geometry[50] = -0.5;
		geometry[51] = -0.5; geometry[52] = -0.5; geometry[53] = 0.5;

		geometry[54] = 0.5; geometry[55] = -0.5; geometry[56] = -0.5;
		geometry[57] = 0.5; geometry[58] = -0.5; geometry[59] = 0.5;

		geometry[60] = -0.5; geometry[61] = 0.5; geometry[62] = -0.5;
		geometry[63] = -0.5; geometry[64] = 0.5; geometry[65] = 0.5;

		geometry[66] = 0.5; geometry[67] = 0.5; geometry[68] = -0.5;
		geometry[69] = 0.5; geometry[70] = 0.5; geometry[71] = 0.5;

		bindBuffer(VBO, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*72, geometry, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//End cube setup
		//*****************************************************************
		//Sphere setup -FIX
		ballVAO = requestBuffer(VAO);
		bindBuffer(VAO, ballVAO);

		ballVBO = requestBuffer(VBO);
		geometry = new GLfloat[468];

		point p = point(0, -1, 0);
		matrix4x4 rotMat = matrix4x4();
		for(int rZ = 0; rZ < 1; rZ++)
		{
			rotMat.rotate(0,0,(rZ+1)*15,XYZ);
			p = rotMat.apply(p);
			geometry[rZ*39] = p.getX(); geometry[(rZ*39)+1] = p.getY(); geometry[(rZ*39)+2] = p.getZ();
			rotMat.loadIdentity();
			for(int rY = 1; rY<13; rY++)
			{
				rotMat.rotate(0, rY*30, 0, XYZ);
				p = rotMat.apply(p);
				geometry[(rZ*39)+(rY*3)] = p.getX(); geometry[(rZ*39)+(rY*3)+1] = p.getY(); geometry[(rZ*39)+(rY*3)+2] = p.getZ();
				rotMat.loadIdentity();
			}
		}
		bindBuffer(VBO, ballVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*468, geometry, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		delete geometry;
	}

	void draw3D::cube(float x, float y, float z, float xAngle, float yAngle, float zAngle, float xSize, float ySize, float zSize, float r, float g, float b, float a, bool fill)
	{
		glDisable(GL_CULL_FACE);

		modelMatrix.translate(x,y,z);
		modelMatrix.rotate(xAngle, yAngle, zAngle, orotorder);
		modelMatrix.scale(xSize, ySize, zSize);
		
		Shaders.setModelMat(modelMatrix.glForm());
		Shaders.setUseTextures(false);
		Shaders.setDiffuseColor(r,g,b,a);

		bindBuffer(VAO, cubeVAO);
		bindBuffer(VBO, cubeVBO);
		if(fill) glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
		else glDrawArrays(GL_LINES, 0, 24);

		Shaders.setUseTextures(true);
		glEnable(GL_CULL_FACE);
	}

	void draw3D::cube(world& World, float x, float y, float z, float xAngle, float yAngle, float zAngle, float xSize, float ySize, float zSize, float r, float g, float b, float a, bool fill)
	{
		modelMatrix.loadIdentity();
		modelMatrix.rotate(World.getCamAngleX(), World.getCamAngleY(), World.getCamAngleZ(), crotorder);
		modelMatrix.translate(-World.getCamX(), -World.getCamY(), -World.getCamZ());
		modelMatrix.translate(x, y, z);
		modelMatrix.scale(xSize, ySize, zSize);
		modelMatrix.rotate(-xAngle, -yAngle, -zAngle, orotorder);
		cube(0, 0, 0, 0, 0, 0, 1, 1, 1, r, g, b, a, fill);
	}

	void draw3D::ball(float x, float y, float z, float xAngle, float yAngle, float zAngle, float xSize, float ySize, float zSize, float r, float g, float b, float a, bool fill)
	{
		glDisable(GL_CULL_FACE);

		modelMatrix.translate(x,y,z);
		modelMatrix.rotate(xAngle, yAngle, zAngle, orotorder);
		modelMatrix.scale(xSize, ySize, zSize);
		
		Shaders.setModelMat(modelMatrix.glForm());
		Shaders.setUseTextures(false);
		Shaders.setDiffuseColor(r,g,b,a);

		bindBuffer(VAO, ballVAO);
		bindBuffer(VBO, ballVBO);
		if(fill) glDrawArrays(GL_TRIANGLE_STRIP, 0, 156);
		else glDrawArrays(GL_LINES, 0, 156);

		Shaders.setUseTextures(true);
		glEnable(GL_CULL_FACE);
	}

	void draw3D::ball(world& World, float x, float y, float z, float xAngle, float yAngle, float zAngle, float xSize, float ySize, float zSize, float r, float g, float b, float a, bool fill)
	{
		modelMatrix.loadIdentity();
		modelMatrix.rotate(World.getCamAngleX(), World.getCamAngleY(), World.getCamAngleZ(), crotorder);
		modelMatrix.translate(-World.getCamX(), -World.getCamY(), -World.getCamZ());
		modelMatrix.translate(x, y, z);
		modelMatrix.scale(xSize, ySize, zSize);
		modelMatrix.rotate(-xAngle, -yAngle, -zAngle, orotorder);
		ball(0, 0, 0, 0, 0, 0, 1, 1, 1, r, g, b, a, fill);
	}
}