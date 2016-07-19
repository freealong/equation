#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>

namespace Ui {
class gui;
}

class gui: public QMainWindow {
Q_OBJECT

public:
	explicit gui(QWidget *parent = 0);
	~gui();

protected:
    virtual void closeEvent(QCloseEvent* event);

signals:
	void beginScreenshot();

protected slots:
	void OnHiddenMonitorTimeout();
	void finishScreenshot(const QPixmap& pixmap);
	void cropImage();
	void process();

protected:
	QTimer* m_hiddenMonitor;

private:
	Ui::gui *ui;
};

#endif // GUI_H
