#include <iostream>
#include "YanaPServer/Servlet/HttpServer.h"
#include "YanaPServer/Servlet/ServletEvent.h"

using namespace YanaPServer::Servlet;

class TestServletEvent : public IServletEvent
{

public:

	TestServletEvent() {}
	virtual ~TestServletEvent() {}

	virtual void OnPost() override
	{

	}

	virtual void OnGet() override
	{

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
