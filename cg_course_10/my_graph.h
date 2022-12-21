#pragma once
#include "stdio.h"
#include "math.h"
#define X 0
#define Y 1
#define Z 2
#define W 3
#define BCKG_COLOR 8
#define WINDOW_SIZE 512

class point
{
	float* multiplication(float mtx[4][4])
	{
		float x_ = x;
		float y_ = y;
		float z_ = z;
		float w_ = w;
		float temp[4] = { x, y, z, w };
		float res[4] = { 0,0,0,0 };

		res[X] = temp[0] * mtx[0][0] + temp[1] * mtx[1][0] + temp[2] * mtx[2][0] + temp[3] * mtx[3][0];
		res[Y] = temp[0] * mtx[0][1] + temp[1] * mtx[1][1] + temp[2] * mtx[2][1] + temp[3] * mtx[3][1];
		res[Z] = temp[0] * mtx[0][2] + temp[1] * mtx[1][2] + temp[2] * mtx[2][2] + temp[3] * mtx[3][2];
		res[W] = temp[0] * mtx[0][3] + temp[1] * mtx[1][3] + temp[2] * mtx[2][3] + temp[3] * mtx[3][3];

		x = res[X];
		y = res[Y];
		z = res[Z];
		w = res[W];
		return res;
	}

	void rotateX(float ygol) {
		ygol = ygol * 3.1415 / 180;

		float matrix[4][4] = {
			1, 0, 0, 0,	0, cos(ygol), -sin(ygol), 0,
			0, sin(ygol), cos(ygol), 0, 0, 0, 0, 1 };
		multiplication(matrix);
	}

	void rotateY(float ygol) {
		ygol = ygol * 3.1415 / 180;

		float matrix[4][4] = {
			cos(ygol), 0, -sin(ygol), 0,0, 1, 0, 0,
			sin(ygol), 0, cos(ygol), 0,	0, 0, 0, 1 };
		multiplication(matrix);
	}

	void rotateZ(float ygol) {
		ygol = ygol * 3.1415 / 180;

		float matrix[4][4] = {
			cos(ygol), -sin(ygol), 0, 0,	sin(ygol), cos(ygol), 0, 0,
			0, 0, 1, 0,		0, 0, 0, 1 };
		multiplication(matrix);
	}

	float sx, sy, sz, sw;
public:

	float x, y, z, w;
	point(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
	{
		w = 1;
	}
	point()
	{
		x = 0; y = 0; z = 0; w = 1;
	}


	void move(float _x, float _y, float _z)
	{
		float matrix[4][4] = {
			1,  0,  0,  0,	0,  1,  0,  0,
			0,  0,  1,  0,	_x, _y, _z, 1 };

		multiplication(matrix);
	}

	void map(float _x, float _y, float _z) {
		float matrix[4][4] = {
			_x, 0, 0, 0, 0, _y, 0, 0,
			0, 0, _z, 0, 0, 0, 0, 1 };

		multiplication(matrix);
	}


	void rotate(float ygol, int _axis) {
		if (_axis == X)
			rotateX(ygol);
		if (_axis == Y)
			rotateY(ygol);
		if (_axis == Z)
			rotateZ(ygol);
	}
};



class plane
{

public:
	point** v;
	int first_vertex_idx;
	int point_number;

	int color;
	float A, B, C, D;
	float Xmin, Xmax, Ymin, Ymax;

	plane(point* _A, point* _B, point* _C)
	{
		point_number = 3;
		v = new point * [point_number];
		v[0] = _A;
		v[1] = _B;
		v[2] = _C;
		updateABCD();
		updMinValues();
	}

	plane(point* _A, point* _B, point* _C, point* _D)
	{
		point_number = 4;
		v = new point * [point_number];
		v[0] = _A;
		v[1] = _B;
		v[2] = _C;
		v[3] = _D;
		updateABCD();
		updMinValues();
	}

	void set(int _firts_vertex_idx, int _color)
	{
		first_vertex_idx = _firts_vertex_idx;
		color = _color;
	}


	void set(int _firts_vertex_idx, int _num_of_points, int _color)
	{
		first_vertex_idx = _firts_vertex_idx;
		point_number = _num_of_points;
		color = _color;
	}


	void updateABCD()
	{
		int i = 0;
		float M[3] = { v[i]->x, v[i]->y, v[i]->z };
		int ai = i - 1;
		if (ai < 0)
			ai = 2;
		int bi = i + 1;
		if (bi > 2)
			bi = 0;
		float a[3] = { v[ai]->x - v[i]->x, v[ai]->y - v[i]->y, v[ai]->z - v[i]->z };
		float b[3] = { v[bi]->x - v[i]->x, v[bi]->y - v[i]->y, v[bi]->z - v[i]->z };

		A = a[Y] * b[Z] - a[Z] * b[Y];
		B = a[X] * b[Z] - a[Z] * b[X];
		B = -B;
		C = a[X] * b[Y] - a[Y] * b[X];

		D = M[X] * A + M[Y] * B + M[Z] * C;
		D = -D;
		point* cam = new point(0, 0, 0);

		float val = A * cam->x + B * cam->y + C * cam->z + D;
		if (val <= 0)
		{
			A = -A;
			B = -B;
			C = -C;
			D = -D;
		}
	}

	void updMinValues()
	{
		Xmin = WINDOW_SIZE;
		Ymin = WINDOW_SIZE;
		Xmax = -1;
		Ymax = -1;
		for (int i = 0; i < point_number; i++)
		{
			if (v[i]->x < Xmin)
				Xmin = v[i]->x;

			if (v[i]->y < Ymin)
				Ymin = v[i]->y;

			if (v[i]->x >= Xmax)
				Xmax = v[i]->x;

			if (v[i]->y >= Ymax)
				Ymax = v[i]->y;
		}
	}

};