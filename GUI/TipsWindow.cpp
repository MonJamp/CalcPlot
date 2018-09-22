#include <QString>
#include <QGridLayout>
#include <QTextBrowser>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QShowEvent>
#include <QHideEvent>

#include <random>

#include "TipsWindow.h"

 
TipsWindow::TipsWindow(bool show_startup_tips)
{
	this->show_tips = show_startup_tips;

	InitLayout();
	LoadTips();

	tips_index = std::rand() % tips.size();
	tips_text->setPlainText( tips[tips_index] );
}

void TipsWindow::showEvent(QShowEvent *event)
{
	show_tips_checkbox->setChecked(show_tips);

	event->accept();
}

void TipsWindow::hideEvent(QHideEvent *event)
{
	emit hideRequest();
	event->accept();
}

void TipsWindow::next_tip()
{
	tips_text->setPlainText( tips[ ++tips_index % tips.size() ] );
}

void TipsWindow::prev_tip()
{
	tips_text->setPlainText( tips[ --tips_index % tips.size() ] );
}

void TipsWindow::toggle_startup_tips()
{
	show_tips = !show_tips;
}

void TipsWindow::InitLayout()
{
	QGridLayout *layout = new QGridLayout;

	tips_text = new QTextBrowser;
	layout->addWidget(tips_text, 0, 1, -1, 1);

	QPixmap crossplot_icon = QPixmap(100, 100);
	crossplot_icon.fill();
	QLabel *crossplot_label = new QLabel();
	crossplot_label->setPixmap(crossplot_icon);
	crossplot_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	layout->addWidget(crossplot_label, 0, 2);

	QPushButton *next_button = new QPushButton("&Next Tip", this);
	connect(next_button, &QPushButton::clicked, this, &TipsWindow::next_tip);
	layout->addWidget(next_button, 1, 2);

	QPushButton *prev_button = new QPushButton("&Previous Tip", this);
	connect(prev_button, &QPushButton::clicked, this, &TipsWindow::prev_tip);
	layout->addWidget(prev_button, 2, 2);

	show_tips_checkbox = new QCheckBox("Show Tips on Startup", this);
	show_tips_checkbox->setChecked(show_tips);
	connect(show_tips_checkbox, &QCheckBox::clicked, this, &TipsWindow::toggle_startup_tips);
	layout->addWidget(show_tips_checkbox, 3, 2);

	layout->setColumnStretch(1, 30);
	layout->setColumnStretch(2, 5);

	setLayout(layout);
	this->setMinimumSize(400, 200);
	this->setMaximumSize(500, 250);
}

void TipsWindow::LoadTips()
{
	tips =  {
		"hi",
		"hello",
		"yo",
		"bonjour",
		"hola",
		"myushimyushi",
		"namste",
		"heil"
	};
}
