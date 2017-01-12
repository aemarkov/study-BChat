#pragma once

#include "IUserManager.h"
#include "UserManagerCreator.h"
#include "util\Singleton\SingletonContainer.h"
using namespace std;

class UserManagerContainer : public SingletonContainer<IUserManager, UserManagerCreator>
{	
};

