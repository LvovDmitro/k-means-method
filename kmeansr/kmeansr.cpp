#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <fstream>
#include<random>
#include<vector>

using namespace sf;
using namespace std;
const int n = 1000000;//количество точек
const int k = 4;//количество кластеров, т.е. после каждой итерации, распределение лучше
random_device random;//старт генаратора
mt19937 generator(random());//стартовое значение, семя, mt - имя
uniform_int_distribution<int> distrib(0, 500);//равномерное распределение точек
int x[n], j , y[n] , centrx[k],yC[k], col[k], xcol[k], ycol[k];
VertexArray list(Points);//точки
Vector2f point;
CircleShape circlesh1(4); //4 - радиус 
CircleShape circlesh2(4);//кластеры
CircleShape circlesh3(4);
CircleShape circlesh4(4);

void Distribution()
{
	for (int i = 0; i < n; i++)
	{
		x[i] = distrib(generator);//равномерное распределение точек
		y[i] = distrib(generator);
	}
	for (int i = 0; i < k; i++)
	{
		centrx[i] = distrib(generator);//равномерное распределение центр масс
		yC[i] = distrib(generator);
	}
}
void CentreClusters()
{
	for (int i = 0; i < k; i++)
	{
		centrx[i] = xcol[i] / col[i];
		yC[i] = ycol[i] / col[i];
	}
}

void Paint()
{
	circlesh1.setPosition(centrx[0], yC[0]);
	circlesh1.setFillColor(Color::Red);
	circlesh2.setPosition(centrx[1], yC[1]);
	circlesh2.setFillColor(Color::Blue);
	circlesh3.setPosition(centrx[2], yC[2]);
	circlesh3.setFillColor(Color::White);
	circlesh4.setPosition(centrx[3], yC[3]);
	circlesh4.setFillColor(Color::Green);
	RenderWindow window(VideoMode(500, 500), "Kmeans", Style::Default);
	window.setPosition(Vector2i(700, 200));
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(list);
		window.draw(circlesh1);
		window.draw(circlesh2);
		window.draw(circlesh3);
		window.draw(circlesh4);
		window.display();
	}
}
void Сlustering()
{
	for (int i = 0; i < n; i++)
	{
		point.x = x[i];
		point.y = y[i];
		if (sqrt(pow(centrx[0] - point.x, 2) + pow(yC[0] - point.y, 2)) <= sqrt(pow(centrx[1] - point.x, 2) + pow(yC[1] - point.y, 2)) && sqrt(pow(centrx[0] - point.x, 2) + pow(yC[0] - point.y, 2)) <= sqrt(pow(centrx[2] - point.x, 2) + pow(yC[2] - point.y, 2)) && sqrt(pow(centrx[0] - point.x, 2) + pow(yC[0] - point.y, 2)) <= sqrt(pow(centrx[3] - point.x, 2) + pow(yC[3] - point.y, 2)))
		{
			col[0]++;
			xcol[0] += point.x;//определяем точки по кластерам
			ycol[0] += point.y;
			list.append(Vertex(point, Color::Red));
		}
		else if (sqrt(pow(centrx[1] - point.x, 2) + pow(yC[1] - point.y, 2)) <= sqrt(pow(centrx[2] - point.x, 2) + pow(yC[2] - point.y, 2)) && sqrt(pow(centrx[1] - point.x, 2) + pow(yC[1] - point.y, 2)) <= sqrt(pow(centrx[3] - point.x, 2) + pow(yC[3] - point.y, 2)))
		{
			col[1]++;
			xcol[1] += point.x;
			ycol[1] += point.y;
			list.append(Vertex(point, Color::Green));
		}
		else if (sqrt(pow(centrx[2] - point.x, 2) + pow(yC[2] - point.y, 2)) <= sqrt(pow(centrx[3] - point.x, 2) + pow(yC[3] - point.y, 2)))
		{
			col[2]++;
			xcol[2] += point.x;
			ycol[2] += point.y;
			list.append(Vertex(point, Color::Blue));
		}
		else
		{
			col[3]++;
			xcol[3] += point.x;
			ycol[3] += point.y;
			list.append(Vertex(point, Color::Yellow));
		}

	}
	CentreClusters();
	for (int i = 0; i < j; i++)//обнуление для последующих вычислений
	{
		col[i] = 0;
		xcol[i] = 0;
		ycol[i] = 0;
	}
}
int main()
{
	cin >> j;
	Distribution();
	for (int i = 0; i <= j; i++)
	{
		Сlustering();
		Paint();
	}
}