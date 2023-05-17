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
	Date date;  // ���һ��Date������Ϊ���ڳ�Ա
}MyACC[1000], T;  //����һ�������洢��Ŀ��

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
	cout << "�ֶ�������������1���ļ���ȡ��������2" << endl;
	cin >> flag2;
	if (flag2 == 1)
		Hand_Input();
	else if (flag2 == 2)
		File_Input();
	Dateint();
}

int datejudge(int y, int m, int d)                           //�ж����ںϷ��� 
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
			TYPE = "��ʳ";
			validChoice = true;
			break;
		case 2:
			TYPE = "ѧϰ";
			validChoice = true;
			break;
		case 3:
			TYPE = "ҽ��";
			validChoice = true;
			break;
		case 4:
			TYPE = "��ͨ";
			validChoice = true;
			break;
		case 5:
			TYPE = "ˮ��";
			validChoice = true;
			break;
		case 6:
			TYPE = "����";
			validChoice = true;
			break;
		case 7:
			TYPE = "����";
			validChoice = true;
			break;
		case 8:
			TYPE = "���";
			validChoice = true;
			break;
		case 9:
			TYPE = "����";
			validChoice = true;
			break;
		case 0:
			TYPE = "����";
			validChoice = true;
			break;
		default:
			cout << "ѡ�񲻴��ڣ��������������֣�" << endl;
			break;
		}
	}
}


void Hand_Input() //������Ŀ����
{
	int flag;
	char temp;
	cout << "����Ҫ¼������������¼��\n";
	cin >> flag;
	cin.ignore();//���Ի��з�
	while (flag--)
	{
		cnt++;
		Myid = cnt;
		cout << "��������֧���\n";
		cin >> MyACC[Myid].money;
		do {
			cout << "������ȷ�Ľ�������(�� �� ��)" << endl;
			cin >> MyACC[Myid].date.year;
			cin >> MyACC[Myid].date.month;
			cin >> MyACC[Myid].date.day;
		} while (!datejudge(MyACC[Myid].date.year, MyACC[Myid].date.month, MyACC[Myid].date.day));
		cout << "��֧������\n";
		cin >> MyACC[Myid].name;
		cout << "��֧����(�����Ӧ��ţ�\n1-->��ʳ\n2-->ѧϰ\n3-->ҽ��\n4-->��ͨ\n5-->ˮ��\n6-->����\n7-->����\n8-->���\n9-->����\n0-->����" << endl;
		TypeInput(MyACC[Myid].type);
		cout << "�Ƿ���Ҫ��ע��Ϣ��(Y/N)\n";
		cin >> temp;
		if (temp == 'Y')
			cin >> MyACC[Myid].ps;
		else
			MyACC[Myid].ps = "NULL";
		cout << "��" << cnt << "��¼����ɣ�\n";
	}
}

void File_Input() // ���ļ�������
{
	std::ifstream fin("MyAccount.txt");
	if (!fin.is_open()) {
		std::cout << "�޷����ļ�!�����Ƿ��������ļ���\n";
		exit(0);
	}
	else {
		cnt = 1;
		while (fin >> MyACC[cnt].money >> MyACC[cnt].date.year >> MyACC[cnt].date.month >> MyACC[cnt].date.day
			>> MyACC[cnt].name >> MyACC[cnt].type >> MyACC[cnt].ps) {
			cnt++;
		}
		cnt--;
		std::cout << "������ɣ���" << cnt << "����Ŀ" << std::endl;
	}
	fin.close();
}

void save() // ����������ļ�
{
	std::ofstream fout("MyAccount.txt", std::ios::app);
	if (!fout.is_open()) {
		std::cout << "�޷����ļ��������Ƿ�������ļ�!" << std::endl;
		exit(0);
	}
	else {
		for (int i = 1; i <= cnt; i++) {
			fout << MyACC[i].money << " " << MyACC[i].date.year << " " << MyACC[i].date.month << " " << MyACC[i].date.day
				<< " " << MyACC[i].name << " " << MyACC[i].type << " " << MyACC[i].ps << std::endl;
		}
		std::cout << "����ɹ���" << std::endl;
	}
	fout.close();
}

