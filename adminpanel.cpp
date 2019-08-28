#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "lineeditpopupdialoag.h"
#include <comboboxdelegate.h>
#include <category.h>
#include <status.h>
#include <return.h>
#include <normaldelegate.h>
#include <noteditabledelegate.h>

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

    pCbD_ = new ComboBoxDelegate(ui->tableView);
    ui->tableView->setAutoScroll(true);
    ui->tableView->setItemDelegateForColumn(BookRecordTableViewColumns::CATEGORY, pCbD_);
    ui->tableView->setItemDelegateForColumn(BookRecordTableViewColumns::STATUS, pCbD_);

    NormalDelegate *ld = new NormalDelegate();
    connect(ld, &NormalDelegate::InvalidIsbn, this, &AdminPanel::HandleInvalidIsbn);

    ui->tableView->setItemDelegateForColumn(BookRecordTableViewColumns::ID, new NotEditableDelegate());
    ui->tableView->setItemDelegateForColumn(BookRecordTableViewColumns::ISBN13, ld);
    ui->tableView->setItemDelegateForColumn(BookRecordTableViewColumns::TITLE, ld);
    ui->tableView->setItemDelegateForColumn(BookRecordTableViewColumns::AUTHOR, ld);

    pBookRecordSearchProxyModel_ = new QubyxSearchFilterProxyModel();
    pBookRecordSearchProxyModel_->setSourceModel(pBookRecordModel_);

    pLoanRecordSearchProxyModel_ = new QubyxSearchFilterProxyModel();
    pLoanRecordSearchProxyModel_->setSourceModel(pLoanRecordModel_);

    ui->tableView->setModel(pBookRecordSearchProxyModel_);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);

    ui->tableView_loanRecords->setModel(pLoanRecordSearchProxyModel_);
    ui->tableView_loanRecords->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::ID, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::TITLE, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::AUTHOR, QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::ISBN13, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::STATUS, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(BookRecordTableViewColumns::CATEGORY, QHeaderView::ResizeToContents);

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
    ReloadBooksToView();
    ReloadLoansToView();

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
    loan_records_filters_->addButton(ui->checkBox_filter_loanRecord_returnDate, 4);
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

}

void AdminPanel::HandleInvalidIsbn()
{
    QMessageBox::warning(this, tr("Oops!"),
                               tr("ISBN13 is not valid!"),
                                   QMessageBox::Ok);
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

bool AdminPanel::ReloadBooksToView()
{
    bool ret_status = pBookRecordModel_->select();
    qDebug() << "Reloaded Books data to TableView: " << ret_status;

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
        return false;
    }
    return ret_status;
}

bool AdminPanel::ReloadLoansToView()
{
    bool ret_status = pLoanRecordModel_->select();
    qDebug() << "Reloaded Loans data to TableView: " << ret_status;

    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlQuery qry = QSqlQuery(conn);
    if (qry.exec("SELECT COUNT(*) FROM loan_record"))
    {
        qry.first();
        qDebug() << "Loan Record: Real Row Count" << qry.value(0).toInt();
        ui->label_numLoanRecords_var->setText(QString::number(qry.value(0).toInt()));
        while (pLoanRecordModel_->canFetchMore())
               pLoanRecordModel_->fetchMore();
    }
    else
    {
        QMessageBox::warning(this, tr("Warning!"), tr("Could not fetch number of loan records from DB!"));
        return false;
    }

    this->UpdateOverdueRecordsToLabel();
    return ret_status;
}


void AdminPanel::ReceiveLogin(QString username)
{
    QString title = this->windowTitle() + " - " + username;
    this->setWindowTitle(title);
    ReloadBooksToView();
    this->show();
}

