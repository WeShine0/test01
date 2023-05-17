#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<cstdio>
using namespace std;
int cnt = 0, flag2, Myid;
class Date {
public:
	int year;
	int month;
	int day;
};

class MyAccount {
public:
	double money;
	int flag_print;
	int dateint;
	string name;
	string type;
	string ps;
	Date date;  // 添加一个Date对象作为日期成员
}MyACC[1000], T;  //定义一个类来存储账目表

class MonthStats {
public:
	double income;
	double expense;
	double balance;
};


void Dateint()
{
	for (int i = 1; i <= cnt; i++)
	{
		MyACC[i].dateint = 10000 * MyACC[i].date.year + 100 * MyACC[i].date.month + MyACC[i].date.day;
	}
}

void Hand_Input();
void File_Input();
void Deleteid(MyAccount* arr, int& size, int index);

void input()
{
	cout << "手动输入账务请输1，文件读取账务请输2" << endl;
	cin >> flag2;
	if (flag2 == 1)
		Hand_Input();
	else if (flag2 == 2)
		File_Input();
	Dateint();
}

int datejudge(int y, int m, int d)                           //判断日期合法性 
{
	int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		month[1] = 29;
	return  y >= 1000 && y <= 9999 && m > 0 && m <= 12 && d > 0 && d <= month[m - 1];
}

void TypeInput(string& TYPE)
{
	int choice;
	bool validChoice = false;

	while (!validChoice) {
		cin >> choice;

		switch (choice)
		{
		case 1:
			TYPE = "饮食";
			validChoice = true;
			break;
		case 2:
			TYPE = "学习";
			validChoice = true;
			break;
		case 3:
			TYPE = "医疗";
			validChoice = true;
			break;
		case 4:
			TYPE = "交通";
			validChoice = true;
			break;
		case 5:
			TYPE = "水电";
			validChoice = true;
			break;
		case 6:
			TYPE = "娱乐";
			validChoice = true;
			break;
		case 7:
			TYPE = "服饰";
			validChoice = true;
			break;
		case 8:
			TYPE = "借出";
			validChoice = true;
			break;
		case 9:
			TYPE = "收入";
			validChoice = true;
			break;
		case 0:
			TYPE = "其他";
			validChoice = true;
			break;
		default:
			cout << "选择不存在！请重新输入数字：" << endl;
			break;
		}
	}
}


void Hand_Input() //输入账目函数
{
	int flag;
	char temp;
	cout << "您需要录入多少条账务记录？\n";
	cin >> flag;
	cin.ignore();//忽略换行符
	while (flag--)
	{
		cnt++;
		Myid = cnt;
		cout << "请输入收支金额\n";
		cin >> MyACC[Myid].money;
		do {
			cout << "输入正确的交易日期(年 月 日)" << endl;
			cin >> MyACC[Myid].date.year;
			cin >> MyACC[Myid].date.month;
			cin >> MyACC[Myid].date.day;
		} while (!datejudge(MyACC[Myid].date.year, MyACC[Myid].date.month, MyACC[Myid].date.day));
		cout << "收支项名称\n";
		cin >> MyACC[Myid].name;
		cout << "收支类型(输入对应序号）\n1-->饮食\n2-->学习\n3-->医疗\n4-->交通\n5-->水电\n6-->娱乐\n7-->服饰\n8-->借出\n9-->收入\n0-->其他" << endl;
		TypeInput(MyACC[Myid].type);
		cout << "是否需要备注信息？(Y/N)\n";
		cin >> temp;
		if (temp == 'Y')
			cin >> MyACC[Myid].ps;
		else
			MyACC[Myid].ps = "NULL";
		cout << "第" << cnt << "条录入完成！\n";
	}
}

void File_Input() // 从文件中输入
{
	std::ifstream fin("MyAccount.txt");
	if (!fin.is_open()) {
		std::cout << "无法打开文件!请检查是否建立输入文件！\n";
		exit(0);
	}
	else {
		cnt = 1;
		while (fin >> MyACC[cnt].money >> MyACC[cnt].date.year >> MyACC[cnt].date.month >> MyACC[cnt].date.day
			>> MyACC[cnt].name >> MyACC[cnt].type >> MyACC[cnt].ps) {
			cnt++;
		}
		cnt--;
		std::cout << "输入完成，共" << cnt << "条账目" << std::endl;
	}
	fin.close();
}

