#include "imagewidgt.h"

ImageWidgt::ImageWidgt(const QString &imagefile, QWidget *parent, bool CanCover)
	: QWidget(parent), m_ImageFile(imagefile), m_tempImage("tempImage.jpg"), m_CanConver(CanCover), m_value(0)
{
	m_PixColor = QColor(0, 0, 0);
	QImage image(m_ImageFile);
	bool sucess = image.save(m_tempImage);

	QImage Tempimage(m_tempImage);
	this->setFixedSize(Tempimage.width(), Tempimage.height());
	setMouseTracking(true);
}

void ImageWidgt::SetImage(const QString &imagefile)
{
	m_ImageFile = imagefile;
	QImage image(m_ImageFile);
	bool sucess = image.save(m_tempImage);
	this->setFixedSize(image.width(), image.height());
}

ImageWidgt::~ImageWidgt()
{
	QDir dir;
	dir.remove(m_tempImage);
}

void ImageWidgt::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_CanConver)
	{
		return;
	}
	QPoint po = event->pos();
	QImage image(m_tempImage);
	m_PixColor = image.pixelColor(event->pos());
	emit colorChange(m_PixColor);
}

void ImageWidgt::mouseReleaseEvent(QMouseEvent *event)
{
	int sr, sb, sg;
	m_PixColor.getRgb(&sr, &sg, &sb);
	if (m_CanConver)
	{
		QImage image(m_tempImage);
		for (int x = 0; x < image.width(); x++)
		{
			for (int y = 0; y < image.height(); y++)
			{
				int dr, db, dg;
				QColor pixColor = image.pixelColor(x, y);
				pixColor.getRgb(&dr, &dg, &db);
				if (dr > sr - m_value && dr < sr + m_value && dg > sg - m_value && dg < sg + m_value && db > sb - m_value && db < sb + m_value)
				{
					CorrdPair pair;
					pair.x = x;
					pair.y = y;
					m_Bemodified.append(pair);
					continue;
				}
				else
				{
					m_replaceColor = pixColor;
				}
				if (m_Bemodified.size() > 0)
				{
					for (auto item : m_Bemodified)
					{
						image.setPixelColor(item.x, item.y, m_replaceColor);
					}
					m_Bemodified.clear();
				}
			}
		}
		image.save(m_tempImage);
	}
}

QColor ImageWidgt::GetCurrentPosColor()
{
	return m_PixColor;
}

void ImageWidgt::resetImage()
{
	QDir dir;
	dir.remove(m_tempImage);
	QFile file(m_ImageFile);
	file.copy(m_tempImage);
	update();
}

void ImageWidgt::paintEvent(QPaintEvent *event)
{
	QPainter panter(this);
	QString imagestr;
	if (m_CanConver)
	{
		imagestr = m_tempImage;
	}
	else
	{
		imagestr = m_ImageFile;
	}
	QImage image(imagestr);
	panter.drawImage(0, 0, image);
}