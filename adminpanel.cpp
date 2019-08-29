#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "lineeditpopupdialoag.h"
#include <comboboxdelegate.h>
#include <category.h>
#include <status.h>
#include <return.h>
#include <normaldelegate.h>
#include <noteditabledelegate.h>
#include <addbookrecorddialog.h>
#include <editbookrecorddialog.h>

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QSqlRecord>
#include <QTimer>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QScrollBar>
#include <QDate>
#include <QVector>

AdminPanel::AdminPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);

    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    pBookRecordModel_ = new BookRecordQSqlRelationalTableModel(this, conn);
    pLoanRecordModel_ = new LoanRecordQSqlRelationalTableModel(this, conn);

    connect(pBookRecordModel_, &BookRecordQSqlRelationalTableModel::dataChanged, this, &AdminPanel::HandleDataChanged);
    connect(pBookRecordModel_, &BookRecordQSqlRelationalTableModel::DataIsEmpty, this, &AdminPanel::HandleDataIsEmpty);

    pBookRecordModel_->setTable("book");
    pBookRecordModel_->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pBookRecordModel_->setRelation(BookRecordTableViewColumns::CATEGORY, QSqlRelation("category", "cat_id", "cat_name"));
    pBookRecordModel_->setRelation(BookRecordTableViewColumns::STATUS, QSqlRelation("status", "status_id", "status_name"));
    pBookRecordModel_->select();

    pLoanRecordModel_->setTable("loan_record");
    pLoanRecordModel_->setRelation(5, QSqlRelation("book_return", "return_id", "return_name"));
    pLoanRecordModel_->select();

    this->on_checkBox_readOnly_stateChanged(1);

    pBookRecordSearchProxyModel_ = new QubyxSearchFilterProxyModel();
    pBookRecordSearchProxyModel_->setSourceModel(pBookRecordModel_);

    pLoanRecordSearchProxyModel_ = new QubyxSearchFilterProxyModel();
    pLoanRecordSearchProxyModel_->setSourceModel(pLoanRecordModel_);

    ui->tableView_bookRecords->setModel(pBookRecordSearchProxyModel_);
    ui->tableView_bookRecords->setEditTriggers(QAbstractItemView::DoubleClicked);

    ui->tableView_loanRecords->setModel(pLoanRecordSearchProxyModel_);
    ui->tableView_loanRecords->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_bookRecords->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::ID, QHeaderView::ResizeToContents);
    ui->tableView_bookRecords->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::TITLE, QHeaderView::Stretch);
    ui->tableView_bookRecords->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::AUTHOR, QHeaderView::Interactive);
    ui->tableView_bookRecords->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::ISBN13, QHeaderView::ResizeToContents);
    ui->tableView_bookRecords->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::STATUS, QHeaderView::ResizeToContents);
    ui->tableView_bookRecords->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::CATEGORY, QHeaderView::ResizeToContents);

    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::ID, Qt::Horizontal, tr("ID"));
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::ISBN13, Qt::Horizontal, tr("ISBN13"));
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::TITLE, Qt::Horizontal, tr("Title"));
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::AUTHOR, Qt::Horizontal, tr("Author"));
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::CATEGORY, Qt::Horizontal, tr("Category"));
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::STATUS, Qt::Horizontal, tr("Status"));

    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::ID, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/book-line.svg")), Qt::DecorationRole);
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::ISBN13, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/bookmark-2-line.svg")), Qt::DecorationRole);
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::TITLE, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/book-2-line.svg")), Qt::DecorationRole);
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::AUTHOR, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/ball-pen-line.svg")), Qt::DecorationRole);
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::CATEGORY, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/hashtag.svg")), Qt::DecorationRole);
    pBookRecordSearchProxyModel_->setHeaderData(BookRecordTableViewColumns::STATUS, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/computer-line.svg")), Qt::DecorationRole);

    ui->tableView_loanRecords->horizontalHeader()->setSectionResizeMode(LoanRecordTableViewColumns::RECORD_ID, QHeaderView::ResizeToContents);
    ui->tableView_loanRecords->horizontalHeader()->setSectionResizeMode(LoanRecordTableViewColumns::BOOK_ID, QHeaderView::ResizeToContents);
    ui->tableView_loanRecords->horizontalHeader()->setSectionResizeMode(LoanRecordTableViewColumns::PERSON_ID, QHeaderView::Stretch);
    ui->tableView_loanRecords->horizontalHeader()->setSectionResizeMode(LoanRecordTableViewColumns::LOAN_DATE, QHeaderView::ResizeToContents);
    ui->tableView_loanRecords->horizontalHeader()->setSectionResizeMode(LoanRecordTableViewColumns::DUE_DATE, QHeaderView::ResizeToContents);
    ui->tableView_loanRecords->horizontalHeader()->setSectionResizeMode(LoanRecordTableViewColumns::HAVE_RETURNED, QHeaderView::ResizeToContents);

    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::RECORD_ID, Qt::Horizontal, tr("Record ID"));
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::BOOK_ID, Qt::Horizontal, tr("Book ID"));
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::PERSON_ID, Qt::Horizontal, tr("Person ID"));
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::LOAN_DATE, Qt::Horizontal, tr("Loan Date"));
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::DUE_DATE, Qt::Horizontal, tr("Due Date"));
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::HAVE_RETURNED, Qt::Horizontal, tr("Returned?"));

    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::RECORD_ID, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/file-text-line.svg")), Qt::DecorationRole);
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::BOOK_ID, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/book-line.svg")), Qt::DecorationRole);
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::PERSON_ID, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/user-received-line.svg")), Qt::DecorationRole);
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::LOAN_DATE, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/calendar-line.svg")), Qt::DecorationRole);
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::DUE_DATE, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/calendar-event-line.svg")), Qt::DecorationRole);
    pLoanRecordSearchProxyModel_->setHeaderData(LoanRecordTableViewColumns::HAVE_RETURNED, Qt::Horizontal, QVariant::fromValue(QIcon(":/remix_icons/release/resources/icons/database-2-line.svg")), Qt::DecorationRole);

    qDate_format_ = ui->comboBox_qDateFormat->currentText();
    ui->label_today->setText("Today: " + QDate::currentDate().toString(qDate_format_));
    RefreshBookTab();
    pBookRecordModel_->select();
    RefreshLoanTab();
    pLoanRecordModel_->select();

    ui->tabWidget->setCurrentIndex(0);

    book_records_filters_ = new QButtonGroup(this);
    loan_records_filters_ = new QButtonGroup(this);

    book_records_filters_->setExclusive(false);
    loan_records_filters_->setExclusive(false);

    book_records_filters_->addButton(ui->checkBox_filter_id, 0);
    book_records_filters_->addButton(ui->checkBox_filter_isbn13, 1);
    book_records_filters_->addButton(ui->checkBox_filter_title, 2);
    book_records_filters_->addButton(ui->checkBox_filter_author, 3);
    book_records_filters_->addButton(ui->checkBox_filter_category, 4);
    book_records_filters_->addButton(ui->checkBox_filter_status, 5);

    loan_records_filters_->addButton(ui->checkBox_filter_loanRecord_recordId, 0);
    loan_records_filters_->addButton(ui->checkBox_filter_loanRecord_bookId, 1);
    loan_records_filters_->addButton(ui->checkBox_filter_loanRecord_personId, 2);
    loan_records_filters_->addButton(ui->checkBox_filter_loanRecord_loanDate, 3);
    loan_records_filters_->addButton(ui->checkBox_filter_loanRecord_dueDate, 4);
    loan_records_filters_->addButton(ui->checkBox_filter_loanRecord_hvReturned, 5);

    connect(book_records_filters_, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
        [=](QAbstractButton *, bool ){ FilterTableView(); });
    connect(loan_records_filters_, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
        [=](QAbstractButton *, bool ){ FilterTableView(); });

    ui->tabWidget->setCurrentIndex(1);
    FilterTableView();
    ui->tabWidget->setCurrentIndex(0);
    FilterTableView();

    pLoanRecordModel_->SetHightlightOverdueEnabled(false);
    pLoanRecordModel_->SetHightlightOnLoanEnabled(false);

    connect(this, &AdminPanel::FetchFailed, this, &AdminPanel::HandleFailedFetch);
    connect(this, &AdminPanel::FetchNumBookSuccess, this, &AdminPanel::UpdateNumBookToLabel);
    connect(this, &AdminPanel::FetchNumLoanSuccess, this, &AdminPanel::UpdateNumLoanToLabel);
    connect(this, &AdminPanel::FetchNumOverdueSuccess, this, &AdminPanel::UpdateNumOverdueToLabel);
    ReloadNumLoan();
    ReloadNumOverdue();
}

