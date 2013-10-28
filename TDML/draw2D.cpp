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
		Shaders.setDiffuseColor(r,g,b,a);
		Shaders.setUseTextures(false);
		glDisable(GL_DEPTH_TEST);

		projMatrix.loadIdentity();
		projMatrix.ortho2D(0,0,Window.getWidth(),Window.getHeight());
		Shaders.setProjMat(projMatrix.glForm());

		modelMatrix.loadIdentity();
		//modelMatrix.rotate(0, 0, 180+Math.angleBetween(y1/(Window.getHeight()),x1/(Window.getWidth()),y2/(Window.getHeight()),x2/(Window.getWidth())), XYZ);
		//modelMatrix.scale(Math.distance(x1,y1,0,x2,y2,0)/(Window.getWidth()/2), w/(Window.getHeight()/2), 0);
		//modelMatrix.translate(((x1/(Window.getWidth()/2))-1), 1-(y1/(Window.getHeight()/2)), 0);
		modelMatrix.rotate(0, 0, 180+Math.angleBetween(y1/(Window.getHeight()),x1/(Window.getWidth()),y2/(Window.getHeight()),x2/(Window.getWidth())), XYZ);
		modelMatrix.scale(Math.distance(x1,y1,0,x2,y2,0), w, 0);
		modelMatrix.translate(x1,y1,0);
		Shaders.setModelMat(modelMatrix.glForm());
		/*Log.output(w); Log.output("\n");
		Log.output((Window.getHeight()/2)); Log.output("\n");
		Log.output(w/(Window.getHeight()/2)); Log.output("\n");*/

		bindBuffer(VBO, menuvboid);
		bindBuffer(VAO, menuvaoid);
		glDrawArrays(GL_QUADS, 0, 4);

		resetProjection();

		modelMatrix.loadIdentity();
		Shaders.setModelMat(modelMatrix.glForm());

		Shaders.setUseTextures(true);
		glEnable(GL_DEPTH_TEST);
	}
}