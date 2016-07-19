#ifndef ZOOMINWINDOW_H
#define ZOOMINWINDOW_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class ZoomInWindow;
}

class ZoomInWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ZoomInWindow(QWidget *parent = 0);
    ~ZoomInWindow();

    void Focus(const QPoint& point);
    void Update();
    void PaintZoomInWidget();

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event);
    
private:
    Ui::ZoomInWindow *ui;
    QPoint m_point;
    int m_scale;
    QSize m_grabSize;
};

#endif // ZOOMINWINDOW_H
