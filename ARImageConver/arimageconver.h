#ifndef ARIMAGECONVER_H
#define ARIMAGECONVER_H

#include <QtWidgets/QMainWindow>
#include "ui_arimageconver.h"
#include "imagewidgt.h"

class ARImageConver : public QMainWindow
{
	Q_OBJECT

public:
	ARImageConver(QWidget *parent = 0);
	~ARImageConver();
private:
	Ui::ARImageConverClass ui;
	ImageWidgt			*m_SourceimageWidget;
	ImageWidgt			*m_DirimageWidget;
	QWidget				*m_TargetColorlabel;
	QLabel				*m_Rgblabel;
	QLabel				*m_Sliderlabel;
public slots:
	void				ChangemMouceColor(QColor color);
	void				sliderChange(int value);
	void				openFile();
	void				reset();
};

#endif // ARIMAGECONVER_H
