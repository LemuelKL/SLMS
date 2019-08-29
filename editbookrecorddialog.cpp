#include "editbookrecorddialog.h"
#include "ui_editbookrecorddialog.h"

#include <QtDebug>
#include <category.h>
#include <status.h>
#include <isbn13validator.h>

EditBookRecordDialog::EditBookRecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBookRecordDialog)

{
    ui->setupUi(this);

    this->setWindowTitle("Edit Book Record");

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

    ui->lineEdit_isbn13->setMaxLength(13);

    QValidator *validator = new Isbn13Validator(this);
    connect(validator, SIGNAL(InvalidIsbn13()), this, SLOT(HandleInvalidIsbn13()));
    connect(validator, SIGNAL(IntermediateIsbn13()), this, SLOT(HandleIntermidateIsbn13()));
    connect(validator, SIGNAL(ValidIsbn13()), this, SLOT(HandleValidIsbn13()));
    ui->lineEdit_isbn13->setValidator(validator);
}

void EditBookRecordDialog::HandleInvalidIsbn13()
{
    ui->lineEdit_isbn13->setStyleSheet("background-color: red");
    ui->pushButton_submit->setEnabled(false);
}

void EditBookRecordDialog::HandleIntermidateIsbn13()
{
    ui->lineEdit_isbn13->setStyleSheet("background-color: yellow");
    ui->pushButton_submit->setEnabled(false);
}

void EditBookRecordDialog::HandleValidIsbn13()
{
    ui->lineEdit_isbn13->setStyleSheet("background-color: green");
    ui->pushButton_submit->setEnabled(true);
}

EditBookRecordDialog::~EditBookRecordDialog()
{
    delete ui;
}

void EditBookRecordDialog::SetId(int id)
{
    id_ = id;
}

void EditBookRecordDialog::SetIsbn13(QString isbn13)
{
    isbn13_ = isbn13;
}

void EditBookRecordDialog::SetTitle(QString title)
{
    title_ = title;
}

void EditBookRecordDialog::SetAuthor(QString author)
{
    author_ = author;
}

void EditBookRecordDialog::SetCategory(int category)
{
    category_ = category;
}

void EditBookRecordDialog::SetStatus(int status)
{
    status_ = status;
}

void EditBookRecordDialog::PopulateWidgets()
{
    ui->lineEdit_isbn13->setText(isbn13_);
    ui->lineEdit_title->setText(title_);
    ui->lineEdit_author->setText(author_);
    ui->comboBox_category->setCurrentIndex(category_);
    ui->comboBox_status->setCurrentIndex(status_);
}
void EditBookRecordDialog::on_pushButton_submit_clicked()
{
    emit Submitted(ui->lineEdit_isbn13->text(), ui->lineEdit_title->text(), ui->lineEdit_author->text(), ui->comboBox_category->currentIndex(), ui->comboBox_status->currentIndex(), id_);
    this->hide();
}
