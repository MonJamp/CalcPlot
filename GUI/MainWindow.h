#pragma once

#include <QMainWindow>

#include "CrossPlot/Settings.h"
#include "TipsWindow.h"

class QString;
class MainWindow;


class MainWindowSettings : public Settings
{
public:
	MainWindowSettings(QString file_path) : Settings(file_path) {}

	void LoadDefaults(MainWindow *window);
	void Load();
	void Save();

	int x_pos;
	int y_pos;
	int width;
	int height;
	bool show_tips;

};

class MainWindow : public QMainWindow
{
public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent *event) override;
	void moveEvent(QMoveEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

private slots:
	void graph_2d();
	void graph_3d();

	void help();
	void tips();
	void about();

	void save_settings();
	void load_settings();

private:
	void InitMenuBar();

	MainWindowSettings* settings;
	TipsWindow* tips_window;

};
