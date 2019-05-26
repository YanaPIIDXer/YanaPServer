#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include "../Util/Stream/SimpleStream.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @struct SHttpResponse
 * @brief HTTPレスポンス
 */
struct SHttpResponse
{

	//! コンテンツを流し込むストリーム
	Util::Stream::CSimpleStream ContentStream;

};

}
}

#endif		// #ifndef __HTTPRESPONSE_H__
