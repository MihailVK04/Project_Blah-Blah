#include "Administrator.h"

Administrator::Administrator(const String& username, const String& password, int key) : NormalUser(username,password)
{
	adminKey = key;
}

int Administrator::getKey() const
{
	return adminKey;
}

NormalUser* Administrator::clone() const
{
	return new Administrator(*this);
}
