#include <iostream>
#include "YanaPServer/Servlet/HttpServer.h"
#include "YanaPServer/Servlet/Servlet.h"
#include "YanaPServer/Servlet/HttpServerEvent.h"

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
		ResponseStream.AppendLine("POST OK.");
	}

	virtual void OnGet(const SHttpRequest &Request, CStringStream &ResponseStream) override
	{
		// POSTテスト用にHTMLを構築。
		ResponseStream.AppendLine("<html>");
		ResponseStream.AppendLine("<head>");
		ResponseStream.AppendLine("<title>TestPage</title>");
		ResponseStream.AppendLine("</head>");
		ResponseStream.AppendLine("<body>");
		ResponseStream.AppendLine("<form action=\"./\" method=\"POST\">");
		ResponseStream.AppendLine("	<input type=\"submit\" value=\"POST\">");
		ResponseStream.AppendLine("</form>");
		ResponseStream.AppendLine("</body>");
		ResponseStream.AppendLine("</html>");
	}

	virtual void OnError(const SHttpRequest &Request, CStringStream &ResponseStream) override
	{
		std::cout << "ERROR" << std::endl;
		std::cout << "Path:" << Request.Path << std::endl;

		ResponseStream.Append("Error.\n");
	}

};

// HTTPサーバイベント
class TestHttpServerEvent : public IHttpServerEvent
{

public:

	// コンストラクタ
	TestHttpServerEvent() {}

	// デストラクタ
	virtual ~TestHttpServerEvent() {}

	// エラー
	virtual void OnError(const SHttpRequest & Request, YanaPServer::Util::Stream::CStringStream & ResponseStream) override
	{
		ResponseStream.Append("TestHttpServerEvent::OnError()");
	}

	// NotFound
	virtual void OnNotFound(const SHttpRequest & Request, YanaPServer::Util::Stream::CStringStream & ResponseStream) override
	{
		ResponseStream.Append("TestHttpServerEvent::OnNotFound()");
	}

};

int main()
{
	std::cout << "Servlet Test" << std::endl;

	TestServlet Servlet;
	TestHttpServerEvent ServerEvent;
	CHttpServer Server(&ServerEvent);
	Server.AddServlet(&Servlet);

	Server.StartListen(4423);

	while (Server.Service());

	return 0;
}
