#pragma once

/**
 * @brief Account fee policy
 */
template<int AcceptFee, int TransferFee, int PaymentFee, bool IsPaymentAccount, short AccountType>
struct AccountPolicy
{
    static const bool _isPaymentAccount = IsPaymentAccount;

    static int transferFee(int amount) {
        return amount * TransferFee / 100;
    }

    static int paymentFee(int amount)
    {
        return amount * PaymentFee / 100;
    }

    static int acceptFee(int amount)
    {
        return amount * AcceptFee / 100;
    }

    static const short _accountType = AccountType;
};
