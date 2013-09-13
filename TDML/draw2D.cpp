//draw2D.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	void draw2D::line(float x1, float y1, float x2, float y2, float w, float r, float g, float b, float a)
	{
		//Shaders.dispInfo();
		Shaders.setDiffuseColor(r,g,b,a);
		Shaders.setUseTextures(false);
		glDisable(GL_DEPTH_TEST);
		projMatrix.loadIdentity();
		Shaders.setProjMat(projMatrix.glForm());
		modelMatrix.loadIdentity();
		//modelMatrix.scale(0.5, 0.5, 0.5);
		modelMatrix.rotate(0, 0, 180+Math.angleBetween(y1,x1,y2,x2), XYZ);
		modelMatrix.scale(Math.distance(x1,y1,0,x2,y2,0)/(Window.getWidth()/2), w/(Window.getHeight()/2), 0);
		
		modelMatrix.translate(((x1/(Window.getWidth()/2))-1), 1-(y1/(Window.getHeight()/2)), 0);
		Shaders.setModelMat(modelMatrix.glForm());

		glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
		//glBindTexture(GL_TEXTURE_2D, 0); //Bullshit texture... needed?
		glBindVertexArray(menuvaoid);
		glDrawArrays(GL_QUADS, 0, 4);

		projMatrix.loadIdentity();
		projMatrix.perspective(Config.getFOV(), (float)Window.getWidth()/(float)Window.getHeight(), 1.000f, 1000000.0f); //TODO: throw this in a function
		Shaders.setProjMat(projMatrix.glForm());
		modelMatrix.loadIdentity();
		Shaders.setModelMat(modelMatrix.glForm());
		Shaders.setUseTextures(true);
		glEnable(GL_DEPTH_TEST);
	}
}