void AdminPanel::HandleInvalidIsbn()
{
    QMessageBox::warning(this, tr("Oops!"), tr("ISBN13 is not valid!"), QMessageBox::Ok);
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::ReceiveLogin(QString username)
{
    QString title = this->windowTitle() + " - " + username;
    this->setWindowTitle(title);
    RefreshBookTab();
    this->show();
}

bool AdminPanel::RefreshBookTab()
{
    ReloadNumBook();

    bool ret_status = pBookRecordModel_->select();
    qDebug() << "Reloaded Books data to TableView: " << ret_status;
    return ret_status;
}
bool AdminPanel::RefreshLoanTab()
{
    ReloadNumLoan();
    ReloadNumOverdue();

    bool ret_status = pLoanRecordModel_->select();
    qDebug() << "Reloaded Loans data to TableView: " << ret_status;
    return ret_status;
}

void AdminPanel::ReloadNumLoan()
{
    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery qry = QSqlQuery(conn);
    if (qry.exec("SELECT COUNT(*) FROM loan_record"))
    {
        qry.first();
        emit FetchNumLoanSuccess(qry.value(0).toInt());
        return;
    }
    else
    {
        emit FetchFailed("Failed fetching number of loan records from DB!");
        return;
    }
}
void AdminPanel::UpdateNumLoanToLabel(int num)
{
    qDebug() << "Updated Loan Label";
    ui->label_numLoanRecords_var->setText(QString::number(num));
}

void AdminPanel::ReloadNumOverdue()
{
    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery qry = QSqlQuery(conn);
    QString str_today = QDate::currentDate().toString("yyyyMMdd");
    if (qry.exec("SELECT record_id FROM loan_record WHERE return_date < " + str_today))
    {
        emit FetchNumOverdueSuccess(qry.record().count());
        return;
    }
    else
    {
        emit FetchFailed("Failed fetching number of overdue records from DB!");
        return;
    }
}
void AdminPanel::UpdateNumOverdueToLabel(int num)
{
    qDebug() << "Updated Overdue Label";
    ui->label_numOverdueLoanRecords_var->setText(QString::number(num));
}

void AdminPanel::HandleFailedFetch(QString desciprtion)
{
    qDebug() << "FAILED FETCH:" << desciprtion;
    QMessageBox::warning(this, "Oops!", desciprtion);
}

void AdminPanel::ReceiveAddBookRequest(QString isbn13, QString title, QString author, int category, int status, int amount)
{
    qDebug() << isbn13 << title << author << category << status << amount;
    QSqlRecord record = pBookRecordModel_->record();
    record.setValue(AdminPanel::ISBN13, isbn13);
    record.setValue(AdminPanel::TITLE, title);
    record.setValue(AdminPanel::AUTHOR, author);
    record.setValue(AdminPanel::CATEGORY, category);
    record.setValue(AdminPanel::STATUS, status);

    QSqlTableModel::EditStrategy old_strat = pBookRecordModel_->editStrategy();
    pBookRecordModel_->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);

    for (int i = 0; i < amount; i++)
    {
        pBookRecordModel_->insertRecord(-1, record);
    }
    qDebug() << "Inserted" << amount << "book records:" << pBookRecordModel_->submitAll();

    pBookRecordModel_->setEditStrategy(old_strat);
}

