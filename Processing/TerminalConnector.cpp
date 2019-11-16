#include "TerminalConnector.h"

#include <QDebug>

#include "TransactionQueue.h"
#include <Account/IAccount.h>
#include <Card/ICard.h>
#include <Database/Storage.h>
#include "StringUtils.h"

const QString TerminalConnector::MALFORMED_MESSAGE("MF");
const QString TerminalConnector::FAILURE_MESSAGE("F");

const QString TerminalConnector::TRANSACTION_PENDING("P");
const QString TerminalConnector::TRANSACTION_FAILED("F");
const QString TerminalConnector::TRANSACTION_SUCCEEDED("S");

TerminalConnector::TerminalConnector(
        const QString& portName,
        const IAccount& ownerAccount,
        QObject* parent
    ) : QThread(parent), _portName(portName), _ownerAccount(ownerAccount)
{

}

TerminalConnector::~TerminalConnector()
{

}

void TerminalConnector::run()
{
    QSerialPort port;
    port.setPortName(_portName);
    port.setBaudRate(9600);
    port.setReadBufferSize(1024);

    if (!port.open(QIODevice::ReadWrite)) {
        emit close(tr("Can't open %1, error code %2")
                 .arg(_portName).arg(port.error()));
        qDebug() << "Error opening port!";
        return;
    }

    QByteArray buf;

    while (port.isOpen() && _run)
    {
        port.waitForReadyRead();
        buf.append(port.readAll());
        if (buf.contains('\n')) {
            QString message(buf.left(buf.indexOf('\n') + 1));
            buf.remove(0, buf.indexOf('\n') + 1);
            message.chop(2);
            sendResponse(port, processMessage(message));
        }
    }

    emit close(tr("Port %1 was closed").arg(_portName));
}

const QString TerminalConnector::processMessage(const QString& message)
{
    if (message.startsWith("TR")) {
        return processCreateTransactionCommand(message);
    }

    if (message.startsWith("CH")) {
        return processGetTransactionStatusCommand(message);
    }

    if (message.startsWith("CC")) {
        return processCheckCardCommand(message);
    }

    return MALFORMED_MESSAGE;
}

const QString TerminalConnector::processCreateTransactionCommand(const QString &command)
{
    QStringList commandParts(command.split('/'));

    if (commandParts.length() != 4 || commandParts[1].length() != 14 || commandParts[3].length() != 4)
        return MALFORMED_MESSAGE;

    // TODO Refactor this code into template
    const auto cardId(hexQStringToStdArray<7>(commandParts[1]));
    const int amount = commandParts[2].toInt();
    const auto cardPin(qStringToStdArray<4>(commandParts[3]));

    const ICard * card = Storage::getInstance().getCard(cardId);

    // Retrieve card
    if (card == nullptr)
        return FAILURE_MESSAGE;

    if (!card->verifyPin(cardPin))
        return FAILURE_MESSAGE;

    const size_t transactionId(Storage::getInstance().getNextTransactionId());
    TransactionQueue::getInstance().receiveTransaction(const_cast<IAccount *>(card->getAccount()), const_cast<IAccount *>(&_ownerAccount), amount, transactionId);

    return QString::number(transactionId);
}

const QString TerminalConnector::processCheckCardCommand(const QString &command)
{
    QStringList commandParts(command.split('/'));
    if (commandParts.length() != 2)
        return MALFORMED_MESSAGE;

    const auto cardId(hexQStringToStdArray<7>(commandParts[1]));
    const ICard * card = Storage::getInstance().getCard(cardId);

    return card == nullptr ? TRANSACTION_FAILED : TRANSACTION_SUCCEEDED;
}

const QString TerminalConnector::processGetTransactionStatusCommand(const QString &command)
{
    QStringList commandParts(command.split('/'));
    if (commandParts.length() != 2)
        return MALFORMED_MESSAGE;

    const size_t transactionId(commandParts[1].toUInt());
    auto status = TransactionQueue::getInstance().getTransactionStatus(transactionId);

    switch (status) {
        case TransactionStatus::Pending:
            return TRANSACTION_PENDING;
        case TransactionStatus::Failed:
            return TRANSACTION_FAILED;
        case TransactionStatus::Succeeded:
            return TRANSACTION_SUCCEEDED;
    }

    return "";
}

void TerminalConnector::sendResponse(QSerialPort& port, const QString& response)
{
    port.write((response + "\r\n").toLatin1());
}
