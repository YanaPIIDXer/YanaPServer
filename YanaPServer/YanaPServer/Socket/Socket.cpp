#include "Socket.h"
#include "Behaviour/SocketBehaviour.h"
#include "Behaviour/WidnowsSocketBehaviour.h"
#include "Behaviour/NullSocketBehaviour.h"

using namespace YanaPServer::Socket::Behaviour;

namespace YanaPServer
{
namespace Socket
{

// �R���X�g���N�^
CSocket::CSocket()
	: pBehaviour(NULL)
{
}

// �f�X�g���N�^
CSocket::~CSocket()
{
	ReleaseBehaviour();
}


// �����C���^�t�F�[�X�̐���.
void CSocket::CreateBehaviour()
{
#ifdef _WIN32
	pBehaviour = new CWindowsSocketBehaviour();
#else
	pBehaviour = new CNullSocketBehaviour();
#endif
}

// �����C���^�t�F�[�X�̉��.
void CSocket::ReleaseBehaviour()
{
	if (pBehaviour == NULL) { return; }

	pBehaviour->Release();
	delete pBehaviour;
	pBehaviour = NULL;
}

}
}
