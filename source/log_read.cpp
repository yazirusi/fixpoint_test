#include"log_read.h"

int main() {
    Log_data log_data;

    //�t�@�C���ǂݍ��݊֐����Ăяo��
    log_data.load();
    
    int qNum;
    std::cout << "���̔ԍ�����͂��Ă�������(1�`4)\n";
    std::cout << "���͔ԍ�:";
    std::cin >> qNum;
    std::cout << std::endl;

    switch (qNum)
    {
        case 1:
            //
            log_data.question1();
            //���Ԍo�ߊ֐��Ăяo��
            log_data.timeCount();
            break;
        case 2:
            log_data.question2();
            break;
        case 3:
            log_data.question3();
            break;
    }
}

//log�t�@�C���ǂݍ��݊֐�
void Log_data::load() {
    //���O����
    std::cout << "�t�@�C���̖��O����͂��邩�A�t�@�C�����h���b�O�A���h�h���b�v���Ă��������B\n";
    std::cout << "�t�@�C����:";
    std::cin >> filename;
    const char* filePath = filename.c_str();
    std::ifstream input_file(filename);
    FILE* file = fopen(filePath, "r");
    //�t�@�C�����J�����ۑ�����
    if (!input_file.is_open()) {
        std::cerr << "�t�@�C�����J���܂���ł����B" << std::endl;
        std::exit(EXIT_FAILURE);
    }


    //���[�J���ϐ�
    int y, m, d, h, mm, s;
    char ad[20];
    char pn[5];

    //�t�@�C�����I���܂œǂݍ���
    //log_deat�N���X�̃����o�ϐ��ɓǂݍ��񂾒l��ۑ�����
    while (fscanf(file, "%4d%2d%2d%2d%2d%2d,%[^,],%s", &y, &m, &d, &h, &mm, &s, &ad, &pn) != EOF) {
        year.push_back(y);
        month.push_back(m);
        day.push_back(d);
        Hours.push_back(h);
        minutes.push_back(mm);
        seconds.push_back(s);
        address.push_back(ad);
        ping.push_back(pn);
    }
    fclose(file);

    //log.text����ǂݎ�����f�[�^��\��
    //�^�C���A�E�g�����ԍ���ۑ�
    for (int i = 0; i < year.size(); i++)
    {
        if (ping.at(i)=="-")
        {
            errorNum.push_back(i);
            /*std::cout << year.at(i) << "�N";
            std::cout << month.at(i) << "��";
            std::cout << day.at(i) << "��";
            std::cout << Hours.at(i) << "��";
            std::cout << minutes.at(i) << "��";
            std::cout << seconds.at(i) << "�b";
            std::cout << "ip:" << address.at(i);
            std::cout << "pin:" << ping.at(i) << "\n";*/
        }
    }
}

void Log_data::question1() {
    int num = 0;
    int size = errorNum.at(0) + 1;
    while (1)
    {
        //���������̃A�h���X�Ɠ�������ping���������A���Ă����ԂȂ�true
        if (address.at(errorNum.at(num)) == address.at(size) && ping.at(size) != "-") {
            //�������A�����ԍ�������
            returnNum.push_back(size);
            //std::cout << "�G���[�ԍ��F"<<returnNum.at(num) << "\n";
            num++;
            //���������̃A�h���X���c���Ă��邩�m�F
            if (num >= errorNum.size())
            {
                break;
            }
            else {
                size = errorNum.at(num);
            }
        }
        size++;
    }

    /*for (int i = errorNum.at(0); ; i++)
    {
        if (address.at(errorNum.at(0)) == address.at(i) && ping.at(i) != "-") {
            returnNum.push_back(i);
        }
    }*/
}

