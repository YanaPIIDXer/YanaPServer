#include <iostream>
#include "YanaPServer/Servlet/HttpServer.h"
#include "YanaPServer/Servlet/ServletEvent.h"

using namespace YanaPServer::Servlet;

class TestServletEvent : public IServletEvent
{

public:

	TestServletEvent() {}
	virtual ~TestServletEvent() {}

	virtual void OnPost(const SHttpRequest &Request) override
	{
		std::cout << "POST" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;
	}

	virtual void OnGet(const SHttpRequest &Request) override
	{
		std::cout << "GET" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;
	}

	virtual void OnError(const SHttpRequest &Request) override
	{
		std::cout << "ERROR" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;
	}

};

int main()
{
	std::cout << "Servlet Test" << std::endl;

	TestServletEvent Event;
	CHttpServer Server(&Event);
	Server.StartListen(4423);

	while (Server.Service());

	return 0;
}
