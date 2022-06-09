#pragma once

#include <QtWidgets/QWidget>
#include <QString>
#include "config.h"
#include "ui_DialogSettings.h"

class DialogSettings : public QDialog
{
	Q_OBJECT

public:
	DialogSettings(QWidget *parent = Q_NULLPTR);
	~DialogSettings();

private:
	Ui::Dialog ui;
	

	void Init();
	void InitConnecting();
	void UpdateLanguage();

private slots:
	void btnOKResponsed();
};