void AdminPanel::on_pushButton_addBook_clicked()
{
    AddBookRecordDialog *dialog = new AddBookRecordDialog();
    connect(dialog, &AddBookRecordDialog::Submitted, this, &AdminPanel::ReceiveAddBookRequest);
    dialog->exec();
    ReloadNumBook();
    return;
}

void AdminPanel::on_pushButton_reloadBook_clicked()
{
    if (RefreshBookTab())
    {
        QMessageBox::information(this, tr("Done!"), tr("Successfully reloaded book data from DB to view!"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, tr("Oops!"), tr("Something went wrong!"), QMessageBox::Ok);
    }
}

void AdminPanel::on_pushButton_reloadLoans_clicked()
{
    if (RefreshLoanTab())
    {
        QMessageBox::information(this, tr("Done!"), tr("Successfully reloaded loan data from DB to view!"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, tr("Oops!"), tr("Something went wrong!"), QMessageBox::Ok);
    }
}

void AdminPanel::HandleDataChanged()
{
    qDebug() << "Data changed! Updating rowCount label";
    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery qry = QSqlQuery(conn);
    if (qry.exec("SELECT COUNT(*) FROM book"))
    {
        qry.first();
        qDebug() << "Book Record: Real Row Count" << qry.value(0).toInt();
        ui->label_numBookRecords_var->setText(QString::number(qry.value(0).toInt()));
        while (pBookRecordModel_->canFetchMore())
               pBookRecordModel_->fetchMore();
    }
    else
    {
        QMessageBox::warning(this, tr("Warning!"), tr("Could not fetch number of book records from DB!"));
        return;
    }
}

void AdminPanel::HandleDataIsEmpty(QModelIndex last_empty_index)
{
    QString desc_text = "";
    desc_text += "The ";
    desc_text += ui->tableView_bookRecords->model()->headerData(last_empty_index.column(), Qt::Horizontal).toString();
    desc_text += " field is empty!";
    QMessageBox::warning(this, tr("Oops!"), tr(desc_text.toStdString().c_str()), QMessageBox::Ok);
    RefreshBookTab();
}

void AdminPanel::on_pushButton_deleteRecords_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure?", "Deletion will NOT be cached and will be submitted to the DB automatically, continue?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        RemoveSelectedRows();
    }
    ReloadNumBook();
}

