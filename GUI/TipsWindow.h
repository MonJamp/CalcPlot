#pragma once

#include <QDialog>

#include <vector>

class QString;
class QCheckBox;
class QTextBrowser;


class TipsWindow : public QDialog
{
Q_OBJECT
public:
	TipsWindow(bool show_startup_tips = false);

	bool show_tips;

protected:
	void showEvent(QShowEvent *event) override;
	void hideEvent(QHideEvent *event) override;

Q_SIGNALS:
	void hideRequest();

private slots:
	void next_tip();
	void prev_tip();
	void toggle_startup_tips();

private:
	void InitLayout();
	void LoadTips();

	int tips_index;
	std::vector<QString> tips;
	QCheckBox *show_tips_checkbox;
	QTextBrowser *tips_text;
};
