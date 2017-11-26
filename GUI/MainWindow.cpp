#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnBottomHint
                       | Qt::MSWindowsFixedSizeDialogHint);
    this->setMinimumSize(size());
    this->setMaximumSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWaitingMode(const bool mode)
{
    ui->makeTransactionButton->setDisabled(mode);
    ui->refreshButton->setDisabled(mode);
    ui->settingsButton->setDisabled(mode);
}

void MainWindow::setLoggedInCard(const quint64 cardNumber)
{
    ui->loggedInCardValueLabel->setText(QString::number(cardNumber));
}

void MainWindow::requestForAccInfo()
{
    setWaitingMode(true);
    QList<QListWidgetItem*> cards = ui->cardsView->selectedItems();
    if (cards.empty())
    {
        // qDebug("Default");
        emit callForAccMoney(ui->loggedInCardValueLabel->text().toULongLong());
    }
    else
    {
        // qDebug("NDefault");
        emit callForAccMoney(cards.first()->text().toULongLong());
        // qDebug(cards.first()->text().toStdString().c_str());
    }
}

void MainWindow::requestForCards()
{
    setWaitingMode(true);
    emit callForAccCards();
}

void MainWindow::requestForTransaction()
{
    setWaitingMode(true);
    emit callForTransaction();
}

void MainWindow::requestForQuit()
{
    exit(0);
}

void MainWindow::reactGotAccMoney(quint64 money)
{
    ui->accMoneyValueLabel->setText(QString::number(money));
    qDebug("Got acc money");

    QList<QListWidgetItem*> cards = ui->cardsView->selectedItems();
    if (cards.empty())
    {
        emit callForPayments(ui->loggedInCardValueLabel->text().toULongLong());
    }
    else
    {
        emit callForPayments(cards.first()->text().toULongLong());
    }
}

void MainWindow::reactGotAccCards(QMap<quint64, quint8>& cards)
{
    QMapIterator<quint64, quint8> iter(cards);
    while (iter.hasNext())
    {
        iter.next();
        QString str = QString::number(iter.key());
        ui->cardsView->addItem(str);
    }

    setWaitingMode(false);
}

void MainWindow::reactGotPaymentsAmount(unsigned amount)
{
    // TODO: Show all payments info.
    QString str("Your number of payments: ");
    QMessageBox::information(this, "Information",
                             str.append(QString::number(amount)));
    setWaitingMode(false);
}

void MainWindow::reactError(QString info)
{
    QMessageBox::information(this, "Error", info);
    setWaitingMode(false);
}

void MainWindow::reactOnCardClicked()
{
    QString card(ui->cardsView->selectedItems().first()->text());

}