void AdminPanel::RemoveSelectedRows()
{
    if (ui->tableView_bookRecords->selectionModel()->hasSelection() == false)
    {
        QMessageBox::warning(this, "Oops!", "You haven't selected any rows!", QMessageBox::Ok);
    }
    else
    {
        QSqlTableModel::EditStrategy old_strat = pBookRecordModel_->editStrategy();
        pBookRecordModel_->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);

        foreach (QModelIndex index, ui->tableView_bookRecords->selectionModel()->selectedRows())
        {
            pBookRecordSearchProxyModel_->removeRow(index.row());
        }
        pBookRecordModel_->submitAll();
        pBookRecordModel_->setEditStrategy(old_strat);
        RefreshBookTab();
    }
}

bool AdminPanel::NoCheckedCheckbox(QButtonGroup *button_group)
{
    QListIterator<QAbstractButton *> i(button_group->buttons());
    while (i.hasNext())
    {
        QAbstractButton *b = i.next();
        QCheckBox *cb = qobject_cast<QCheckBox*>(b);
        if (cb->checkState() == Qt::Checked)
        {
            return true;
        }
    }
    return false;
}

void AdminPanel::FilterTableView()
// https://stackoverflow.com/questions/18378062/qt-how-i-can-filter-more-than-one-columns
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        if (!NoCheckedCheckbox(book_records_filters_))
        {
            ShowWarnTickAtLeastOne();
            return;
        }

        pBookRecordSearchProxyModel_->invalidate();
        pBookRecordSearchProxyModel_->SetFilterEnabled(true);
        pBookRecordSearchProxyModel_->ClearColsToFilter();
        pBookRecordSearchProxyModel_->SetOverdueFilterEnabled(false);

        QVector<int> cols_to_filter;
        Qt::CheckState s_id = ui->checkBox_filter_id->checkState();
        if (s_id == Qt::Checked)
            cols_to_filter.append(0);
        Qt::CheckState s_isbn13 = ui->checkBox_filter_isbn13->checkState();
        if (s_isbn13 == Qt::Checked)
            cols_to_filter.append(1);
        Qt::CheckState s_title = ui->checkBox_filter_title->checkState();
        if (s_title == Qt::Checked)
            cols_to_filter.append(2);
        Qt::CheckState s_author = ui->checkBox_filter_author->checkState();
        if (s_author == Qt::Checked)
            cols_to_filter.append(3);
        Qt::CheckState s_category = ui->checkBox_filter_category->checkState();
        if (s_category == Qt::Checked)
            cols_to_filter.append(4);
        Qt::CheckState s_status = ui->checkBox_filter_status->checkState();
        if (s_status == Qt::Checked)
            cols_to_filter.append(5);

        pBookRecordSearchProxyModel_->SetColsToFilter(cols_to_filter);
        qDebug() << "pBookRecordSearchProxyModel_ - Fitlering on column" << cols_to_filter;

        QRegExp regExp(ui->lineEdit->text(), (ui->checkBox_filter_caseSensitive->checkState() == Qt::Checked) ? Qt::CaseSensitive : Qt::CaseInsensitive, QRegExp::FixedString);
        pBookRecordSearchProxyModel_->setFilterRegExp(regExp);

        while (pBookRecordModel_->canFetchMore())
        {
            pBookRecordModel_->fetchMore();
        }
        qDebug() << "pBookRecordModel_ - Source:" << pBookRecordModel_->rowCount() << "pBookRecordSearchProxyModel_ - Displaying:" << pBookRecordSearchProxyModel_->rowCount();
    }

    if (ui->tabWidget->currentIndex() == 1)
    {
        if (!NoCheckedCheckbox(loan_records_filters_))
        {
            ShowWarnTickAtLeastOne();
            return;
        }

        pLoanRecordSearchProxyModel_->invalidate();
        pLoanRecordSearchProxyModel_->SetFilterEnabled(true);
        pLoanRecordSearchProxyModel_->ClearColsToFilter();
        pLoanRecordSearchProxyModel_->SetOverdueFilterEnabled((ui->checkBox_filter_loanRecord_overdue->checkState() == Qt::Checked));

        QVector<int> cols_to_filter;
        Qt::CheckState s_r_id = ui->checkBox_filter_loanRecord_recordId->checkState();
        if (s_r_id == Qt::Checked)
            cols_to_filter.append(0);
        Qt::CheckState s_bk_id = ui->checkBox_filter_loanRecord_bookId->checkState();
        if (s_bk_id == Qt::Checked)
            cols_to_filter.append(1);
        Qt::CheckState s_person_id = ui->checkBox_filter_loanRecord_personId->checkState();
        if (s_person_id == Qt::Checked)
            cols_to_filter.append(2);
        Qt::CheckState s_ld = ui->checkBox_filter_loanRecord_loanDate->checkState();
        if (s_ld == Qt::Checked)
            cols_to_filter.append(3);
        Qt::CheckState s_rd = ui->checkBox_filter_loanRecord_dueDate->checkState();
        if (s_rd == Qt::Checked)
            cols_to_filter.append(4);
        Qt::CheckState s_hvRet = ui->checkBox_filter_loanRecord_hvReturned->checkState();
        if (s_hvRet == Qt::Checked)
            cols_to_filter.append(5);

        pLoanRecordSearchProxyModel_->SetColsToFilter(cols_to_filter);
        qDebug() << "pLoanRecordSearchProxyModel_ - Fitlering on column" << cols_to_filter;

        QRegExp regExp(ui->lineEdit->text(), (ui->checkBox_filter_caseSensitive->checkState() == Qt::Checked) ? Qt::CaseSensitive : Qt::CaseInsensitive, QRegExp::FixedString);
        pLoanRecordSearchProxyModel_->setFilterRegExp(regExp);

        while (pLoanRecordModel_->canFetchMore())
        {
            pLoanRecordModel_->fetchMore();

        }
        qDebug() << "pLoanRecordModel_ - Source:" << pLoanRecordModel_->rowCount() << "pLoanRecordSearchProxyModel_ - Displaying:" << pLoanRecordSearchProxyModel_->rowCount();
    }
}

