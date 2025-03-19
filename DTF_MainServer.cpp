// DTF_MainServer.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <iostream>
#include "myGlobal.h"
#include "framework.h"
#include "Monitor.h"
#include "DTF_MainServer.h"

#define MAX_LOADSTRING 100


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
CHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
CHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.


    // 전역 문자열을 초기화합니다.
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_DTFMAINSERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DTFMAINSERVER));

    Init();

    //----------------------------------------------------------------------------------------------------------
    // Circulation Thread number
    //----------------------------------------------------------------------------------------------------------

    MAX_THREAD = MAX_USER / gUserper; // Userper is 20
    MAX_QUEUE = MAX_THREAD;

    // Start WinSock
    WinSockStart();

    // Create Event
    int i;
    for (i = 0; i < MAX_USER; ++i)
    {
        gEvent[i] = WSACreateEvent();
    }

    // Accept Thread
    gServerHandle = (HANDLE)_beginthreadex(NULL, 0, ServerThread, NULL, 0, NULL);

    // User Thread
    for (i = 0; i < MAX_THREAD; ++i)
    {
        gUserHandle[i] = NULL;
        gUserHandle[i] = (HANDLE)_beginthreadex(NULL, 0, UserThread, (void*)i, 0, NULL);
    }

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DTFMAINSERVER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DTFMAINSERVER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 320, 240, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    gMainWnd = hWnd;
    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {

        int error = _mkdir("Log");

        gListboxWindow = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOINTEGRALHEIGHT, 0, 20, 0, 0, hWnd, (HMENU)101, (HINSTANCE)(GetWindowLongPtr(hWnd, GWLP_HINSTANCE)), NULL);
        if (gListboxWindow != NULL)
        {
            LOGFONT logfont;

            memset(&logfont, 0, sizeof(LOGFONT));

            logfont.lfCharSet = DEFAULT_CHARSET;
            logfont.lfHeight = -12;
            strcpy(logfont.lfFaceName, "Arial");
            gArialFont = CreateFontIndirect(&logfont);
            SendMessage(gListboxWindow, WM_SETFONT, (WPARAM)gArialFont, (LPARAM)0);
        }

    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_SIZE:
    {
        if (wParam != SIZE_MINIMIZED)
        {
            MoveWindow(gListboxWindow, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
        }
    }break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CLOSE:
    {


        int i;
        SAFE_CLOSE(gServerHandle);


        for (i = 0; i < MAX_USER; ++i)
        {
            WSACloseEvent(gEvent[i]);
        }

        for (i = 0; i < MAX_THREAD; ++i)
        {
            SAFE_CLOSE(gUserHandle[i]);
        }

        SAFE_CLOSESOCKET(gServerSocket);


        WSACleanup();
        DestroyWindow(hWnd);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        if (gArialFont != NULL)
            DeleteObject(gArialFont);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// Quit server when press Ctrl + C
BOOL CtrlHandler(DWORD dwType)
{
    if (dwType == CTRL_C_EVENT)
    {
        gServerHandle = NULL;
        // 연결된 모든 클라이언트 및 리슨 소켓을 닫고 프로그램을 종료한다.
        ::shutdown(gServerSocket, SD_BOTH);
        // 연결 리스트에 등록된 모든 정보를 삭제한다.

        for (int i = 0; i < g_User.GetUserCount(); i++) {
            g_User.mUser[i].LogOut();
            Log("모든 클라이언트 연결을 종료했습니다.");
        }

        //클라이언트와 통신하는 스레드들이 종료되기를 기다린다.
        ::Sleep(100);
        ::closesocket(gServerSocket);

        //윈속 해제
        ::WSACleanup();
        exit(0);
        return TRUE;
    }

    return FALSE;
}

void Init()
{
    gServerPort = 25000;
    gServerNum = 0;
    gUserper = 1;
    //gbUseUDP = 0;
}

BOOL WinSockStart()
{
    WSAData wsaData;
    int     error;

    error = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (error == SOCKET_ERROR)
    {
        WSACleanup();
        return FALSE;
    }


    char str[256]; memset(str, 0x00, sizeof(str));

    PHOSTENT phostent;
    IN_ADDR in;
    if ((phostent = gethostbyname(gHostName)) == NULL)
    {
        sprintf(str, "gethostbyname() generated error %d", WSAGetLastError());
        Log(str);
    }
    else
    {
        memcpy(&in, phostent->h_addr, 4);
        memset(gIP, 0x00, sizeof(gIP));
        sprintf(gIP, "%s", inet_ntoa(in));
        sprintf(str, "Host Name Is [ %s ] IP : [%s]", phostent->h_name, gIP);
        Log(str);
    }
    return TRUE;
}

unsigned __stdcall ServerThread(void* pArg)
{
    Log("Digimon Team Fight ServerThread Start..TCPPort : %d", gServerPort);
    char szBuffer[1024];	memset(szBuffer, 0x00, sizeof(szBuffer));

    gServerSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (gServerSocket == INVALID_SOCKET)
    {
        sprintf(szBuffer, "Socket error code=%x", WSAGetLastError());
        Log(szBuffer);
        return 0;
    }

    //나겔알고리즘 비적용
    BOOL opt_val = TRUE;
    setsockopt(gServerSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&opt_val, sizeof(opt_val));
    DWORD size = 0x8000;
    setsockopt(gServerSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&size, sizeof(size));
    setsockopt(gServerSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&size, sizeof(size));

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(gServerPort);

    //Bind
    if (::bind(gServerSocket, (struct sockaddr*)&sa, sizeof(sa)) != 0)
    {
        sprintf(szBuffer, "bind error code=%d", WSAGetLastError());
        Log(szBuffer);
        return 0;
    }

    //Listen
    if (listen(gServerSocket, 500) != 0)
    {
        sprintf(szBuffer, "listen error code=%d", WSAGetLastError());
        Log(szBuffer);
        return 0;
    }

    Monitor AcceptMutex;

    while (gServerHandle)
    {
        struct sockaddr_in ca;
        int clientAddressLength = sizeof(ca);
        int nLength = sizeof(ca);

        SOCKET socket = accept(gServerSocket, (struct sockaddr*)&ca, &nLength);

        if (socket == INVALID_SOCKET)
        {
            closesocket(socket);

            Log("Failed Socket Create");
            AcceptMutex.Off();
            continue;
        }
        //유저등록에 실패하면 소켓을 닫아버린다..

        if (g_User.AddUser(socket, ca) == false)
        {
            closesocket(socket);

            Log("ADDUser Fail %d.%d.%d.%d",
                ca.sin_addr.S_un.S_un_b.s_b1,
                ca.sin_addr.S_un.S_un_b.s_b2,
                ca.sin_addr.S_un.S_un_b.s_b3,
                ca.sin_addr.S_un.S_un_b.s_b4);
        }
        AcceptMutex.Off();

        Sleep(1);
    }
    return 0;

}

unsigned __stdcall UserThread(void* pArg)
{
    WSANETWORKEVENTS events;

    DWORD dwReturn = 0, dwRet = 0;

    //int nread;
    int ThreadArray = (int)pArg;
    int UserArray = (ThreadArray * gUserper);
    int i = 0;
    int inum = 0;
    //Log("UserThread %d", ThreadArray );
    while (gUserHandle[ThreadArray])
    {
        //64개..
        dwReturn = WSAWaitForMultipleEvents(gUserper, &gEvent[UserArray], FALSE, WSA_INFINITE, FALSE);

        if (dwReturn != WSA_WAIT_FAILED)
        {
            for (i = 0; i < gUserper; ++i)
            {
                inum = UserArray + i;

                // UserManager
                if (g_User.mUser[inum].mhSocket)
                {

                    dwRet = WSAEnumNetworkEvents(g_User.mUser[inum].mhSocket, gEvent[inum], &events);

                    if (dwRet == 0)
                    {
                        //FD_READ EVENT 면.
                        if ((events.lNetworkEvents & FD_READ) == FD_READ)
                        {
                            g_User.mUser[inum].Recv();
                        }
                        if ((events.lNetworkEvents & FD_WRITE) == FD_WRITE)
                        {
                            g_User.mUser[inum].FlushSendBuffer();
                        }
                        if ((events.lNetworkEvents & FD_CLOSE) == FD_CLOSE)
                        {
                            //접속 종료 처리
                            //Log("g_User.DelUser( inum %d );", inum );
                            g_User.DelUser(inum);
                        }
                    }
                }
            }
        }
        Sleep(1);
    }
    return 0;
}

