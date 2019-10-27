#pragma once
#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<0, 10, 5, false> SavingsAccountPolicy;
typedef AccountModel<SavingsAccountPolicy> SavingsAccount;
