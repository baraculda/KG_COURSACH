#include "my_graph.h"
#include <stdio.h>
#include <queue>
#include <iostream>
using namespace std;

class vertexArray
{
public:
	point** allPoints;
	int number_of_vertexs;

	vertexArray()
	{
		allPoints = nullptr;
		number_of_vertexs = 0;
	}

	vertexArray(int _number, point** _points) // уникальный
	{
		allPoints = _points;
		number_of_vertexs = _number;
	}

	void set(point* A, point* B, point* C, point* D)
	{
		number_of_vertexs = 4;
		allPoints = new point * [number_of_vertexs];
		allPoints[0] = A;
		allPoints[1] = B;
		allPoints[2] = C;
		allPoints[3] = D;

	};

	void set(point* A, point* B, point* C, point* D, point* E, point* F, point* G, point* H)
	{
		number_of_vertexs = 8;
		allPoints = new point * [number_of_vertexs];
		allPoints[0] = A;
		allPoints[1] = B;
		allPoints[2] = C;
		allPoints[3] = D;
		allPoints[4] = E;
		allPoints[5] = F;
		allPoints[6] = G;
		allPoints[7] = H;
	};
};

class planeArray
{
public:
	int number_of_planes;
	plane** planes;
	planeArray()
	{
		number_of_planes = 0;
		planes = nullptr;
	}

	planeArray(int _number, plane** _planes) // уникальный
	{
		planes = _planes;
		number_of_planes = _number;
	}


	void updateCoef()
	{
		for (int i = 0; i < number_of_planes; i++)
		{
			planes[i]->updateABCD();
			planes[i]->updMinValues();
		}
	}

};


class window
{
public:

	int Xstart, Ystart, size;

	window() {};
	window(float x, float y, float s) : Xstart(x), Ystart(y), size(s) {};

};






class Warnok_draw
{
	vertexArray* sceneVertexs; // все вершины в сцене
	planeArray* scenePlanes; // все многоугольники в сцене
	point* p1 = new point();
	point* p2 = new point();

	void checkSizing(int _i, window* _w, bool* _isNotVisible)
	{
		int Xleft = _w->Xstart;
		int Xright = _w->Xstart + _w->size - 1;
		int Ydown = _w->Ystart;
		int Yup = _w->Ystart + _w->size - 1;

		*_isNotVisible = true;

		if (scenePlanes->planes[_i]->Xmin > Xright) {
			*_isNotVisible = false;
		}
		if (scenePlanes->planes[_i]->Xmax < Xleft) {
			*_isNotVisible = false;
		}

		if (scenePlanes->planes[_i]->Ymin > Yup) {
			*_isNotVisible = false;
		}
		if (scenePlanes->planes[_i]->Ymax < Ydown) {
			*_isNotVisible = false;
		}

	}


	// линейная
	void visualize(window* _w, int _color)
	{
		for (int x = _w->Xstart; x < _w->Xstart + _w->size; x++)
		{
			setcolor(_color);
			line(x, _w->Ystart, x, _w->Ystart + _w->size);
		}
	}

	void isPointVisible(point* p, point* p1, point* p2, int* pointSeen)
	{
		int rab1 = (p->x - p1->x) * (p2->y - p1->y);
		int rab2 = (p->y - p1->y) * (p2->x - p1->x);
		int rab3 = rab1 - rab2;

		if (rab3 > 0)
			*pointSeen = 1;
		if (rab3 == 0)
			*pointSeen = 0;

		if (rab3 < 0)
			*pointSeen = -1;
	}

	void calcPixelColor(int i, window* _w, int* z)
	{
		point* middle = new point;

		middle->x = _w->Xstart + _w->size / 2;
		middle->y = _w->Ystart + _w->size / 2;

		if (scenePlanes->planes[i]->C == 0)
		{
			for (int j = 1; j < scenePlanes->number_of_planes; j++)
			{
				*z = max(sceneVertexs->allPoints[j]->z, sceneVertexs->allPoints[j - 1]->z);
			}
		}
		else
		{
			float A = scenePlanes->planes[i]->A;
			float B = scenePlanes->planes[i]->B;
			float C = scenePlanes->planes[i]->C;
			float D = scenePlanes->planes[i]->D;
			*z = -(A * middle->x + B * middle->y + D) / C;
		}

	}