void Log_data::timeCount()
{
    /*int hms1, hms2, hms3;
    int hms4, hms5, hms6;
    int hms7, hms8, hms9;*/
    int h, m, s;
    int hh = 3600;
    int mm = 60;
    int bigH = 86400;

    for (int i = 0; i < errorNum.size(); i++)
    {
        int BYear, BMonth, BDay, FYear, FMonth, FDay, leap;
        int monthday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
        int totalday, day1, day2, day3;
        int ii;

        /*printf("�̏���F");
        scanf("%d%d%d", &BYear, &BMonth, &BDay);
        printf("�������F");
        scanf("%d%d%d", &FYear, &FMonth, &FDay);
        printf("\n");*/

        /* �@ */
        day1 = 0;
        if ((!(year.at(errorNum.at(i)) % 4) && (year.at(errorNum.at(i)) % 100)) 
            || !(year.at(errorNum.at(i)) % 400)) {
            leap = 1;
        }
        else {
            leap = 0;
        }

        //printf("day1�̐��l=%d\n", month.at(errorNum.at(i)));

        for (ii = 1; ii <= month.at(errorNum.at(i)) - 1; ii++) {
            day1 += monthday[ii];
            if (ii == 2) day1 += leap;
        }

        day1 += day.at(errorNum.at(i));
        //printf("day1=%d\n", day1);

        /* �A */
        day2 = 0;

        for (ii = year.at(errorNum.at(i)); ii <= year.at(returnNum.at(i)) - 1; ii++) {
            day2 += 365;
            if ((!(ii % 4) && (ii % 100)) || !(ii % 400)) {
                leap = 1;
            }
            else {
                leap = 0;
            }
            day2 += leap;
        }

        //printf("day2=%d\n", day2);

        /* �B */

        day3 = 0;

        if ((!(year.at(returnNum.at(i)) % 4) && (year.at(returnNum.at(i)) % 100)) 
            || !(year.at(returnNum.at(i)) % 400)) {
            leap = 1;
        }
        else {
            leap = 0;
        }

        for (ii = 1; ii <= month.at(returnNum.at(i)) - 1; ii++) {
            day3 += monthday[ii];
            if (ii == 2) day3 += leap;
        }

        day3 += day.at(returnNum.at(i));
        //printf("day3=%d\n", day3);

        /* �o�ߓ� */
        totalday = day2 + day3 - day1;
        //printf("day=%d\n", totalday);

        //----------------------------------------------------------------------
        //�����������Ԃ̍��v�l
        int noTime = 0;
        noTime = (Hours.at(errorNum.at(i)) * hh) + (minutes.at(errorNum.at(i)) * mm) 
            + seconds.at(errorNum.at(i));
        //printf("���������b��:%d\n", noTime);
        //���A���Ԃ̍��v�l
        int reTime = 0;
        reTime = (Hours.at(returnNum.at(i)) * hh) + (minutes.at(returnNum.at(i)) * mm)
            + seconds.at(returnNum.at(i));
        //printf("���A�b��:%d\n", reTime);
        int c = 0;
        if (noTime < reTime)
        {
            c = reTime - noTime;
        }
        else if (noTime > reTime)
        {
            c = reTime - noTime;
            c = bigH + c;
        }
        //printf("%d\n", c);
        h = c / hh;
        c = c % hh;
        m = c / mm;
        c = c % mm;
        s = c;

        std::cout << "�^�C���A�E�g����:"
            << year.at(errorNum.at(i)) << "�N" << month.at(errorNum.at(i)) << "��"
            << day.at(errorNum.at(i)) << "��" << Hours.at(errorNum.at(i)) << "��" 
            << minutes.at(errorNum.at(i)) << "��"
            << seconds.at(errorNum.at(i)) << "�b" << "ip:" << address.at(errorNum.at(i))
            << "pin:" << ping.at(errorNum.at(i)) << "\n";
        
        std::cout << "���A����:"
            << year.at(returnNum.at(i)) << "�N" << month.at(returnNum.at(i)) << "��"
            << day.at(returnNum.at(i)) << "��" << Hours.at(returnNum.at(i)) << "��"
            << minutes.at(returnNum.at(i)) << "��"
            << seconds.at(returnNum.at(i)) << "�b" << "ip:" << address.at(returnNum.at(i))
            << "pin:" << ping.at(returnNum.at(i)) << "\n";

        printf("�̏����:%d��%d��%d��%d�b\n", totalday, h, m, s);
    }
}

