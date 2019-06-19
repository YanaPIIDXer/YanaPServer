#include "Servlet/HttpSession.h"
#include "Util/CSVController.h"
#include "Util/RandomString.h"
#include <direct.h>

using namespace YanaPServer::Util;

namespace YanaPServer
{
namespace Servlet
{

const std::string CHttpSession::FileDirectory = "Session/";

// �J�� or ����
HttpSessionPtr CHttpSession::OpenOrCreate(const std::string &SessionId)
{
	std::string Id = SessionId;
	if (Id == "")
	{
		CRandomString IdMaker;
		IdMaker.Generate(32);
		Id = IdMaker.Get();
	}

	CHttpSession *pSession = new CHttpSession(Id);
	pSession->OpenFile();

	return HttpSessionPtr(pSession);
}

// �R���X�g���N�^
CHttpSession::CHttpSession(const std::string &InSessionId)
	: SessionId(InSessionId)
{
}

// �f�X�g���N�^
CHttpSession::~CHttpSession()
{
	SaveFile();
}

// �Z�b�g
void CHttpSession::Set(const std::string &VariableName, const std::string &Value)
{
	Datas[VariableName] = Value;
}

// �擾.
void CHttpSession::Get(const std::string &VariableName, std::string &OutValue) const
{
	OutValue = "";
	const auto &It = Datas.find(VariableName);
	if (It != Datas.end())
	{
		OutValue = It->second;
	}
}


// �t�@�C�����J��
void CHttpSession::OpenFile()
{
	CCSVController CSV;
	std::string FilePath = FileDirectory + SessionId + ".session";
	if (!CSV.Load(FilePath.c_str())) { return; }

	unsigned int Count = CSV.GetRowCount();
	for (unsigned int i = 0; i < Count; i++)
	{
		Columns Row;
		if (!CSV.GetRow(i, Row)) { break; }
		Datas[Row[0]] = Row[1];
	}
}

// �t�@�C���ɕۑ�.
void CHttpSession::SaveFile()
{
#if _WIN32
	_mkdir(FileDirectory.c_str());
#else
	mkdir(FileDirectory.c_str());
#endif

	CCSVController CSV;
	for (const auto &Data : Datas)
	{
		Columns Row;
		Row.resize(2);
		Row[0] = Data.first;
		Row[1] = Data.second;
		CSV.AddRow(Row);
	}

	std::string FilePath = FileDirectory + SessionId + ".session";
	CSV.Save(FilePath.c_str());
}

}
}
