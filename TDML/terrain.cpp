//terrain.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	void terrain::dispInfo()
	{
		Log.output("Terrain:\n");
		Log.output("\tDimensions: "); Log.output((float)dimensions); Log.output("\n");
		Log.output("\tScale: "); Log.output((float)scalexz); Log.output(","); Log.output((float)scaley); Log.output("\n");
		Log.output("\tVBO ID: "); Log.output((float)vboid); Log.output("\n");
		Log.output("\tVAO ID: "); Log.output((float)vaoid); Log.output("\n");
		Log.output("\tTexture ID: "); Log.output((float)texid); Log.output("\n");
	}

	void terrain::setHeightMap(std::vector<std::vector<float>> newheightmap)
	{
		heightmap = newheightmap;
	}

	void terrain::setDimensions(int dim)
	{
		dimensions = dim;
	}

	void terrain::setTextureId(int textureid)
	{
		texid = textureid;
	}
	
	void terrain::setScale(float xz, float y)
	{
		scalexz = xz;
		scaley = y;
	}

	float terrain::getScaleXZ()
	{
		return scalexz;
	}

	float terrain::getScaleY()
	{
		return scaley;
	}

	float terrain::getHeightMapAt(float x, float z)
	{
		float nx = x/scalexz;
		float nz = z/scalexz;
		nx++;
		nz++;
		nx/=2;
		nz/=2;
		nx*=dimensions;
		nz*=dimensions;
		//Log.output(nx); Log.output(","); Log.output(nz); Log.output(":"); Log.output(heightmap[nx][nz]); Log.output("\n");
		int roundedNewX = (int)Math.simpleRoundDown(nx);
		int roundedNewZ = (int)Math.simpleRoundDown(nz);
		float partx = nx-roundedNewX;
		float partz = nz-roundedNewZ;
		//Log.output(partx); Log.output(","); Log.output(partz); 
		if(nx>0 && nx + 1 < dimensions && nz>0 && nz+1 < dimensions)
		{
			if(partx+partz>1)
			{
				//Log.output(":Bottom Right!\n\n");
				float h = heightmap[(unsigned int)nx+1][(unsigned int)nz+1];
				h+=(heightmap[(unsigned int)nx][(unsigned int)nz+1]-heightmap[(unsigned int)nx+1][(unsigned int)nz+1])*(1-partx);
				h+=(heightmap[(unsigned int)nx+1][(unsigned int)nz]-heightmap[(unsigned int)nx+1][(unsigned int)nz+1])*(1-partz);
				return (h-128)*scaley;
			}
			else
			{
				//Log.output(":Top Left!\n\n");
				float h = heightmap[(unsigned int)nx][(unsigned int)nz];
				h+=(heightmap[(unsigned int)nx+1][(unsigned int)nz]-heightmap[(unsigned int)nx][(unsigned int)nz])*partx;
				h+=(heightmap[(unsigned int)nx][(unsigned int)nz+1]-heightmap[(unsigned int)nx][(unsigned int)nz])*partz;
				return (h-128)*scaley;
			}
		}
		else
		{
			return 0;
		}
	}

	vector3d terrain::getAngleAt(float x, float z)
	{
		float nx = x/scalexz;
		float nz = z/scalexz;
		nx++;
		nz++;
		nx/=2;
		nz/=2;
		nx*=dimensions;
		nz*=dimensions;
		int roundedNewX = (int)Math.simpleRoundDown(nx);
		int roundedNewZ = (int)Math.simpleRoundDown(nz);
		float partx = nx-roundedNewX;
		float partz = nz-roundedNewZ;
		if(nx>0 && nx + 1 < dimensions && nz>0 && nz+1 < dimensions)
		{
			if(partx+partz>1)
			{
				return anglemap[nx][nz][0];
			}
			else
			{
				return anglemap[nx][nz][1];
			}
		}
	}

	void terrain::generateVBO()
	{
		points.resize(dimensions+1);
		for(int q = 0; q < dimensions+1; q++)
		{
			points[q].resize(dimensions+1);
		}
		for(int v = 0; v < dimensions; v++)
		{
			for(int v0 = 0; v0 < dimensions; v0++)
			{
				points[v][v0].setPos((float)(v-(dimensions/2))/(dimensions/2), (float)heightmap[v][v0]-128, (float)(v0-(dimensions/2))/(dimensions/2));
			}
		}

		vector3d vec1;
		vector3d vec2;
		for(int v1 = 0; v1 < dimensions-1; v1++)
		{
			anglemap.resize(anglemap.size()+1);
			for(int v2 = 0; v2 < dimensions-1; v2++)
			{
				anglemap[v1].resize(anglemap[v1].size()+1);
				vec1 = vector3d(points[v1+1][v2].getX()-points[v1][v2].getX(), points[v1+1][v2].getY()-points[v1][v2].getY(), points[v1+1][v2].getZ()-points[v1][v2].getZ());
				vec2 = vector3d(points[v1][v2+1].getX()-points[v1][v2].getX(), points[v1][v2+1].getY()-points[v1][v2].getY(), points[v1][v2+1].getZ()-points[v1][v2].getZ());
				anglemap[v1][v2].push_back(vec1^vec2);
				
				vec1 = vector3d(points[v1+1][v2].getX()-points[v1][v2].getX(), points[v1+1][v2].getY()-points[v1][v2].getY(), points[v1+1][v2].getZ()-points[v1][v2].getZ());
				vec2 = vector3d(points[v1][v2+1].getX()-points[v1][v2].getX(), points[v1][v2+1].getY()-points[v1][v2].getY(), points[v1][v2+1].getZ()-points[v1][v2].getZ());
				anglemap[v1][v2].push_back(vec1^vec2);
			}
		}

		vaoid = requestBuffer(VAO);
		bindBuffer(VAO, vaoid);

		vboid = requestBuffer(VBO);
		GLuint numverts = (dimensions-1)*(dimensions-1)*6;
		GLfloat *geometry;
		GLfloat *normals;
		GLfloat *coords;
		geometry = new GLfloat[3*numverts];
		normals = new GLfloat[3*numverts];
		coords = new GLfloat[2*numverts];
		int p = 0;
		for(int v1 = 0; v1 < dimensions-1; v1++)
		{
			for(int v2 = 0; v2 < dimensions-1; v2++)
			{
				geometry[(p*18)] = points[v1][v2].getX();
				geometry[(p*18)+1] = points[v1][v2].getY();
				geometry[(p*18)+2] = points[v1][v2].getZ();
				normals[(p*18)] = 0;
				normals[(p*18)+1] = 1;
				normals[(p*18)+2] = 0;
				coords[(p*12)] = (GLfloat)v1/dimensions;
				coords[(p*12)+1] = TDML::Math.smaller(1, (-((points[v1][v2].getY()-128)/256)));

				geometry[(p*18)+3] = points[v1][v2+1].getX();
				geometry[(p*18)+4] = points[v1][v2+1].getY();
				geometry[(p*18)+5] = points[v1][v2+1].getZ();
				normals[(p*18)+3] = 0;
				normals[(p*18)+4] = 1;
				normals[(p*18)+5] = 0;
				coords[(p*12)+2] = (GLfloat)v1/dimensions;
				coords[(p*12)+3] = TDML::Math.larger(0, (-((points[v1][v2+1].getY()-128)/256)));

				geometry[(p*18)+6] = points[v1+1][v2].getX();
				geometry[(p*18)+7] = points[v1+1][v2].getY();
				geometry[(p*18)+8] = points[v1+1][v2].getZ();
				normals[(p*18)+6] = 0;
				normals[(p*18)+7] = 1;
				normals[(p*18)+8] = 0;
				coords[(p*12)+4] = (GLfloat)(v1+1)/dimensions;
				coords[(p*12)+5] = TDML::Math.smaller(1, (-((points[v1+1][v2].getY()-128)/256)));

				geometry[(p*18)+9] = points[v1+1][v2].getX();
				geometry[(p*18)+10] = points[v1+1][v2].getY();
				geometry[(p*18)+11] = points[v1+1][v2].getZ();
				normals[(p*18)+9] = 0;
				normals[(p*18)+10] = 1;
				normals[(p*18)+11] = 0;
				coords[(p*12)+6] = (GLfloat)(v1+1)/dimensions;
				coords[(p*12)+7] = TDML::Math.smaller(1, (-((points[v1+1][v2].getY()-128)/256)));

				geometry[(p*18)+12] = points[v1][v2+1].getX();
				geometry[(p*18)+13] = points[v1][v2+1].getY();
				geometry[(p*18)+14] = points[v1][v2+1].getZ();
				normals[(p*18)+12] = 0;
				normals[(p*18)+13] = 1;
				normals[(p*18)+14] = 0;
				coords[(p*12)+8] = (GLfloat)v1/dimensions;
				coords[(p*12)+9] = TDML::Math.larger(0, (-((points[v1][v2+1].getY()-128)/256)));

				geometry[(p*18)+15] = points[v1+1][v2+1].getX();
				geometry[(p*18)+16] = points[v1+1][v2+1].getY();
				geometry[(p*18)+17] = points[v1+1][v2+1].getZ();
				normals[(p*18)+15] = 0;
				normals[(p*18)+16] = 1;
				normals[(p*18)+17] = 0;
				coords[(p*12)+10] = (GLfloat)(v1+1)/dimensions;
				coords[(p*12)+11] = TDML::Math.larger(0, (-((points[v1+1][v2+1].getY()-128)/256)));

				p++;
			}
		}
		bindBuffer(VBO, vboid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*numverts, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3*numverts, geometry);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*3*numverts, sizeof(float)*2*numverts, coords);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*5*numverts, sizeof(float)*3*numverts, normals);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)((dimensions-1) * (dimensions-1) * 30 * sizeof(GLfloat))); // Normals
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)((dimensions-1) * (dimensions-1) * 18 * sizeof(GLfloat))); // Texture Coords

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		bindBuffer(VAO, 0);

		delete geometry;
		delete normals;
		delete coords;
	}
			
	void terrain::display()
	{
		bindBuffer(VBO, vboid);
		bindBuffer(TEX, texid);
		bindBuffer(VAO, vaoid);
		glDrawArrays(GL_TRIANGLES, 0, (dimensions-1) * (dimensions-1) * 6);
		bindBuffer(VAO, 0);
	}
}