#include "logindialog.h"
#include "ui_logindialog.h"
#include <status.h>
#include <category.h>
#include <return.h>

#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
#include <QtSql>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QFileInfo>

void LoginDialog::InitializeDatabase()
{
    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery *qry = new QSqlQuery(conn);

    qDebug() << "Created DB Table book:         " << qry->exec("CREATE TABLE \"book\" ( \"id\" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \"isbn13\" TEXT NOT NULL, \"title\" TEXT NOT NULL, \"author\" TEXT NOT NULL, \"category\" INTEGER NOT NULL, \"status\" INTEGER NOT NULL )");
    qDebug() << "Created DB Table category:     " << qry->exec("CREATE TABLE \"category\" ( \"cat_id\" INTEGER, \"cat_name\" TEXT, PRIMARY KEY(\"cat_id\") )");
    qDebug() << "Created DB Table loan_record:  " << qry->exec("CREATE TABLE \"loan_record\" ( \"record_id\" INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \"book_id\" INTEGER, \"person_id\" TEXT, \"loan_date\" INTEGER, \"due_date\" INTEGER, \"returned\" INTEGER )");
    qDebug() << "Created DB Table status:       " << qry->exec("CREATE TABLE \"status\" ( \"status_id\" INTEGER, \"status_name\" TEXT, PRIMARY KEY(\"status_id\") )");
    qDebug() << "Created DB Table user:         " << qry->exec("CREATE TABLE \"user\" ( \"username\" TEXT NOT NULL UNIQUE, \"password_sha512\" TEXT NOT NULL, \"role\" INTEGER DEFAULT 0 )");
    qDebug() << "Created DB Table book_return:  " << qry->exec("CREATE TABLE \"book_return\" (\"return_id\"	INTEGER,\"return_name\"	TEXT,PRIMARY KEY(\"return_id\"))");

    if(qry->exec("INSERT INTO user(\"username\", \"password_sha512\", \"role\") VALUES(\"admin\", \"c7ad44cbad762a5da0a452f9e854fdc1e0e7a52a38015f23f3eab1d80b931dd472634dfac71cd34ebc35d16ab7fb8a90c81f975113d6c7538dc69dd8de9077ec\", \"9\")"))
    {
        QMessageBox::information(this, tr("New user account created!"), tr("Username: admin\nPassword: admin\nUser role: administrative(9)"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(this, tr("Critical Error!"), tr("Cannot create first user account!"), QMessageBox::Ok);
    }
    for (int i = 0; i < Category::count_; i++)
    {
        qDebug() << "Inserting category" << i << qry->exec("INSERT INTO \"category\"(\"cat_id\",\"cat_name\") VALUES ("+QString::number(i)+",\""+QString(Category::EnumToString(i))+"\")");
    }
    for (int i = 0; i < Status::count_; i++)
    {
        qDebug() << "Inserting status" << i << qry->exec("INSERT INTO \"status\"(\"status_id\",\"status_name\") VALUES ("+QString::number(i)+",\""+QString(Status::EnumToString(i))+"\")");
    }
    for (int i = 0; i < Return::count_; i++)
    {
        qDebug() << "Inserting book_return" << i << qry->exec("INSERT INTO \"book_return\"(\"return_id\",\"return_name\") VALUES ("+QString::number(i)+",\""+QString(Return::EnumToString(i))+"\")");
    }
}

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    empty_db_ = IsEmptyDB();

    QSqlDatabase conn = QSqlDatabase::addDatabase("QSQLITE", "SLMS");
    conn.setDatabaseName(QCoreApplication::applicationDirPath() + QDir::separator() + "slms.sqlite");
    if (!conn.open())
    {
        qDebug() << "Cannot open DB connection!";
        QMessageBox::critical(this, "Error!", "Cannot open DB connection!");
        return;
    }
    else
    {
        qDebug() << "SQL Driver Feature - Size:" << conn.driver()->hasFeature(QSqlDriver::DriverFeature::QuerySize);
        qDebug() << "SQL Driver Feature - Transaction:" << conn.driver()->hasFeature(QSqlDriver::DriverFeature::Transactions);
        conn.exec("PRAGMA synchronous = OFF");
        conn.exec("PRAGMA journal_mode = MEMORY");
        qDebug() << "Opened DB connection!";
    }
    if (empty_db_)
    {
        InitializeDatabase();
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::HashBySha512(const char *plain_text, char *hex_hash)
{
    QCryptographicHash sha512_hasher(QCryptographicHash::Sha512);
    sha512_hasher.addData(plain_text, int(strlen(plain_text)));
    strncpy(hex_hash, sha512_hasher.result().toHex(), 128);
}

void LoginDialog::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    char hash_password[129];
    HashBySha512(password.toStdString().c_str(), hash_password);
    hash_password[128] = '\0';

    if (username.length() > 0 && password.length() > 0)
    {
        QSqlDatabase conn = QSqlDatabase::database("SLMS");
        QSqlQuery qry = QSqlQuery(conn);
        if (qry.exec("SELECT role FROM user WHERE username = '"+username+"' AND password_sha512 = '"+hash_password+"'"))
        {
            int count = 0;
            while(qry.next())
            {
                count++;
            }
            qry.first();
            if (count == 1)
            {
                int userrole = qry.value(0).toInt();
                switch(userrole)
                {
                case 0:
                    emit LoginGuest(username);
                    break;
                case 1:
                    emit LoginStudent(username);
                    break;
                case 2:
                    emit LoginTeacher(username);
                    break;
                case 9:
                    emit LoginAdmin(username);
                    break;
                default:
                    break;
                }
                this->hide();
                return;
            }
            else
            {
                QMessageBox::warning(this, "Oops!", "Incorrect Username or Password!");
            }
        }
        else
        {
            qDebug() << "Failed to execute query!";
            QSqlError err = qry.lastError();
            qDebug() << err;
            QMessageBox::warning(this, "Oops!", "Failed to execute query!\n" + err.text());
        }
    }
    else
    {
        QMessageBox::warning(this, "Oops!", "Missing Login Credentials!");
    }
}

bool LoginDialog::IsEmptyDB()
{
    QString file_path = QCoreApplication::applicationDirPath() + QDir::separator() + "slms.sqlite";
    bool file_exists = QFileInfo::exists(file_path) && QFileInfo(file_path).isFile();
    qDebug() << "DB File Exist:" << file_exists;
    if (file_exists)
    {
        return false;
    }
    return true;
}
