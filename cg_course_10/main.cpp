#include "../libwinbgi/src/graphics.h"
#include <stdio.h>
#include <iostream>

#include "figure.h"
#include "my_graph.h"
#include "my_algorithm.h"

#define SHADOW_CLR 0
#define MOVE_DELTA 32

void menu(Warnok_draw* scene, prism* obj1, prism* obj2)
{
	initwindow(WINDOW_SIZE, WINDOW_SIZE);
	
	obj1->map_each(2, 2, 2);
	obj1->move_each(64, 128, 0);

	obj2->map_each(0.5, 0.5, 0.5);
	obj2->move_each(128, 128, 0);

	obj1->makeShadow();
	obj2->makeShadow();
	obj1->projection_prizma();
	obj2->projection_prizma();

	scene->draw_scene();

	obj1->unprojection_prizma();
	obj2->unprojection_prizma();

	printf("done\n");
	char c = '1';
	bool exit_flag = false;
	while (!exit_flag)
	{
		c = getch();
		switch (c)
		{
		case '1':
			obj1->map_each(0.5, 0.5, 0.5);
			break;
		case '2':
			obj1->map_each(2, 2, 2);
			break;

		case 'd':
			obj1->move_each(MOVE_DELTA, 0, 0);
			break;

		case 'a':
			obj1->move_each(-MOVE_DELTA, 0, 0);
			break;

		case 'w':
			obj1->move_each(0, -MOVE_DELTA, 0);
			break;
		case 's':
			obj1->move_each(0, MOVE_DELTA, 0);
			break;

		case 'q':
			obj1->move_each(0, 0, MOVE_DELTA);
			break;
		case 'e':
			obj1->move_each(0, 0, -MOVE_DELTA);
			break;

		case 'r':
			obj1->rotate_each(20, X);
			break;
		case 'f':
			obj1->rotate_each(-20, X);
			break;
		case 't':
			obj1->rotate_each(20, Y);
			break;
		case 'g':
			obj1->rotate_each(-20, Y);
			break;
		case 'z':
			obj1->rotate_each(20, Z);
			break;
		case 'x':
			obj1->rotate_each(-20, Z);
			break;


		case '6':
			obj2->map_each(0.5, 0.5, 0.5);
			break;
		case '7':
			obj2->map_each(2, 2, 2);
			break;

		case 'k':
			obj2->move_each(MOVE_DELTA, 0, 0);
			break;

		case 'h':
			obj2->move_each(-MOVE_DELTA, 0, 0);
			break;

		case 'u':
			obj2->move_each(0, -MOVE_DELTA, 0);
			break;
		case 'j':
			obj2->move_each(0, MOVE_DELTA, 0);
			break;

		case 'y':
			obj2->move_each(0, 0, MOVE_DELTA);
			break;
		case 'i':
			obj2->move_each(0, 0, -MOVE_DELTA);
			break;

		case 'c':
			obj2->rotate_each(20, X);
			break;
		case 'v':
			obj2->rotate_each(-20, X);
			break;
		case 'b':
			obj2->rotate_each(20, Y);
			break;
		case 'n':
			obj2->rotate_each(-20, Y);
			break;
		case 'o':
			obj2->rotate_each(20, Z);
			break;
		case 'l':
			obj2->rotate_each(-20, Z);
			break;

		case '/':
			exit_flag = true;
			break;
		default:
			break;
		}
		if (!exit_flag)
		{
			obj1->makeShadow();
			obj2->makeShadow();
			obj1->projection_prizma();
			obj2->projection_prizma();
			scene->draw_scene();
			obj1->unprojection_prizma();
			obj2->unprojection_prizma();
		}
		printf("done\n");
	}


	getch();
	closegraph();

}


