#include "addbookrecorddialog.h"
#include "ui_addbookrecorddialog.h"

#include <category.h>
#include <status.h>
#include <isbn13validator.h>

AddBookRecordDialog::AddBookRecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookRecordDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Add Book Record");

    ui->lineEdit_isbn13->setText("");
    ui->lineEdit_title->setText("");
    ui->lineEdit_author->setText("");

    for (int i = 0; i < Category::count_; i++)
    {
        ui->comboBox_category->addItem(Category::EnumToString(i));
    }
    for (int i = 0; i < Status::count_; i++)
    {
        ui->comboBox_status->addItem(Status::EnumToString(i));
    }

    ui->comboBox_category->setCurrentIndex(0);
    ui->comboBox_status->setCurrentIndex(0);

    ui->spinBox_amount->setValue(1);
    ui->spinBox_amount->setRange(1, 1000);

    ui->lineEdit_isbn13->setMaxLength(13);

    QValidator *validator = new Isbn13Validator(this);
    connect(validator, SIGNAL(InvalidIsbn13()), this, SLOT(HandleInvalidIsbn13()));
    connect(validator, SIGNAL(IntermediateIsbn13()), this, SLOT(HandleIntermidateIsbn13()));
    connect(validator, SIGNAL(ValidIsbn13()), this, SLOT(HandleValidIsbn13()));
    ui->lineEdit_isbn13->setValidator(validator);

}

void AddBookRecordDialog::HandleInvalidIsbn13()
{
    ui->lineEdit_isbn13->setStyleSheet("background-color: red");
    ui->pushButton_submit->setEnabled(false);
}

void AddBookRecordDialog::HandleIntermidateIsbn13()
{
    ui->lineEdit_isbn13->setStyleSheet("background-color: yellow");
    ui->pushButton_submit->setEnabled(false);
}

void AddBookRecordDialog::HandleValidIsbn13()
{
    ui->lineEdit_isbn13->setStyleSheet("background-color: green");
    ui->pushButton_submit->setEnabled(true);
}


AddBookRecordDialog::~AddBookRecordDialog()
{
    delete ui;
}

void AddBookRecordDialog::on_pushButton_submit_clicked()
{
    emit Submitted(ui->lineEdit_isbn13->text(), ui->lineEdit_title->text(), ui->lineEdit_author->text(), ui->comboBox_category->currentIndex(), ui->comboBox_status->currentIndex(), ui->spinBox_amount->value());
    this->hide();
}
