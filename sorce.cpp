#include<iostream>
#include<string>
#include<fstream>
#include<regex>

class Birthday {
	std::string name, week;
	int Year{ 0 }, Month{ 0 }, Day{ 0 };

public:
	void setName(const std::string& newname) { name = newname; }
	std::string getName() { return name; }
	void setWeek(const std::string& newweek) { week = newweek; }
	std::string getWeek() { return week; }
	void setYear(int newYear) { Year = newYear; }
	int getYear() { return Year; }
	void setMonth(int newmonth) { Month = newmonth; }
	int getMonth() { return Month; }
	void setDay(int newday) { Day = newday; }
	int getDay() { return Day; }
};

int C, Y, G;
int year = 0, month = 0, day = 0;
Birthday A;

void save()
{
	std::string deta;
	std::cin >> deta;
	std::ofstream outfile("deta.txt", std::ios_base::out);
	outfile << deta;
}

void set(int m)
{
	if (m <= 2) {
		year = year - 1;
		month = month + 12;
	}
}

void CY(int y)
{
	C = floor(y / 100);
	Y = y % 100;
}

void cale(int y, int c)
{
	if (1582 <= y) {
		G = 5 * c + floor(c / 4);
	}
	else if (4 <= y <= 1582) {
		G = 6 * c + 5;
	}
}

void week(int y, int m, int d, int y2, int g)
{
	int h = 0;
	int f = floor(26 * (m + 1) / 10);
	int v = floor(y2 / 4);
	h = (d + f + y2 + v + g) % 7;

	if (h == 0) {
		A.setWeek("土曜日");
	}
	else if (h == 1) {
		A.setWeek("日曜日");
	}
	else if (h == 2) {
		A.setWeek("月曜日");
	}
	else if (h == 3) {
		A.setWeek("火曜日");
	}
	else if (h == 4) {
		A.setWeek("水曜日");
	}
	else if (h == 5) {
		A.setWeek("木曜日");
	}
	else if (h == 6) {
		A.setWeek("金曜日");
	}
}

void show() {
	std::cout << A.getName() << "さんが生まれた" << A.getYear() << "年" << A.getMonth() << "月" << A.getDay() << "日は" << A.getWeek() << "です\n";
}

int main()
{
	std::cout << "氏名,生年月日(西暦)を入力してください\n";
	std::cout << "記入例:氏名,1992,2,14(1992年2月14日の場合)\n\n";
	save();
	std::ifstream detafile("deta.txt"); //ファイル読み込み
	std::string str;
	std::regex rx(R"(,|、)");

	while (getline(detafile, str))
	{
		std::sregex_token_iterator it(str.begin(), str.end(), rx, -1);
		std::sregex_token_iterator end;

		while (it != end)
		{
			A.setName(*it++);
			year = stoi(*it++);
			month = stoi(*it++);
			day = stoi(*it++);
			A.setYear(year);
			A.setMonth(month);
			A.setDay(day);
		}
		detafile.close();
	}
	set(month);
	CY(year);
	cale(year, C);
	week(year, month, day, Y, G);
	show();
}