#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include "../Util/Stream/SimpleStream.h"

namespace YanaPServer
{
namespace Servlet
{

/**
 * @struct SHttpResponse
 * @brief HTTP���X�|���X
 */
struct SHttpResponse
{

	//! �R���e���c�𗬂����ރX�g���[��
	Util::Stream::CSimpleStream ContentStream;

};

}
}

#endif		// #ifndef __HTTPRESPONSE_H__