void del()  //ɾ����Ŀ����
{
	int delid;
	cout << "��������Ҫɾ���ļ�¼ID:\n";
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
	cout << "��¼�ѳɹ�ɾ��" << endl;
}

void searchAccount()//����
{
	cout << "��ѯȫ����¼����1�����ֶβ�ѯ����2" << endl;
	cin >> flag2;
	if (flag2 == 1)    //��ѯȫ����¼
	{
		cout << "��ѯ�ɹ���" << endl;
		for (int i = 1; i <= cnt; i++)
			cout << "id:" << i << "   money:" << MyACC[i].money << "  date:" << MyACC[i].date.year << " " << MyACC[i].date.month
			<< " " << MyACC[i].date.day << " " << "   name:" << MyACC[i].name << "   type:" << MyACC[i].type << "   ps:" << MyACC[i].ps << endl;
	}
	else {
		int choice;
		cout << "��ѡ�����������\n";
		cout << "1. �������\n";
		cout << "2. ���²���\n";
		cout << "3. ���ղ���\n";
		cout << "4. ����ϸ����\n";
		cout << "5. �����Ͳ���\n";
		cout << "6. ��������\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int searchYear;
			cout << "��������ҵ���ݣ�\n";
			cin >> searchYear;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].date.year == searchYear)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
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
			cout << "��������ҵ�������·ݣ�\n";
			cin >> searchYear >> searchMonth;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].date.month == searchMonth && MyACC[i].date.year == searchYear)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
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
			cout << "��������ҵľ������ڣ��� �� �գ���\n";
			cin >> searchYear >> searchMonth >> searchDay;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].date.day == searchDay && MyACC[i].date.month == searchMonth && MyACC[i].date.year == searchYear)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
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
			cout << "��������ҵ���ϸ�ؼ��֣�\n";
			cin >> searchDetail;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].name.find(searchDetail) != string::npos)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
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
			cout << "��������ҵ����ͣ�������ţ�\n1-->��ʳ\n2-->ѧϰ\n3-->ҽ��\n4-->��ͨ\n5-->ˮ��\n6-->����\n7-->����\n8-->���\n9-->����\n0-->����" << endl;
			TypeInput(searchType);
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].type == searchType)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
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
			cout << "��������ҵĽ�\n";
			cin >> searchAmount;
			for (int i = 1; i <= cnt; i++)
			{
				if (MyACC[i].money == searchAmount)
				{
					cout << "id: " << i;
					cout << "  money: " << MyACC[i].money;
					cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
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
			cout << "��Ч��ѡ��\n";
			break;
		}
	}
}

void change()									//�޸�
{
	int flag = 1;							//������ʶ
	int key;
	cout << "��������Ҫ�޸ĵ���Ŀ���\n";
	cin >> Myid; //����Ҫ�޸���Ŀ��Ӧ�����
	cout << "ѡ��Ҫ�޸ĵ���Ŀ��Ϣ���ͣ�1������֧��2���������ڣ�3������֧�����ƣ�4������֧���ͣ�5����ע��Ϣ 6���޸�����\n";
	cin >> key; //ѡ��Ҫ�޸ĵİ�� (1-6)
	if (key == 1) {
		cout << "��֧���:" << endl;
		cin >> MyACC[Myid].money;
		getchar();
	}
	else if (key == 2) {
		cout << "����:" << endl;
		cin >> MyACC[Myid].date.year >> MyACC[Myid].date.month >> MyACC[Myid].date.day;
		getchar();
		fflush(stdin);
	}
	else if (key == 3) {
		cout << "����:" << endl;
		cin >> MyACC[Myid].name;
		getchar();
		fflush(stdin);
	}
	else if (key == 4) {
		cout << "���ͣ�������ţ�\n1-->��ʳ\n2-->ѧϰ\n3-->ҽ��\n4-->��ͨ\n5-->ˮ��\n6-->����\n7-->����\n8-->���\n9-->����\n0-->����" << endl;
		TypeInput(MyACC[Myid].type);
		getchar();
		fflush(stdin);
	}
	else if (key == 5) {
		cout << "��ע:" << endl;
		cin >> MyACC[Myid].ps;
		getchar();
		fflush(stdin);
	}
	cout << "�޸ĳɹ�" << endl << "�޸ĺ������ĿΪ:" << endl << "id:" << Myid << " " << "money:" << MyACC[Myid].money << " " << "date:" << MyACC[Myid].date.year << " "
		<< MyACC[Myid].date.month << MyACC[Myid].date.day << "name:" << MyACC[Myid].name << "type:" << MyACC[Myid].type << " " << "ps:" << MyACC[Myid].ps << endl;
}

