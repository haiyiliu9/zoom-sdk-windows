#include <string>
#include "DemoUI.h"
#include "AuthServiceMgr.h"
#include "PreMeetingServiceMgr.h"
#include "MeetingServiceMgr.h"
#include "MessageWnd.h"

CDemoUI::CDemoUI()
{
	ResetAllControls();
	m_pAuthServiceMgr = new CAuthServiceMgr(this);
	//m_preMeetingServiceMgr = new CPreMeetingServiceMgr(this);
	m_pMeetingServiceMgr = new CMeetingServiceMgr(this);
	m_bNormalUser = true;
	m_bStar = true;
	m_pMessageWnd = NULL;
	m_bSDKInit = false;
}

CDemoUI::~CDemoUI()
{
	if (m_pAuthServiceMgr)
	{
		delete m_pAuthServiceMgr;
		m_pAuthServiceMgr = NULL;
	}

	//if (m_preMeetingServiceMgr)
	//{
	//	delete m_preMeetingServiceMgr;
	//	m_preMeetingServiceMgr = NULL;
	//}

	if (m_pMeetingServiceMgr)
	{
		delete m_pMeetingServiceMgr;
		m_pMeetingServiceMgr = NULL;
	}

	m_bNormalUser = true;
	m_bStar = true;

	if (m_pMessageWnd)
	{
		delete m_pMessageWnd;
		m_pMessageWnd = NULL;
	}
	m_bSDKInit = false;
}

void CDemoUI::InitWindow()
{
	//InitServiceMgr();
	InitAllControls();
}

void CDemoUI::InitAllControls()
{

	m_containerAuthUI = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("container_auth")));
	m_containerUserUI = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("container_user")));
	m_containerLoginUI = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("container_login")));
	m_containerPTApi = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("container_pt_api")));
	m_containerStart = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("container_start")));
	m_containerWaitingUI = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("waiting_panel")));

	m_containerMeetingApi = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("container_meeting_api")));
	m_containerShareApi = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("container_share_api")));
	m_containerVideoApi = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("container_video_api")));
	m_containerAudioApi = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("container_audio_api")));

	m_editWebDomain = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_web_domain")));
	m_editKey = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_key")));
	m_editSecret = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_secret")));
	m_editEmail = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_email")));
	m_editPassword = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_password")));
	m_editMeetingNumber = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_meeting_number")));
	m_editUserId = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_user_id")));
	m_editUserToken = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_user_token")));
	m_editUserName = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_user_name")));

	m_chkRememberMe = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("chk_remember_me")));

	m_lableAuthError = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lb_auth_errorinfo")));
	m_lableLoginError = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lb_login_errorinfo")));
	m_lableUserId = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lb_user_id")));
	m_lableUserToken = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lb_user_token")));
	m_lableUserName = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lb_user_name")));
	m_lableMeetingAPIStatus = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lb_meeting_api_status")));

	m_btnAuth = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_auth")));	
	m_btnNormal = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_normal_user")));
	m_btnApi = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_api_user")));
	m_btnLogin = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_login")));
	m_btnStart = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_start")));
	m_btnJoin = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_join")));
	m_btnStartOk = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_start_ok")));
	m_btnEnd = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_end")));
	m_btnLeave = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_leave")));
	m_btnCancel = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_close")));
	m_btnStartMonitorShare = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_start_monitor_share")));
	m_btnStartAppShare = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_start_app_share")));
	m_btnStopShare = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_stop_share")));
	m_btnMuteVideo = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_mute_video")));
	m_btnUnmuteVideo = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_unmute_video")));
	m_btnPingVideo = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_pin_video")));
	m_btnUnpingVideo = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_unpin_video")));
	m_btnMuteAudio = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_mute_audio")));
	m_btnUnmuteAudio = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_unmute_audio")));
	m_btnShareApi = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_share_api")));
	m_btnVideoApi = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_video_api")));
	m_btnAudioApi = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_audio_api")));

	m_listUsers = static_cast<CListUI*>(m_PaintManager.FindControl(_T("list_users")));

	m_gifWaiting = static_cast<CGifAnimUI*>(m_PaintManager.FindControl(_T("gif_waiting"))); 

	ShowWaiting(false);
}