void AdminPanel::on_pushButton_updateView_clicked()
{
    FilterTableView();
}

void AdminPanel::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1 == Qt::Checked)
        FilterTableView();
}

void AdminPanel::on_pushButton_loan_clicked()
{
    QString loaner_id = ui->lineEdit_personId->text();
    QString loan_book_id = ui->lineEdit_bookId->text();
    ui->lineEdit_personId->clear();
    ui->lineEdit_bookId->clear();
    if (loaner_id.length() == 0 || loan_book_id.length() == 0)
    {
        QMessageBox::warning(this, tr("Oops!"),
                                   tr("Fields must not be empty!"),
                                       QMessageBox::Ok);
        return;
    }
    int num_days = ui->comboBox_nDays->currentText().toInt();

    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery qry = QSqlQuery(conn);
    if (qry.exec("SELECT status FROM book WHERE id = '"+loan_book_id+"'"))
    {
        int count = 0;
        while(qry.next())
        {
            count++;
        }
        qry.first();
        if (count == 1)
        {
            int status = qry.value(0).toInt();
            if (status != Status::AVAILABLE)
            {
                QMessageBox::warning(this, tr("Error!"),tr("This book is not available for loaning!"), QMessageBox::Ok);
                return;
            }
            else
            {
                QDate today = QDate::currentDate();
                QDate due_date = today.addDays(num_days);
                if (qry.exec("UPDATE book SET status = '"+QString::number(Status::ON_LOAN)+"' WHERE id = '"+loan_book_id+"'") &&
                    qry.exec("INSERT INTO loan_record (book_id, person_id, loan_date, return_date, returned) VALUES ('"+loan_book_id+"', '"+loaner_id+"', '"+today.toString("yyyyMMdd")+"', '"+due_date.toString("yyyyMMdd")+"', '"+QString::number(Return::NO)+"')")   )
                {
                    QString msg = "Successfully updated DB!\n";
                    msg += "\nBook ID: \t\t\t"+loan_book_id;
                    msg += "\nBorrower ID: \t\t"+loaner_id;
                    msg += "\nDate of borrow: \t\t"+today.toString();
                    msg += "\nReturn on or before: \t"+due_date.toString();
                    QMessageBox::information(this, tr("Success!"), tr(msg.toStdString().c_str()), QMessageBox::Ok);
                }
                else
                {
                    QSqlError err = qry.lastError();
                    QMessageBox::warning(this, tr("Failed to execute query!"), tr(err.text().toUtf8().data()), QMessageBox::Ok);
                }
                RefreshBookTab();
                RefreshLoanTab();
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Error!"), tr("No such book in DB!"), QMessageBox::Ok);
            return;
        }
    }
    else
    {
        QSqlError err = qry.lastError();
        QMessageBox::warning(this, tr("Failed to execute query!"), tr(err.text().toUtf8().data()), QMessageBox::Ok);
        return;
    }
}

void AdminPanel::on_pushButton_return_clicked()
{
    QString loaner_id = ui->lineEdit_personId->text();
    QString loan_book_id = ui->lineEdit_bookId->text();
    ui->lineEdit_personId->clear();
    ui->lineEdit_bookId->clear();

    if (loan_book_id.length() == 0)
    {
        QMessageBox::warning(this, tr("Oops!"), tr("Field must not be empty!"), QMessageBox::Ok);
        return;
    }

    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlTableModel *model = new QSqlTableModel(this, conn);

    int book_status = -1;
    model->setTable("book");
    model->select();
    while (model->canFetchMore())
           model->fetchMore();
    for (int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex book_id = model->index(i, BookRecordTableViewColumns::ID);
        if (book_id.data().toString() == loan_book_id)
        {
            QModelIndex status = model->index(i, BookRecordTableViewColumns::STATUS);
            book_status = status.data().toInt();
        }
    }
    if (book_status == -1)
    {
        QMessageBox::critical(this, tr("Critical!"), tr("Unable to fetch book information, ABORT!"), QMessageBox::Ok);
        return;
    }
    if (book_status == Status::LOST)
    {
        QMessageBox::warning(this, tr("Oops!"), tr("Cannot return a Lost book, ABORT!"), QMessageBox::Ok);
        return;
    }
    if (book_status == Status::UNKNOWN)
    {
        QMessageBox::warning(this, tr("Oops!"), tr("Cannot return a Unknown book, ABORT!"), QMessageBox::Ok);
        return;
    }
    if (book_status == Status::AVAILABLE)
    {
        QMessageBox::warning(this, tr("Oops!"), tr("Cannot return an Available book, ABORT!"), QMessageBox::Ok);
        return;
    }

    bool ret_lr_setData = false, ret_lr_submitAll = false;
    bool ret_br_setData = false, ret_br_submitAll = false;
    bool book_returned_already = true;
    bool book_overdue = false;
    QDate due_date;
    QDate today = QDate::currentDate();
    model->setTable("loan_record");
    model->select();
    while (model->canFetchMore())
           model->fetchMore();
    int num_records = model->rowCount();

    if (num_records < 1)
    {
        QMessageBox::warning(this, tr("Oops!"), tr("No loan records to process!"), QMessageBox::Ok);
        return;
    }
    for (int i = 0; i < num_records; i++)
    {
        QModelIndex book_id = model->index(i, LoanRecordTableViewColumns::BOOK_ID);
        if (book_id.data().toString() == loan_book_id)
        {
            QModelIndex hv_returned = model->index(i, LoanRecordTableViewColumns::HAVE_RETURNED);
            if (hv_returned.data().toInt() == Return::NO)
            {
                book_returned_already = false;
                QModelIndex index_due_date = model->index(i, LoanRecordTableViewColumns::DUE_DATE);
                due_date = QDate::fromString(index_due_date.data().toString(), "yyyyMMdd");
                if (today > due_date)
                {
                    book_overdue = true;
                }
                ret_lr_setData = model->setData(hv_returned, Return::YES, Qt::EditRole);
                ret_lr_submitAll = model->submitAll();
            }
        }
    }

    model->setTable("book");
    model->select();
    while (model->canFetchMore())
           model->fetchMore();
    for (int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex book_id = model->index(i, BookRecordTableViewColumns::ID);
        if (book_id.data().toString() == loan_book_id)
        {
            QModelIndex status = model->index(i, BookRecordTableViewColumns::STATUS);
            ret_br_setData = model->setData(status, Status::AVAILABLE, Qt::EditRole);
            ret_br_submitAll = model->submitAll();
        }
    }

    if (ret_lr_setData && ret_lr_submitAll && ret_br_setData && ret_br_submitAll)
    {
        if (book_overdue)
        {
            QString msg = "";
            msg += "Record updated!\n\n";
            QString days_delta = QString::number(due_date.daysTo(today));
            msg += "Book is overdue ";
            msg += days_delta;
            msg += " days";
            QMessageBox::information(this, tr("Done!"), tr(msg.toStdString().c_str()), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this, tr("Done!"), tr("Record updated!"), QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Oops!"), tr("There were some error when interacting with the DB, please manually review the record!"
                                                   "\nret_lr_setData:%1 ret_lr_submitAll:%2 ret_br_setData:%3 ret_br_submitAll:%4").arg(ret_lr_setData).arg(ret_lr_submitAll).arg(ret_br_setData).arg(ret_br_submitAll), QMessageBox::Ok);
    }
    RefreshBookTab();
    RefreshLoanTab();
}

void AdminPanel::on_pushButton_clicked()
{
    QString qry_str = ui->plainTextEdit->toPlainText();

    if (qry_str.length() < 1)
    {
        QMessageBox::warning(this, tr("Oops!"), tr("The query cannot be empty!"), QMessageBox::Ok);
        return;
    }

    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery query(conn);
    bool result = query.exec(qry_str);
    qDebug() << "Executing SQL Mass Action: " << result << qry_str;
    if (result)
    {
        qDebug() << "Query result:" << query.result();
        QMessageBox::information(this, tr("Done!"), tr("Successfully executed the query in DB!"), QMessageBox::Ok);
    }
    else
    {
        QString err_text_desc = "";
        err_text_desc += "There were some error when interacting with the DB!";
        err_text_desc += "\n\n";
        err_text_desc += query.lastError().text();
        QMessageBox::warning(this, tr("Oops!"), tr(err_text_desc.toStdString().c_str()), QMessageBox::Ok);
    }
    RefreshBookTab();
    RefreshLoanTab();
}

void AdminPanel::ReceivePersonId(QString person_id)
{
    ui->lineEdit->clear();
    ui->lineEdit_personId->setText(person_id);
}

void AdminPanel::ReceiveBookId(QString book_id)
{
    ui->lineEdit->clear();
    ui->lineEdit_bookId->setText(book_id);
}


void AdminPanel::on_pushButton_editPersonId_clicked()
{
    LineEditPopupDialog *d = new LineEditPopupDialog;
    d->setWindowTitle("Set Person ID");
    connect(d, SIGNAL(ValueSubmitted(QString)), this, SLOT(ReceivePersonId(QString)));
    d->exec();
}

void AdminPanel::on_pushButton_editBookId_clicked()
{
    LineEditPopupDialog *d = new LineEditPopupDialog;
    d->setWindowTitle("Set Book ID");
    connect(d, SIGNAL(ValueSubmitted(QString)), this, SLOT(ReceiveBookId(QString)));
    d->exec();
}

void AdminPanel::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
    {
        ui->groupBox_recordManipulation->setEnabled(true);
        ui->frame_bookRecords_columnFilters->setEnabled(true);
        ui->frame_loanRecords_columnFilters->setEnabled(false);
    }
    if (index == 1)
    {
        ui->groupBox_recordManipulation->setEnabled(false);
        ui->frame_bookRecords_columnFilters->setEnabled(false);
        ui->frame_loanRecords_columnFilters->setEnabled(true);
    }
}

