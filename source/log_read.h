#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <GL/glut.h>
#include <sstream>
#include <iomanip>

#include <time.h>
//#include <unistd.h>
#pragma warning(disable : 4996)

//----------------------------------------------------
// クラスの宣言
//----------------------------------------------------

//
class Log_data
{
public:
	Log_data();
	~Log_data();

	//年を保持する変数
	std::vector<int> year;
	//月を保持する変数
	std::vector<int> month;
	//日を保持する変数
	std::vector<int> day;
	//時を保持する変数
	std::vector<int> Hours;
	//分を保持する変数
	std::vector<int> minutes;
	//秒を保持する変数
	std::vector<int> seconds;
	//アドレスを保持する変数
	std::vector<std::string> address;
	//pingを保持する変数
	std::vector<std::string> ping;
	//タイムアウトした番号を保持する変数
	std::vector<int> errorNum;
	//タイムアウトから復帰した番号を保持する変数
	std::vector<int> returnNum;
	//タイムアウトしたアドレスとタイムアウト回数を保持する変数
	//std::vector<std::vector<std::string>> errorAddress;
	std::vector<std::string> errorAddress;
	//タイムアウトしたアドレスのカウント数(添え字が一緒)
	std::vector<int> timeOutNum;
	//question2タイムアウトの回数制限の変数
	int timeOutLimit;
	//question3直近m回の変数
	int aveNum;
	//question3平均t秒の変数
	int aveSeconds;
	//ping計算のアドレス一覧
	std::vector<std::string> pingAddress;
	//それぞれのアドレスの過負荷状態
	std::vector<bool> pingTotal;
	//アドレスの直近T回を数えるための変数
	std::vector<int> pingNum;
	//
	int pingNumAve[100][100];

	//logファイル読み込み関数
	void load();
	//経過時間関数
	void timeCount();
	//設問１の関数
	void question1();
	//設問２の関数
	void question2();
	//設問３の関数
	void question3();

private:
	
};

Log_data::Log_data()
{
}

Log_data::~Log_data()
{
}

//----------------------------------------------------
// 構造体の宣言
//----------------------------------------------------

//
typedef struct {
	
}log_data;

//----------------------------------------------------
// 変数の宣言
//----------------------------------------------------

//読み込むファイルの名前
std::string filename;

//----------------------------------------------------
// 関数の宣言
//----------------------------------------------------