void CDemoUI::ResetAllControls()
{
	m_containerAuthUI = NULL;
	m_containerUserUI = NULL;	
	m_containerStart = NULL;
	m_containerMeetingApi = NULL;
	m_containerShareApi = NULL;
	m_containerVideoApi = NULL;
	m_containerAudioApi = NULL;
	
	m_editWebDomain = NULL;
	m_editKey = NULL;
	m_editSecret	= NULL;
	m_editEmail = NULL;
	m_editPassword = NULL;
	m_editMeetingNumber = NULL;
	m_editUserId = NULL;
	m_editUserToken = NULL;
	m_editUserName = NULL;

	m_chkRememberMe = NULL;

	m_lableAuthError = NULL;
	m_lableLoginError = NULL;
	m_lableUserId = NULL;
	m_lableUserToken = NULL;
	m_lableUserName = NULL;
	m_lableMeetingAPIStatus = NULL;

	m_btnAuth = NULL;	
	m_btnNormal	= NULL;
	m_btnApi = NULL;
	m_btnLogin = NULL;
	m_btnStart = NULL;
	m_btnJoin = NULL;
	m_btnStartOk = NULL;
	m_btnEnd = NULL;
	m_btnLeave = NULL;
	m_btnCancel= NULL;
	m_btnStartMonitorShare = NULL;
	m_btnStartAppShare = NULL;
	m_btnStopShare = NULL;
	m_btnMuteVideo = NULL;
	m_btnUnmuteVideo = NULL;
	m_btnPingVideo = NULL;
	m_btnUnpingVideo = NULL;
	m_btnMuteAudio = NULL;
	m_btnShareApi = NULL;
	m_btnVideoApi = NULL;
	m_btnAudioApi = NULL;
	m_btnUnmuteAudio = NULL;

	m_listUsers = NULL;
}

void CDemoUI::SwitchUIPageByType(UIPageType emPageType /* = UIPAGE_AUTH */)
{
	ShowWaiting(false);
	bool bAuth(false), bUser(false), bLogin(false), bPT(false), bStart(false), bJoin(false), bMeetingApi(false);
	if (emPageType == UIPAGE_AUTH)
	{
		bAuth = true;
	}
	else if (emPageType == UIPAGE_USER)
	{
		bUser = true;
	}
	else if (emPageType == UIPAGE_LOGIN)
	{
		bLogin = true;
	}
	else if (emPageType == UIPAGE_PT)
	{
		bPT = true;
	}
	else if (emPageType == UIPAGE_START)
	{
		bStart = true;

		bool bShow = m_bNormalUser ? false : true;

		if (m_lableUserId)
			m_lableUserId->SetVisible(bShow);

		if (m_editUserId)
			m_editUserId->SetVisible(bShow);

		if (m_lableUserToken)
			m_lableUserToken->SetVisible(bShow);

		if (m_editUserToken)
			m_editUserToken->SetVisible(bShow);

		if (m_lableUserName)
			m_lableUserName->SetVisible(bShow);

		if (m_editUserName)
			m_editUserName->SetVisible(bShow);
	}
	else if (emPageType == UIPAGE_JOIN)
	{
		bStart = true;

		if (m_lableUserId)
			m_lableUserId->SetVisible(false);

		if (m_editUserId)
			m_editUserId->SetVisible(false);

		if (m_lableUserToken)
		{
			m_lableUserToken->SetText(_T("Meeting Password:"));
			m_lableUserToken->SetVisible(true);
		}

		if (m_editUserToken)
			m_editUserToken->SetVisible(true);

		if (m_lableUserName)
			m_lableUserName->SetVisible(true);

		if (m_editUserName)
			m_editUserName->SetVisible(true);
	}
	else if (emPageType == UIPAGE_MEETING)
	{
		bMeetingApi = true;
	}

	if (m_containerAuthUI && m_containerUserUI && m_containerLoginUI && m_containerPTApi && m_containerStart && m_containerMeetingApi)
	{
		m_containerAuthUI->SetVisible(bAuth);
		m_containerUserUI->SetVisible(bUser);
		m_containerLoginUI->SetVisible(bLogin);
		m_containerPTApi->SetVisible(bPT);
		m_containerStart->SetVisible(bStart);
		m_containerMeetingApi->SetVisible(bMeetingApi);
	}
}

