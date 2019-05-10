#include <iostream>
#include "YanaPServer/Servlet/HttpServer.h"

using namespace YanaPServer::Servlet;

int main()
{
	std::cout << "Servlet Test" << std::endl;

	CHttpServer Server;
	Server.StartListen(4423);

	while (Server.Service());

	return 0;
}
