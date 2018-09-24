#pragma once

#include <QMainWindow>
#include <QOpenGLFunctions>

class Graph_2D_Window : public QMainWindow, protected QOpenGLFunctions
{
public:
	Graph_2D_Window();
	
protected:

private slots:
	void graph();
	
private:
	void InitMenuBar();
	
};