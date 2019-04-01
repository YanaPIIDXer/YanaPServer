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
	if (bInitialized)
	{
		// ��U���.
		Release();
	}

	WSADATA WsaData;
	int Result = WSAStartup(MAKEWORD(2, 0), &WsaData);
	if (Result != 0) { return false; }

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
