#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "../Application/ApplicationBase.h"
#include "../Peer/PeerBase.h"
#include "ServletFinder.h"
#include "HttpServerEvent.h"

namespace YanaPServer
{
namespace Servlet
{

class IServlet;

/**
 * @class CHttpDefaultServerEvent
 * @brief 標準のサーバイベント
 *        オーバーライドするクラスを定義して設定しない場合はコイツが使用される。
 * @detail シングルトンクラス
 */
class CHttpDefaultServerEvent : public IHttpServerEvent
{

public:

	/**
	 * @brief デストラクタ
	 */
	virtual ~CHttpDefaultServerEvent() {}

	/**
	 * @fn virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) override
	 * @brief エラー発生
	 * @param[in] Request HTTPリクエスト
	 * @param[in] Response HTTPレスポンス
	 */
	virtual void OnError(const SHttpRequest &Request, SHttpResponse &Response) override
	{
		Response.ContentStream.AppendStringLine("Error.");
	}

	/**
	 * @fn virtual void OnNotFound(const SHttpRequest &Request, SHttpResponse &Response) override
	 * @brief 対応Servletが見つからなかった
	 * @param[in] Request HTTPリクエスト
	 * @param[in] Response HTTPレスポンス
	 */
	virtual void OnNotFound(const SHttpRequest &Request, SHttpResponse &Response) override
	{
		Response.ContentStream.AppendString(Request.Path.c_str());
		Response.ContentStream.AppendStringLine(" 404 NotFound.");
	}

	// ========= Singleton =============

public:

	/**
	 * @fn static CHttpDefaultServerEvent &GetInstance()
	 * @brief Singletonインスタンス取得
	 * @return Singletonインスタンス
	 */
	static CHttpDefaultServerEvent &GetInstance() { return Instance; }

private:

	CHttpDefaultServerEvent() {}
	static CHttpDefaultServerEvent Instance;

};

/**
 * @class CHttpServer
 * @brief HTTPサーバ
 */
class CHttpServer : public YanaPServer::Application::CApplicationBase
{

public:

	/**
	 * @brief コンストラクタ
	 */
	CHttpServer();

	/**
	 * @brief コンストラクタ
	 * @param[in] pInEvent サーバイベント
	 */
	CHttpServer(IHttpServerEvent *pInEvent);

	/**
	 * @brief デストラクタ
	 */
	virtual ~CHttpServer();

	/**
	 * @fn void AddServlet(IServlet *pServlet)
	 * @brief Servlet追加。
	 * @param[in] pServlet Servlet
	 */
	void AddServlet(IServlet *pServlet);

protected:

	/**
	 * @fn virtual CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override final
	 * @brief Peer生成
	 * @param[in] pSocket ソケット
	 * @return CPeerBaseを派生したオブジェクトを生成して返す。
	 */
	virtual YanaPServer::Peer::CPeerBase *CreatePeer(YanaPServer::Socket::ISocket *pSocket) override;

private:

	// ServletFinder
	CServletFinder ServletFinder;

	// サーバイベント
	IHttpServerEvent *pEvent;

};

}
}

#endif		// #ifndef __HTTPSERVER_H__