void AdminPanel::on_pushButton_addBook_clicked()
{
    QSqlRecord record = pBookRecordModel_->record();
    record.setValue(AdminPanel::ISBN13, "UNCONFIGURED ISBN13");
    record.setValue(AdminPanel::TITLE, "UNCONFIGURED TITLE");
    record.setValue(AdminPanel::AUTHOR, "UNCONFIGURED AUTHOR");
    record.setValue(AdminPanel::CATEGORY, 0);
    record.setValue(AdminPanel::STATUS, 0);

    while (pBookRecordModel_->canFetchMore())
        pBookRecordModel_->fetchMore();
    if (pBookRecordModel_->insertRecord(-1, record))
    {
        if (ui->checkBox_submitChangesAutomatically->checkState() == Qt::Checked)
            ReloadBooksToView();
        QModelIndex source_index = pBookRecordModel_->index(pBookRecordModel_->rowCount() - 1, AdminPanel::ISBN13);
        QModelIndex proxy_index = pBookRecordSearchProxyModel_->mapFromSource(source_index);
        ui->tableView->scrollTo(proxy_index);
        ui->tableView->setCurrentIndex(proxy_index);
        ui->tableView->edit(proxy_index);
    }
    else
    {
        QMessageBox::critical(this, "Oh no!", "Something went wrong when inserting a new record!");
    }
}

void AdminPanel::on_pushButton_reloadBook_clicked()
{
    if (ReloadBooksToView())
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
    if (ReloadLoansToView())
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
    desc_text += ui->tableView->model()->headerData(last_empty_index.column(), Qt::Horizontal).toString();
    desc_text += " field is empty!";
    QMessageBox::warning(this, tr("Oops!"), tr(desc_text.toStdString().c_str()), QMessageBox::Ok);
    ReloadBooksToView();
}

void AdminPanel::on_pushButton_deleteRecords_clicked()
{
    if (ui->checkBox_submitChangesAutomatically->checkState() == Qt::Checked)
    {
        RemoveSelectedRows();
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure?", "Deletion will NOT be cached and will be submitted to the DB automatically, continue?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            RemoveSelectedRows();
        }
    }
}

void AdminPanel::RemoveSelectedRows()
{
    if (ui->tableView->selectionModel()->hasSelection() == false)
    {
        QMessageBox::warning(this, "Oops!", "You haven't selected any rows!", QMessageBox::Ok);
    }
    else
    {
        foreach (QModelIndex index, ui->tableView->selectionModel()->selectedRows())
        {
            pBookRecordSearchProxyModel_->removeRow(index.row());
        }
        pBookRecordModel_->submitAll();
        ReloadBooksToView();
    }
}

