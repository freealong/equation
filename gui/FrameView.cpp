#include "FrameView.h"
#include <QPainter>
#include <QDebug>
#include "ScreenshotService.h"

FrameView::FrameView(QWidget *parent)
	: QWidget(parent)
{
    m_padding = 4;
    setMouseTracking(true);
}

FrameView::~FrameView()
{

}

void FrameView::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), ScreenshotService::Instance()->GetScreenshotPixmap(), geometry());

	QWidget::paintEvent(event);
}

void FrameView::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::NoButton)
    {
        int region = HitTest(event->pos());
        if (region != -1)
            emit RegionHoverd(region);
    }

    QWidget::mouseMoveEvent(event);
}

void FrameView::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int region = HitTest(event->pos());
        if (region != -1)
            emit RegionPressed(region);
    }

	QWidget::mousePressEvent(event);
}

void FrameView::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);
}

void FrameView::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit ViewDblClicked();
    QWidget::mouseDoubleClickEvent(event);
}

void FrameView::leaveEvent(QEvent* event)
{
    emit RegionHoverd(-1);
}

void FrameView::CutIn9Parts()
{
    int width = this->width();
    int height = this->height();
    
    m_rectParts[CropRegion::Top]          = QRect(m_padding, 0, width - 2 * m_padding, m_padding);
    m_rectParts[CropRegion::TopRight]     = QRect(width - m_padding, 0, m_padding, m_padding);
    m_rectParts[CropRegion::Right]        = QRect(width - m_padding, m_padding, m_padding, height - 2 * m_padding);
    m_rectParts[CropRegion::RightBottom]  = QRect(width - m_padding, height - m_padding, m_padding, m_padding);
    m_rectParts[CropRegion::Bottom]       = QRect(m_padding, height - m_padding, width - 2 * m_padding, m_padding);
    m_rectParts[CropRegion::LeftBottom]   = QRect(0, height - m_padding, m_padding, m_padding);
    m_rectParts[CropRegion::Left]         = QRect(0, m_padding, m_padding, height - 2 * m_padding);
    m_rectParts[CropRegion::LeftTop]      = QRect(0, 0, m_padding, m_padding);
    m_rectParts[CropRegion::Inner]        = QRect(m_padding, m_padding, width - 2 * m_padding, height - 2 * m_padding);
}

int FrameView::HitTest(const QPoint& pos)
{
    for (int i = 0; i < 9; i++)
    {
        if (m_rectParts[i].contains(pos))
            return i;
    }
    
    return -1;
}

