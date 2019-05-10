#include "Servlet/HttpServer.h"

using namespace YanaPServer::Peer;

// コンストラクタ
CHttpServer::CHttpServer()
	: CApplicationBase([](PeerPtr pPeer) {})
{
}

// デストラクタ
CHttpServer::~CHttpServer()
{
}