void CDemoUI::ShowMeetingApiByType(UIApiType emApiType /* = UIAPI_SHARE */)
{
	bool bShare(false), bVideo(false), bAudio(false);
	if (emApiType == UIAPI_SHARE)
	{
		bShare = true;
	}
	else if (emApiType == UIAPI_VIDEO)
	{
		bVideo = true;
	}
	else if (emApiType == UIAPI_AUDIO)
	{
		bAudio = true;
	}

	if (m_containerShareApi && m_containerVideoApi && m_containerAudioApi)
	{
		m_containerShareApi->SetVisible(bShare);
		m_containerVideoApi->SetVisible(bVideo);
		m_containerAudioApi->SetVisible(bAudio);
	}
}

bool CDemoUI::SDKAuth()
{
	if (!m_editWebDomain || !m_editKey || !m_editSecret || !m_pAuthServiceMgr)
		return false;

	std::wstring strWebDomain = m_editWebDomain->GetText().GetData();
	std::wstring strKey = m_editKey->GetText().GetData();
	std::wstring strSecret = m_editSecret->GetText().GetData();
	if (strWebDomain.length() <= 0 || strKey.length() <= 0 || strSecret.length() <= 0)
		return false;

	if (!m_bSDKInit)
	{
		ZOOM_SDK_NAMESPACE::InitParam initParam;
		initParam.strWebDomain = strWebDomain.c_str();
		if (m_pAuthServiceMgr)
			m_bSDKInit = m_pAuthServiceMgr->Init(initParam);
	}

	if (!m_bSDKInit)
	{
		return false;
	}

	m_editWebDomain->SetEnabled(false);
	
	ZOOM_SDK_NAMESPACE::AuthParam authParam;
	authParam.appKey = strKey.c_str();
	authParam.appSecret = strSecret.c_str();

	bool bAuth = m_pAuthServiceMgr->SDKAuth(authParam);
	if (bAuth)
	{
		ShowWaiting(true);
	}

	return bAuth;
}

bool CDemoUI::Login()
{
	if (!m_editEmail || !m_editEmail || !m_editSecret || !m_pAuthServiceMgr)
		return false;

	std::wstring strEmail = m_editEmail->GetText().GetData();
	std::wstring strPassword = m_editPassword->GetText().GetData();
	if (strEmail.length() <= 0 || strPassword.length() <= 0)
		return false;

	bool bRememberMe = m_chkRememberMe->GetCheck();

	ZOOM_SDK_NAMESPACE::LoginParam param;
	param.userName = strEmail.c_str();
	param.password = strPassword.c_str();
	param.bRememberMe = bRememberMe;

	bool bRet = m_pAuthServiceMgr->Login(param);
	if (bRet)
	{
		ShowWaiting(true);
	}

	return bRet;
}

bool CDemoUI::Start()
{
	bool bRet(false);
	
	if (m_bNormalUser)
		bRet = NormalUserStart();
	else
		bRet = APIUserStart();

	if (bRet)
	{
		ShowWaiting(true);
	}

	return bRet;
}

bool CDemoUI::NormalUserStart()
{
	if (!m_editMeetingNumber || !m_editUserId || !m_editUserToken || !m_pMeetingServiceMgr)
		return false;

	std::wstring strMeetingNumber =  m_editMeetingNumber->GetText().GetData();
	if (strMeetingNumber.length() <= 0 )
			return false;

	ZOOM_SDK_NAMESPACE::StartParam startParam;
	startParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_NORMALUSER;
	ZOOM_SDK_NAMESPACE::StartParam4NormalUser& normalParam = startParam.param.normaluserStart;
	normalParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());

	return m_pMeetingServiceMgr->Start(startParam);
}

