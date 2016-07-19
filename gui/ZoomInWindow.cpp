#include "ZoomInWindow.h"
#include "ui_ZoomInWindow.h"
#include <QPainter>
#include "ScreenshotService.h"
#include <QDebug>

ZoomInWindow::ZoomInWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomInWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);

    ui->m_zoomInWidget->installEventFilter(this);
    ui->m_zoomInWidget->setMouseTracking(true);
    
    m_scale = 5;
    m_grabSize = QSize(33, 23);
    ui->m_zoomInWidget->setFixedSize(m_grabSize * m_scale);
}

ZoomInWindow::~ZoomInWindow()
{
    delete ui;
}

bool ZoomInWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->m_zoomInWidget && event->type() == QEvent::Paint)
    {
        PaintZoomInWidget();
    }

    return QWidget::eventFilter(watched, event);
}

void ZoomInWindow::Focus(const QPoint& point)
{
    m_point = point;
}

void ZoomInWindow::Update()
{
    ui->m_zoomInWidget->repaint();
    
    const QImage& image = ScreenshotService::Instance()->GetScreenshotImage();
    QRgb rgb = image.pixel(m_point);
    int red = qRed(rgb);
    int green = qGreen(rgb);
    int blue = qBlue(rgb);
    
    ui->m_pos->setText(tr("position: (%1, %2)").arg(m_point.x()).arg(m_point.y()));
    ui->m_color->setText(tr("color: (%1, %2, %3)").arg(red).arg(green).arg(blue));
    /*
    ui->m_color->setText(tr("color: (%1, %2, %3)")
                         .arg(red, 2, 16, QLatin1Char('0'))
                         .arg(green, 2, 16, QLatin1Char('0'))
                         .arg(blue, 2, 16, QLatin1Char('0')));*/
}

void ZoomInWindow::PaintZoomInWidget()
{
    QPainter painter(ui->m_zoomInWidget);
    painter.fillRect(rect(), Qt::black);
    
    const QPixmap& pixmap = ScreenshotService::Instance()->GetScreenshotPixmap();

    QRect grabRect(m_point, m_grabSize);
    grabRect.translate(-m_grabSize.width() / 2, -m_grabSize.height() / 2);
    painter.drawPixmap(ui->m_zoomInWidget->rect(), pixmap, grabRect);
    
    QPen crossPen(QColor(255, 0, 0));
    crossPen.setWidth(m_scale);
    painter.setPen(crossPen);
    
    QPoint center(ui->m_zoomInWidget->rect().center());
    painter.drawLine(center - QPoint(30, 0), center - QPoint(m_scale, 0));
    painter.drawLine(center + QPoint(m_scale, 0), center + QPoint(30, 0));
    painter.drawLine(center - QPoint(0, 30), center - QPoint(0, m_scale));
    painter.drawLine(center + QPoint(0, m_scale), center + QPoint(0, 30));
}
