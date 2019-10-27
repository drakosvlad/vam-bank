#pragma once
#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<0, 1, 0, false> SavingsAccountPolicy;
typedef AccountModel<SavingsAccountPolicy> SavingsAccount;
