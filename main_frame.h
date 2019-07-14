#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <QFrame>

namespace SCATTER
{

class Chart;

class MathStatistic;
class ScatterEllipse;

namespace Frames
{

class GenlFrame;
class AddFrame;

class MainFrame : public QFrame
{
    Q_OBJECT

private:
    // данные для передачи во фреймы
    QObject *m_GenlData;
    QObject *m_AddData;

private:
    GenlFrame *m_GenlFrame; // фрейм для вывода основных данных
    AddFrame  *m_AddFrame;  // фрейм для вывода дополнительных данных
    Chart     *m_Chart;     // график

public:
    MainFrame(QWidget *parent = nullptr);
    virtual ~MainFrame() {}

private:
	// обновляем данные эллипса на фреме m_AddFrame
    void setEllipse(ScatterEllipse &ellipse);
	// обновляем основные данные на фрейме m_GenlFrame
    void setGenData(MathStatistic &math);

signals:
    void on_change_ellipse(bool ellipse);

public slots:
    // обновление графика
    void update_chart(MathStatistic &math, ScatterEllipse &ellipse, ScatterEllipse &ellipse_3);

    void update_ellipse(ScatterEllipse &ellipse);

    void on_legend(bool on);
};

} // namespace Frames
} // namespace SCATTER

#endif // MAIN_FRAME_H
