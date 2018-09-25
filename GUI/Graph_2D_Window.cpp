#include <QMenuBar>
#include <QCloseEvent>
#include <QInputDialog>
#include <QString>

#include "Graph_2D_Window.h"
#include "Calculator.h"

#ifdef DEBUG
  #include <iostream>
#endif


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
	graph_menu->addAction(tr("Enter equation..."), this, &Graph_2D_Window::enter_equation);
	
	graph_menu->addSeparator();
	
	graph_menu->addAction(exit_icon, tr("&Quit"), this, &QWidget::close);
}

void Graph_2D_Window::enter_equation()
{
	bool ok;
	
	QString text = QInputDialog::getText(this, tr("Equation"), tr("Enter equation: "), QLineEdit::Normal, tr(""), &ok);
	
	#ifdef DEBUG //Output points to console
		points = Calc::InfixToPoints(text.toStdString(), -10, 10, 1);
		
		for(unsigned int i = 0; i < points.size(); ++i) {
			if(i % 2 == 0) {
				std::cout << "(" << points[i] << ", ";
			} else {
				std::cout << points[i] << ")" << std::endl;
			}
		}
	#endif
}
