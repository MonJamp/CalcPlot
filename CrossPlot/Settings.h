#pragma once

#include <QFile>
#include <QString>
#include <QDataStream>


struct Settings
{
public:
	Settings(QString file_path)
	{
		settings_file = new QFile(file_path);
		data_stream = new QDataStream(settings_file);
	}


	virtual void LoadDefaults() {}
	virtual void Load() {}
	virtual void Save() {}

protected:
	QFile *settings_file;
	QDataStream *data_stream;
};
