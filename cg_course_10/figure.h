#pragma once

#include <stdio.h>
#include "my_graph.h"

class prism
{
	point* middle;

	void upd_mid()
	{
		middle->x = 0;
		for (int i = 0; i < vertex_num; i++)
			middle->x += vertex[i]->x;

		middle->x /= (float)vertex_num;

		middle->y = 0;
		for (int i = 0; i < vertex_num; i++)
			middle->y += vertex[i]->y;

		middle->y /= (float)vertex_num;

		middle->z = 0;
		for (int i = 0; i < vertex_num; i++)
			middle->z += vertex[i]->z;

		middle->z /= (float)vertex_num;

		middle->w = 1;
	}


public:
	int side_num;
	int vertex_num;
	point** vertex;
	plane** sides;

	point** sh_vertex;
	plane** sh_sides;

	prism()
	{
	}

	prism(point** _v, point** _sh_v, plane** _s, plane** _sh_s, int _side_num, int _vertex_num)
	{
		vertex = _v;
		sides = _s;

		sh_vertex = _sh_v;
		sh_sides = _sh_s;
		middle = new point;
		side_num = _side_num;
		vertex_num = _vertex_num;
	}


	prism(point** _vertx, plane** _sides, int _side_num, int _vertex_num)
	{
		vertex = _vertx;
		sides = _sides;
		side_num = _side_num;
		vertex_num = _vertex_num;
		sh_vertex = nullptr;
		sh_sides = nullptr;
		middle = new point;
	}

	void move_each(double _x, double _y, double _z)
	{
		for (int i = 0; i < vertex_num; i++)
			vertex[i]->move(_x, _y, _z);
	}

	void map_each(double _x, double _y, double _z)
	{
		upd_mid();
		move_each(-middle->x, -middle->y, -middle->z);
		for (int i = 0; i < vertex_num; i++)
			vertex[i]->map(_x, _y, _z);
		move_each(middle->x, middle->y, middle->z);
	}

	void rotate_each(double ygol, int plane)
	{
		upd_mid();
		move_each(-middle->x, -middle->y, -middle->z);
		for (int i = 0; i < vertex_num; i++)
			vertex[i]->rotate(ygol, plane);
		move_each(middle->x, middle->y, middle->z);
	}

	void makeShadow()
	{
		for (int i = 0; i < vertex_num; i++)
		{
			sh_vertex[i]->x = vertex[i]->x;
			sh_vertex[i]->z = vertex[i]->z;
			sh_vertex[i]->y = 300;
			sh_vertex[i]->rotate(10, X);
		}
	}

	void projection_prizma()
	{
		for (int i = 0; i < vertex_num; i++)
		{
			vertex[i]->rotate(10, X);
		}
	}

	void unprojection_prizma()
	{
		for (int i = 0; i < vertex_num; i++)
		{
			vertex[i]->rotate(-10, X);
		}
	}
};