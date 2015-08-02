#include "transactiondescdialog.h"
#include "ui_transactiondescdialog.h"

#include "transactiontablemodel.h"

#include <QModelIndex>
#include <QDesktopServices>

TransactionDescDialog::TransactionDescDialog(const QModelIndex &idx, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionDescDialog)
{
    int newSize;

    ui->setupUi(this);
    QString desc = idx.data(TransactionTableModel::LongDescriptionRole).toString();

    txId = idx.data(TransactionTableModel::TxIDRole).toString();
    newSize = txId.size();
    if (newSize >= 4)
        newSize -= 4;
    else
        newSize = 0;
    txId.resize(newSize);

    ui->detailText->setHtml(desc);
}

TransactionDescDialog::~TransactionDescDialog()
{
    delete ui;
}

void TransactionDescDialog::on_showTxDetails_clicked()
{
    QString url;
    if (!txId.isNull() && !txId.isEmpty())
        url = "http://securechain.info/en/tx/" + txId;
    QDesktopServices::openUrl(QUrl(url));
}