void AdminPanel::ShowWarnTickAtLeastOne()
{
    QMessageBox::warning(this, tr("Oops!"), tr("Please check at least one checkbox!"), QMessageBox::Ok);
}

void AdminPanel::on_checkBox_filter_loanRecord_overdue_stateChanged(int arg1)
{
    FilterTableView();
}

void AdminPanel::on_checkBox_updateViewAsIType_stateChanged(int arg1)
{
    if (arg1 == Qt::CheckState::Checked)
        FilterTableView();
}

void AdminPanel::on_checkBox_filter_caseSensitive_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    FilterTableView();
}

void AdminPanel::on_checkBox_filter_loanRecord_onLoan_stateChanged(int arg1)
{
    pLoanRecordSearchProxyModel_->SetOnLoanFilterEnabled(arg1 == Qt::Checked);
    FilterTableView();
}

void AdminPanel::on_checkBox_highlight_overdue_stateChanged(int arg1)
{
    pLoanRecordModel_->SetHightlightOverdueEnabled(arg1 == Qt::Checked);
    RefreshLoanTab();
}

void AdminPanel::on_checkBox_highlight_onLoan_stateChanged(int arg1)
{
    pLoanRecordModel_->SetHightlightOnLoanEnabled(arg1 == Qt::Checked);
    RefreshLoanTab();
}