	void cover(window* _w, int* number)
	{
		int Zmax = -100000;
		int num = 0;

		point* windowMiddle = new point;

		windowMiddle->x = _w->Xstart + _w->size / 2;
		windowMiddle->y = _w->Ystart + _w->size / 2;


		// для каждого многоугольника
		for (int i = 0; i < scenePlanes->number_of_planes; i++)
		{
			int index = scenePlanes->planes[i]->first_vertex_idx;

			int middleIsSeen = 0;


			// для каждого ребра многоугольника
			for (int j = 0; j < scenePlanes->planes[i]->point_number - 1; j++) //  -1?
			{
				p1->x = sceneVertexs->allPoints[index]->x;
				p1->y = sceneVertexs->allPoints[index]->y;
				p2->x = sceneVertexs->allPoints[index + 1]->x;
				p2->y = sceneVertexs->allPoints[index + 1]->y;

				isPointVisible(windowMiddle, p1, p2, &middleIsSeen);
				if (middleIsSeen < 0)
					break; // METKA_1

				index++;
			}

			if (middleIsSeen < 0)
			{ // skip
			}
			else
			{
				// последнее ребро многоугольника
				p1->x = sceneVertexs->allPoints[index]->x;
				p1->y = sceneVertexs->allPoints[index]->y;
				int start_idx = scenePlanes->planes[i]->first_vertex_idx;
				p2->x = sceneVertexs->allPoints[start_idx]->x;
				p2->y = sceneVertexs->allPoints[start_idx]->y;

				isPointVisible(windowMiddle, p1, p2, &middleIsSeen);

				if (middleIsSeen >= 0)
				{
					int z = 0;
					calcPixelColor(i, _w, &z);
					if (z >= Zmax)
					{
						Zmax = z;
						*number = i;
					}
				}
			}

		}// METKA_1
	}

	void mainWarnokAlgorithm()
	{
		vector<window*> stack;
		window* main_frame = new window(0, 0, 512);

		stack.push_back(main_frame);

		bool isWindowNotEmpty;

		while (stack.size() != 0)
		{
			window* curWindow = stack.back();

			stack.pop_back();

			isWindowNotEmpty = false;
			int idx = 0;
			while (idx < scenePlanes->number_of_planes && isWindowNotEmpty == false)
			{
				checkSizing(idx, curWindow, &isWindowNotEmpty);
				idx++;
			}

			if (isWindowNotEmpty == true)
			{

				if (curWindow->size > 1)
				{
					// разбить на окна
					int s = curWindow->size / 2;
					int Xst = curWindow->Xstart;
					int Yst = curWindow->Ystart;

					window* newWindow1 = new window(Xst + s, Yst + s, s);
					stack.push_back(newWindow1);

					window* newWindow2 = new window(Xst, Yst + s, s);
					stack.push_back(newWindow2);

					window* newWindow3 = new window(Xst + s, Yst, s);
					stack.push_back(newWindow3);

					window* newWindow4 = new window(Xst, Yst, s);
					stack.push_back(newWindow4);

				}
				else
				{
					//  если окно размером с пиксел, то вычислить его атрибуты 
					int number = -1;
					cover(curWindow, &number);

					if (number >= 0)
					{
						// visualize
						visualize(curWindow, scenePlanes->planes[number]->color);
					}
					else
					{
						// visualise with bkg color
						visualize(curWindow, BCKG_COLOR);
					}
				}
			}
			else
			{
				visualize(curWindow, BCKG_COLOR);
			}
		}

	}

public:

	Warnok_draw()
	{
	}

	Warnok_draw(vertexArray* _all_vertexs, planeArray* _all_planes)
	{
		sceneVertexs = _all_vertexs; // все вершины в сцене
		scenePlanes = _all_planes; // все многоугольники в сцене
	}

	void draw_scene()
	{

		scenePlanes->updateCoef();


		mainWarnokAlgorithm();

	}

};