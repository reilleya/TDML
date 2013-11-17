//matrix3x3.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	matrix3x3::matrix3x3()
	{
		p11=1; p12=0; p13=0;
		p21=0; p22=1; p23=0;
		p31=0; p32=0; p33=1;
	}

	/*matrix3x3::matrix3x3(matrix4x4 mat)
	{
		p11 = mat.p11; p12 = mat.p12; p13 = mat.p13;
		p21 = mat.p21; p22 = mat.p22; p23 = mat.p23;
		p31 = mat.p31; p32 = mat.p32; p33 = mat.p33;
	}*/

	void matrix3x3::dispInfo()
	{
		Log.output("3x3 Matrix:\n");
		Log.output(p11); Log.output(","); Log.output(p12); Log.output(","); Log.output(p13); Log.output("\n");
		Log.output(p21); Log.output(","); Log.output(p22); Log.output(","); Log.output(p23); Log.output("\n");
		Log.output(p31); Log.output(","); Log.output(p32); Log.output(","); Log.output(p33); Log.output("\n");
	}

	matrix3x3 matrix4x4::rotPart()
	{
		matrix3x3 temp = matrix3x3();
		temp.p11 = p11; temp.p12 = p12; temp.p13 = p13;
		temp.p21 = p31; temp.p22 = p22; temp.p23 = p23;
		temp.p31 = p31; temp.p32 = p32; temp.p33 = p33;
		return temp;
	}

	matrix3x3 matrix3x3::operator * (matrix3x3 b)
	{
		matrix3x3 temp = matrix3x3();
		temp.p11 = (p11*b.p11)+(p12*b.p21)+(p13*b.p31);
		temp.p12 = (p11*b.p12)+(p12*b.p22)+(p13*b.p32);
		temp.p13 = (p11*b.p13)+(p12*b.p23)+(p13*b.p33);
		
		temp.p21 = (p21*b.p11)+(p22*b.p21)+(p23*b.p31);
		temp.p22 = (p21*b.p12)+(p22*b.p22)+(p23*b.p32);
		temp.p23 = (p21*b.p13)+(p22*b.p23)+(p23*b.p33);

		temp.p31 = (p31*b.p11)+(p32*b.p21)+(p33*b.p31);
		temp.p32 = (p31*b.p12)+(p32*b.p22)+(p33*b.p32);
		temp.p33 = (p31*b.p13)+(p32*b.p23)+(p33*b.p33);
		return temp;
	}

	matrix3x3 matrix3x3::operator * (float b)
	{
		matrix3x3 temp = matrix3x3();
		temp.p11 = p11*b; temp.p12 = p12*b; temp.p13 = p13*b;
		temp.p21 = p21*b; temp.p22 = p22*b; temp.p23 = p23*b;
		temp.p31 = p31*b; temp.p32 = p32*b; temp.p33 = p33*b;
		return temp;
	}

	void matrix3x3::xRotFromAngle(float angle)
	{
		p11 = 1;
		p12 = 0;
		p13 = 0;

		p21 = 0;
		p22 = Math.cos(angle);
		p23 = -Math.sin(angle);

		p31 = 0;
		p32 = Math.sin(angle);
		p33 = Math.cos(angle);
	}

	void matrix3x3::yRotFromAngle(float angle)
	{
		p11 = Math.cos(angle);
		p12 = 0;
		p13 = Math.sin(angle);

		p21 = 0;
		p22 = 1;
		p23 = 0;

		p31 = -Math.sin(angle);
		p32 = 0;
		p33 = Math.cos(angle);
	}

	void matrix3x3::zRotFromAngle(float angle)
	{
		p11 = Math.cos(angle);
		p12 = -Math.sin(angle);
		p13 = 0;

		p21 = Math.sin(angle);
		p22 = Math.cos(angle);
		p23 = 0;

		p31 = 0;
		p32 = 0;
		p33 = 1;
	}

	float matrix3x3::determinant()
	{
		return ((p11*d2x2(p22,p23,p32,p33))
			   -(p12*d2x2(p21,p23,p31,p33))
			   +(p13*d2x2(p21,p22,p31,p32)));
	}

	matrix3x3 matrix3x3::inverse()
	{
		matrix3x3 temp = matrix3x3();
		temp.p11 = d2x2(p22,p23,p32,p33); temp.p12 = d2x2(p13,p12,p33,p32); temp.p13 = d2x2(p12,p13,p22,p23); 
		temp.p21 = d2x2(p23,p21,p33,p31); temp.p22 = d2x2(p11,p13,p31,p33); temp.p23 = d2x2(p13,p11,p23,p21); 
		temp.p31 = d2x2(p21,p22,p31,p32); temp.p32 = d2x2(p12,p11,p32,p31); temp.p33 = d2x2(p11,p12,p21,p22); 
		temp = temp*(1/determinant());
		return temp;
	}

	matrix3x3 matrix3x3::transpose()
	{
		matrix3x3 temp = matrix3x3();
		temp.p11 = p11; temp.p12 = p21; temp.p13 = p31;
		temp.p21 = p12; temp.p22 = p22; temp.p23 = p32;
		temp.p31 = p13; temp.p32 = p32; temp.p33 = p33;
		return temp;
	}

	vector3d matrix3x3::apply(vector3d original)
	{
		vector3d temp = vector3d(0,0,0);
		temp.x = (p11*original.x)+(p12*original.y)+(p13*original.z);
		temp.y = (p21*original.x)+(p22*original.y)+(p23*original.z);
		temp.z = (p31*original.x)+(p32*original.y)+(p33*original.z);
		return temp;
	}

	point matrix3x3::apply(point original)
	{
		point temp(
		(p11*original.getX())+(p12*original.getY())+(p13*original.getZ()),
		(p21*original.getX())+(p22*original.getY())+(p23*original.getZ()),
		(p31*original.getX())+(p32*original.getY())+(p33*original.getZ()));
		return temp;
	}

	float* matrix3x3::glForm()
	{
		float temp[9] = {
						p11, p12, p13,
						p21, p22, p23,
						p31, p32, p33
						};
		return temp;
	}
}