void AdminPanel::on_comboBox_qDateFormat_currentTextChanged(const QString &arg1)
{
    qDate_format_ = arg1.trimmed();
    ui->label_today->setText("Today: " + QDate::currentDate().toString(arg1));
    SyncQDateFormatToLRQSRTM();
    RefreshLoanTab();
}

void AdminPanel::SyncQDateFormatToLRQSRTM()
{
    pLoanRecordModel_->SetQDateFormat(qDate_format_);
}

void AdminPanel::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F8)
    {
        on_pushButton_editBookId_clicked();
        on_pushButton_editPersonId_clicked();
        on_pushButton_loan_clicked();
    }
    if (event->key() == Qt::Key_F9)
    {
        on_pushButton_editBookId_clicked();
        on_pushButton_return_clicked();
    }
}

void AdminPanel::on_checkBox_readOnly_stateChanged(int arg1)
{
    if (ui->checkBox_readOnly->checkState() == Qt::Checked)
    {
        pCbD_ = new ComboBoxDelegate(ui->tableView_bookRecords);
        pCbD_->SetEditorEnabled(false);
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::CATEGORY, pCbD_);
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::STATUS, pCbD_);

        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::ID, new NotEditableDelegate());
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::ISBN13, new NotEditableDelegate());
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::TITLE, new NotEditableDelegate());
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::AUTHOR, new NotEditableDelegate());
    }
    else
    {
        pCbD_ = new ComboBoxDelegate(ui->tableView_bookRecords);
        pCbD_->SetEditorEnabled(true);
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::CATEGORY, pCbD_);
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::STATUS, pCbD_);

        NormalDelegate *ld = new NormalDelegate();
        connect(ld, &NormalDelegate::InvalidIsbn, this, &AdminPanel::HandleInvalidIsbn);
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::ID, new NotEditableDelegate());
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::ISBN13, ld);
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::TITLE, ld);
        ui->tableView_bookRecords->setItemDelegateForColumn(BookRecordTableViewColumns::AUTHOR, ld);
    }
}

