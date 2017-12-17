#ifndef IM_IMCHAT_H
#define IM_IMCHAT_H
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable:4477)
#pragma warning (disable:4819)

#ifdef _TESTAPIS_
// /clr模式包含该头文件将会导致
// error LNK2022 : 元数据操作失败(8013118D) : 重复类型(group_filter)中的布局信息不一致 : (0x0200020b)。
// 2>LINK : fatal error LNK1255 : 由于元数据错误，链接失败
#include <WS2tcpip.h>
#else
#include <winsock2.h>
#endif
#include <process.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <map>

typedef struct IMUSR {
	int optionum = 0x0;
	char addr[MAX_PATH] = { NULL };
	char comm[64] = { NULL };
	char psw[24] = { NULL };
	char usr[24] = { NULL };
	int err = 0;
} st_imusr;

struct CHATMSG
{
	char lastuser[256] = { NULL };
	char lastgrop[256] = { NULL };
};

struct LPR
{
	SOCKET sock;
	CRITICAL_SECTION wrcon;
	void* dlg;
	CHATMSG *msg;
};

struct CMD {
	int idx; std::string val;
};

const CMD idx_CMD[] =
{
	{ 0x00,"命令菜单" },
	{ 0x01,"注册" },
	{ 0x02,"登陆" },
	{ 0x03,"登出" },
	{ 0x04,"帮助" },
	{ 0x08,"好友列表" },
	{ 0x09,"设置密码" },
	{ 0x05,"刷新列表" },
	{ 0x06,"群" },
	{ 0x07,"群成员" },
	{ 0x0A,"创建群" },
	{ 0x0B,"加入群" },
	{ 0x0C,"退群" },
};

enum  em_CMD{
	REGIST = 0,
	LOGIN,
	LOGOUT,
	HELP,
	FRIENDLIST,
	SETPSW,
	REFRASH,
	VIEWGROUP,
	MEMBER,
	HOSTGROUP,
	JOINGROUP,
	EXITGROUP,
	CHAT = 0xe,
	TALK,
};

int InitChat(st_imusr* imusr = NULL);
int StartChat(int err, void(*func)(void*));
int SetChatCmd(unsigned int opt);
int SetLogInfo(char* usr, char* psw);
int CloseChat();

#endif
