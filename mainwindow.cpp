#include "mainwindow.h"

#include "application.h"

#include "main_frame.h"
#include "item.h"

#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QActionGroup>

namespace SCATTER
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // меню "Файл":
    m_ActionOpenFile = new QAction(this);
    m_ActionOpenFile->setText(tr("Open File"));
    m_ActionOpenFile->setShortcut(Qt::CTRL + Qt::Key_O);
    m_ActionQuit = new QAction(this);
    m_ActionQuit->setText(tr("Quit"));
    m_ActionQuit->setShortcut(Qt::CTRL + Qt::Key_Q);

    QMenu *menu_file = new QMenu(this);
    menu_file->setTitle(tr("File"));
    menuBar()->addMenu(menu_file);
    menu_file->addAction(m_ActionOpenFile);
    menu_file->addSeparator();
    menu_file->addAction(m_ActionQuit);

    // меню "График":
    m_ActionAllPoints = new QAction(this);
    m_ActionAllPoints->setText(tr("All Points"));
    m_ActionAllPoints->setCheckable(true);
    m_ActionAllPoints->setChecked(true);

	// элемент меню для задания знаяения расчетного коэффициента 
	// в зависимости от выбранной надежности Р
    m_ActionGroup = new QActionGroup(this);
    m_Action95 = new QAction(this);
    m_Action95->setText(tr("P = 0,95"));
    m_Action95->setCheckable(true);
    m_Action98 = new QAction(this);
    m_Action98->setText(tr("P = 0,98"));
    m_Action98->setCheckable(true);
    m_Action99 = new QAction(this);
    m_Action99->setText(tr("P = 0,99"));
    m_Action99->setCheckable(true);
    m_Action999 = new QAction(this);
    m_Action999->setText(tr("P = 0,999"));
    m_Action999->setCheckable(true);

    m_ActionGroup->addAction(m_Action95);
    m_ActionGroup->addAction(m_Action98);
    m_ActionGroup->addAction(m_Action99);
    m_ActionGroup->addAction(m_Action999);
    m_ActionGroup->setExclusive(true);
    m_Action95->setChecked(true);

    m_ActionLegend = new QAction(this);
    m_ActionLegend->setText(tr("Legend"));
    m_ActionLegend->setCheckable(true);
    m_ActionLegend->setChecked(false);

    QMenu *menu_chart = new QMenu(this);
    menu_chart->setTitle(tr("Chart"));
    menuBar()->addMenu(menu_chart);
    menu_chart->addAction(m_ActionAllPoints);
    QMenu *menu_tkr = new QMenu(this);
    menu_tkr->setTitle(tr("Reliability"));
    menu_chart->addMenu(menu_tkr);
    menu_tkr->addAction(m_Action95);
    menu_tkr->addAction(m_Action98);
    menu_tkr->addAction(m_Action99);
    menu_tkr->addAction(m_Action999);
    m_ActionGroup->setDisabled(true);
    menu_chart->addSeparator();
    menu_chart->addAction(m_ActionLegend);


    // меню "Справка":
    m_ActionHelp = new QAction(this);
    m_ActionHelp->setText(tr("Help"));
    m_ActionHelp->setShortcut(Qt::Key_F1);
    m_ActionAbout = new QAction(this);
    m_ActionAbout->setText(tr("About..."));
    m_ActionAboutQt = new QAction(this);
    m_ActionAboutQt->setText(tr("About Qt..."));

    QMenu *menu_help = new QMenu(this);
    menu_help->setTitle(tr("Help"));
    menuBar()->addMenu(menu_help);
    menu_help->addAction(m_ActionHelp);
    menu_help->addAction(m_ActionAbout);
    menu_help->addAction(m_ActionAboutQt);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
    connect(m_ActionOpenFile,  SIGNAL(triggered()),
            this,              SLOT(on_open_file()));
    connect(m_ActionQuit,      SIGNAL(triggered()),
            this,              SLOT(close()));
    connect(m_ActionAllPoints, SIGNAL(toggled(bool)),
            this,              SLOT(on_all_points(bool)));

    connect(m_Action95,        SIGNAL(toggled(bool)),
            this,              SLOT(on_t_kr_95(bool)));
    connect(m_Action98,        SIGNAL(toggled(bool)),
            this,              SLOT(on_t_kr_98(bool)));
    connect(m_Action99,        SIGNAL(toggled(bool)),
            this,              SLOT(on_t_kr_99(bool)));
    connect(m_Action999,       SIGNAL(toggled(bool)),
            this,              SLOT(on_t_kr_999(bool)));

    connect(m_ActionLegend,    SIGNAL(toggled(bool)),
             this,             SIGNAL(on_legend(bool)));
    connect(m_ActionHelp,      SIGNAL(triggered()),
            this,              SLOT(on_help()));
    connect(m_ActionAbout,     SIGNAL(triggered()),
            this,              SLOT(on_about()));
    connect(m_ActionAboutQt,   SIGNAL(triggered()),
            this,              SLOT(on_about_qt()));

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    point_type = true;

	// объект с данными
    m_Item = new Item(this);

	// главный фрейм (содержит окна вывода данных и график)
    m_MainFrame = new Frames::MainFrame(this);
    this->setCentralWidget(m_MainFrame);

    connect(m_Item,      &Item::update_chart,
            m_MainFrame, &Frames::MainFrame::update_chart);

    connect(this,        &MainWindow::on_legend,
            m_MainFrame, &Frames::MainFrame::on_legend);

    connect(m_MainFrame, &Frames::MainFrame::on_change_ellipse,
            m_Item,      &Item::on_change_ellipse);
    connect(m_Item,      &Item::update_ellipse,
            m_MainFrame, &Frames::MainFrame::update_ellipse);
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void MainWindow::on_open_file()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"),
                                            nullptr,
                                            tr("Text files (*.txt)"));
    qDebug() << fileName;

	// сичтываем данные из файла и обрабатываем их 
	// в соответствии с параметрами point_type и t_kr
    m_Item->setData(fileName, point_type, t_kr);
}


