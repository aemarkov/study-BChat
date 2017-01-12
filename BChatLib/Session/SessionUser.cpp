#include "SessionUser.h"

/*SessionUser::SessionUser()
{
}*/

SessionUser::SessionUser(User user, INetwork * client)
{
	this->client = client;
	this->user = user;;
}
