#include "ScreenshotService.h"
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>

ScreenshotService* ScreenshotService::m_instance = 0;

ScreenshotService::ScreenshotService()
{
    QDesktopWidget* desktop = QApplication::desktop();
    m_screenRect = desktop->screenGeometry();
}

ScreenshotService::~ScreenshotService()
{
    if (m_instance)
    {
        delete m_instance;
    }
}

ScreenshotService* ScreenshotService::Instance()
{
    if (!m_instance)
    {
        m_instance = new ScreenshotService();
    }

    return m_instance;
}

void ScreenshotService::Screenshot()
{
    //QScreen *screen = QApplication::primaryScreen();
    //m_screenshot = screen->grabWindow(0);
    
    QDesktopWidget* desktop = QApplication::desktop();
    m_screenshot = QPixmap::grabWindow(desktop->winId());    
    
    m_image = m_screenshot.toImage();

	QImage image = m_image;
	int bytesPerLine = image.width() * image.depth() / 8;
	for (int i = 0; i < image.height(); i++)
	{
		uchar* lineBuf = image.scanLine(i);
		for (int j = 0; j < bytesPerLine; j++)
		{
			lineBuf[j] = lineBuf[j] * 1 / 2;
		}
	}
	m_darkPixmap = QPixmap::fromImage(image);
}

QRect ScreenshotService::GetScreenRect()
{
    return m_screenRect;
}

const QPixmap& ScreenshotService::GetScreenshotPixmap()
{
    return m_screenshot;
}

const QImage& ScreenshotService::GetScreenshotImage()
{
    return m_image;
}

const QPixmap& ScreenshotService::GetDarkPixmap()
{
	return m_darkPixmap;
}
