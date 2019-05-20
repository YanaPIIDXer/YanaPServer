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

	virtual void OnPost(const SHttpRequest &Request, CStringStream &ResponseStream) override
	{
		std::cout << "POST" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream.Append("POST OK.\n");
	}

	virtual void OnGet(const SHttpRequest &Request, CStringStream &ResponseStream) override
	{
		std::cout << "GET" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		//ResponseStream.Append("GET OK.\n");
		// POSTテスト用にHTMLを構築。
		ResponseStream.Append("<html>\n");
		ResponseStream.Append("<head>\n");
		ResponseStream.Append("<title>TestPage</title>\n");
		ResponseStream.Append("</head>\n");
		ResponseStream.Append("<body>\n");
		ResponseStream.Append("<form action=\"./\" method=\"POST\">\n");
		ResponseStream.Append("	<input type=\"submit\" value=\"POST\">\n");
		ResponseStream.Append("</form>\n");
		ResponseStream.Append("</body>\n");
		ResponseStream.Append("</html>\n");
	}

	virtual void OnError(const SHttpRequest &Request, CStringStream &ResponseStream) override
	{
		std::cout << "ERROR" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream.Append("Error.\n");
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
