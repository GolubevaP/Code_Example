#include "main_frame.h"

#include "genl_frame.h"
#include "add_frame.h"
#include "chart.h"

#include "mathstatistic.h"
#include "scatterellipse.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QtMath>

namespace SCATTER
{
namespace Frames
{

MainFrame::MainFrame(QWidget *parent)
    : QFrame(parent)
{
    setStyleSheet("background: #FFDEAD");

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    QHBoxLayout *layout = new QHBoxLayout();
    // на горизонтальной разметке располагаем фреймы:

    m_GenlFrame = new GenlFrame(this);
    layout->addWidget(m_GenlFrame);

    m_AddFrame = new AddFrame(this);
    layout->addWidget(m_AddFrame);

    layout->addStretch();

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    m_Chart = new Chart(this);
    m_Chart->setSizePolicy(QSizePolicy::Expanding,
                           QSizePolicy::Expanding);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    QVBoxLayout *main = new QVBoxLayout(this);
    // на вертикальной разметке располагаем фреймы и график
    main->addLayout(layout);
    main->addWidget(m_Chart);

    connect(m_AddFrame, SIGNAL(on_change_ellipse(bool)),
            this,       SIGNAL(on_change_ellipse(bool)));

}

void MainFrame::setEllipse(ScatterEllipse &ellipse)
{
    QVariant var;

    var.setValue(ellipse.SemiAxis().x());
    m_AddFrame->setEe(var.toString());
    var.setValue(ellipse.SemiAxis().y());
    m_AddFrame->setEn(var.toString());
    var.setValue(ellipse.Square());
    m_AddFrame->setSm(var.toString());
    var.setValue(ellipse.Square() / 10000);
    m_AddFrame->setSg(var.toString());
}

void MainFrame::setGenData(MathStatistic &math)
{
    QVariant var;
    
    var.setValue(math.MathExpect().x());
    m_GenlFrame->setXCoord(var.toString());
    var.setValue(math.MathExpect().y());
    m_GenlFrame->setZCoord(var.toString());
    var.setValue(math.Alpha() * 180 / 3.14);
    m_GenlFrame->setTitlAngle(var.toString());
    qreal slip = sqrt(math.MathExpect().x() * math.MathExpect().x() + math.MathExpect().y() * math.MathExpect().y());
    var.setValue(slip);
    m_GenlFrame->setSlip(var.toString());
}

void MainFrame::update_chart(MathStatistic &math, ScatterEllipse &ellipse, ScatterEllipse &ellipse_3)
{
    // обновляем данные для графика и перерисовываем его
    m_Chart->getData(math, ellipse, ellipse_3);

    m_Chart->Plot();

    setGenData(math);

    bool result = m_Chart->ellipseType();
    if (result)
        setEllipse(ellipse_3);
    else
        setEllipse(ellipse);
}

void MainFrame::update_ellipse(ScatterEllipse &ellipse)
{
    setEllipse(ellipse);

    bool result = m_AddFrame->change_ellipse();
    m_Chart->change_ellipse(result);
}

void MainFrame::on_legend(bool on)
{
    if (on)
        m_Chart->chart()->legend()->show();
    else
        m_Chart->chart()->legend()->hide();
}

} // namespace Frames
} // namespace SCATTER
