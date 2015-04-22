#ifndef AUTOMATFORM_H
#define AUTOMATFORM_H

#include <QWidget>
#include <QSignalMapper>

namespace Ui {
class AutomatForm;
}

class AutomatForm : public QWidget
{
    Q_OBJECT

public:
    //explicit AutomatForm(QWidget *parent = 0);
    ~AutomatForm();

    static AutomatForm* getAutomatForm();

private slots:
    void goto_main(QString msn);

private:
    explicit AutomatForm(QWidget *parent = 0);
    Ui::AutomatForm *ui;

    QSignalMapper back_to;
};

#endif // AUTOMATFORM_H