#ifndef ADD_FRAME_H
#define ADD_FRAME_H

#include <QFrame>

class QLineEdit;
class QPushButton;

namespace SCATTER
{
namespace Frames
{

class AddFrame : public QFrame
{
    Q_OBJECT

private:
    QLineEdit *m_Ee; // полуось по оси элиипса Х
    QLineEdit *m_En; // полуось по оси эллипса Y
    QLineEdit *m_Sm; // площадь эллипса в м
    QLineEdit *m_Sg; // площадь эллипа в гектарах

    QPushButton *m_ChangeEllipse;

public:
    AddFrame(QWidget *parent = nullptr);
    virtual ~AddFrame() {}

    // функции считывания и задания данных во фрейме:

    void setEe(const QString &value);
    void setEn(const QString &value);
    void setSm(const QString &value);
    void setSg(const QString &value);

    bool change_ellipse();


signals:
	// сигнал "сменить эллипс"
    void on_change_ellipse(bool checked);
};

} // namespace Frames
} // namespace SCATTER

#endif // ADD_FRAME_H
