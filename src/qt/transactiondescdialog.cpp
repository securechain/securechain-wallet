// Copyright (c) 2011-2013 The Bitcoin developers
// Copyright (c) 2015-2018 The Securechain developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "transactiondescdialog.h"
#include "ui_transactiondescdialog.h"

#include "transactiontablemodel.h"

#include <QModelIndex>
#include <QDesktopServices>
#include <QUrl>

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
