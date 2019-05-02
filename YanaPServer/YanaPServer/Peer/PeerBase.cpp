#include "PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

// �R���X�g���N�^
PeerBase::PeerBase(ISocket *pInSocket)
	: pSocket(pInSocket)
{
}

// �f�X�g���N�^
PeerBase::~PeerBase()
{
	ReleaseSocket();
}


// �\�P�b�g���.
void PeerBase::ReleaseSocket()
{
	if (pSocket == nullptr) { return; }

	pSocket->Release();
	delete pSocket;
	pSocket = nullptr;
}

}
}
