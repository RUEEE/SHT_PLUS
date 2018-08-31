#pragma once
#include "stdafx.h"
struct position
{
	float x; float y;
	void print(std::ostream &os) {
		os << x << "\t" << y << std::endl;
	}
};



struct eachShot
{
	BYTE rate;			//发弹间隔
	BYTE delay;			//发弹时间点
	WORD power;			//每发子弹的威力
	position pos;		//发弹点相对坐标
	position hitBox;	//子弹判定的长和宽
	float angle;		//发射方向
	float speed;		//发射速度
	DWORD unknown1;		//fsl之后加入
	BYTE option;		//子机号,0=main
	BYTE unknown2;
	WORD ANM;			//自机弹贴图
	WORD SE;			//音效
	BYTE rate2;			//rate2
	BYTE delay2;			//delay2
	DWORD flags[12];
	void print(std::ostream &os)
	{
		using namespace std;
		os << "~rate_(BYTE,+0):      \t" << (int)rate << endl;
		os << "~delay_(BYTE,+1):     \t" << (int)delay << endl;
		os << "~power_(WORD,+2):     \t" << power << endl;
		os << "~pos_(2*DWORD,+4):    \t" << pos.x << "\t" << pos.y << endl;
		os << "~hitBox_(2*DWORD,+C): \t" << hitBox.x << "\t" << hitBox.y << endl;
		os << "~angle_(DWORD,+14):   \t" << angle << endl;
		os << "~speed_(DWORD,+18):   \t" << speed << endl;
		os << "~unknown1_(DWORD,+1C):\t" << unknown1 << endl;
		os << "~option_(BYTE,+20):   \t" << (int)option << endl;
		os << "~unknown2_(BYTE,+21): \t" << (int)unknown2 << endl;
		os << "~ANM_(WORD,+22):      \t" << ANM << endl;
		os << "~SE_(WORD,+24):       \t" << (signed short)SE << endl;
		os << "~rate2_(BYTE,+26):    \t" << (int)rate2 << endl;
		os << "~delay2_(BYTE,+27):   \t" << (int)delay2 << endl;
		os << "~flags_(12*DWORD,+28):\t";
		os << hex;
		for (int i = 0; i < 12; i++)os << flags[i] << "\t";
		os << dec << endl;
	}
	void write(std::istream &is)
	{
		using namespace std;
		string strBuffer;
		int iBuf;
		is >> strBuffer;
		if (strBuffer != "~rate_(BYTE,+0):") { cout << "Error:Wrong string,the original string is \"~rate_(BYTE,+0):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> iBuf; rate = iBuf;
		is >> strBuffer;
		if (strBuffer != "~delay_(BYTE,+1):") { cout << "Error:Wrong string,the original string is \"~delay_(BYTE,+1):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> iBuf; delay = iBuf;
		is >> strBuffer;
		if (strBuffer != "~power_(WORD,+2):") { cout << "Error:Wrong string,the original string is \"~power_(WORD,+2):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> power;
		is >> strBuffer;
		if (strBuffer != "~pos_(2*DWORD,+4):") { cout << "Error:Wrong string,the original string is \"~pos_(2*DWORD,+4):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> pos.x; is >> pos.y;
		is >> strBuffer;
		if (strBuffer != "~hitBox_(2*DWORD,+C):") { cout << "Error:Wrong string,the original string is \"~hitBox_(2*DWORD,+C):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> hitBox.x; is >> hitBox.y;
		is >> strBuffer;
		if (strBuffer != "~angle_(DWORD,+14):") { cout << "Error:Wrong string,the original string is \"~angle_(DWORD,+14):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> angle;
		is >> strBuffer;
		if (strBuffer != "~speed_(DWORD,+18):") { cout << "Error:Wrong string,the original string is \"~speed_(DWORD,+18):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> speed;
		is >> strBuffer;
		if (strBuffer != "~unknown1_(DWORD,+1C):") { cout << "Error:Wrong string,the original string is \"~unknown1_(DWORD,+1C):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> unknown1;
		is >> strBuffer;
		if (strBuffer != "~option_(BYTE,+20):") { cout << "Error:Wrong string,the original string is \"~option_(BYTE,+20):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> iBuf; option = iBuf;
		is >> strBuffer;
		if (strBuffer != "~unknown2_(BYTE,+21):") { cout << "Error:Wrong string,the original string is \"~unknown2_(BYTE,+21):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> iBuf; unknown2 = iBuf;
		is >> strBuffer;
		if (strBuffer != "~ANM_(WORD,+22):") { cout << "Error:Wrong string,the original string is \"~ANM_(WORD,+22):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> ANM;
		is >> strBuffer;
		if (strBuffer != "~SE_(WORD,+24):") { cout << "Error:Wrong string,the original string is \"~SE_(WORD,+24):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> iBuf; SE = iBuf;
		is >> strBuffer;
		if (strBuffer != "~rate2_(BYTE,+26):") { cout << "Error:Wrong string,the original string is \"~rate2_(BYTE,+26):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> iBuf; rate2 = iBuf;
		is >> strBuffer;
		if (strBuffer != "~delay2_(BYTE,+27):") { cout << "Error:Wrong string,the original string is \"~delay2_(BYTE,+27):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> iBuf; delay2 = iBuf;
		is >> strBuffer;
		if (strBuffer != "~flags_(12*DWORD,+28):") { cout << "Error:Wrong string,the original string is \"~flags_(12*DWORD,+28):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> hex;
		for (int i = 0; i < 12; i++)
		{
			is >> flags[i];
		}
		is >> dec;
	}
};

struct playerArg
{
	WORD  maxPower;									//默认4
	WORD  totalOffset;								//最大offset数量
	float hitBox;									//判定				(无用)
	float powerAttractSpeed;						//收p点的速度		(无用)
	float powerAttractHitBox;						//收p点的判定(高速)	(无用)
	float normalSpeed;								//高速 速度
	float forcedSpeed;								//低速速度
	float normalDiagonalSpeed;						//斜向高速(指分配到xy的速度)
	float forcedDiagonalSpeed;						//斜向低速
	WORD  maxPowerLevel;							//最大的子机数(power的最大百位值)	
	WORD  unknown1;									//不知道
	DWORD powerVar;									//power要修改的内容(40)
	DWORD maxDamage;								//单帧子弹最高伤害
	DWORD unknown[5];								//不知道
	void print(std::ostream &os)
	{
		using namespace std;
		os << ":maxPower:            \t" << maxPower << endl;
		os << ":totalOffset:         \t" << totalOffset << endl;
		os << ":(deleted):           \t" << hitBox << endl;
		os << ":(deleted):           \t" << powerAttractSpeed << endl;
		os << ":(deleted):           \t" << powerAttractHitBox << endl;
		os << ":normalSpeed:         \t" << normalSpeed << endl;
		os << ":forcedSpeed:         \t" << forcedSpeed << endl;
		os << ":normalDiagonalSpeed: \t" << normalDiagonalSpeed << endl;
		os << ":forcedDiagonalSpeed: \t" << forcedDiagonalSpeed << endl;
		os << ":maxPowerLevel:       \t" << maxPowerLevel << endl;
		os << ":unknown1:            \t" << unknown1 << endl;
		os << ":powerVar:            \t" << powerVar << endl;
		os << ":maxDamage:            \t" << maxDamage << endl;
		os << ":unknown:             \t";
		for (int i = 0; i < 5; i++)
		{
			os << unknown[i] << "\t";
		}
		os << endl;
	}
	void write(std::istream &is)
	{
		using namespace std;
		string strBuffer;
		is >> strBuffer;

		if (strBuffer != ":maxPower:") { cout << "Error:Wrong string,the original string is \":maxPower:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> maxPower;
		is >> strBuffer;
		if (strBuffer != ":totalOffset:") { cout << "Error:Wrong string,the original string is \":totalOffset:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> totalOffset;
		is >> strBuffer;
		if (strBuffer != ":(deleted):") { cout << "Error:Wrong string,the original string is \":(deleted):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> hitBox;
		is >> strBuffer;
		if (strBuffer != ":(deleted):") { cout << "Error:Wrong string,the original string is \":(deleted):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> powerAttractSpeed;
		is >> strBuffer;
		if (strBuffer != ":(deleted):") { cout << "Error:Wrong string,the original string is \":(deleted):\" ,but now is" << strBuffer; system("pause"); return; }
		is >> powerAttractHitBox;
		is >> strBuffer;
		if (strBuffer != ":normalSpeed:") { cout << "Error:Wrong string,the original string is \":normalSpeed:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> normalSpeed;
		is >> strBuffer;
		if (strBuffer != ":forcedSpeed:") { cout << "Error:Wrong string,the original string is \":forcedSpeed:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> forcedSpeed;
		is >> strBuffer;
		if (strBuffer != ":normalDiagonalSpeed:") { cout << "Error:Wrong string,the original string is \":normalDiagonalSpeed:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> normalDiagonalSpeed;
		is >> strBuffer;
		if (strBuffer != ":forcedDiagonalSpeed:") { cout << "Error:Wrong string,the original string is \":forcedDiagonalSpeed:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> forcedDiagonalSpeed;
		is >> strBuffer;
		if (strBuffer != ":maxPowerLevel:") { cout << "Error:Wrong string,the original string is \":maxPowerLevel:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> maxPowerLevel;
		is >> strBuffer;
		if (strBuffer != ":unknown1:") { cout << "Error:Wrong string,the original string is \":unknown1:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> unknown1;
		is >> strBuffer;
		if (strBuffer != ":powerVar:") { cout << "Error:Wrong string,the original string is \":powerVar:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> powerVar;
		is >> strBuffer;
		if (strBuffer != ":maxDamage:") { cout << "Error:Wrong string,the original string is \":maxDamage:\" ,but now is" << strBuffer; system("pause"); return; }
		is >> maxDamage;
		is >> strBuffer;
		if (strBuffer != ":unknown:")
		{
			cout << "Error:Wrong string,the original string is \":unknown:\" ,but now is" << strBuffer; system("pause"); return;
		}
		for (int i = 0; i < 5; i++)
		{
			is >> unknown[i];
		}
	}


};
