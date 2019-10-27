#include <vector>
#include "IUser.h"
#include "IAccount.h"
#include "ITransaction.h"

/**
 * Singleton class that provides a global storage for all bank data
 */
class Storage
{
private:
  Storage() {  }

  std::vector<IUser> _users;
  std::vector<IAccount> _accounts;
  std::vector<ICard> _cards;
  std::vector<ITransaction> _transactions;

  Storage* _instance = nullptr;
public:
  Storage& getInstance();

  IUser& getUser(const std::string login);
  IAccount& getAccount(const size_t id);
  ICard& getCard(const std::array<unsigned char, 16> number);
  
  const std::vector<IUser>& getUsers();
  const std::vector<IAccount>& getAccounts();
  const std::vector<ICard>& getCards();
  const std::vector<ITransaction>& getTransactions();

  void addUser(IUser& user);
  void addAccount(IAccount& account);
  void addCard(ICard& card);
  void addTransaction(ITransaction& transaction);

  void removeUser(const std::string login);
  void removeAccount(const size_t id);
  void removeCard(const std::array<unsigned char, 16> number);
};
