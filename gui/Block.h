#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

#include "CropRegion.h"

class Block : public QWidget
{
    Q_OBJECT
public:
    explicit Block(int region, QWidget *parent = 0);
    ~Block();
    
protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void leaveEvent(QEvent* event);
    
signals:
    void BlockHovered(int region);
    void BlockPressed(int region);
    
protected:
    int m_region;
};

#endif // BLOCK_H
