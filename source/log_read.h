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
// �N���X�̐錾
//----------------------------------------------------

//
class Log_data
{
public:
	Log_data();
	~Log_data();

	//�N��ێ�����ϐ�
	std::vector<int> year;
	//����ێ�����ϐ�
	std::vector<int> month;
	//����ێ�����ϐ�
	std::vector<int> day;
	//����ێ�����ϐ�
	std::vector<int> Hours;
	//����ێ�����ϐ�
	std::vector<int> minutes;
	//�b��ێ�����ϐ�
	std::vector<int> seconds;
	//�A�h���X��ێ�����ϐ�
	std::vector<std::string> address;
	//ping��ێ�����ϐ�
	std::vector<std::string> ping;
	//�^�C���A�E�g�����ԍ���ێ�����ϐ�
	std::vector<int> errorNum;
	//�^�C���A�E�g���畜�A�����ԍ���ێ�����ϐ�
	std::vector<int> returnNum;
	//�^�C���A�E�g�����A�h���X�ƃ^�C���A�E�g�񐔂�ێ�����ϐ�
	//std::vector<std::vector<std::string>> errorAddress;
	std::vector<std::string> errorAddress;
	//�^�C���A�E�g�����A�h���X�̃J�E���g��(�Y�������ꏏ)
	std::vector<int> timeOutNum;
	//question2�^�C���A�E�g�̉񐔐����̕ϐ�
	int timeOutLimit;
	//question3����m��̕ϐ�
	int aveNum;
	//question3����t�b�̕ϐ�
	int aveSeconds;
	//ping�v�Z�̃A�h���X�ꗗ
	std::vector<std::string> pingAddress;
	//���ꂼ��̃A�h���X�̉ߕ��׏��
	std::vector<bool> pingTotal;
	//�A�h���X�̒���T��𐔂��邽�߂̕ϐ�
	std::vector<int> pingNum;
	//
	int pingNumAve[100][100];

	//log�t�@�C���ǂݍ��݊֐�
	void load();
	//�o�ߎ��Ԋ֐�
	void timeCount();
	//�ݖ�P�̊֐�
	void question1();
	//�ݖ�Q�̊֐�
	void question2();
	//�ݖ�R�̊֐�
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
// �\���̂̐錾
//----------------------------------------------------

//
typedef struct {
	
}log_data;

//----------------------------------------------------
// �ϐ��̐錾
//----------------------------------------------------

//�ǂݍ��ރt�@�C���̖��O
std::string filename;

//----------------------------------------------------
// �֐��̐錾
//----------------------------------------------------