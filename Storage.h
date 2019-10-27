#include <vector>
#include "UserModel.h"
#include "AccountModel.h"
#include "TransactionModel.h"

/**
 * Singleton class that provides a global storage for all bank data
 */
class Storage
{
private:
  Storage() {  }

  std::vector<UserModel> _users;
  std::vector<AccountModel> _accounts;
  std::vector<CardModel> _cards;
  std::vector<TransactionModel> _transactions;

  Storage* _instance = nullptr;
public:
  Storage& getInstance();

  IUser& getUser(const std::string login);
  IAccount& getAccount(const size_t id);
  ICard& getCard(const std::array<unsigned char, 16> number);
  
  const IUser** getUsers();
  const IAccount** getAccounts();
  const ICard** getCards();
  const ITransaction** getTransactions();

  void addUser(IUser& user);
  void addAccount(IAccount& account);
  void addCard(ICard& card);
  void addTransaction(ITransaction& transaction);

  void removeUser(const std::string login);
  void removeAccount(const size_t id);
  void removeCard(const std::array<unsigned char, 16> number);
};
