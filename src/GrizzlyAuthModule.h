
#ifndef GRIZZLYAUTH_H_
#define GRIZZLYAUTH_H_

#include <stdio.h>
#include <sys/time.h>
#include <sstream>
#include <cstdlib>

#include "mongoose/mongoose.h"
#include "hashLib++/src/hashlibpp.h"
#include "GrizzlyModule.h"
#include "tools/file.h"

using namespace std;

class GrizzlyAuthModule : public GrizzlyModule
{

private:
	map<string, session> sessions;
	string cssPath;
	string dataPath;
	string loginPageHeader;
	mg_connection* currConn;
	char buffer[512];

public:
	GrizzlyAuthModule();
	virtual ~GrizzlyAuthModule();

	void setCSSPath(string param);
	void setDataPath(string param);

	bool addAccount(string login, string password);
	session getSession();
	void deleteSession();

	std::string getModuleDescription(){ return "Login to Grizzly Manager";}
	std::string onRequest(const map<string, string>* query);
	void setCurrentConnection(mg_connection* conn);
	void init();

};

#endif /* GRIZZLYAUTH_H_ */
