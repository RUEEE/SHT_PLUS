// SHT_PLUS.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "method.h"
#pragma pack(1)

playerArg normalArg;
std::vector<int> offsets;
std::vector<position> powerPosN;
std::vector<position> powerPosF;
std::vector<std::vector<eachShot>> shots;
//sht结构: playerArg,powerPosN,powerPosF,offsets,shots
void readSht(std::istream &shtFile, std::ostream &fout)
{
	using namespace std;
	shtFile.read((char*)&normalArg, sizeof(normalArg));
	int numPower = normalArg.maxPower;
	int numOffset = normalArg.totalOffset;
	for (int i = 0; i < numPower; i++)
	{
		for (int j = -1; j < i; j++)
		{
			position subP;
			shtFile.read((char*)&subP, sizeof(subP));
			powerPosN.push_back(subP);
		}
	}
	
	for (int i = 0; i < numPower; i++)
	{
		for (int j = -1; j < i; j++)
		{
			position subP;
			shtFile.read((char*)&subP, sizeof(subP));
			powerPosF.push_back(subP);
		}
	}
	
	for (int i = 0; i < numOffset; i++)
	{
		int w;
		shtFile.read((char*)&w, sizeof(w));
		offsets.push_back(w);
	}
	
	for (int i = 0; i < numOffset; i++)
	{
		vector<eachShot> ebx;
		while (1)
		{
			eachShot eax;
			int testNum;
			shtFile.read((char*)&testNum, sizeof(testNum));
			if (testNum == 0xFFFFFFFF)break;
			*(int*)&eax.rate = testNum;
			shtFile.read((char*)(&eax.pos), sizeof(eax)-sizeof(int));
			ebx.push_back(eax);
		}
		shots.push_back(ebx);
	}
	//读取完了
	normalArg.print(fout);
	fout << "\n\t\t:powerPosN\n";
	for (int i = 0,k=0; i < numPower; i++)
	{
		fout << "  ~Power " << i+1 << endl;
		for (int j = -1; j < i; j++,k++)
		{
			fout << powerPosN[k].x << "\t" << powerPosN[k].y << endl;
		}
		
	}
	fout << "\n\t\t:powerPosF\n";
	for (int i = 0, k = 0; i < numPower; i++)
	{
		fout << "  ~Power " << i + 1 << endl;
		for (int j = -1; j < i; j++, k++)
		{
			fout << powerPosF[k].x << "\t" << powerPosF[k].y << endl;
		}

	}
	
	fout << "\n\t\t:shots\n";

	{
		int shotsi = 1;
		for (auto &eax : shots)
		{
			fout.clear();
			fout << "\t  @shots " << shotsi << endl;;
			int shotsj = 1;
			for (auto &ebx : eax)
			{
				fout << "  :shot " << shotsj << endl;
				ebx.print(fout);
				shotsj++;
			}fout << ":end" << endl;
			shotsi++;
		}
	}

}