bool CDemoUI::APIUserStart()
{
	if (!m_editMeetingNumber || !m_editUserId || !m_editUserToken || !m_editUserName || !m_pMeetingServiceMgr)
		return false;

	std::wstring strMeetingNumber, strUserId, strUserToken, strUserName;
	strMeetingNumber =  m_editMeetingNumber->GetText().GetData();
	strUserId = m_editUserId->GetText().GetData();
	strUserToken = m_editUserToken->GetText().GetData();
	strUserName = m_editUserName->GetText().GetData();
	if (strMeetingNumber.length() <= 0 || strUserId.length() <= 0 || strUserToken.length() <= 0 || strUserName.length() <= 0)
		return false;

	ZOOM_SDK_NAMESPACE::StartParam startParam;
	startParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_APIUSER;
	ZOOM_SDK_NAMESPACE::StartParam4APIUser& apiuserParam = startParam.param.apiuserStart;

	apiuserParam.userID = strUserId.c_str();
	apiuserParam.userToken = strUserToken.c_str();
	apiuserParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());
	apiuserParam.userName = strUserName.c_str();

	return m_pMeetingServiceMgr->Start(startParam);
}

bool CDemoUI::Join()
{
	bool bRet(false);

	if (m_bNormalUser)
		bRet = NormalUserJoin();
	else
		bRet = APIUserJoin();

	if (bRet)
	{
		ShowWaiting(true);
	}

	return bRet;
}

bool CDemoUI::NormalUserJoin()
{
	if (!m_editMeetingNumber || !m_editUserToken || !m_editUserName || !m_pMeetingServiceMgr)
		return false;

	std::wstring strMeetingNumber = m_editMeetingNumber->GetText().GetData();
	std::wstring strUserId = _T("");
	std::wstring strUserToken = m_editUserToken->GetText().GetData();
	std::wstring strUserName = m_editUserName->GetText().GetData();
	if (strMeetingNumber.length() <= 0 || strUserName.length() <= 0)
		return false;

	ZOOM_SDK_NAMESPACE::JoinParam joinParam;
	joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_NORMALUSER;
	ZOOM_SDK_NAMESPACE::JoinParam4NormalUser& normalParam = joinParam.param.normaluserJoin;
	normalParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());
	normalParam.userName = strUserName.c_str();
	normalParam.psw = strUserToken.c_str();

	return m_pMeetingServiceMgr->Join(joinParam);
}

bool CDemoUI::APIUserJoin()
{
	if (!m_editMeetingNumber || !m_editUserId || !m_editUserToken || !m_editUserName || !m_pMeetingServiceMgr)
		return false;

	std::wstring strMeetingNumber = m_editMeetingNumber->GetText().GetData();
	std::wstring strUserId = _T("");
	std::wstring strUserToken = m_editUserToken->GetText().GetData();
	std::wstring strUserName = m_editUserName->GetText().GetData();
	if (strMeetingNumber.length() <= 0 || strUserName.length() <= 0)
		return false;

	ZOOM_SDK_NAMESPACE::JoinParam joinParam;
	joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_APIUSER;
	ZOOM_SDK_NAMESPACE::JoinParam4APIUser& apiParam = joinParam.param.apiuserJoin;
	apiParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());
	apiParam.userName = strUserName.c_str();
	apiParam.psw = strUserToken.c_str();

	return m_pMeetingServiceMgr->Join(joinParam);
}

bool CDemoUI::Leave()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	return m_pMeetingServiceMgr->Leave();
}

bool CDemoUI::End()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	return m_pMeetingServiceMgr->End();
}

BOOL CALLBACK MyInfoEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MONITORINFOEX iMonitor;
	iMonitor.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, &iMonitor);

	if (iMonitor.dwFlags == DISPLAY_DEVICE_MIRRORING_DRIVER)
	{
		return true;
	}
	else
	{
		reinterpret_cast< std::vector<std::wstring>* >(dwData)->push_back(iMonitor.szDevice);
		return true;
	}
}

bool CDemoUI::StartMonitorShare()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	std::vector<std::wstring> vecMonitorArray;
	EnumDisplayMonitors(NULL, NULL, &MyInfoEnumProc, reinterpret_cast<LPARAM>(&vecMonitorArray));

	std::wstring strMonitorId;
	if (vecMonitorArray.size() <= 0)
		strMonitorId = _T("");
	else
		strMonitorId = vecMonitorArray[0];


	return m_pMeetingServiceMgr->StartMonitorShare(strMonitorId.c_str());
}