void save() // 保存输出到文件
{
	std::ofstream fout("MyAccount.txt", std::ios::app);
	if (!fout.is_open()) {
		std::cout << "无法打开文件！请检查是否建立输出文件!" << std::endl;
		exit(0);
	}
	else {
		for (int i = 1; i <= cnt; i++) {
			fout << MyACC[i].money << " " << MyACC[i].date.year << " " << MyACC[i].date.month << " " << MyACC[i].date.day
				<< " " << MyACC[i].name << " " << MyACC[i].type << " " << MyACC[i].ps << std::endl;
		}
		std::cout << "保存成功！" << std::endl;
	}
	fout.close();
}

void del()  //删除账目函数
{
	int delid;
	cout << "请输入需要删除的记录ID:\n";
	cin >> delid;
	Deleteid(&MyACC[delid], cnt, delid - 1);
}

void Deleteid(MyAccount* arr, int& size, int index)
{

	for (int i = index; i < size - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	size--;
	cout << "记录已成功删除" << endl;
}

void searchAccount()//查找
{
	cout << "查询全部记录输入1，按字段查询输入2" << endl;
	cin >> flag2;
	if (flag2 == 1)    //查询全部记录
	{
		cout << "查询成功！" << endl;
		for (int i = 1; i <= cnt; i++)
			cout << "id:" << i << "   money:" << MyACC[i].money << "  date:" << MyACC[i].date.year << " " << MyACC[i].date.month
			<< " " << MyACC[i].date.day << " " << "   name:" << MyACC[i].name << "   type:" << MyACC[i].type << "   ps:" << MyACC[i].ps << endl;
	}
	else {
		int choice;
		cout << "请选择查找条件：\n";
		cout << "1. 按年查找\n";
		cout << "2. 按月查找\n";
		cout << "3. 按日查找\n";
		cout << "4. 按明细查找\n";
		cout << "5. 按类型查找\n";
		cout << "6. 按金额查找\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int searchYear;
			cout << "请输入查找的年份：\n";
			cin >> searchYear;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].date.year == searchYear)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
					cout << "  name:" << MyACC[i].name;
					cout << "  type:" << MyACC[i].type;
					if (!MyACC[i].ps.empty())
					{
						cout << "  ps:" << MyACC[i].ps;
					}
					cout << endl;
				}
			}
			break;
		}
		case 2:
		{
			int searchMonth, searchYear;
			cout << "请输入查找的年份与月份：\n";
			cin >> searchYear >> searchMonth;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].date.month == searchMonth && MyACC[i].date.year == searchYear)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
					cout << "  name:" << MyACC[i].name;
					cout << "  type:" << MyACC[i].type;
					if (!MyACC[i].ps.empty())
					{
						cout << "  ps:" << MyACC[i].ps;
					}
					cout << endl;
				}
			}
			break;
		}
		case 3:
		{
			int searchDay, searchMonth, searchYear;
			cout << "请输入查找的具体日期（年 月 日）：\n";
			cin >> searchYear >> searchMonth >> searchDay;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].date.day == searchDay && MyACC[i].date.month == searchMonth && MyACC[i].date.year == searchYear)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
					cout << "  name:" << MyACC[i].name;
					cout << "  type:" << MyACC[i].type;
					if (!MyACC[i].ps.empty())
					{
						cout << "  ps:" << MyACC[i].ps;
					}
					cout << endl;
				}
			}
			break;
		}
		case 4:
		{
			string searchDetail;
			cout << "请输入查找的明细关键字：\n";
			cin >> searchDetail;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].name.find(searchDetail) != string::npos)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
					cout << "  name:" << MyACC[i].name;
					cout << "  type:" << MyACC[i].type;
					if (!MyACC[i].ps.empty())
					{
						cout << "  ps:" << MyACC[i].ps;
					}
					cout << endl;
				}
			}
			break;
		}
		case 5:
		{
			string searchType;
			cout << "请输入查找的类型（输入序号）\n1-->饮食\n2-->学习\n3-->医疗\n4-->交通\n5-->水电\n6-->娱乐\n7-->服饰\n8-->借出\n9-->收入\n0-->其他" << endl;
			TypeInput(searchType);
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].type == searchType)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
					cout << "  name:" << MyACC[i].name;
					cout << "  type:" << MyACC[i].type;
					if (!MyACC[i].ps.empty())
					{
						cout << "  ps:" << MyACC[i].ps;
					}
					cout << endl;
				}
			}
			break;
		}
		case 6:
		{
			int searchAmount;
			cout << "请输入查找的金额：\n";
			cin >> searchAmount;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].money == searchAmount)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
					cout << "  name:" << MyACC[i].name;
					cout << "  type:" << MyACC[i].type;
					if (!MyACC[i].ps.empty())
					{
						cout << "  ps:" << MyACC[i].ps;
					}
					cout << endl;
				}
			}
			break;
		}
		default:
			cout << "无效的选择\n";
			break;
		}
	}
}

