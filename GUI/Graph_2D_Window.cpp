#include <QMenuBar>
#include <QCloseEvent>

#include "Graph_2D_Window.h"


Graph_2D_Window::Graph_2D_Window()
{
	this->move(100, 100);
	this->resize(200, 200);
	
	InitMenuBar();
	this->show();
}

void Graph_2D_Window::InitMenuBar()
{
	const QIcon exit_icon = QIcon::fromTheme("application-exit");
	
	QMenu *graph_menu = menuBar()->addMenu(tr("&Graph"));
	graph_menu->addAction(tr("Enter equation..."), this, &Graph_2D_Window::graph);
	
	graph_menu->addSeparator();
	
	graph_menu->addAction(exit_icon, tr("&Quit"), this, &QWidget::close);
}

void Graph_2D_Window::graph()
{
	// TODO: open dialog
}