void Log_data::question2() {
    std::cout << "�^�C���A�E�g�̉񐔐��������߂Ă�������\n";
    std::cout << "�^�C���A�E�g�̉񐔐���:";
    std::cin >> timeOutLimit;
    std::cout << std::endl;

    //errorAddress.resize(1);
    //timeOutNum.resize(1);
    //errorAddress.at(0).resize(1);
    //log.text����ǂݎ�����f�[�^��\��
    //�^�C���A�E�g�����A�h���X��ۑ�
    for (int i = 0; i < year.size(); i++)
    {
        //�^�C���A�E�g������true
        if (ping.at(i) == "-")
        {
            if (errorAddress.size() == 0)
            {
                errorAddress.push_back(address.at(i));
                timeOutNum.push_back(0);
            }
            for (int a = 0; a < errorAddress.size(); a++)
            {
                //�����A�h���X�̏ꍇ�J�E���g+1����
                if (errorAddress.at(a) == address.at(i)) {
                    timeOutNum.push_back(timeOutNum.at(a)++);
                }
                else
                {
                    //�����A�h���X���Ȃ��Ȃ�G���[�A�h���X�ɓ����
                    errorAddress.push_back(address.at(i));
                    timeOutNum.push_back(0);
                    //std::cout << "���߂�1";
                }
                //�����A�h���X�̏ꍇ�J�E���g+1����
                /*if (errorAddress.at(a).at(0) == address.at(i))
                {
                    int num = stoi(errorAddress.at(a).at(1));
                    num++;
                    errorAddress.at(a).at(1) = num;
                    std::cout << "�A���}"<<errorAddress.at(a).at(0) << "\n";
                }
                else
                {
                    //errorAddress.resize(errorAddress.size() + 1);
                    //errorAddress.at(0).resize(errorAddress.size() + 1);
                    //std::cout << "���߂�1" << errorAddress.at(a).at(0) << "\n";
                    //errorAddress.at(a).push_back(address.at(i).front());
                    //errorAddress.resize(errorAddress.size() + 1);
                    //errorAddress.at(a).at(0) == address.at(i);
                    ///errorAddress.at(a).push_back(0);
                    errorAddress.at(a).push_back(address.at(i));
                    std::cout << "���߂�" << errorAddress.at(a).at(0) << "\n";
                    std::cout << errorAddress.at(a).at(0)<<"or" << address.at(i) << "\n";
                }*/
            }
        }
        else {
            //�^�C���A�E�g�������Ă邩����
            for (int z = 0; z < errorAddress.size(); z++)
            {
                if (errorAddress.at(z) == address.at(i) 
                    && timeOutNum.at(z) < timeOutLimit)
                {
                    timeOutNum.at(z) = 0;
                }
            }
        }
    }

    //N��ȏ�^�C���A�E�g���Ă�����̏ᔻ��
    for (int a = 0; a < errorAddress.size(); a++)
    {
        //for (int b = 0; b < errorAddress.at(a).size(); b++)
        {
            //std::cout << errorAddress.at(a).at(b) << "\n";
            if (timeOutNum.at(a) >= timeOutLimit)
            {
                std::cout << errorAddress.at(a) << "�̃T�[�o�[��" <<
                    timeOutLimit <<"��ȏ�A���Ń^�C���A�E�g���Ă���̂Ō̏�ł�\n";
            }
        }
    }
}

