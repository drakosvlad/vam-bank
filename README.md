# Vam Bank

University project created by Bohdana Poberezhets, Vladyslav Bozhko and Vladyslav Zhulkevskyi


Vam Bank is a model of a bank information system. It's key features include:
- Support for multiple simultaneous client sessions
- Different bank account types with interest rates and transactions fees
- Thread-safe transactions processing
- Integration with our custom-made wireless POS Terminal with support for NFC cards

![Transaction menu screenshot](https://raw.githubusercontent.com/drakosvlad/vam-bank/master/Repository/main-menu.png)

*Transaction menu screenshot*

Supported bank account types:
- Debit (No top-up fee, 1% transfer fee, no in-store payment fee)
- Credit (30 days grace period, 3% monthly rate / No top-up fee, 5% transfer fee, no in-store payment fee)
- Savings (2% monthly rate / No top-up fee, 10% transfer fee, 5% in-store payment fee)
- Several system accounts for processing fees and savings

## Architecture

![Class diagram](https://raw.githubusercontent.com/drakosvlad/vam-bank/master/Repository/architecture.png)

*Class diagram*

The transaction processing, interest calculation and POS Terminal integrations are performed in separate threads. The transaction queue is processed sequentially, in one thread, so that the transactions can't conflict with each other. 

For data persistence we are using Proxy-Model architecture – read requests are handled by data models, while write requests are forwarded to the database service.

For calculating different fees for the transactions between the accounts of different types, we are using the templates specified with Policy classes that handle the fees calculation.
