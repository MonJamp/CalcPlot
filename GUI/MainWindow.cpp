#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QResizeEvent>

#include "MainWindow.h"

#ifdef DEBUG
  #include <iostream>
#endif


void MainWindowSettings::LoadDefaults(MainWindow *window)
{
	x_pos = window->pos().x();
	y_pos = window->pos().y();
	width = window->size().width();
	height = window->size().height();
	show_tips = true;
}

void MainWindowSettings::Load()
{
	settings_file->open(QIODevice::ReadOnly);
	
	if(settings_file->exists() == false)
	{
		#ifdef DEBUG
		  std::cout << "Using Default Settings..." << std::endl;
		#endif
		
		return;
	}
	else
	{
		*data_stream >> x_pos >> y_pos >> width >> height >> show_tips;
	}
	
	settings_file->close();
}

void MainWindowSettings::Save()
{
	settings_file->open(QIODevice::WriteOnly);
	
	*data_stream << x_pos << y_pos << width << height << show_tips;
	
	settings_file->close();
}


MainWindow::MainWindow()
{
	tips_window = new TipsWindow();
	settings = new MainWindowSettings("main_window.cplot");
	//Store default settings first then try to load settings from file
	settings->LoadDefaults(this);
	load_settings();

	InitMenuBar();
	this->show();

	if(settings->show_tips)
	{
		tips_window->show();
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	this->save_settings();
	tips_window->close();

	event->accept();
}

void MainWindow::moveEvent(QMoveEvent *event)
{
	settings->x_pos = event->pos().x();
	settings->y_pos = event->pos().y();

	event->accept();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	settings->width = event->size().width();
	settings->height = event->size().height();

	event->accept();
}

void MainWindow::graph_2d()
{
	graph_2d_window = new Graph_2D_Window();
	graph_2d_window->show();
}

void MainWindow::graph_3d()
{
}

void MainWindow::help()
{
}

void MainWindow::tips()
{
	tips_window->show();
}

void MainWindow::about()
{
	QMessageBox::about(this,
	                   tr("About CalcPlot"),
	                   tr("Linux/Windows x86"));
}

void MainWindow::InitMenuBar()
{
	const QIcon exit_icon = QIcon::fromTheme("application-exit");
	const QIcon help_icon = QIcon::fromTheme("help-contents");
	const QIcon tips_icon = QIcon::fromTheme("help-faq");
	const QIcon about_icon = QIcon::fromTheme("help-about");

	QMenu *file_menu = menuBar()->addMenu(tr("&Window"));
	file_menu->addAction(tr("Graph &2D"), this, &MainWindow::graph_2d);
	file_menu->addAction(tr("Graph &3D"), this, &MainWindow::graph_3d);

	file_menu->addSeparator();

	file_menu->addAction(exit_icon, tr("&Quit"), this, &QWidget::close);

	QMenu *help_menu = menuBar()->addMenu(tr("&Help"));
	help_menu->addAction(help_icon, tr("&Help"), this, &MainWindow::help);
	help_menu->addAction(tips_icon, tr("&Tips"), this, &MainWindow::tips);
	help_menu->addAction(about_icon, tr("&About"), this, &MainWindow::about);

	#ifdef DEBUG
		QMenu *dev_menu = menuBar()->addMenu(tr("&Dev"));
		dev_menu->addAction(tr("&Save Settings"), this, &MainWindow::save_settings);
		dev_menu->addAction(tr("&Load Settings"), this, &MainWindow::load_settings);
	#endif

	connect(tips_window, &TipsWindow::hideRequest, this, &MainWindow::save_settings);
}

void MainWindow::save_settings()
{
	settings->show_tips = tips_window->show_tips;

	settings->Save();

	std::cout << "Settings Saved!" << std::endl;
}

void MainWindow::load_settings()
{
	settings->Load();

	this->move(settings->x_pos, settings->y_pos);
	this->resize(settings->width, settings->height);
	tips_window->show_tips = settings->show_tips;

	std::cout << "Settings Loaded!" << std::endl;
}
