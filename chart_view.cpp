#include "chart.h"

#include "mathstatistic.h"
#include "scatterellipse.h"

#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QValueAxis>

namespace SCATTER
{

Chart::Chart(QWidget *parent)
    : QChartView (new QChart(), parent)
{
    chart()->legend()->hide();
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void Chart::setAxis()
{
    QValueAxis *axis_x = new QValueAxis();
    QValueAxis *axis_y = new QValueAxis();

    axis_x->setRange(MinMax.at(0).x(), MinMax.at(1).x());
    axis_x->setTickCount(11);
    axis_x->applyNiceNumbers();
    axis_x->setTitleText(tr("X, m"));

    qDebug() << "axis x" << axis_x->min() << axis_x->max();

    axis_y->setRange(MinMax.at(0).y(), MinMax.at(1).y());
    axis_y->setTickCount(11);
    axis_y->applyNiceNumbers();
    axis_y->setTitleText(tr("Z, m"));

    qDebug() << "axis y" << axis_y->min() << axis_y->max();

    chart()->addAxis(axis_y, Qt::AlignLeft);
    chart()->addAxis(axis_x, Qt::AlignBottom);
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void Chart::Plot()
{
    chart()->removeAllSeries();

    QAbstractAxis *axis_x = chart()->axisX();
    chart()->removeAxis(axis_x);
    QAbstractAxis *axis_y = chart()->axisY();
    chart()->removeAxis(axis_y);

    setAxis();

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ДАННЫЕ:

    // центр рассеивания
    QtCharts::QScatterSeries *center = new QtCharts::QScatterSeries();
    center->setName(tr("Center"));
    center->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
    center->setMarkerSize(10.0);
    center->setColor(QColor(255, 127, 0, 255));
    center->append(Center);
//    center->setPointLabelsVisible(true);

    // цель
    QtCharts::QScatterSeries *target = new QtCharts::QScatterSeries();
    target->setName(tr("Target"));
    target->append(0, 0);
    target->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeRectangle);
    target->setMarkerSize(12.0);
    target->setColor(QColor(Qt::darkRed));

    // точки
    QtCharts::QScatterSeries *points = new QtCharts::QScatterSeries();
    points->setName(tr("Points"));
    points->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
    points->setMarkerSize(7.0);
    points->setColor(QColor(0, 0, 255, 255));
    for (int i = 0; i < Points.size(); ++i)
    {
        points->append(Points.at(i));
    }

    // точки "ошибки"
    QtCharts::QScatterSeries *extra_points = new QtCharts::QScatterSeries();
    extra_points->setName(tr("extra Points"));
    extra_points->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
    extra_points->setMarkerSize(7.0);
    extra_points->setColor(QColor(Qt::red));
    for (int i = 0; i < Extras.size(); ++i)
    {
        extra_points->append(Extras.at(i));
    }


    QColor color1, color2;
    if (ellipse)
    {
        color2 = QColor(255 ,0, 0, 255);
        color1 = QColor(0, 255, 127, 255);
    }
    else
    {
        color1 = QColor(255 ,0, 0, 255);
        color2 = QColor(0, 255, 127, 255);
    }

    // единичный эллипс рассеивания
    QtCharts::QSplineSeries *series_el_s = new QtCharts::QSplineSeries();
    series_el_s->setName(tr("el sigma"));
    series_el_s->setColor(color1);
    for (int i=0; i<EllipseSigma.size(); ++i)
    {
        series_el_s->append(EllipseSigma.at(i));
    }

    // эллипс рассеивания 3 сигма
    QtCharts::QSplineSeries *series_el_s3 = new QtCharts::QSplineSeries();
    series_el_s3->setName(tr("el 3 sigma"));
    series_el_s3->setColor(color2);
    for (int i=0; i<EllipseSigma3.size(); ++i)
    {
        series_el_s3->append(EllipseSigma3.at(i));
    }

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ОСИ:

    QPen *axis_pen_a = new QPen();
    axis_pen_a->setStyle(Qt::DashLine);
    axis_pen_a->setColor(QColor(127, 0, 255, 255));

    // ось координат по оси эллипса Х
    QtCharts::QLineSeries *axisA = new QtCharts::QLineSeries();
    axisA->setName(tr("axis A"));
    axisA->setPen(*axis_pen_a);
    for (int i=0; i < AxisA.size(); ++i)
    {
        axisA->append(AxisA.at(i));
    }

    QPen *axis_pen_b = new QPen();
    axis_pen_b->setStyle(Qt::DashLine);
    axis_pen_b->setColor(QColor(255, 0, 255, 255));

    // ось координт по оси эллипса Y
    QtCharts::QLineSeries *axisB = new QtCharts::QLineSeries();
    axisB->setName(tr("axis B"));
    axisB->setPen(*axis_pen_b);
    for (int i=0; i < AxisB.size(); ++i)
    {
        axisB->append(AxisB.at(i));
    }


    QPen *axis_pen_main = new QPen();
    axis_pen_main->setColor(QColor(Qt::black));
    axis_pen_main->setWidth(2);

    // ось Х
    QtCharts::QLineSeries *axis_main_x = new QtCharts::QLineSeries();
    axis_main_x->setPen(*axis_pen_main);
    axis_main_x->append(MinMax.at(0).x()*2, 0);
    axis_main_x->append(MinMax.at(1).x()*2, 0);


    // ось Y
    QtCharts::QLineSeries *axis_main_y = new QtCharts::QLineSeries();
    axis_main_y->setPen(*axis_pen_main);
    axis_main_y->append(0, MinMax.at(0).y()*2);
    axis_main_y->append(0, MinMax.at(1).y()*2);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    setRenderHint(QPainter::Antialiasing);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    chart()->addSeries(axis_main_x);
    chart()->addSeries(axis_main_y);
    chart()->addSeries(axisA);
    chart()->addSeries(axisB);
    chart()->addSeries(extra_points);
    chart()->addSeries(points);
    chart()->addSeries(center);
    chart()->addSeries(target);
    chart()->addSeries(series_el_s);
    chart()->addSeries(series_el_s3);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    axis_x = chart()->axisX();
    axis_y = chart()->axisY();

    center->attachAxis(axis_x);
    center->attachAxis(axis_y);

    target->attachAxis(axis_x);
    target->attachAxis(axis_y);

    points->attachAxis(axis_x);
    points->attachAxis(axis_y);

    extra_points->attachAxis(axis_x);
    extra_points->attachAxis(axis_y);

    series_el_s->attachAxis(axis_x);
    series_el_s->attachAxis(axis_y);

    series_el_s3->attachAxis(axis_x);
    series_el_s3->attachAxis(axis_y);

    axisA->attachAxis(axis_x);
    axisA->attachAxis(axis_y);

    axisB->attachAxis(axis_x);
    axisB->attachAxis(axis_y);

    axis_main_x->attachAxis(axis_x);
    axis_main_x->attachAxis(axis_y);

    axis_main_y->attachAxis(axis_x);
    axis_main_y->attachAxis(axis_y);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    chart()->setTitle("Scatter Ellipses");
    chart()->setDropShadowEnabled(false);
}

void Chart::change_ellipse(bool value)
{
    ellipse  = value;

    QList<QAbstractSeries *> list;
    list << chart()->series();

    chart()->removeSeries(list.at(9));
    chart()->removeSeries(list.at(8));

    QColor color1, color2;
    if (ellipse)
    {
        color2 = QColor(255 ,0, 0, 255);
        color1 = QColor(0, 255, 127, 255);
    }
    else
    {
        color1 = QColor(255 ,0, 0, 255);
        color2 = QColor(0, 255, 127, 255);
    }
    // единичный эллипс рассеивания
    QtCharts::QSplineSeries *series_el_s = new QtCharts::QSplineSeries();
    series_el_s->setName(tr("el sigma"));
    series_el_s->setColor(color1);
    for (int i=0; i<EllipseSigma.size(); ++i)
    {
        series_el_s->append(EllipseSigma.at(i));
    }

    // эллипс рассеивания 3 сигма
    QtCharts::QSplineSeries *series_el_s3 = new QtCharts::QSplineSeries();
    series_el_s3->setName(tr("el 3 sigma"));
    series_el_s3->setColor(color2);
    for (int i=0; i<EllipseSigma3.size(); ++i)
    {
        series_el_s3->append(EllipseSigma3.at(i));
    }

    chart()->addSeries(series_el_s);
    chart()->addSeries(series_el_s3);

    QAbstractAxis *axis_x = chart()->axisX();
    QAbstractAxis *axis_y = chart()->axisY();

    series_el_s->attachAxis(axis_x);
    series_el_s->attachAxis(axis_y);

    series_el_s3->attachAxis(axis_x);
    series_el_s3->attachAxis(axis_y);
}