void change()									//修改
{
	int flag = 1;							//结束标识
	int key;
	cout << "请输入需要修改的账目序号\n";
	cin >> Myid; //输入要修改账目对应的序号
	cout << "选择要修改的账目信息类型，1代表收支金额，2代表交易日期，3代表收支项名称，4代表收支类型，5代表备注信息 6则修改所有\n";
	cin >> key; //选择要修改的板块 (1-6)
	if (key == 1) {
		cout << "收支金额:" << endl;
		cin >> MyACC[Myid].money;
		getchar();
	}
	else if (key == 2) {
		cout << "日期:" << endl;
		cin >> MyACC[Myid].date.year >> MyACC[Myid].date.month >> MyACC[Myid].date.day;
		getchar();
		fflush(stdin);
	}
	else if (key == 3) {
		cout << "名称:" << endl;
		cin >> MyACC[Myid].name;
		getchar();
		fflush(stdin);
	}
	else if (key == 4) {
		cout << "类型（输入序号）\n1-->饮食\n2-->学习\n3-->医疗\n4-->交通\n5-->水电\n6-->娱乐\n7-->服饰\n8-->借出\n9-->收入\n0-->其他" << endl;
		TypeInput(MyACC[Myid].type);
		getchar();
		fflush(stdin);
	}
	else if (key == 5) {
		cout << "备注:" << endl;
		cin >> MyACC[Myid].ps;
		getchar();
		fflush(stdin);
	}
	cout << "修改成功" << endl << "修改后该条账目为:" << endl << "id:" << Myid << " " << "money:" << MyACC[Myid].money << " " << "date:" << MyACC[Myid].date.year << " "
		<< MyACC[Myid].date.month << MyACC[Myid].date.day << "name:" << MyACC[Myid].name << "type:" << MyACC[Myid].type << " " << "ps:" << MyACC[Myid].ps << endl;
}

void report()
{
	cout << "输入对应序号来统计金额\n1.按年统计\n2.按月统计\n3.按账类型统计" << endl;
	int option;
	cin >> option;
	double sum = 0;
	double sumplus = 0;
	double summinus = 0;

	switch (option)
	{
	case 1:
	{
		int searchYear;
		cout << "请输入统计的年份：\n";
		cin >> searchYear;
		for (int i = 1; i <= cnt; i++)
		{
			if (MyACC[i].date.year == searchYear)
			{
				sum += MyACC[i].money;
				if (MyACC[i].money >= 0)
					sumplus += MyACC[i].money;
				else
					summinus += MyACC[i].money;
			}
		}
		break;
	}
	case 2:
	{
		int searchMonth, searchYear;
		cout << "请输入统计的具体月份（年 月）：\n";
		cin >> searchYear >> searchMonth;
		for (int i = 1; i <= cnt; i++)
		{
			if (MyACC[i].date.month == searchMonth && MyACC[i].date.year == searchYear)
			{
				sum += MyACC[i].money;
				if (MyACC[i].money >= 0)
					sumplus += MyACC[i].money;
				else
					summinus += MyACC[i].money;
			}
		}
		break;
	}
	case 3:
	{
		string searchType;
		cout << "统计的账单类型（输入序号）\n1-->饮食\n2-->学习\n3-->医疗\n4-->交通\n5-->水电\n6-->娱乐\n7-->服饰\n8-->借出\n9-->收入\n0-->其他" << endl;
		TypeInput(searchType);
		for (int i = 1; i <= cnt; i++)
		{
			if (MyACC[i].type == searchType)
			{
				sum += MyACC[i].money;
				if (MyACC[i].money >= 0)
					sumplus += MyACC[i].money;
				else
					summinus += MyACC[i].money;
			}
		}
		break;
	}
	default:
	{
		cout << "无效选项！" << endl;
		return;
	}
	}
	cout << "账务统计完成！\n在此阶段，收入：" << sumplus << "元，支出：" << summinus << "元，结余：" << sum << "元" << endl;
}

