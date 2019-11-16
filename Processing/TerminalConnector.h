#pragma once

#include <QThread>
#include <QSerialPort>

class IAccount;

class TerminalConnector : public QThread
{
    Q_OBJECT
private:
    static const QString MALFORMED_MESSAGE;
    static const QString FAILURE_MESSAGE;

    static const QString TRANSACTION_PENDING;
    static const QString TRANSACTION_SUCCEEDED;
    static const QString TRANSACTION_FAILED;

    QString _portName;
    const IAccount& _ownerAccount;
    bool _run = true;

    void run() override;

    const QString processMessage(const QString &message);

    const QString processCheckCardCommand(const QString &command);
    const QString processCreateTransactionCommand(const QString &command);
    const QString processGetTransactionStatusCommand(const QString &command);
    void sendResponse(QSerialPort& port, const QString& response);
public:
    TerminalConnector(const QString& portName, const IAccount& ownerAccount, QObject *parent = nullptr);
    ~TerminalConnector() override;

    void stopProcessing() { _run = false; }
signals:
      void transaction(size_t fromAccount, size_t toAccount, int amount, size_t transactionId);
      void close(const QString& close);
};
