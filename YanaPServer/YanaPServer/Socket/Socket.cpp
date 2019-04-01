#include "Socket.h"
#include "Behaviour/SocketBehaviour.h"

using namespace YanaPServer::Socket::Behaviour;

namespace YanaPServer
{
namespace Socket
{

// コンストラクタ
CSocket::CSocket()
{
}

// デストラクタ
CSocket::~CSocket()
{
	delete pBehaviour;
}

}
}
