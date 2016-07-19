#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "ZoomInWindow.h"
#include "FrameView.h"
#include "Block.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    
    static QRect MakeRect(const QPoint& p1, const QPoint& p2);
    void UpdateZoomInWindow(const QPoint& curPos);
    void MoveBlocks();
    
signals:
    void finishCrop(const QPixmap& pixmap);

protected slots:
    void OnRegionHovered(int region);
    void OnRegionPressed(int region);
    void OnViewDblClicked();
    void DoScreenshot();

private:
    Ui::MainWidget *ui;
    ZoomInWindow* m_zoomInWindow;
	QPoint m_startPos;
    QRect m_oldViewGeo;
	FrameView* m_frameView;
    bool m_viewCreating;
    bool m_regionPressed;
    bool startCrop;
    int m_pressedRegion;
    Block* m_blocks[8];
};

#endif // MAINWIDGET_H
