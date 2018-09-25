#pragma once

#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QInputDialog>

#include <vector>


class Graph_2D_Window : public QMainWindow, protected QOpenGLFunctions
{
public:
	Graph_2D_Window();
	
protected:

private slots:
	void enter_equation();
	
private:
	void InitMenuBar();
	
	std::vector<double> points;
	
};
