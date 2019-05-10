#include <iostream>
#include "YanaPServer/Servlet/HttpServer.h"
#include "YanaPServer/Servlet/Servlet.h"

using namespace YanaPServer::Servlet;
using namespace YanaPServer::Util::Stream;

class TestServlet : public IServlet
{

public:

	TestServlet() {}
	virtual ~TestServlet() {}

	virtual const char *GetPath() const { return "/"; }

	virtual void OnPost(const SHttpRequest &Request, CDynamicMemoryStreamWriter &ResponseStream) override
	{
		std::cout << "POST" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream.Serialize("POST OK.\n");
	}

	virtual void OnGet(const SHttpRequest &Request, CDynamicMemoryStreamWriter &ResponseStream) override
	{
		std::cout << "GET" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream.Serialize("GET OK.\n");
	}

	virtual void OnError(const SHttpRequest &Request, CDynamicMemoryStreamWriter &ResponseStream) override
	{
		std::cout << "ERROR" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream.Serialize("Error.\n");
	}

};

int main()
{
	std::cout << "Servlet Test" << std::endl;

	TestServlet Servlet;
	CHttpServer Server;
	Server.AddServlet(&Servlet);

	Server.StartListen(4423);

	while (Server.Service());

	return 0;
}