void MainWindow::on_all_points(bool on)
{
	// если пункт "Все точки" включен, выбор "Надежности" заблокирован
    if (on)
    {
        m_ActionGroup->setDisabled(true);
    }
    else
    {
        m_ActionGroup->setDisabled(false);
    }

	// обновляем рассчетные данные в соответствии с новыми параметрами
    point_type = on;
    m_Item->update_data(point_type, t_kr);
}

// задаем расчетный коэффициент для надежности 0,95
void MainWindow::on_t_kr_95(bool on)
{
    if (on)
    {
        t_kr = 1.96;
        m_Item->update_data(point_type, t_kr);

    }
}

// задаем расчетный коэффициент для надежности 0,98
void MainWindow::on_t_kr_98(bool on)
{
    if (on)
    {
        t_kr = 2.326;
        m_Item->update_data(point_type, t_kr);
    }
}

// задаем расчетный коэффициент для надежности 0,99
void MainWindow::on_t_kr_99(bool on)
{
    if (on)
    {
        t_kr = 2.576;
        m_Item->update_data(point_type, t_kr);
    }
}

// задаем расчетный коэффициент для надежности 0,999
void MainWindow::on_t_kr_999(bool on)
{
    if (on)
    {
        t_kr = 3.291;
        m_Item->update_data(point_type, t_kr);
    }
}


void MainWindow::on_help()
{
    QString title = tr("Help for ") + APP->applicationDisplayName();
    QString text = tr("Help for this program");
    QMessageBox::about(this, title, text);
}

void MainWindow::on_about()
{
    QString title = tr("About ") + APP->applicationDisplayName();
    QString text = tr("This program is designed to calculate\n"
                      " the probable dispersion parameters.");
    QMessageBox::about(this, title, text);
}

void MainWindow::on_about_qt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

} // namespace SCATTER