bool CDemoUI::StartAppShare()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;	

	InitMessageWnd(_T("App Handle:"));	

	std::wstring strUserID(_T(""));
	if (m_pMessageWnd)
		strUserID = m_pMessageWnd->GetInputVal();	

	UnInitMessageWnd();

	if (strUserID.length() <= 0)
		return false;

	TCHAR* offset;
	HWND hwndSharedApp = (HWND)wcstol(strUserID.c_str(), &offset, 16);

	return m_pMeetingServiceMgr->StartAppShare(hwndSharedApp);
}

bool CDemoUI::StopShare()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	return m_pMeetingServiceMgr->StopShare();
}

bool CDemoUI::MuteVideo()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	return m_pMeetingServiceMgr->MuteVideo();
}

bool CDemoUI::UnmuteVideo()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	return m_pMeetingServiceMgr->UnmuteVideo();
}

bool CDemoUI::PinVideo()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	InitMessageWnd();

	bool bPin(true), bFirstView(true);
	std::wstring strUserID(_T(""));
	if (m_pMessageWnd)
		strUserID = m_pMessageWnd->GetInputVal();	

	UnInitMessageWnd();

	if (strUserID.length() <= 0)
		return false;
	
	return m_pMeetingServiceMgr->PinVideo(bPin, bFirstView, _wtoi(strUserID.c_str()));
}

bool CDemoUI::UnpinVideo()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	InitMessageWnd();

	bool bPin(false), bFirstView(true);
	std::wstring strUserID(_T(""));
	if (m_pMessageWnd)
		strUserID = m_pMessageWnd->GetInputVal();	

	UnInitMessageWnd();

	if (strUserID.length() <= 0)
		return false;

	return m_pMeetingServiceMgr->PinVideo(bPin, bFirstView, _wtoi(strUserID.c_str()));
}

bool CDemoUI::MuteAudio()
{	
	if (m_pMeetingServiceMgr == NULL)
		return false;

	InitMessageWnd();

	std::wstring strUserID(_T(""));
	if (m_pMessageWnd)
		strUserID = m_pMessageWnd->GetInputVal();

	UnInitMessageWnd();

	if (strUserID.length() <= 0)
		return false;

	return m_pMeetingServiceMgr->MuteAudio(_wtoi(strUserID.c_str()));
}

bool CDemoUI::UnMuteAudio()
{
	if (m_pMeetingServiceMgr == NULL)
		return false;

	InitMessageWnd();

	std::wstring strUserID(_T(""));
	if (m_pMessageWnd)
		strUserID = m_pMessageWnd->GetInputVal();	

	UnInitMessageWnd();

	if (strUserID.length() <= 0)
		return false;

	return m_pMeetingServiceMgr->UnMuteAudio(_wtoi(strUserID.c_str()));
}

void CDemoUI::InitMessageWnd(std::wstring strLabelText)
{
	if (m_pMessageWnd == NULL)
		m_pMessageWnd = new CMessageWnd();

	m_pMessageWnd->SetLabelText(strLabelText);
	m_pMessageWnd->Create(this->GetHWND(), _T("sdk_demo"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	m_pMessageWnd->CenterWindow();
	m_pMessageWnd->ShowModal();
}

void CDemoUI::UnInitMessageWnd()
{
	if (m_pMessageWnd)
	{
		delete m_pMessageWnd;
		m_pMessageWnd = NULL;
	}
}

void CDemoUI::Notify( TNotifyUI& msg )
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnAuth)
		{
			SDKAuth();
		}
		else if (msg.pSender == m_btnNormal)
		{
			SwitchUIPageByType(UIPAGE_LOGIN);
		}
		else if (msg.pSender == m_btnApi)
		{
			m_bNormalUser = false;			
			SwitchUIPageByType(UIPAGE_PT);
		}
		else if (msg.pSender == m_btnLogin)
		{
			m_bNormalUser = true;
			Login();
		}
		else if (msg.pSender == m_btnStart)
		{
			m_bStar = true;
			SwitchUIPageByType(UIPAGE_START);
		}
		else if (msg.pSender == m_btnJoin)
		{
			m_bStar = false;
			SwitchUIPageByType(UIPAGE_JOIN);
		}
		else if (msg.pSender == m_btnStartOk)
		{
			//Create Meeting Service
			if (m_pMeetingServiceMgr)
				m_pMeetingServiceMgr->Init();

			if (m_bStar)
				Start();
			else
				Join();
		}
		else if (msg.pSender == m_btnShareApi)
		{
			ShowMeetingApiByType(UIAPI_SHARE);
		}
		else if (msg.pSender == m_btnVideoApi)
		{
			ShowMeetingApiByType(UIAPI_VIDEO);
		}
		else if (msg.pSender == m_btnAudioApi)
		{
			ShowMeetingApiByType(UIAPI_AUDIO);
		}
		else if (msg.pSender == m_btnEnd)
		{
			End();
		}
		else if (msg.pSender == m_btnLeave)
		{
			Leave();
		}
		else if (msg.pSender == m_btnStartMonitorShare)
		{
			StartMonitorShare();
		}		
		else if (msg.pSender == m_btnStartAppShare)
		{
			StartAppShare();
		}
		else if (msg.pSender == m_btnStopShare)
		{
			StopShare();
		}
		else if (msg.pSender == m_btnMuteVideo)
		{
			MuteVideo();
		}
		else if (msg.pSender == m_btnUnmuteVideo)
		{
			UnmuteVideo();
		}
		else if (msg.pSender == m_btnPingVideo)
		{
			PinVideo();
		}
		else if (msg.pSender == m_btnUnpingVideo)
		{
			UnpinVideo();
		}
		else if (msg.pSender == m_btnMuteAudio)
		{
			MuteAudio();
		}
		else if (msg.pSender == m_btnUnmuteAudio)
		{
			UnMuteAudio();
		}
	}

	//__super::Notify(msg);
}