void Log_data::question3() {
    std::cout << "����T�̉񐔐��������߂Ă�������\n";
    std::cout << "����T�̉�:";
    std::cin >> aveNum;
    std::cout << std::endl;

    std::cout << "����m�̕b�����������߂Ă�������\n";
    std::cout << "����m�̕b��:";
    std::cin >> aveSeconds;
    std::cout << std::endl;

    //---------------------------
    //���Ԃ���������v�f����萔or���I�ȓ񎟌��z���
    //�N��ێ�����ϐ�
    int yearTmp[100][100];
    //����ێ�����ϐ�
    int monthTmp[100][100];
    //����ێ�����ϐ�
    int dayTmp[100][100];
    //����ێ�����ϐ�
    int HoursTmp[100][100];
    //����ێ�����ϐ�
    int minutesTmp[100][100];
    //�b��ێ�����ϐ�
    int secondsTmp[100][100];
    //
    std::string addresTmp[100][100];
    //
    bool pingError[100][100];

    //----------------------------

    //
    for (int i = 0; i < year.size(); i++)
    {
        //�^�C���A�E�g���ĂȂ��Ȃ�true
        if (ping.at(i) != "-")
        {
            //�ŏ��ɉ��������Ă��Ȃ��Ȃ�
            if (pingAddress.size() == 0)
            {
                pingAddress.push_back(address.at(i));
                pingNum.push_back(0);
                pingTotal.push_back(false);
            }
            //�A�h���X����
            for (int a = 0; a < pingAddress.size(); a++)
            {
                //�����A�h���X�̏ꍇ�J�E���g+1����
                if (pingAddress.at(a) == address.at(i)) {
                    //pingTotal.at(a) = pingTotal.at(a) + stoi(ping.at(i));
                    pingNumAve[a][pingNum.at(a)] = stoi(ping.at(i));
                    yearTmp[a][pingNum.at(a)] = year.at(i);
                    monthTmp[a][pingNum.at(a)] = month.at(i);
                    dayTmp[a][pingNum.at(a)] = day.at(i);
                    HoursTmp[a][pingNum.at(a)] = Hours.at(i);
                    minutesTmp[a][pingNum.at(a)] = minutes.at(i);
                    secondsTmp[a][pingNum.at(a)] = seconds.at(i);
                    addresTmp[a][pingNum.at(a)] = address.at(i);
                    pingNum.at(a)++;
                    /*std::cout << a << "a��F" << i << "i��F" << ping.at(i) << "ping�F"
                        << pingAddress.at(a) << ":" << pingNum.at(a) << ":"
                        << pingNumAve[a][pingNum.at(a)] << "\n";*/
                    break;
                }
                else if (a == pingAddress.size()-1)
                {
                    //�����A�h���X���Ȃ��Ȃ�G���[�A�h���X�ɓ����
                    pingAddress.push_back(address.at(i));
                    pingNumAve[pingAddress.size()-1][0] = stoi(ping.at(i));
                    yearTmp[pingAddress.size() - 1][0] = year.at(i);
                    monthTmp[pingAddress.size() - 1][0] = month.at(i);
                    dayTmp[pingAddress.size() - 1][0] = day.at(i);
                    HoursTmp[pingAddress.size() - 1][0] = Hours.at(i);
                    minutesTmp[pingAddress.size() - 1][0] = minutes.at(i);
                    secondsTmp[pingAddress.size() - 1][0] = seconds.at(i);
                    addresTmp[pingAddress.size() - 1][0] = address.at(i);
                    pingNum.push_back(1);
                    pingTotal.push_back(false);
                    ///pingNum.resize(pingNum.size() + 1);
                    ///pingNum.at(pingAddress.size() - 1) = 1;
                    break;
                }
            }

            //�A�h���X����
            for (int a = 0; a < pingAddress.size(); a++)
            {
                //�e�A�h���X��m��ȏ�ping�f�[�^�������Ă��邩����
                if (pingNum.at(a) >= aveNum)
                {
                    int total = 0;
                    int pingNumBig = pingNum.at(a);
                    int num = aveNum;
                    int ele1 = 0;
                    int ele2 = 0;
                    int ele3 = 0;
                    int ele4 = 0;
                    //����m��̕��ω������Ԃ�t�~���b�����߂�
                    while (num >= 1)
                    {
                        if (num == aveNum)
                        {
                            /*elementNum1.push_back(a);
                            elementNum2.push_back(pingNumBig - num);*/
                            ele1 = a;
                            ele2 = pingNumBig - num;
                        }
                        /*std::cout << total+ pingNumAve[a][pingNumBig - num] << "="
                            << total << "+"
                            << pingNumAve[a][pingNumBig - num] << "\n";*/
                        total += pingNumAve[a][pingNumBig - num];
                        num--;
                        if (num >= 1)
                        {
                            /*elementNum3.push_back(a);
                            elementNum4.push_back(pingNumBig - num + 1);*/
                            ele3 = a;
                            ele4 = pingNumBig - num + 1;
                        }
                    }
                    if ((total = total / aveNum) > aveSeconds)
                    {
                        pingTotal.at(a) = true;
                        pingError[a][pingNum.at(a)-1] = false;
                    }
                    //std::cout << pingAddress.at(a) << ":" << total << "�~���b\n";
                    //�̏Ⴕ�����Ԃ����߂�

                }
            }
        }
    }

    for (int i = 0; i < 100; i++)
    //for (int i = 0; i < elementNum1.size(); i++)
    {
        for (int n = 0; n < 100; n++)
        {
            if (pingError[i][n] == false)
            {
                std::cout << addresTmp[i][n] << "�̃T�[�o�[��"
                    << yearTmp[i][n - (aveNum - 1)] << "�N"
                    << monthTmp[i][n - (aveNum - 1)] << "��"
                    << dayTmp[i][n - (aveNum - 1)] << "��"
                    << HoursTmp[i][n - (aveNum - 1)] << "��"
                    << minutesTmp[i][n - (aveNum - 1)] << "��"
                    << secondsTmp[i][n - (aveNum - 1)] << "�b"
                    << "����"
                    << yearTmp[i][n] << "�N"
                    << monthTmp[i][n] << "��"
                    << dayTmp[i][n] << "��"
                    << HoursTmp[i][n] << "��"
                    << minutesTmp[i][n] << "��"
                    << secondsTmp[i][n] << "�b"
                    << "�̊ԉߕ��׏�Ԃł��B\n";
            }
        }
    }

    //�f�o�b�O�p
    /*
    for (int a = 0; a < pingAddress.size(); a++)
    {
        //if (pingTotal.at(a) == true)
        //std::cout << pingAddress.at(a) << "\n";

        for (int i = 0; i < pingNum.at(a); i++)
        {
            std::cout << pingAddress.at(a) << ":"
                << pingNum.at(a) << ":"
                << pingNumAve[a][i] << "\n";
        }
    }*/
}