#include "Peer/PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

using namespace YanaPServer::Socket;

// �R���X�g���N�^
CPeerBase::CPeerBase(YanaPServer::Socket::ISocket *pInSocket)
	: pSocket(pInSocket)
{
	pSocket->SetEventListener(this);
}

// �f�X�g���N�^
CPeerBase::~CPeerBase()
{
	if (pSocket == nullptr) { return; }

	pSocket->Release(ESocketDisconnectReason::Destruct);
	delete pSocket;
	pSocket = nullptr;
}

// ���t���[���̏���.
void CPeerBase::Poll()
{
	if (!IsValid()) { return; }

	pSocket->Poll();
}

// �\�P�b�g�C�x���g���I�[�o�[���C�h����C�x���g���X�i���Z�b�g
void CPeerBase::SetOverrideEventListener(ISocketEventListener *pListener)
{
	pSocket->SetEventListener(pListener);
}

// ���M
void CPeerBase::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return; }

	pSocket->Send(pData, Size);
}

}
}
