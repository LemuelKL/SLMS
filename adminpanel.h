#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <comboboxdelegate.h>
#include <bookrecordqsqlrelationaltablemodel.h>
#include <qubyxsearchfilterproxymodel.h>
#include <loanrecordqsqlrelationaltablemodel.h>
#include <bookcoverdownloader.h>

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QButtonGroup>
#include <QSortFilterProxyModel>

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);
    ~AdminPanel();

    enum BookRecordTableViewColumns
    {
        ID = 0,
        ISBN13,
        TITLE,
        AUTHOR,
        CATEGORY,
        STATUS
    };

    enum LoanRecordTableViewColumns
    {
        RECORD_ID = 0,
        BOOK_ID,
        PERSON_ID,
        LOAN_DATE,
        DUE_DATE,
        HAVE_RETURNED
    };

signals:
    void FetchFailed(QString description);
    void FetchNumBookSuccess(int num);
    void FetchNumLoanSuccess(int num);
    void FetchNumOverdueSuccess(int num);

public slots:
    void ReceiveLogin(QString username);

    void HandleDataChanged();

    void HandleDataIsEmpty(QModelIndex);

    void HandleInvalidIsbn();

    void ReceivePersonId(QString);

    void ReceiveBookId(QString);

    void ReceiveAddBookRequest(QString, QString, QString, int, int, int);

    void ReceiveEditBookRequest(QString, QString, QString, int, int, int);

private slots:
    void on_pushButton_addBook_clicked();

    void on_pushButton_reloadBook_clicked();

    void on_pushButton_deleteRecords_clicked();

    void on_pushButton_updateView_clicked();

    void FilterTableView();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_loan_clicked();

    void on_pushButton_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_editPersonId_clicked();

    void on_pushButton_editBookId_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_reloadLoans_clicked();

    void on_checkBox_filter_loanRecord_overdue_stateChanged(int arg1);

    void on_checkBox_updateViewAsIType_stateChanged(int arg1);

    void on_checkBox_filter_caseSensitive_stateChanged(int arg1);

    void on_checkBox_filter_loanRecord_onLoan_stateChanged(int arg1);

    void on_checkBox_highlight_overdue_stateChanged(int arg1);

    void on_checkBox_highlight_onLoan_stateChanged(int arg1);

    void on_comboBox_qDateFormat_currentTextChanged(const QString &arg1);

    void on_checkBox_readOnly_stateChanged(int arg1);

    void on_pushButton_editBook_clicked();

    bool RefreshBookTab();
    bool RefreshLoanTab();

    void HandleFailedFetch(QString desciprtion);
    void UpdateNumBookToLabel(int num);
    void UpdateNumLoanToLabel(int num);
    void UpdateNumOverdueToLabel(int num);

    void DownloadBookCover(QString isbn13);

    void UpdateSearchNumLabel();

private:
    Ui::AdminPanel *ui;

    ComboBoxDelegate *pCbD_;
    QModelIndex last_index_;

    BookRecordQSqlRelationalTableModel *pBookRecordModel_;
    QubyxSearchFilterProxyModel *pBookRecordSearchProxyModel_;

    LoanRecordQSqlRelationalTableModel *pLoanRecordModel_;
    QubyxSearchFilterProxyModel *pLoanRecordSearchProxyModel_;

    QButtonGroup *book_records_filters_;
    QButtonGroup *loan_records_filters_;

    QString qDate_format_;

    void ShowWarnTickAtLeastOne();
    void SyncQDateFormatToLRQSRTM();
    void RemoveSelectedRows();
    void keyPressEvent(QKeyEvent *event);

    bool NoCheckedCheckbox(QButtonGroup *button_group);

    void ReloadNumBook();
    void ReloadNumLoan();
    void ReloadNumOverdue();

    bool only_search_in_current_view_;
    bool force_ignore_search_term;

    void CreateBookCoverFolderIfNotExist();
};

#endif // ADMINPANEL_H
