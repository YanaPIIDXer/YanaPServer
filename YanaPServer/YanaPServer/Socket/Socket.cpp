#include "Socket.h"
#include "Behaviour/SocketBehaviour.h"

using namespace YanaPServer::Socket::Behaviour;

namespace YanaPServer
{
namespace Socket
{

// �R���X�g���N�^
CSocket::CSocket()
{
}

// �f�X�g���N�^
CSocket::~CSocket()
{
	delete pBehaviour;
}

}
}
