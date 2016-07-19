#include "gui.h"
#include "ui_gui.h"
#include "MainWidget.h"

gui::gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui)
{
    ui->setupUi(this);
    m_hiddenMonitor = new QTimer(this);
    m_hiddenMonitor->setInterval(50);

    QObject::connect(m_hiddenMonitor, SIGNAL(timeout()), this, SLOT(OnHiddenMonitorTimeout()));
    QObject::connect(ui->cropImageButton, SIGNAL(clicked()), this, SLOT(cropImage()));
    QObject::connect(ui->processButton, SIGNAL(clicked()), this, SLOT(process()));
}

void gui::closeEvent(QCloseEvent* event)
{
	QApplication::quit();
}

void gui::OnHiddenMonitorTimeout()
{
	if (!isVisible())
	{
		m_hiddenMonitor->stop();
		emit beginScreenshot();
	}
}

void gui::finishScreenshot(const QPixmap& pixmap)
{
	ui->label->setPixmap(pixmap);
	show();
}

void gui::cropImage()
{
	hide();
	m_hiddenMonitor->start();
}

void gui::process()
{
    ui->latexText->setPlainText(QString("test"));
}

gui::~gui()
{
	delete m_hiddenMonitor;
    delete ui;
}

