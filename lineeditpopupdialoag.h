#ifndef LINEEDITPOPUPDIALOG_H
#define LINEEDITPOPUPDIALOG_H

#include <QDialog>

namespace Ui {
class LineEditPopupDialog;
}

class LineEditPopupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineEditPopupDialog(QWidget *parent = nullptr);
    ~LineEditPopupDialog();

signals:
    void ValueSubmitted(const QString&);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::LineEditPopupDialog *ui;
};

#endif // LINEEDITPOPUPDIALOG_H
