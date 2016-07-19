#ifndef SCREENSHOTSERVICE_H
#define SCREENSHOTSERVICE_H

#include <QPixmap>
#include <QImage>

class ScreenshotService
{
private:
    ScreenshotService();
    ScreenshotService(const ScreenshotService&);
    ScreenshotService& operator =(const ScreenshotService&);

public:
    ~ScreenshotService();
    static ScreenshotService* Instance();
    void Screenshot();
    
    QRect GetScreenRect();
    const QPixmap& GetScreenshotPixmap();
    const QImage& GetScreenshotImage();
	const QPixmap& GetDarkPixmap();

protected:
    static ScreenshotService* m_instance;
    QPixmap m_screenshot;
    QImage m_image;
	QPixmap m_darkPixmap;
    QRect m_screenRect;

};

#endif // SCREENSHOTSERVICE_H
