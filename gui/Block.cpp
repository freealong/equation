#include "Block.h"
#include <QPainter>

Block::Block(int region, QWidget *parent) : 
    QWidget(parent),
    m_region(region)
{
    setMouseTracking(true);
}

Block::~Block()
{
    
}

void Block::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 128));
}

void Block::mouseMoveEvent(QMouseEvent* event)
{
    emit BlockHovered(m_region);
    QWidget::mouseMoveEvent(event);
}

void Block::mousePressEvent(QMouseEvent* event)
{
    emit BlockPressed(m_region);
    QWidget::mousePressEvent(event);
}

void Block::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
}

void Block::leaveEvent(QEvent* event)
{
    emit BlockHovered(-1);
}