void AdminPanel::FilterTableView()
// https://stackoverflow.com/questions/18378062/qt-how-i-can-filter-more-than-one-columns
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        bool has_at_least_one_checked = false;
        QList<QAbstractButton*> br_chkbxes = book_records_filters_->buttons();
        QListIterator<QAbstractButton*> i(br_chkbxes);
        while (i.hasNext())
        {
            QAbstractButton* b = i.next();
            QCheckBox* cb = qobject_cast<QCheckBox*>(b);
            if (cb->checkState() == Qt::Checked)
            {
                has_at_least_one_checked = true;
                break;
            }
        }
        if (!has_at_least_one_checked)
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
        qDebug() << "pBookRecordSearchProxyModel_ Fitlering on column" << cols_to_filter;

        QRegExp regExp(ui->lineEdit->text(), (ui->checkBox_filter_caseSensitive->checkState() == Qt::Checked) ? Qt::CaseSensitive : Qt::CaseInsensitive, QRegExp::FixedString);
        pBookRecordSearchProxyModel_->setFilterRegExp(regExp);

        while (pBookRecordModel_->canFetchMore())
               pBookRecordModel_->fetchMore();

        qDebug() << "pBookRecordModel_ Source" << pBookRecordModel_->rowCount() << "pBookRecordSearchProxyModel_ Displaying" << pBookRecordSearchProxyModel_->rowCount();
    }
    if (ui->tabWidget->currentIndex() == 1)
    {
        bool has_at_least_one_checked = false;
        QList<QAbstractButton*> br_chkbxes = loan_records_filters_->buttons();
        QListIterator<QAbstractButton*> i(br_chkbxes);
        while (i.hasNext())
        {
            QAbstractButton* b = i.next();
            QCheckBox* cb = qobject_cast<QCheckBox*>(b);
            if (cb->checkState() == Qt::Checked)
            {
                has_at_least_one_checked = true;
                break;
            }
        }
        if (!has_at_least_one_checked)
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
        Qt::CheckState s_rd = ui->checkBox_filter_loanRecord_returnDate->checkState();
        if (s_rd == Qt::Checked)
            cols_to_filter.append(4);
        Qt::CheckState s_hvRet = ui->checkBox_filter_loanRecord_hvReturned->checkState();
        if (s_hvRet == Qt::Checked)
            cols_to_filter.append(5);

        pLoanRecordSearchProxyModel_->SetColsToFilter(cols_to_filter);
        qDebug() << "pLoanRecordSearchProxyModel_ Fitlering on column" << cols_to_filter;

        QRegExp regExp(ui->lineEdit->text(), (ui->checkBox_filter_caseSensitive->checkState() == Qt::Checked) ? Qt::CaseSensitive : Qt::CaseInsensitive, QRegExp::FixedString);
        pLoanRecordSearchProxyModel_->setFilterRegExp(regExp);

        while (pLoanRecordModel_->canFetchMore())
               pLoanRecordModel_->fetchMore();

        qDebug() << "pLoanRecordModel_ Source" << pLoanRecordModel_->rowCount() << "pLoanRecordSearchProxyModel_ Displaying" << pLoanRecordSearchProxyModel_->rowCount();
    }
}

void AdminPanel::on_pushButton_duplicateRecords_clicked()
{
    if (ui->tableView->selectionModel()->hasSelection() && ui->tableView->selectionModel()->selectedRows().size() == 1)
    {
        QModelIndex a = ui->tableView->selectionModel()->selectedRows()[0];
        int row = a.row();
        int num_duplicate_row = ui->spinBox_copiesToMake->value();
        int i;

        auto proxy = static_cast<QSortFilterProxyModel*>(ui->tableView->model());
        auto const proxyIndex1 = proxy->index(row, 1);
        auto const proxyIndex2 = proxy->index(row, 2);
        auto const proxyIndex3 = proxy->index(row, 3);
        auto const proxyIndex4 = proxy->index(row, 4);
        auto const proxyIndex5 = proxy->index(row, 5);

        QSqlRecord record = pBookRecordModel_->record();
        record.setValue(1, ui->tableView->model()->data(proxyIndex1).toString());
        record.setValue(2, ui->tableView->model()->data(proxyIndex2).toString());
        record.setValue(3, ui->tableView->model()->data(proxyIndex3).toString());
        record.setValue(4, Category::StringToEnum(ui->tableView->model()->data(proxyIndex4).toString()));
        record.setValue(5, Status::StringToEnum(ui->tableView->model()->data(proxyIndex5).toString()));

        for (i = 0; i < num_duplicate_row; i++)
        {
            // HISTORY : (Future coders could ignore) This block must be recalculated every loop! (because of model reset);

            qDebug() << "Duplicate - Trying to insert: " << record.value(1) << record.value(2) << record.value(3) << record.value(4) << record.value(5);
            qDebug() << "Duplicate - insertRecord state: " << pBookRecordModel_->insertRecord(-1, record);
        }
        QString body_text = "Done duplicating " + QString::number(i) + " records!";
        QMessageBox::information(this, tr("Success!"), tr(body_text.toLocal8Bit().data()), QMessageBox::Ok);
        ui->spinBox_copiesToMake->setValue(0);
    }
    else
    {
        QMessageBox::warning(this, tr("Oops!"), tr("Please select ONE record to duplicate."), QMessageBox::Ok);
    }

}

