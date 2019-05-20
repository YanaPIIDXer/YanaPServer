#include "Peer/PeerBase.h"

namespace YanaPServer
{
namespace Peer
{

using namespace YanaPServer::Socket;

// �R���X�g���N�^
CPeerBase::CPeerBase(YanaPServer::Socket::ISocket *pInSocket)
	: pSocket(pInSocket)
	, bDisconnect(false)
{
	pSocket->SetEventListener(this);
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

	if (bDisconnect)
	{
		ReleaseSocket();
	}
}

// �\�P�b�g�C�x���g���I�[�o�[���C�h����C�x���g���X�i���Z�b�g
void CPeerBase::SetOverrideEventListener(ISocketEventListener *pListener)
{
	pSocket->SetEventListener(pListener);
}

// ���M.
void CPeerBase::Send(const char *pData, unsigned int Size)
{
	if (!IsValid()) { return; }

	pSocket->Send(pData, Size);
}

// �ؒf.
void CPeerBase::Disconnect()
{
	// Socket��Poll�������ɐؒf�����\��������̂ŁA
	// ����̂͂����Ƀt���O�������ĂĂ����B
	// Poll������A�ؒf�t���O�������Ă���Ή�́B
	bDisconnect = true;
}


// �\�P�b�g���.
void CPeerBase::ReleaseSocket()
{
	if (pSocket == nullptr) { return; }

	pSocket->Release(ESocketDisconnectReason::Destruct);
	delete pSocket;
	pSocket = nullptr;
}

}
}