int main()
{
	point* A = new point(0, 100, 100);
	point* B = new point(100, 100, 100);
	point* C = new point(100, 100, 0);
	point* D = new point(0, 100, 0);
	point* E = new point(50, 0, 100);
	point* F = new point(150, 0, 100);
	point* G = new point(150, 0, 0);
	point* H = new point(50, 0, 0);

	plane* ABFE = new plane(A, B, F, E);
	ABFE->set(0, 5);

	plane* BCGF = new plane(B, C, G, F);
	BCGF->set(4, 2);

	plane* CDHG = new plane(C, D, H, G);
	CDHG->set(8, 9);

	plane* DAEH = new plane(D, A, E, H);
	DAEH->set(12, 1);

	plane* EFGH = new plane(E, F, G, H);
	EFGH->set(16, 3);

	plane* DCBA = new plane(D, C, B, A);
	DCBA->set(20, 4);


	point* prism1_points[8] = { A, B, C, D, E, F, G, H };
	plane* prizm1_planes[6] = { ABFE, BCGF, CDHG, DAEH, EFGH,  DCBA };


	point* s_A = new point(0, 100, 100);
	point* s_B = new point(100, 100, 100);
	point* s_C = new point(100, 100, 0);
	point* s_D = new point(0, 100, 0);
	point* s_E = new point(0, 0, 100);
	point* s_F = new point(100, 0, 100);
	point* s_G = new point(100, 0, 0);
	point* s_H = new point(0, 0, 0);

	plane* s_ABFE = new plane(s_A, s_B, s_F, s_D);
	s_ABFE->set(24, SHADOW_CLR);

	plane* s_BCGF = new plane(s_B, s_C, s_G, s_F);
	s_BCGF->set(28, SHADOW_CLR);

	plane* s_CDHG = new plane(s_C, s_D, s_H, s_G);
	s_CDHG->set(32, SHADOW_CLR);

	plane* s_DAEH = new plane(s_D, s_A, s_E, s_H);
	s_DAEH->set(36, SHADOW_CLR);

	plane* s_EFGH = new plane(s_E, s_F, s_G, s_H);
	s_EFGH->set(40, SHADOW_CLR);

	plane* s_DCBA = new plane(s_D, s_C, s_B, s_A);
	s_DCBA->set(44, SHADOW_CLR);

	point* s_points[4 * 6] = {
		 s_A,  s_B,  s_F,  s_E,
		 s_B,  s_C,  s_G,  s_F,
		 s_C,  s_D,  s_H,  s_G,
		 s_D,  s_A,  s_E,  s_H,
		 s_E,  s_F,  s_G,  s_H,
		 s_D,  s_C,  s_B,  s_A
	};

	plane* shadow_prism1_planes[6] = { s_ABFE, s_BCGF, s_CDHG, s_DAEH, s_EFGH,  s_DCBA };

	point* shadow_prism1_points[8] = {
		 s_A,  s_B,  s_C,  s_D,  s_E,  s_F,  s_G,  s_H
	};




	point* A2 = new point(0, 32, 0);
	point* B2 = new point(16, 32, 32);
	point* C2 = new point(20, 32, 0);
	point* D2 = new point(0, 0, 0);
	point* E2 = new point(16, 0, 32);
	point* F2 = new point(20, 0, 0);

	plane* DEF2 = new plane(D2, E2, F2);
	DEF2->set(48, 4);

	plane* ACB2 = new plane(A2, C2, B2);
	ACB2->set(51, 6);

	plane* ABED2 = new plane(A2, B2, E2, D2);
	ABED2->set(54, 12);

	plane* BCFE2 = new plane(B2, C2, F2, E2);
	BCFE2->set(58, 13);

	plane* CADF2 = new plane(C2, A2, D2, F2);
	CADF2->set(62, 11);


	point* prism2_points[6] = { A2, B2, C2, D2, E2, F2 };
	plane* prizm2_planes[5] = { DEF2, ACB2, ABED2, BCFE2, CADF2 };


	point* s_A2 = new point(0, 20, 0);
	point* s_B2 = new point(10, 10, 30);
	point* s_C2 = new point(20, 20, 0);
	point* s_D2 = new point(0, 0, 0);
	point* s_E2 = new point(10, 0, 30);
	point* s_F2 = new point(20, 0, 0);

	plane* s_DEF2 = new plane(s_D2, s_E2, s_F2);
	s_DEF2->set(66, SHADOW_CLR);

	plane* s_ACB2 = new plane(s_A2, s_C2, s_B2);
	s_ACB2->set(69, SHADOW_CLR);

	plane* s_ABED2 = new plane(s_A2, s_B2, s_E2, s_D2);
	s_ABED2->set(72, SHADOW_CLR);

	plane* s_BCFE2 = new plane(s_B2, s_C2, s_F2, s_E2);
	s_BCFE2->set(76, SHADOW_CLR);

	plane* s_CADF2 = new plane(s_C2, s_A2, s_D2, s_F2);
	s_CADF2->set(80, SHADOW_CLR);


	point* shadow_prism2_points[6] = { s_A2, s_B2, s_C2, s_D2, s_E2, s_F2 };
	plane* shadow_prism2_planes[5] = { s_DEF2, s_ACB2, s_ABED2, s_BCFE2, s_CADF2 };




	point* all_points2[4 * 6 * 2 + (6 + 4 * 3) * 2] = {
	A, B, F, E, // 0
	B, C, G, F, // 4
	C, D, H, G, // 8
	D, A, E, H, // 12
	E, F, G, H, // 16
	D, C, B, A, // 20

	s_A,  s_B,  s_F,  s_E, // 24
	s_B,  s_C,  s_G,  s_F, // 28
	s_C,  s_D,  s_H,  s_G, // 32
	s_D,  s_A,  s_E,  s_H, // 36
	s_E,  s_F,  s_G,  s_H, // 40
	s_D,  s_C,  s_B,  s_A,  // 44


	D2, E2, F2, // 48
	A2, C2, B2, // 51
	A2, B2, E2, D2, // 54
	B2, C2, F2, E2, // 58
	C2, A2, D2, F2,  // 62

	s_D2, s_E2, s_F2, // 66
	s_A2, s_C2, s_B2, // 69
	s_A2, s_B2, s_E2, s_D2, // 72
	s_B2, s_C2, s_F2, s_E2, // 76
	s_C2, s_A2, s_D2, s_F2 // 80

	};


	plane* all_planes2[6 * 2 + 5 * 2] = {
		ABFE, BCGF, CDHG, DAEH, EFGH,  DCBA,
		s_ABFE, s_BCGF, s_CDHG, s_DAEH, s_EFGH,  s_DCBA,
		DEF2, ACB2, ABED2, BCFE2, CADF2,
		s_DEF2, s_ACB2, s_ABED2, s_BCFE2, s_CADF2
	};


	vertexArray* scenePoints2 = new vertexArray(4 * 6 * 2 + 3 * 2 * 2 + 4 * 3 * 2, all_points2);
	planeArray* scenePlanes2 = new planeArray(6 * 2 + 5 * 2, all_planes2);


	prism* obj2 = new prism(prism1_points, shadow_prism1_points, prizm1_planes, shadow_prism1_planes, 6, 8);
	prism* obj1 = new prism(prism2_points, shadow_prism2_points, prizm2_planes, shadow_prism2_planes, 5, 6);

	Warnok_draw* scene = new Warnok_draw(scenePoints2, scenePlanes2);
	menu(scene, obj1, obj2);

	return 0;
}

