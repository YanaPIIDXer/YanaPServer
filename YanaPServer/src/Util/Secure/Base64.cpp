#include "Util/Secure/Base64.h"

namespace YanaPServer
{
namespace Util
{
namespace Secure
{

const std::string CBase64::Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// デコード
bool CBase64::Decode(const std::string &Src, std::vector<unsigned char> &OutResult)
{
	OutResult.clear();
	if (Src.size() & 0x00000003) { return false; }

	std::vector<unsigned char> Dest;

	for (std::size_t i = 0; i < Src.size(); i += 4)
	{
		if (Src[i + 0] == '=' || Src[i + 1] == '=') { return false; }
		else if (Src[i + 2] == '=')
		{
			const auto S1 = Table.find(Src[i + 0]);
			const auto S2 = Table.find(Src[i + 1]);
			if (S1 == std::string::npos || S2 == std::string::npos) { return false; }

			Dest.push_back((char)((S1 & 0x3F) << 2) | ((S2 & 0x30) >> 4));
		}
		else if (Src[i + 3] == '=')
		{
			const auto S1 = Table.find(Src[i + 0]);
			const auto S2 = Table.find(Src[i + 1]);
			const auto S3 = Table.find(Src[i + 2]);
			if (S1 == std::string::npos || S2 == std::string::npos || S3 == std::string::npos) { return false; }

			Dest.push_back((char)((S1 & 0x3F) << 2) | ((S2 & 0x30) >> 4));
			Dest.push_back((char)((S2 & 0x0F) << 4) | ((S3 & 0x3C) >> 2));
		}
		else
		{
			const auto S1 = Table.find(Src[i + 0]);
			const auto S2 = Table.find(Src[i + 1]);
			const auto S3 = Table.find(Src[i + 2]);
			const auto S4 = Table.find(Src[i + 3]);
			if (S1 == std::string::npos || S2 == std::string::npos || S3 == std::string::npos || S4 == std::string::npos) { return false; }

			Dest.push_back((char)((S1 & 0x3F) << 2) | ((S2 & 0x30) >> 4));
			Dest.push_back((char)((S2 & 0x0F) << 4) | ((S3 & 0x3C) >> 2));
			Dest.push_back((char)((S3 & 0x03) << 6) | (S4 & 0x3F));
		}
	}

	OutResult.swap(Dest);
	return true;
}

}
}
}
