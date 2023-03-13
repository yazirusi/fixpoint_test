#include"log_read.h"

int main() {
    Log_data log_data;

    //ファイル読み込み関数を呼び出し
    log_data.load();
    
    int qNum;
    std::cout << "問題の番号を入力してください(1～4)\n";
    std::cout << "入力番号:";
    std::cin >> qNum;
    std::cout << std::endl;

    switch (qNum)
    {
        case 1:
            //
            log_data.question1();
            //時間経過関数呼び出し
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

//logファイル読み込み関数
void Log_data::load() {
    //名前入力
    std::cout << "ファイルの名前を入力するか、ファイルをドラッグアンドドロップしてください。\n";
    std::cout << "ファイル名:";
    std::cin >> filename;
    const char* filePath = filename.c_str();
    std::ifstream input_file(filename);
    FILE* file = fopen(filePath, "r");
    //ファイルが開くか保存する
    if (!input_file.is_open()) {
        std::cerr << "ファイルが開きませんでした。" << std::endl;
        std::exit(EXIT_FAILURE);
    }


    //ローカル変数
    int y, m, d, h, mm, s;
    char ad[20];
    char pn[5];

    //ファイルが終わるまで読み込む
    //log_deatクラスのメンバ変数に読み込んだ値を保存する
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

    //log.textから読み取ったデータを表示
    //タイムアウトした番号を保存
    for (int i = 0; i < year.size(); i++)
    {
        if (ping.at(i)=="-")
        {
            errorNum.push_back(i);
            /*std::cout << year.at(i) << "年";
            std::cout << month.at(i) << "月";
            std::cout << day.at(i) << "日";
            std::cout << Hours.at(i) << "時";
            std::cout << minutes.at(i) << "分";
            std::cout << seconds.at(i) << "秒";
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
        //応答無しのアドレスと同じかつpingが応答復帰している状態ならtrue
        if (address.at(errorNum.at(num)) == address.at(size) && ping.at(size) != "-") {
            //応答復帰した番号を入れる
            returnNum.push_back(size);
            //std::cout << "エラー番号："<<returnNum.at(num) << "\n";
            num++;
            //応答無しのアドレスが残っているか確認
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

        /*printf("故障日：");
        scanf("%d%d%d", &BYear, &BMonth, &BDay);
        printf("応当日：");
        scanf("%d%d%d", &FYear, &FMonth, &FDay);
        printf("\n");*/

        /* ① */
        day1 = 0;
        if ((!(year.at(errorNum.at(i)) % 4) && (year.at(errorNum.at(i)) % 100)) 
            || !(year.at(errorNum.at(i)) % 400)) {
            leap = 1;
        }
        else {
            leap = 0;
        }

        //printf("day1の数値=%d\n", month.at(errorNum.at(i)));

        for (ii = 1; ii <= month.at(errorNum.at(i)) - 1; ii++) {
            day1 += monthday[ii];
            if (ii == 2) day1 += leap;
        }

        day1 += day.at(errorNum.at(i));
        //printf("day1=%d\n", day1);

        /* ② */
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

        /* ③ */

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

        /* 経過日 */
        totalday = day2 + day3 - day1;
        //printf("day=%d\n", totalday);

        //----------------------------------------------------------------------
        //応答無し時間の合計値
        int noTime = 0;
        noTime = (Hours.at(errorNum.at(i)) * hh) + (minutes.at(errorNum.at(i)) * mm) 
            + seconds.at(errorNum.at(i));
        //printf("応答無し秒間:%d\n", noTime);
        //復帰時間の合計値
        int reTime = 0;
        reTime = (Hours.at(returnNum.at(i)) * hh) + (minutes.at(returnNum.at(i)) * mm)
            + seconds.at(returnNum.at(i));
        //printf("復帰秒間:%d\n", reTime);
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

        std::cout << "タイムアウト日時:"
            << year.at(errorNum.at(i)) << "年" << month.at(errorNum.at(i)) << "月"
            << day.at(errorNum.at(i)) << "日" << Hours.at(errorNum.at(i)) << "時" 
            << minutes.at(errorNum.at(i)) << "分"
            << seconds.at(errorNum.at(i)) << "秒" << "ip:" << address.at(errorNum.at(i))
            << "pin:" << ping.at(errorNum.at(i)) << "\n";
        
        std::cout << "復帰日時:"
            << year.at(returnNum.at(i)) << "年" << month.at(returnNum.at(i)) << "月"
            << day.at(returnNum.at(i)) << "日" << Hours.at(returnNum.at(i)) << "時"
            << minutes.at(returnNum.at(i)) << "分"
            << seconds.at(returnNum.at(i)) << "秒" << "ip:" << address.at(returnNum.at(i))
            << "pin:" << ping.at(returnNum.at(i)) << "\n";

        printf("故障期間:%d日%d時%d分%d秒\n", totalday, h, m, s);
    }
}

void Log_data::question2() {
    std::cout << "タイムアウトの回数制限を決めてください\n";
    std::cout << "タイムアウトの回数制限:";
    std::cin >> timeOutLimit;
    std::cout << std::endl;

    //errorAddress.resize(1);
    //timeOutNum.resize(1);
    //errorAddress.at(0).resize(1);
    //log.textから読み取ったデータを表示
    //タイムアウトしたアドレスを保存
    for (int i = 0; i < year.size(); i++)
    {
        //タイムアウトしたらtrue
        if (ping.at(i) == "-")
        {
            if (errorAddress.size() == 0)
            {
                errorAddress.push_back(address.at(i));
                timeOutNum.push_back(0);
            }
            for (int a = 0; a < errorAddress.size(); a++)
            {
                //同じアドレスの場合カウント+1する
                if (errorAddress.at(a) == address.at(i)) {
                    timeOutNum.push_back(timeOutNum.at(a)++);
                }
                else
                {
                    //同じアドレスがないならエラーアドレスに入れる
                    errorAddress.push_back(address.at(i));
                    timeOutNum.push_back(0);
                    //std::cout << "初めて1";
                }
                //同じアドレスの場合カウント+1する
                /*if (errorAddress.at(a).at(0) == address.at(i))
                {
                    int num = stoi(errorAddress.at(a).at(1));
                    num++;
                    errorAddress.at(a).at(1) = num;
                    std::cout << "連続マ"<<errorAddress.at(a).at(0) << "\n";
                }
                else
                {
                    //errorAddress.resize(errorAddress.size() + 1);
                    //errorAddress.at(0).resize(errorAddress.size() + 1);
                    //std::cout << "初めて1" << errorAddress.at(a).at(0) << "\n";
                    //errorAddress.at(a).push_back(address.at(i).front());
                    //errorAddress.resize(errorAddress.size() + 1);
                    //errorAddress.at(a).at(0) == address.at(i);
                    ///errorAddress.at(a).push_back(0);
                    errorAddress.at(a).push_back(address.at(i));
                    std::cout << "初めて" << errorAddress.at(a).at(0) << "\n";
                    std::cout << errorAddress.at(a).at(0)<<"or" << address.at(i) << "\n";
                }*/
            }
        }
        else {
            //タイムアウトが続いてるか判定
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

    //N回以上タイムアウトしていたら故障判定
    for (int a = 0; a < errorAddress.size(); a++)
    {
        //for (int b = 0; b < errorAddress.at(a).size(); b++)
        {
            //std::cout << errorAddress.at(a).at(b) << "\n";
            if (timeOutNum.at(a) >= timeOutLimit)
            {
                std::cout << errorAddress.at(a) << "のサーバーは" <<
                    timeOutLimit <<"回以上連続でタイムアウトしているので故障です\n";
            }
        }
    }
}

void Log_data::question3() {
    std::cout << "直近Tの回数制限を決めてください\n";
    std::cout << "直近Tの回数:";
    std::cin >> aveNum;
    std::cout << std::endl;

    std::cout << "平均mの秒数制限を決めてください\n";
    std::cout << "平均mの秒数:";
    std::cin >> aveSeconds;
    std::cout << std::endl;

    //---------------------------
    //時間が合ったら要素数を定数or動的な二次元配列へ
    //年を保持する変数
    int yearTmp[100][100];
    //月を保持する変数
    int monthTmp[100][100];
    //日を保持する変数
    int dayTmp[100][100];
    //時を保持する変数
    int HoursTmp[100][100];
    //分を保持する変数
    int minutesTmp[100][100];
    //秒を保持する変数
    int secondsTmp[100][100];
    //
    std::string addresTmp[100][100];
    //
    bool pingError[100][100];

    //----------------------------

    //
    for (int i = 0; i < year.size(); i++)
    {
        //タイムアウトしてないならtrue
        if (ping.at(i) != "-")
        {
            //最初に何も入っていないなら
            if (pingAddress.size() == 0)
            {
                pingAddress.push_back(address.at(i));
                pingNum.push_back(0);
                pingTotal.push_back(false);
            }
            //アドレス分回す
            for (int a = 0; a < pingAddress.size(); a++)
            {
                //同じアドレスの場合カウント+1する
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
                    /*std::cout << a << "a回：" << i << "i回：" << ping.at(i) << "ping："
                        << pingAddress.at(a) << ":" << pingNum.at(a) << ":"
                        << pingNumAve[a][pingNum.at(a)] << "\n";*/
                    break;
                }
                else if (a == pingAddress.size()-1)
                {
                    //同じアドレスがないならエラーアドレスに入れる
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

            //アドレス分回す
            for (int a = 0; a < pingAddress.size(); a++)
            {
                //各アドレスがm回以上pingデータを持っているか見る
                if (pingNum.at(a) >= aveNum)
                {
                    int total = 0;
                    int pingNumBig = pingNum.at(a);
                    int num = aveNum;
                    int ele1 = 0;
                    int ele2 = 0;
                    int ele3 = 0;
                    int ele4 = 0;
                    //直近m回の平均応答時間がtミリ秒を求める
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
                    //std::cout << pingAddress.at(a) << ":" << total << "ミリ秒\n";
                    //故障した期間を求める

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
                std::cout << addresTmp[i][n] << "のサーバーは"
                    << yearTmp[i][n - (aveNum - 1)] << "年"
                    << monthTmp[i][n - (aveNum - 1)] << "月"
                    << dayTmp[i][n - (aveNum - 1)] << "日"
                    << HoursTmp[i][n - (aveNum - 1)] << "時"
                    << minutesTmp[i][n - (aveNum - 1)] << "分"
                    << secondsTmp[i][n - (aveNum - 1)] << "秒"
                    << "から"
                    << yearTmp[i][n] << "年"
                    << monthTmp[i][n] << "月"
                    << dayTmp[i][n] << "日"
                    << HoursTmp[i][n] << "時"
                    << minutesTmp[i][n] << "分"
                    << secondsTmp[i][n] << "秒"
                    << "の間過負荷状態です。\n";
            }
        }
    }

    //デバッグ用
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