void AdminPanel::on_pushButton_updateView_clicked()
{
    FilterTableView();
}

void AdminPanel::on_lineEdit_textChanged(const QString &arg1)
{
    if (ui->checkBox_updateViewAsIType->checkState() == Qt::Checked)
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
                ReloadBooksToView();
                ReloadLoansToView();
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
    ReloadBooksToView();
    ReloadLoansToView();
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
    ReloadBooksToView();
    ReloadLoansToView();
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


void AdminPanel::on_pushButton_submitChangesToDb_clicked()
{
    bool submissionState = pBookRecordModel_->submitAll();
    if (submissionState)
    {
        QMessageBox::information(this, tr("Done!"), tr("Successfully submitted all cached changes to the database!"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, tr("Error!"), tr("Something went wrong!"), QMessageBox::Ok);
    }
}

void AdminPanel::on_checkBox_submitChangesAutomatically_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        pBookRecordModel_->submitAll();
        pBookRecordModel_->select();
        pBookRecordModel_->setEditStrategy(QSqlTableModel::OnFieldChange);
    }
    else
    {
        pBookRecordModel_->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
}

void AdminPanel::on_pushButton_revertChanges_clicked()
{
    pBookRecordModel_->revertAll();
    QMessageBox::information(this, tr("Done!"), tr("Cleared all cached changes!"), QMessageBox::Ok);
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
    FilterTableView();
}

void AdminPanel::ShowWarnTickAtLeastOne()
{
    QMessageBox::warning(this, tr("Oops!"), tr("Please check at least one checkbox!"), QMessageBox::Ok);
}

void AdminPanel::UpdateOverdueRecordsToLabel()
{
    QSqlDatabase conn = QSqlDatabase::database("SLMS");
    QSqlTableModel *model = new QSqlTableModel(this, conn);
    model->setTable("loan_record");
    model->select();

    int num_records = -1;
    QSqlDatabase conn2 = QSqlDatabase::database("SLMS");
    QSqlQuery qry = QSqlQuery(conn2);
    if (qry.exec("SELECT COUNT(*) FROM loan_record"))
    {
        qry.first();
        num_records = qry.value(0).toInt();
        while (pLoanRecordModel_->canFetchMore())
               pLoanRecordModel_->fetchMore();
    }
    else
    {
        QMessageBox::warning(this, tr("Warning!"), tr("Could not fetch number of loan records from DB!"));
        return;
    }
    ui->label_numLoanRecords_var->setText(QString::number(num_records));
    if (num_records == 0)
    {
        ui->label_numOverdueLoanRecords_var->setText("0");
        return;
    }

    int overdue_count = 0;
    QDate today = QDate::currentDate();

    for (int i = 0; i < num_records; i++)
    {
        if (i%256==0 && model->canFetchMore())
            model->fetchMore();
        QModelIndex index_return_date = model->index(i, 4);
        QModelIndex hv_returned = model->index(i, 5);
        QDate return_date = QDate::fromString(index_return_date.data().toString(), "yyyyMMdd");
        if (return_date < today && hv_returned.data().toInt() == Return::NO)
        {
            qDebug() << "Checking" << i;
            overdue_count++;
        }
    }
    ui->label_numOverdueLoanRecords_var->setText(QString::number(overdue_count));
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
    ReloadLoansToView();
}

void AdminPanel::on_checkBox_highlight_onLoan_stateChanged(int arg1)
{
    pLoanRecordModel_->SetHightlightOnLoanEnabled(arg1 == Qt::Checked);
    ReloadLoansToView();
}

void AdminPanel::on_comboBox_qDateFormat_currentTextChanged(const QString &arg1)
{
    qDate_format_ = arg1.trimmed();
    ui->label_today->setText("Today: " + QDate::currentDate().toString(arg1));
    SyncQDateFormatToLRQSRTM();
    ReloadLoansToView();
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

