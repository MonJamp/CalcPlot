#pragma once

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QInputDialog>

#include <vector>


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = 0) : QOpenGLWidget(parent) { }

protected:
    void initializeGL() override
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    }

    void resizeGL(int w, int h) override
    {
        // Update projection matrix and other size related settings:
        m_projection.setToIdentity();
        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
    }

    void paintGL() override
    {
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClear(GL_COLOR_BUFFER_BIT);
    }
	
private:
	QMatrix4x4 m_projection;

};

class Graph_2D_Window : public QMainWindow
{
public:
	Graph_2D_Window();
	
protected:

private slots:
	void enter_equation();
	
private:
	void InitMenuBar();
	
	GLWidget* glWidget;
	std::vector<double> points;
	
};
