#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChartView>
#include <QPointF>

namespace SCATTER
{

class MathStatistic;
class ScatterEllipse;

QT_CHARTS_USE_NAMESPACE

class Chart : public QChartView
{
    Q_OBJECT

private:
    QPointF Center;

    QList<QPointF> Points;
    QList<QPointF> Extras;

    QList<QPointF> EllipseSigma;
    QList<QPointF> EllipseSigma3;

    QList<QPointF> Romb;
    QList<QPointF> MinMax;

    QList<QPointF> AxisA;
    QList<QPointF> AxisB;

    bool ellipse = 0;

public:
    Chart(QWidget *parent = nullptr);
    virtual ~Chart() {}

private:
    void calcAxis();
    void setAxis();
    void getEdges(const QList<QPointF> &values);

public:
    void getData(const MathStatistic &math, const ScatterEllipse &ellipse, const ScatterEllipse &ellipse_3);

    void Plot();

    void change_ellipse(bool ellipse);

    bool ellipseType() { return ellipse; }
};

} // namespace SCATTER

#endif // CHART_H
