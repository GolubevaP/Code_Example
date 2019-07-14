#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAction>

namespace SCATTER
{

class Item;
namespace Frames {
class MainFrame;
}

class MathStatistic;
class ScatterEllipse;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // действия меню "файл":
    QAction *m_ActionOpenFile;
    QAction *m_ActionQuit;

    // действия меню "график":
    QAction *m_ActionAllPoints;
    QAction *m_ActionLegend;

	// действия для выбора значения надежности
    QActionGroup *m_ActionGroup;
    QAction *m_Action95;
    QAction *m_Action98;
    QAction *m_Action99;
    QAction *m_Action999;

    // действия меню "справка":
    QAction *m_ActionHelp;
    QAction *m_ActionAbout;
    QAction *m_ActionAboutQt;

private:
    bool point_type;    // режим вывода точек
                        // (все = 1 / без погрешностей = 0)
						
    qreal t_kr = 1.96;	// рассчетный коэффициент, зависит от надежности

    QString fileName;   // имя файла с координатами

    Item *m_Item;       // данные (из файла и рассчитанные)

    Frames::MainFrame *m_MainFrame; // главный фрейм

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() {}

signals:

    // показать/скрыть легенду графика
    void on_legend(bool on);

public slots:
    // открыть файл
    void on_open_file();

    // выбор режима вывода точек
    void on_all_points(bool on);

	// выбор надежности для рассчета данных
    void on_t_kr_95(bool);
    void on_t_kr_98(bool);
    void on_t_kr_99(bool);
    void on_t_kr_999(bool);

    // слоты для действий меню "справка":
    void on_help();
    void on_about();
    void on_about_qt();
};

} // namespace SCATTER

#endif // MAINWINDOW_H