LRESULT CDemoUI::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE ) 
	{
		m_PaintManager.Init(m_hWnd);

		CDialogBuilder builder;
		STRINGorID xml(GetSkinRes());
		CControlUI* pRoot = builder.Create(xml, _T("xml"), 0, &m_PaintManager);
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		InitWindow(); 

		return lRes;
	}
	else if (uMsg == WM_CLOSE)
	{
		OnClose(uMsg, wParam, lParam, bHandled);		
	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, lParam, bHandled);		
	}
/*	else if( uMsg == WM_NCACTIVATE ) 
	{
		if( ::IsIconic(m_hWnd) ) 
		{
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	else if( uMsg == WM_NCCALCSIZE ) 
	{
		return 0;
	}
	else if( uMsg == WM_NCPAINT ) 
	{
		return 0;
	}
	else if (uMsg == WM_NCHITTEST)
	{
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled);
		return lRes;
	}
	else if (uMsg == WM_NCLBUTTONDBLCLK)  
	{  
		return 0;  
	} */ 

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CDemoUI::ShowStatus(UIPageType emUIPageType, std::wstring strStatus)
{
	CLabelUI* labelStatus = NULL;

	if (emUIPageType == UIPAGE_AUTH)
		labelStatus = m_lableAuthError;
	else if (emUIPageType == UIPAGE_USER)
		;
	else if (emUIPageType == UIPAGE_LOGIN)
		labelStatus = m_lableLoginError;
	else if (emUIPageType == UIPAGE_PT)
		;
	else if (emUIPageType == UIPAGE_START)
		;
	else if (emUIPageType == UIPAGE_JOIN)
		;
	//else if (emUIPageType == UIPAGE_MEETING)
	//	labelStatus = m_lableMeetingAPIStatus;

	if (labelStatus)
	{
		labelStatus->SetTextColor(0xFFFF0000);
		labelStatus->SetFont(5);
		labelStatus->SetText(strStatus.c_str());					
	}
}

void CDemoUI::UpdateUserList(int nIndex, std::wstring strUserName, std::wstring strUserId, bool bAdd)
{
	if (m_listUsers == NULL)
		return;

	if (bAdd)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(0);
		m_listUsers->Add(pListElement);

		pListElement->SetText(0, strUserName.c_str());
		pListElement->SetText(1, strUserId.c_str());
	}
	else
	{
		CListTextElementUI* pListElement = NULL;
		int nCount = m_listUsers->GetCount();		
		for (int i=0; i< nCount; i++)
		{
			pListElement = (CListTextElementUI*)m_listUsers->GetItemAt(i);
			if ( pListElement && strUserId.compare(pListElement->GetText(1)) == 0)
			{
				m_listUsers->RemoveAt(i);
				break;
			}
		}
	}
}

