#ifndef IMAGEWIDGT_H
#define IMAGEWIDGT_H

#include <QtWidgets>

class ImageWidgt : public QWidget
{
	Q_OBJECT
	struct  CorrdPair
	{
		int x;
		int y;
	};
public:
	ImageWidgt(const QString &imagefile, QWidget *parent = nullptr, bool CanCover = false);
	~ImageWidgt();
	QColor			GetCurrentPosColor();
	void			SetImage(const QString &imagefile);
	void			setToleranceValue(int value) {
		m_value = value;
	};
	void			resetImage();
private:
	const QString	m_tempImage;
	QString			 m_ImageFile;
	QColor			m_PixColor;
	bool			m_CanConver;
	QVector<CorrdPair>	m_Bemodified;
	QColor			m_replaceColor;
	int				m_value;
signals:
	void			colorChange(QColor color);
	void			MouseClick();
protected:
	virtual void	paintEvent(QPaintEvent *event);
	virtual void	mouseMoveEvent(QMouseEvent *event);
	virtual void	mouseReleaseEvent(QMouseEvent *event);
};

#endif // IMAGEWIDGT_H
