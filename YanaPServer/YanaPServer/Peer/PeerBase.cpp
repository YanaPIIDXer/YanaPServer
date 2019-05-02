#include "PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

// �R���X�g���N�^
CPeerBase::CPeerBase(ISocket *pInSocket)
	: pSocket(pInSocket)
{
}

// �f�X�g���N�^
CPeerBase::~CPeerBase()
{
	ReleaseSocket();
}


// �\�P�b�g���.
void CPeerBase::ReleaseSocket()
{
	if (pSocket == nullptr) { return; }

	pSocket->Release();
	delete pSocket;
	pSocket = nullptr;
}

}
}
