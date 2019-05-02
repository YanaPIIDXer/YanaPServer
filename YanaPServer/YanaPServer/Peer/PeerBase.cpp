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

// ���t���[���̏���.
void CPeerBase::Poll()
{
	if (!IsValid()) { return; }

	pSocket->Poll();
}

// ���M
void CPeerBase::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return; }

	pSocket->Send(pData, Size);
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
