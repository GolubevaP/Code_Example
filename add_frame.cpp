#include "add_frame.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

namespace SCATTER
{
namespace Frames
{

AddFrame::AddFrame(QWidget *parent)
        : QFrame (parent)
{
    QGridLayout *layout = new QGridLayout(this);

	// подписи размерностей
    QLabel *xm_title = new QLabel(this);
    xm_title->setText(tr("m,"));
    QLabel *zm_title = new QLabel(this);
    zm_title->setText(tr("m"));

	// подпись полуосей эллипса
    QLabel *e_title = new QLabel(this);
    e_title->setText(tr("Semiaxis:"));
    e_title->setSizePolicy(QSizePolicy::Fixed,
                           QSizePolicy::Fixed);
    layout->addWidget(e_title, 0, 0, 1, 1, Qt::AlignLeft);

	// окна вывода полуосей эллипса
    m_Ee = new QLineEdit(this);
    m_Ee->setSizePolicy(QSizePolicy::Fixed,
                        QSizePolicy::Fixed);
    m_Ee->setMaxLength(5);
    layout->addWidget(m_Ee, 0, 1, 1, 1);
    layout->addWidget(xm_title, 0, 2, 1, 1, Qt::AlignLeft);

    m_En = new QLineEdit(this);
    m_En->setSizePolicy(QSizePolicy::Fixed,
                        QSizePolicy::Fixed);
    m_En->setMaxLength(5);
    layout->addWidget(m_En, 0, 3, 1, 1);
    layout->addWidget(zm_title, 0, 4, 1, 1, Qt::AlignLeft);


	// подписи размерностей
    QLabel *sm_title = new QLabel(this);
    sm_title->setText(tr("m^2,"));
    QLabel *sg_title = new QLabel(this);
    sg_title->setText(tr("ga"));

	// полдпись площади эллипса
    QLabel *s_title = new QLabel(this);
    s_title->setText(tr("Ellipse area:"));
    s_title->setSizePolicy(QSizePolicy::Fixed,
                           QSizePolicy::Fixed);
    layout->addWidget(s_title, 1, 0, 1, 1, Qt::AlignRight);

	// окна вывода площади эллипса
    m_Sm = new QLineEdit(this);
    m_Sm->setSizePolicy(QSizePolicy::Fixed,
                        QSizePolicy::Fixed);
    m_Sm->setMaxLength(10);
    layout->addWidget(m_Sm, 1, 1, 1, 1);
    layout->addWidget(sm_title, 1, 2, 1, 1, Qt::AlignLeft);

    m_Sg = new QLineEdit(this);
    m_Sg->setSizePolicy(QSizePolicy::Fixed,
                        QSizePolicy::Fixed);
    m_Sg->setMaxLength(5);
    layout->addWidget(m_Sg, 1, 3, 1, 1);
    layout->addWidget(sg_title, 1, 4, 1, 1, Qt::AlignLeft);


	// кнопка смены эллипса
    m_ChangeEllipse = new QPushButton(tr("Change Ellipse"), this);
    layout->addWidget(m_ChangeEllipse, 0, 6, 1, 1);
    m_ChangeEllipse->setSizePolicy(QSizePolicy::Fixed,
                                   QSizePolicy::Fixed);
    m_ChangeEllipse->setCheckable(true);
    m_ChangeEllipse->setChecked(false);

    connect(m_ChangeEllipse, SIGNAL(toggled(bool)),
            this,            SIGNAL(on_change_ellipse(bool)));

    this->setLayout(layout);

}

void AddFrame::setEe(const QString &value)
{
    m_Ee->setText(value.simplified());
}

void AddFrame::setEn(const QString &value)
{
    m_En->setText(value.simplified());
}

void AddFrame::setSm(const QString &value)
{
    m_Sm->setText(value.simplified());
}

void AddFrame::setSg(const QString &value)
{
    m_Sg->setText(value.simplified());
}

bool AddFrame::change_ellipse()
{
    bool result = m_ChangeEllipse->isChecked();
    return result;
}

} // namespace Frames
} // naemspace SCATTER