void AdminPanel::ReceiveEditBookRequest(int id, QString isbn13, QString title, QString author, int category, int status)
{
    qDebug() << id << isbn13 << title << author << category << status;

    int selected_row = ui->tableView_bookRecords->selectionModel()->selectedRows().at(0).row();
    QSqlRecord new_record = pBookRecordModel_->record(selected_row);

    new_record.setValue(BookRecordTableViewColumns::ISBN13, isbn13);
    new_record.setValue(BookRecordTableViewColumns::TITLE, title);
    new_record.setValue(BookRecordTableViewColumns::AUTHOR, author);
    new_record.setValue(BookRecordTableViewColumns::CATEGORY, category);
    new_record.setValue(BookRecordTableViewColumns::STATUS, status);

    QSqlTableModel::EditStrategy old_strat = pBookRecordModel_->editStrategy();
    pBookRecordModel_->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
    pBookRecordModel_->setRecord(selected_row, new_record);
    pBookRecordModel_->submitAll();
    pBookRecordModel_->setEditStrategy(old_strat);
}

void AdminPanel::on_pushButton_editBook_clicked()
{
    if (ui->tableView_bookRecords->selectionModel()->selectedRows().length() != 1)
    {
        QMessageBox::warning(this, "Oops!", "Please select one row!", QMessageBox::Ok);
        return;
    }
    int selected_row = ui->tableView_bookRecords->selectionModel()->selectedRows().at(0).row();
    QSqlRecord target_record = pBookRecordModel_->record(selected_row);

    EditBookRecordDialog *d = new EditBookRecordDialog();
    d->SetId(target_record.value(BookRecordTableViewColumns::ID).toInt());
    d->SetIsbn13(target_record.value(BookRecordTableViewColumns::ISBN13).toString());
    d->SetTitle(target_record.value(BookRecordTableViewColumns::TITLE).toString());
    d->SetAuthor(target_record.value(BookRecordTableViewColumns::AUTHOR).toString());
    d->SetCategory(Category::StringToEnum(target_record.value(BookRecordTableViewColumns::CATEGORY).toString()));
    d->SetStatus(Status::StringToEnum(target_record.value(BookRecordTableViewColumns::STATUS).toString()));
    d->PopulateWidgets();
    connect(d, &EditBookRecordDialog::Submitted, this, &AdminPanel::ReceiveEditBookRequest);
    d->exec();
}

void AdminPanel::ReloadNumBook()
{
    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery qry = QSqlQuery(conn);
    if (qry.exec("SELECT COUNT(*) FROM book"))
    {
        qry.first();
        emit FetchNumBookSuccess(qry.value(0).toInt());
        return;
    }
    else
    {
        emit FetchFailed("Failed fetching number of book records from DB!");
        return;
    }
}

void AdminPanel::UpdateNumBookToLabel(int num)
{
    qDebug() << "Updated Book Label";
    ui->label_numBookRecords_var->setText(QString::number(num));
}
