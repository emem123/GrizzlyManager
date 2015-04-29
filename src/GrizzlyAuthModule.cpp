
#include "GrizzlyAuthModule.h"

const string accountsFilePath = "../system/accounts";
string trufflePath;

GrizzlyAuthModule::GrizzlyAuthModule(){
	name = "Login";
	slug = "";
}

GrizzlyAuthModule::~GrizzlyAuthModule(){

}

void GrizzlyAuthModule::init()
{
	char* cwd = getcwd(NULL, 0);
	trufflePath = cwd;
	trufflePath += "/truffle";
	loginPageHeader = gz::readTextFile("../data/login.html");

	int occurence = loginPageHeader.find("&css",0);

	if(occurence != -1)
		loginPageHeader.replace(occurence,4, cssPath);

}

string hashMD5(string inputString)
{
	string ret = "";
	hashwrapper *h = new md5wrapper();
	h->test();
	ret = h->getHashFromString(inputString);
	return ret;
}

string hashMD5(string inputString, unsigned int numOfChars)
{
	string ret = "";
	hashwrapper *h = new md5wrapper();
	h->test();
	ret = h->getHashFromString(inputString);
	if(ret.length() < numOfChars)
		return ret;
	else
		return ret.substr(0, numOfChars);
}

session login(string login, string password)
{
	session ret;
	string hashedPswd = hashMD5(password);
	list<string> accounts = gz::readTextFileLines(accountsFilePath);
	vector<string> splittedItems;
	list<string>::iterator accountsIt;
	timeval currTime;

	for(accountsIt = accounts.begin();accountsIt != accounts.end();accountsIt++)
	{
		splittedItems = gz::split((*accountsIt), " ");
		if(splittedItems[0].compare(login) == 0)
		{
			if(splittedItems[1].compare(hashedPswd) == 0)
			{
				gettimeofday(&currTime, NULL);
				ret.login = login;
				ret.timeStamp = (currTime.tv_sec*1000) + (currTime.tv_usec / 1000);
				return ret;
			}
		}
	}
	return ret;
}

string generateTruffle()
{
	stringstream ss;
	string truffle;

	srand(time(NULL));
	ss << rand() % 10000 +1;
	truffle = hashMD5(ss.str(), 16);

	return truffle;
}

bool GrizzlyAuthModule::addAccount(string login, string password)
{
	string hashed = hashMD5(password);
	list<string> accounts = gz::readTextFileLines(accountsFilePath);
	vector<string> splittedItems;
	list<string>::iterator accountsIt;

	for(accountsIt = accounts.begin();accountsIt != accounts.end();accountsIt++)
	{
		splittedItems = gz::split((*accountsIt), " ");
		if(splittedItems.front().compare(login) == 0)
			return false;
	}
	std::ofstream outFile;

	outFile.open(accountsFilePath.c_str(), std::ios_base::app);
	outFile << login << " " << hashed << "\n";

	outFile.close();
	return true;
}

std::string GrizzlyAuthModule::onRequest(const map<string, string>* query)
{
	string name, pass;
	const char* cookies_ptr;
	session logged;
	string res = loginPageHeader;
	string truffle;
	string cookie;
	size_t found;

	buffer[0] = '\0';

	mg_get_var(currConn, "login", buffer, 512);
	name = buffer;

	mg_get_var(currConn, "password", buffer, 512);
	pass = buffer;

	logged = login(name, pass);

	cookies_ptr = mg_get_header(currConn, "Cookie");

	if(cookies_ptr != NULL)
	{
		cookie = cookies_ptr;
		if(!cookie.empty())
		{
			found = cookie.find("truffle=");
			if(found != string::npos)
			{
				cookie = cookie.substr(found + 8, 16);
				if(sessions.find(cookie) != sessions.end())
					res += "<script language=\"javascript\" type=\"text/javascript\">window.location.assign(\"main\")</script>";
			}
		}
	}

	if(!name.empty() && logged.login.empty())
		res += "<login_failed_string>Login failed! Try again.</login_failed_string>";
	else if(!logged.login.empty())
	{
		truffle = generateTruffle();

		sessions[truffle] = logged;
		mg_printf(currConn, "HTTP/1.1 301 Moved Permanently\r\n"
				"Location: /main\r\n"
				"Set-Cookie: truffle=%s;\r\n\r\n", truffle.c_str());
	}

	res += "<input class=\"login_button\" type=\"submit\" name=\"submit\" id=\"submit\" value=\"LOGIN\">";
	res += "</form></div></body></html>";

	return res;
}

session GrizzlyAuthModule::getSession()
{
	session ret;
	string cookie;
	size_t found;
	const char* cookies_ptr;

	cookies_ptr = mg_get_header(currConn, "Cookie");

	if(cookies_ptr != NULL)
	{
		cookie = cookies_ptr;
		if(!cookie.empty())
		{
			found = cookie.find("truffle=");
			if(found != string::npos)
			{
				cookie = cookie.substr(found + 8, 16);
				if(!cookie.empty())
					if(sessions.find(cookie) != sessions.end())
						return sessions.at(cookie);
			}
		}
	}

	return ret;
}

void GrizzlyAuthModule::deleteSession()
{
	string cookie;
	size_t found;

	cookie = mg_get_header(currConn, "Cookie");
	found = cookie.find("truffle=");
	cookie = cookie.substr(found + 8, 16);

	if(sessions.find(cookie) != sessions.end())
		sessions.erase(cookie);
}

void GrizzlyAuthModule::setCurrentConnection(mg_connection* conn)
{
	currConn = conn;
}

void GrizzlyAuthModule::setCSSPath(string param)
{
	cssPath = param;
}

void GrizzlyAuthModule::setDataPath(string param)
{
	dataPath = param;
}
