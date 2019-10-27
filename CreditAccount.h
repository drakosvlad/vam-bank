#pragma once
#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<5, 0, 0, false> SavingsAccountPolicy;
typedef AccountModel<SavingsAccountPolicy> SavingsAccount;
