#pragma once

#include <QThread>

/**
 * @brief Asynchronously processes payroll
 */
class PayrollProcessor : public QThread
{
    Q_OBJECT
private:
    bool _go = true;
    void run() override;
public:
    PayrollProcessor(QObject* parent = nullptr);
    ~PayrollProcessor() override;
    PayrollProcessor(const PayrollProcessor&) = delete;
    PayrollProcessor& operator=(const PayrollProcessor&) = delete;

    void stopProcessing();
};
