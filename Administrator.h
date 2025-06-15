#pragma once
#include "User.h"
 
class Administrator : public NormalUser {
private:
	int adminKey = 0;

public:
	Administrator() = default;
	Administrator(const String& username, const String& password, int key);
	int getKey() const override;
	NormalUser* clone() const override;
};