void writeSht(std::istream &txtFile, std::ostream &fout)
{
	using namespace std;
	normalArg.write(txtFile);
	if (txtFile.fail()) { cout << "Error:Stream fail,at normalArg"; system("pause"); return; }
	int numPower = normalArg.maxPower;
	int numOffset = normalArg.totalOffset;
	string strBuffer;

	txtFile >> strBuffer;
	if (strBuffer != ":powerPosN") { cout << "Error:Wrong string,the original string is \":powerPosN\" ,but now is" << strBuffer; system("pause"); return; }
	for (int i = 0; i < numPower; i++)
	{
		txtFile >> strBuffer;
		if (strBuffer != "~Power") { cout << "Error:Wrong string,the original string is \"~Power\" ,but now is" << strBuffer; system("pause"); return; }
		int e; txtFile >> e;
		if (e != i + 1) { cout << "Error:Wrong number,the original is \"~Power " << i + 1 << "\" ,but now is" << "~Power " << e; system("pause"); return; }
		for (int j = -1; j < i; j++)
		{
			position subP;
			float x, y;
			txtFile >> x >> y;
			subP.x = x; subP.y = y;
			powerPosN.push_back(subP);
		}
	}
	if (txtFile.fail()) { cout << "Error:Stream fail,at PowerPosN"; system("pause"); return; }

	txtFile >> strBuffer;
	if (strBuffer != ":powerPosF") { cout << "Error:Wrong string,the original string is \":powerPosF\" ,but now is" << strBuffer; system("pause"); return; }
	for (int i = 0; i < numPower; i++)
	{
		txtFile >> strBuffer;
		if (strBuffer != "~Power") { cout << "Error:Wrong string,the original string is \"~Power\" ,but now is" << strBuffer; system("pause"); return; }
		int e; txtFile >> e;
		if (e != i + 1) { cout << "Error:Wrong number,the original is \"~Power " << i + 1 << "\" ,but now is" << "~Power " << e; system("pause"); return; }
		for (int j = -1; j < i; j++)
		{
			position subP;
			float x, y;
			txtFile >> x >> y;
			subP.x = x; subP.y = y;
			powerPosF.push_back(subP);
		}
	}
	if (txtFile.fail()) { cout << "Error:Stream fail,at PowerPosF"; system("pause"); return; }

	txtFile >> strBuffer;
	if (strBuffer != ":shots") { cout << "Error:Wrong string,the original string is \":shots\" ,but now is" << strBuffer; system("pause"); return; }
	offsets.push_back(0);
	for (int i = 0, e; i < numOffset; i++)
	{
		vector<eachShot> eax;
		txtFile >> strBuffer;
		if (strBuffer != "@shots") { cout << "Error:Wrong string,the original string is \"@shots\" ,but now is" << strBuffer; system("pause"); return; }
		txtFile >> e;
		if (e != i + 1) { cout << "Error:Wrong number,the original is \"@shots " << i + 1 << "\" ,but now is" << "@shots " << e; system("pause"); return; }
		int si = 0;
		while (1)
		{
			si++;
			eachShot ebx;
			txtFile >> strBuffer;
			if (strBuffer == ":end")break;
			if (strBuffer != ":shot") { cout << "Error:Wrong string,the original string is \":shot\" ,but now is" << strBuffer; system("pause"); return; }
			int e;
			txtFile >> e;
			if (e != si) { cout << "Error:Wrong number,the original is \":shot " << i + 1 << "\" ,but now is" << ":shot " << e; system("pause"); return; }
			ebx.write(txtFile);
			if (txtFile.fail())
			{
				cout << "Error:Stream fail,at shots" << i + 1 << " shot" << si; system("pause"); return;
			}
			eax.push_back(ebx);
		}
		shots.push_back(eax);
		int offset = *offsets.rbegin() + eax.size() * 88 + 4;
		offsets.push_back(offset);
	}
	offsets.pop_back();
	fout.write((char*)&normalArg, sizeof(normalArg));
	for (auto &i : powerPosN)
	{
		fout.write((char*)&i, sizeof(i));
	}
	for (auto &i : powerPosF)
	{
		fout.write((char*)&i, sizeof(i));
	}
	for (auto &w : offsets)
	{
		fout.write((char*)&w, sizeof(w));
	}
	int F = -1;
	for (auto &eax : shots)
	{
		for (auto &ebx : eax)
		{
			fout.write((char*)&ebx, sizeof(ebx));
		}
		fout.write((char*)&F,sizeof(F));
	}
}


int main(int argc, char *argv[])
{
	using namespace std;
	//[v] 版本号
	if (argc == 2 && !strcmp(argv[1],"v"))
	{
		cout << "made by 鶸,版本v0.01(18.7.1)";
		system("pause");
	}
	//[u,sht目录,txt目录]解包
	if (argc == 4 && !strcmp(argv[1], "u"))
	{
		fstream shtFile(argv[2], ios::in | ios::binary);
		fstream fout(argv[3], ios::out);
		fout << setiosflags(ios::fixed);
		fout << setprecision(8);
		readSht(shtFile, fout);
		fout.close();
		shtFile.close();
		cout << "解包成功";
	}
	//[p,sht目录,txt目录]打包
	if (argc == 4 && !strcmp(argv[1], "p"))
	{
		fstream txtFile(argv[3], ios::in);
		fstream fout(argv[2], ios::out | ios::binary);
		writeSht(txtFile, fout);
		txtFile.close();
		fout.close();
		cout << "打包成功";
	}
	Sleep(500);
    return 0;
}

