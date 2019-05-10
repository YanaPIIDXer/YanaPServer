#include <iostream>
#include "YanaPServer/Servlet/HttpServer.h"
#include "YanaPServer/Servlet/Servlet.h"

using namespace YanaPServer::Servlet;

class TestServletEvent : public IServlet
{

public:

	TestServletEvent() {}
	virtual ~TestServletEvent() {}

	virtual void OnPost(const SHttpRequest &Request, std::stringstream &ResponseStream) override
	{
		std::cout << "POST" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream << "POST OK." << std::endl;
	}

	virtual void OnGet(const SHttpRequest &Request, std::stringstream &ResponseStream) override
	{
		std::cout << "GET" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream << "GET OK." << std::endl;
	}

	virtual void OnError(const SHttpRequest &Request, std::stringstream &ResponseStream) override
	{
		std::cout << "ERROR" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream << "Error." << std::endl;
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
