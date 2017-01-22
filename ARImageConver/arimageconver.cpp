#include "arimageconver.h"
#include <QtWidgets>

ARImageConver::ARImageConver(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_SourceimageWidget = new ImageWidgt("", this);
	m_DirimageWidget = new ImageWidgt("", this, true);
	m_SourceimageWidget->setFixedSize(50, 50);
	m_DirimageWidget->setFixedSize(50, 50);
	connect(m_DirimageWidget, &ImageWidgt::colorChange, this, &ARImageConver::ChangemMouceColor);
	QHBoxLayout *Layout = new QHBoxLayout();
	Layout->setSpacing(0);
	ui.centralWidget->setLayout(Layout);

	QLabel *label = new QLabel("Original image", this);
	QVBoxLayout *sourceLayout = new QVBoxLayout;
	sourceLayout->setSpacing(0);
	sourceLayout->addWidget(label);
	sourceLayout->addWidget(m_SourceimageWidget);

	QLabel *Targetlabel = new QLabel("Target image", this);
	m_Rgblabel = new QLabel("rgb", this);
	m_Sliderlabel = new QLabel("value", this);
	QSlider *slider = new QSlider(Qt::Horizontal, this);
	slider->setTickInterval(1);
	slider->setFixedWidth(100);
	slider->setMaximum(100);
	connect(slider, &QSlider::sliderMoved, this, &ARImageConver::sliderChange);
	QPushButton *resetBtn = new QPushButton("reset", this);
	connect(resetBtn, &QPushButton::clicked, this, &ARImageConver::reset);
	m_TargetColorlabel  = new QWidget(this);
	m_TargetColorlabel->setAutoFillBackground(true);
	m_TargetColorlabel->setFixedSize(50, 20);
	QVBoxLayout *TargetLayout = new QVBoxLayout;
	TargetLayout->setSpacing(0);
	TargetLayout->addWidget(Targetlabel);
	TargetLayout->addWidget(m_DirimageWidget);
	TargetLayout->addWidget(m_TargetColorlabel);
	TargetLayout->addWidget(m_Rgblabel);
	TargetLayout->addWidget(slider);
	TargetLayout->addWidget(m_Sliderlabel);
	TargetLayout->addWidget(resetBtn);
	
	Layout->addLayout(sourceLayout);
	Layout->addLayout(TargetLayout);

	connect(ui.actionImage, &QAction::triggered, this, &ARImageConver::openFile);
}

ARImageConver::~ARImageConver()
{

}

void ARImageConver::openFile()
{
	QString imagePath = QFileDialog::getOpenFileName(this, tr("Select image."),
		"/", tr("Images (*.png *.bmp *.jpg)"));
	if (!imagePath.isEmpty())
	{
		m_SourceimageWidget->SetImage(imagePath);
		m_DirimageWidget->SetImage(imagePath);
	}
}

void ARImageConver::ChangemMouceColor(QColor color)
{
	int r, g, b;
	color.getRgb(&r, &g, &b);
	QPalette paltter;
	paltter.setColor(QPalette::Background, color);
	m_TargetColorlabel->setPalette(paltter);
	m_Rgblabel->setText(QString("rgb:%1,%2,%3").arg(r).arg(g).arg(b));
}

void ARImageConver::reset()
{
	m_DirimageWidget->resetImage();
}

void ARImageConver::sliderChange(int value)
{
	m_DirimageWidget->setToleranceValue(value);
	m_Sliderlabel->setText(QString("tolerate:%1").arg(value));
}