bool cmp_money(MyAccount A, MyAccount B)
{
	return A.money > B.money;
}

void moneysort()
{
	sort(MyACC + 1, MyACC + cnt + 1, cmp_money);
	for (int i = 1; i <= cnt; i++)
	{
		cout << "id: " << i;
		cout << "  money: " << MyACC[i].money;
		cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
		cout << "  name:" << MyACC[i].name;
		cout << "  type:" << MyACC[i].type;
		if (MyACC[i].ps.empty())
		{
			cout << "  ps:" << MyACC[i].ps;
		}
		cout << endl;
	}
	printf("已按金额递减排序完成!\n");
}



bool cmp_date(MyAccount A, MyAccount B)
{
	return A.dateint > B.dateint;
}
void datesort()
{
	sort(MyACC + 1, MyACC + 1 + cnt, cmp_date);
	for (int i = 1; i <= cnt; i++)
	{
		cout << "id: " << i;
		cout << "  money: " << MyACC[i].money;
		cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
		cout << "  name:" << MyACC[i].name;
		cout << "  type:" << MyACC[i].type;
		if (MyACC[i].ps.empty())
		{
			cout << "  ps:" << MyACC[i].ps;
		}
		cout << endl;
	}
	cout << "根据日期排序完成！\n";
}
bool cmp_name(const MyAccount& a, const MyAccount& b)
{
	return a.name < b.name;
}

void namesort()
{
	sort(MyACC + 1, MyACC + cnt + 1, cmp_name);
	for (int i = 1; i <= cnt; i++)
	{
		cout << "id: " << i;
		cout << "  money: " << MyACC[i].money;
		cout << "  date: " << MyACC[i].date.year << "年" << MyACC[i].date.month << "月" << MyACC[i].date.day << "日";
		cout << "  name:" << MyACC[i].name;
		cout << "  type:" << MyACC[i].type;
		if (!MyACC[i].ps.empty())
		{
			cout << "  ps:" << MyACC[i].ps;
		}
		cout << endl;
	}
	cout << "已按名称排序完成!\n";
}
void acc_sort()
{
	printf("根据金额排序输入1,根据日期排序输入2,根据名称排序输入3\n");
	cin >> flag2;
	if (flag2 == 1)
		moneysort();
	else if (flag2 == 2)
		datesort();
	else if (flag2 == 3)
		namesort();
}
void UI()
{
	cout << endl << endl;
	cout << "***************************************************************" << endl;
	cout << "**           请输入以下选项编号进行下一步操作!               **" << endl;
	cout << "**               1.输入账目                                  **" << endl;
	cout << "**               2.删除账目明细条目                          **" << endl;
	cout << "**               3.查询账目明细条目                          **" << endl;
	cout << "**               4.修改账目明细条目                          **" << endl;
	cout << "**               5.账务数据排序                              **" << endl;
	cout << "**               6.帐务统计                                  **" << endl;
	cout << "**               7.保存文件                                  **" << endl;
	cout << "*****************0.退出系统************************************" << endl;
}

int main()
{
	cout << "********************欢迎进入个人帐本管理系统*********************" << endl;
	system("color f9");  //可以写成 red 调出颜色组
	system("date /T");
	system("TIME /T");
	UI();
	while (scanf("%d", &flag2) != EOF)
	{
		if (flag2 == 1)
			input();
		else if (flag2 == 2)     //删除账目
			del();
		else if (flag2 == 3)
			searchAccount();
		else if (flag2 == 4)
			change();
		else if (flag2 == 5)
			acc_sort();
		else if (flag2 == 6)
			report();
		else if (flag2 == 7)
			save();				//没有返回到主调函数 
		else if (flag2 == 0)
			exit(0);
		UI();
	}
	return 0;
}
