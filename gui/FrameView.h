#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include "CropRegion.h"

class FrameView : public QWidget
{
	Q_OBJECT

public:
	FrameView(QWidget *parent);
	~FrameView();
    
	void CutIn9Parts();
    
protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void leaveEvent(QEvent* event);

    int HitTest(const QPoint& pos);
    
signals:
    void RegionHoverd(int region);
    void RegionPressed(int region);
    void ViewDblClicked();

private:
	QPixmap m_pixmap;
	QRect m_rectParts[9];
    int m_padding;
};

#endif // FRAMEVIEW_H
