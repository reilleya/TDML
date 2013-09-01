//matrix4x4.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	matrix4x4::matrix4x4()
	{
		p11=1; p12=0; p13=0; p14=0;
		p21=0; p22=1; p23=0; p24=0;
		p31=0; p32=0; p33=1; p34=0;
		p41=0; p42=0; p43=0; p44=1;
	}

	void matrix4x4::dispInfo()
	{
		Log.output("4x4 Matrix:\n");
		Log.output(p11); Log.output(","); Log.output(p12); Log.output(","); Log.output(p13); Log.output(","); Log.output(p14); Log.output("\n");
		Log.output(p21); Log.output(","); Log.output(p22); Log.output(","); Log.output(p23); Log.output(","); Log.output(p24); Log.output("\n");
		Log.output(p31); Log.output(","); Log.output(p32); Log.output(","); Log.output(p33); Log.output(","); Log.output(p34); Log.output("\n");
		Log.output(p41); Log.output(","); Log.output(p42); Log.output(","); Log.output(p43); Log.output(","); Log.output(p44); Log.output("\n");

	}

	void matrix4x4::translate(float x, float y, float z)
	{
		matrix4x4 temp = matrix4x4();
		temp.p41 = x;
		temp.p42 = y;
		temp.p43 = z;
		temp = temp * this;
		copy(temp);
	}

	void matrix4x4::rotate(float x, float y, float z, int order)
	{
		switch(order)
		{
			case 0:
				rotateAxis(x, X_axis);
				rotateAxis(y, Y_axis);
				rotateAxis(z, Z_axis);
				break;

			case 1:
				rotateAxis(x, X_axis);
				rotateAxis(z, Z_axis);
				rotateAxis(y, Y_axis);
				break;

			case 2:
				rotateAxis(z, Z_axis);
				rotateAxis(y, Y_axis);
				rotateAxis(x, X_axis);
				break;

			case 3:
				rotateAxis(z, Z_axis);
				rotateAxis(x, X_axis);
				rotateAxis(y, Y_axis);
				break;

			case 4:
				rotateAxis(y, Y_axis);
				rotateAxis(x, X_axis);
				rotateAxis(z, Z_axis);
				break;

			case 5:
				rotateAxis(y, Y_axis);
				rotateAxis(z, Z_axis);
				rotateAxis(x, X_axis);
				break;
		}
	}

	void matrix4x4::rotateAxis(float degrees, int axis)
	{
		matrix3x3 rot = matrix3x3();
		switch(axis)
		{
			case 0:
				rot.xRotFromAngle(degrees);
				break;

			case 1:
				rot.yRotFromAngle(degrees);
				break;

			case 2:
				rot.zRotFromAngle(degrees);
				break;
		}
		applyRotation(rot);
	}

	void matrix4x4::applyRotation(matrix3x3& rot)
	{
		matrix4x4 temp = matrix4x4();
		temp.p11 = rot.p11;
		temp.p12 = rot.p12;
		temp.p13 = rot.p13;

		temp.p21 = rot.p21;
		temp.p22 = rot.p22;
		temp.p23 = rot.p23;

		temp.p31 = rot.p31;
		temp.p32 = rot.p32;
		temp.p33 = rot.p33;
		temp = temp * this;
		copy(temp);
	}

	void matrix4x4::scale(float x, float y, float z)
	{
		matrix4x4 temp = matrix4x4();
		temp.p11 = x;
		temp.p22 = y;
		temp.p33 = z;
		temp = temp * this;
		copy(temp);
	}

	void matrix4x4::loadIdentity()
	{
		p11=1;
		p12=0;
		p13=0;
		p14=0;
		p21=0;
		p22=1;
		p23=0;
		p24=0;
		p31=0;
		p32=0;
		p33=1;
		p34=0;
		p41=0;
		p42=0;
		p43=0;
		p44=1;
	}

	void matrix4x4::perspective(float fieldOfView, float aspectRatio, float nearZ, float farZ)
	{
		float f = Math.cot(fieldOfView/2);
		p11 = f/aspectRatio; p12 = 0; p13 = 0; p14 = 0;
		p21 = 0; p22 = f; p23 = 0; p24 = 0;
		p31 = 0; p32 = 0; p33 = (farZ+nearZ)/(nearZ-farZ); p34 = (2*farZ*nearZ)/(nearZ-farZ);
		p41 = 0; p42 = 0; p43 = -1; p44 = 0;
	}

	void matrix4x4::ortho(float left, float top, float right, float bottom, float nearZ, float farZ)
	{
		p11 = 2/(right-left); p12 = 0; p13 = 0; p14 = -((right+left)/(right-left));
		p21 = 0; p22 = 2/(top-bottom); p23 = 0; p24 = -(top+bottom)/(top-bottom);
		p31 = 0; p32 = 0; p33 = -2/(farZ-nearZ); p34 = -(farZ+nearZ)/(farZ-nearZ);
		p41 = 0; p42 = 0; p43 = 0; p44 = 1;
	}

	void matrix4x4::ortho2D(float left, float top, float right, float bottom)
	{
		ortho(left, top, right, bottom, 0, 0);
	}

	matrix4x4 matrix4x4::operator * (matrix4x4 b)
	{
		matrix4x4 temp = matrix4x4();
		temp.p11 = (p11*b.p11)+(p12*b.p21)+(p13*b.p31)+(p14*b.p41);
		temp.p12 = (p11*b.p12)+(p12*b.p22)+(p13*b.p32)+(p14*b.p42);
		temp.p13 = (p11*b.p13)+(p12*b.p23)+(p13*b.p33)+(p14*b.p43);
		temp.p14 = (p11*b.p14)+(p12*b.p24)+(p13*b.p34)+(p14*b.p44);
		
		temp.p21 = (p21*b.p11)+(p22*b.p21)+(p23*b.p31)+(p24*b.p41);
		temp.p22 = (p21*b.p12)+(p22*b.p22)+(p23*b.p32)+(p24*b.p42);
		temp.p23 = (p21*b.p13)+(p22*b.p23)+(p23*b.p33)+(p24*b.p43);
		temp.p24 = (p21*b.p14)+(p22*b.p24)+(p23*b.p34)+(p24*b.p44);

		temp.p31 = (p31*b.p11)+(p32*b.p21)+(p33*b.p31)+(p34*b.p41);
		temp.p32 = (p31*b.p12)+(p32*b.p22)+(p33*b.p32)+(p34*b.p42);
		temp.p33 = (p31*b.p13)+(p32*b.p23)+(p33*b.p33)+(p34*b.p43);
		temp.p34 = (p31*b.p14)+(p32*b.p24)+(p33*b.p34)+(p34*b.p44);
		
		temp.p41 = (p41*b.p11)+(p42*b.p21)+(p43*b.p31)+(p44*b.p41);
		temp.p42 = (p41*b.p12)+(p42*b.p22)+(p43*b.p32)+(p44*b.p42);
		temp.p43 = (p41*b.p13)+(p42*b.p23)+(p43*b.p33)+(p44*b.p43);
		temp.p44 = (p41*b.p14)+(p42*b.p24)+(p43*b.p34)+(p44*b.p44);
		return temp;
	}

	matrix4x4 matrix4x4::operator * (matrix4x4* b)
	{
		matrix4x4 temp = matrix4x4();
		temp.p11 = (p11*b->p11)+(p12*b->p21)+(p13*b->p31)+(p14*b->p41);
		temp.p12 = (p11*b->p12)+(p12*b->p22)+(p13*b->p32)+(p14*b->p42);
		temp.p13 = (p11*b->p13)+(p12*b->p23)+(p13*b->p33)+(p14*b->p43);
		temp.p14 = (p11*b->p14)+(p12*b->p24)+(p13*b->p34)+(p14*b->p44);
		
		temp.p21 = (p21*b->p11)+(p22*b->p21)+(p23*b->p31)+(p24*b->p41);
		temp.p22 = (p21*b->p12)+(p22*b->p22)+(p23*b->p32)+(p24*b->p42);
		temp.p23 = (p21*b->p13)+(p22*b->p23)+(p23*b->p33)+(p24*b->p43);
		temp.p24 = (p21*b->p14)+(p22*b->p24)+(p23*b->p34)+(p24*b->p44);

		temp.p31 = (p31*b->p11)+(p32*b->p21)+(p33*b->p31)+(p34*b->p41);
		temp.p32 = (p31*b->p12)+(p32*b->p22)+(p33*b->p32)+(p34*b->p42);
		temp.p33 = (p31*b->p13)+(p32*b->p23)+(p33*b->p33)+(p34*b->p43);
		temp.p34 = (p31*b->p14)+(p32*b->p24)+(p33*b->p34)+(p34*b->p44);
		
		temp.p41 = (p41*b->p11)+(p42*b->p21)+(p43*b->p31)+(p44*b->p41);
		temp.p42 = (p41*b->p12)+(p42*b->p22)+(p43*b->p32)+(p44*b->p42);
		temp.p43 = (p41*b->p13)+(p42*b->p23)+(p43*b->p33)+(p44*b->p43);
		temp.p44 = (p41*b->p14)+(p42*b->p24)+(p43*b->p34)+(p44*b->p44);
		return temp;
	}

	void matrix4x4::timesEquals(matrix4x4& b)
	{
		matrix4x4 temp = matrix4x4();
		p11 = (p11*b.p11)+(p12*b.p21)+(p13*b.p31)+(p14*b.p41);
		p12 = (p11*b.p12)+(p12*b.p22)+(p13*b.p32)+(p14*b.p42);
		p13 = (p11*b.p13)+(p12*b.p23)+(p13*b.p33)+(p14*b.p43);
		p14 = (p11*b.p14)+(p12*b.p24)+(p13*b.p34)+(p14*b.p44);
		
		p21 = (p21*b.p11)+(p22*b.p21)+(p23*b.p31)+(p24*b.p41);
		p22 = (p21*b.p12)+(p22*b.p22)+(p23*b.p32)+(p24*b.p42);
		p23 = (p21*b.p13)+(p22*b.p23)+(p23*b.p33)+(p24*b.p43);
		p24 = (p21*b.p14)+(p22*b.p24)+(p23*b.p34)+(p24*b.p44);

		p31 = (p31*b.p11)+(p32*b.p21)+(p33*b.p31)+(p34*b.p41);
		p32 = (p31*b.p12)+(p32*b.p22)+(p33*b.p32)+(p34*b.p42);
		p33 = (p31*b.p13)+(p32*b.p23)+(p33*b.p33)+(p34*b.p43);
		p34 = (p31*b.p14)+(p32*b.p24)+(p33*b.p34)+(p34*b.p44);
		
		p41 = (p41*b.p11)+(p42*b.p21)+(p43*b.p31)+(p44*b.p41);
		p42 = (p41*b.p12)+(p42*b.p22)+(p43*b.p32)+(p44*b.p42);
		p43 = (p41*b.p13)+(p42*b.p23)+(p43*b.p33)+(p44*b.p43);
		p44 = (p41*b.p14)+(p42*b.p24)+(p43*b.p34)+(p44*b.p44);
	}

	void matrix4x4::copy(matrix4x4& b)
	{
		p11=b.p11;
		p12=b.p12;
		p13=b.p13;
		p14=b.p14;
		p21=b.p21;
		p22=b.p22;
		p23=b.p23;
		p24=b.p24;
		p31=b.p31;
		p32=b.p32;
		p33=b.p33;
		p34=b.p34;
		p41=b.p41;
		p42=b.p42;
		p43=b.p43;
		p44=b.p44;
	}

	vector3d matrix4x4::apply(vector3d original)
	{
		vector3d temp = vector3d(0,0,0);
		temp.x = (p11*original.x)+(p12*original.y)+(p13*original.z);
		temp.y = (p21*original.x)+(p22*original.y)+(p23*original.z);
		temp.z = (p31*original.x)+(p32*original.y)+(p33*original.z);
		return temp;
	}

	point matrix4x4::apply(point original)
	{
		point temp;
		temp.setX((p11*original.getX())+(p12*original.getY())+(p13*original.getZ()));
		temp.setY((p21*original.getX())+(p22*original.getY())+(p23*original.getZ()));
		temp.setZ((p31*original.getX())+(p32*original.getY())+(p33*original.getZ()));
		return temp;
	}

	float* matrix4x4::glForm() 
	{
		float out[16] = {p11, p12, p13, p14,
						 p21, p22, p23, p24,
						 p31, p32, p33, p34,
						 p41, p42, p43, p44};
		return out;
	}
}