void CDemoUI::CleanUpUserList()
{
	if (m_listUsers == NULL)
		return;

	m_listUsers->RemoveAll();
}

void CDemoUI::ShowWaiting(bool bWaiting)
{
	if (m_gifWaiting)
	{
		bWaiting ? m_gifWaiting->PlayGif() : m_gifWaiting->StopGif();
	}

	if (m_containerWaitingUI)
	{
		m_containerWaitingUI->SetVisible(bWaiting);
	}

}

LRESULT CDemoUI::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CDemoUI::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	ResetAllControls();

	//Destroy Meeting Service.
	if (m_pMeetingServiceMgr)
		m_pMeetingServiceMgr->UnInit();

	//Destroy Auth Service and clean up SDK
	if (m_pAuthServiceMgr)
	{
		m_pAuthServiceMgr->LogOut();
		m_pAuthServiceMgr->UnInit();
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CDemoUI::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_PaintManager.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right\
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
			return HTCAPTION;
	}

	return HTCLIENT;
}

void CDemoUI::onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
	TCHAR szLog[MAX_PATH] = { 0 };
	wsprintf(szLog, _T("onAuthenticationReturn:ret=%d\r\n"), ret);
	OutputDebugString(szLog);
	ShowWaiting(false);
	if (ZOOM_SDK_NAMESPACE::AUTHRET_SUCCESS == ret)
		SwitchUIPageByType(UIPAGE_USER);
	else
	{
		ShowStatus(UIPAGE_AUTH, ERROR_AUTH);
	}
}

void CDemoUI::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
{
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::LOGIN_SUCCESS:
		{
			SwitchUIPageByType(UIPAGE_PT);
		}
		break;
	case ZOOM_SDK_NAMESPACE::LOGIN_PROCESSING:
		{
			ShowWaiting(true);
		}
		break;
	case ZOOM_SDK_NAMESPACE::LOGIN_FAILED:
		{
			ShowStatus(UIPAGE_LOGIN, ERROR_LOGIN);
		}
		break;
	}
}

void CDemoUI::onLogout()
{

}

void CDemoUI::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/)
{
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_CONNECTING:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_RECONNECTING:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_DISCONNECTING:
		{
			CleanUpUserList();
			ShowWaiting(true);
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED:
		{
			CleanUpUserList();
			SwitchUIPageByType(UIPAGE_PT);
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING:
		{
			SwitchUIPageByType(UIPAGE_MEETING);
		}
	default:
		break;
	}
}

void CDemoUI::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	if (lstUserID && m_pMeetingServiceMgr)
	{
		int count = lstUserID->GetCount();
		for (int i = 0; i < count; i++)
		{
			int userId = lstUserID->GetItem(i);
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_pMeetingServiceMgr->GetUserByUserID(userId);
			if (pUserInfo)
			{
				TCHAR szUserID[MAX_PATH] = {0};
				wsprintf(szUserID, _T("%d"), pUserInfo->GetUserID());
				UpdateUserList(i, pUserInfo->GetUserName(), szUserID, true);

				TCHAR szLog[MAX_PATH] = { 0 };
				wsprintf(szUserID, _T("onUserJoin:User (%s) join meeting, userid(%d), Is host(%d), Video is on(%d)\r\n"), pUserInfo->GetUserName(), pUserInfo->GetUserID(), pUserInfo->IsHost(), pUserInfo->IsVideoOn());
				OutputDebugString(szLog);
			}
		}

		SwitchUIPageByType(UIPAGE_MEETING);
	}
	else
		ShowStatus(UIPAGE_START, ERROR_START);
}

void CDemoUI::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList /*= NULL*/)
{
	if (lstUserID)
	{
		int count = lstUserID->GetCount();
		for (int i = 0; i < count; i++)
		{
			TCHAR szUserID[MAX_PATH] = {0};
			wsprintf(szUserID, _T("%d"), lstUserID->GetItem(i));
			UpdateUserList(i, _T(""), szUserID, false);

			TCHAR szLog[MAX_PATH] = {0};
			wsprintf(szLog, _T("onUserLeft:userid (%d) left the meeting\r\n"), lstUserID->GetItem(i));
			OutputDebugString(szLog);
		}
	}
}