void report()
{
	cout << "�����Ӧ�����ͳ�ƽ��\n1.����ͳ��\n2.����ͳ��\n3.��������ͳ��" << endl;
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
		cout << "������ͳ�Ƶ���ݣ�\n";
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
		cout << "������ͳ�Ƶľ����·ݣ��� �£���\n";
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
		cout << "ͳ�Ƶ��˵����ͣ�������ţ�\n1-->��ʳ\n2-->ѧϰ\n3-->ҽ��\n4-->��ͨ\n5-->ˮ��\n6-->����\n7-->����\n8-->���\n9-->����\n0-->����" << endl;
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
		cout << "��Чѡ�" << endl;
		return;
	}
	}
	cout << "����ͳ����ɣ�\n�ڴ˽׶Σ����룺" << sumplus << "Ԫ��֧����" << summinus << "Ԫ�����ࣺ" << sum << "Ԫ" << endl;
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
		cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
		cout << "  name:" << MyACC[i].name;
		cout << "  type:" << MyACC[i].type;
		if (MyACC[i].ps.empty())
		{
			cout << "  ps:" << MyACC[i].ps;
		}
		cout << endl;
	}
	printf("�Ѱ����ݼ��������!\n");
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
		cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
		cout << "  name:" << MyACC[i].name;
		cout << "  type:" << MyACC[i].type;
		if (MyACC[i].ps.empty())
		{
			cout << "  ps:" << MyACC[i].ps;
		}
		cout << endl;
	}
	cout << "��������������ɣ�\n";
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
		cout << "  date: " << MyACC[i].date.year << "��" << MyACC[i].date.month << "��" << MyACC[i].date.day << "��";
		cout << "  name:" << MyACC[i].name;
		cout << "  type:" << MyACC[i].type;
		if (!MyACC[i].ps.empty())
		{
			cout << "  ps:" << MyACC[i].ps;
		}
		cout << endl;
	}
	cout << "�Ѱ������������!\n";
}
void acc_sort()
{
	printf("���ݽ����������1,����������������2,����������������3\n");
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
	cout << "**           ����������ѡ���Ž�����һ������!               **" << endl;
	cout << "**               1.������Ŀ                                  **" << endl;
	cout << "**               2.ɾ����Ŀ��ϸ��Ŀ                          **" << endl;
	cout << "**               3.��ѯ��Ŀ��ϸ��Ŀ                          **" << endl;
	cout << "**               4.�޸���Ŀ��ϸ��Ŀ                          **" << endl;
	cout << "**               5.������������                              **" << endl;
	cout << "**               6.����ͳ��                                  **" << endl;
	cout << "**               7.�����ļ�                                  **" << endl;
	cout << "*****************0.�˳�ϵͳ************************************" << endl;
}

int main()
{
	cout << "********************��ӭ��������ʱ�����ϵͳ*********************" << endl;
	system("color f9");  //����д�� red ������ɫ��
	system("date /T");
	system("TIME /T");
	UI();
	while (scanf("%d", &flag2) != EOF)
	{
		if (flag2 == 1)
			input();
		else if (flag2 == 2)     //ɾ����Ŀ
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
			save();				//û�з��ص��������� 
		else if (flag2 == 0)
			exit(0);
		UI();
	}
	return 0;
}
