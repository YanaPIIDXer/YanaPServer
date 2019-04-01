#include "WidnowsSocketBehaviour.h"

namespace YanaPServer
{
namespace Socket
{
namespace Behaviour
{

// �R���X�g���N�^
CWindowsSocketBehaviour::CWindowsSocketBehaviour()
	: bInitialized(false)
{
}

// �f�X�g���N�^
CWindowsSocketBehaviour::~CWindowsSocketBehaviour()
{
	Release();
}

// ������.
bool CWindowsSocketBehaviour::Initialize()
{
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 0), &WsaData);

	bInitialized = true;
	return true;
}

// ���.
void CWindowsSocketBehaviour::Release()
{
	if (!bInitialized) { return; }

	WSACleanup();

	bInitialized = false;
}

}
}
}
