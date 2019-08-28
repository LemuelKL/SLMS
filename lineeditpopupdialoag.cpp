#include "lineeditpopupdialoag.h"
#include "ui_lineeditpopupdialoag.h"

LineEditPopupDialog::LineEditPopupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineEditPopupDialog)
{
    ui->setupUi(this);
    this->setWhatsThis("Enter your input here. Press ENTER to submit. This window would be automatically closed.");
    ui->lineEdit->setFocus();
}

LineEditPopupDialog::~LineEditPopupDialog()
{
    delete ui;
}

void LineEditPopupDialog::on_buttonBox_accepted()
{
    emit ValueSubmitted(ui->lineEdit->text());
    this->hide();
}
