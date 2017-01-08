#include "UserManagerCreator.h"



UserManagerCreator::UserManagerCreator()
{
}


UserManagerCreator::~UserManagerCreator()
{
}

UserManager * UserManagerCreator::Create()
{
	return new UserManager();
}
