#pragma once
#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<0, 1, 0, false> DebitAccountPolicy;
typedef AccountModel<DebitAccountPolicy> DebitAccount;
