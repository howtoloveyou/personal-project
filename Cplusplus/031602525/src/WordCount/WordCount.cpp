// WordCount.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
int i = 0;//i应该小于等于words的值
int error = 0;//1 没有单词 2 单词过长 3 文本过大
class Count{
private:
	char word[20];
	int count = 0;
public:
	Count(){
		for (int i = 0; i < 20; i++)
			word[i] = '\0';
	}

	static int  j_cha(string &str)
	{
		int flag = 0;

		//判断是否为所需字符串
		for (int i = 0; i<str.length(); i++)
		{
			if ((str[i] >= 32 && str[i] <= 126) || str[i] == 9 || str[i] == 10)
			{
				if (str[i] >= 65 && str[i] <= 90)
				{
					str[i] += 32;
				}
				flag++;
			}
		}
		return flag;
	}

	static int  j_wod(string str, Count *wordss)
	{
		error = 0;
		int flag = 0, k = 0, flag2 = 0;
		char strc[20] = { 0 };
		for (k = 0; k < str.length(); k++)//将str复制到strc
		{
			if (str.length() > 20) {
				error = 2;
				break;
			}
			if ((k == str.length() - 1) && (str[k] < 65 || (str[k] > 90 && str[k] < 97) || str[k] > 122)){
				str = str.substr(0, k);//删除最后一个字符
				break;
			}
			strc[k] = str[k];
		}
		if (error != 0){
			return 0;
		}
		if (str.length() < 4){
			return 0;
		}
		else
		{
			if ((str[0] <= 90 && str[0] >= 65) || (str[0] >= 97 && str[0] <= 122)){ flag++; }
			if ((str[1] <= 90 && str[1] >= 65) || (str[1] >= 97 && str[1] <= 122)){ flag++; }
			if ((str[2] <= 90 && str[2] >= 65) || (str[2] >= 97 && str[2] <= 122)){ flag++; }
			if ((str[3] <= 90 && str[3] >= 65) || (str[3] >= 97 && str[3] <= 122)){ flag++; }
			if (flag == 4) //判断为英文单词，录入结构体中
			{
				for (k = 0; k<i; k++)//将现有单词，比较现有记录
				{
					if (strcmp(strc, wordss[k].word) == 0)
					{
						wordss[k].count++;
						flag2 = 1;
						break;
					}
				}
				//没有则存入单词结构体数组保存 
				if (!flag2)
				{
					for (k = 0; k < str.length(); k++)
					{
						wordss[i].word[k] = str[k];
					}
					wordss[i].count++;
					i++;
				}
				return 1;
			}
			else return 0;
		}
	}

	static void sort(Count *member)
	{
		Count stmp;
		for (int j = 0; j<i; j++)
		{
			for (int k = 0; k<i - j - 1; k++)
			{
				if (member[k].count < member[k + 1].count)
				{
					stmp = member[k];
					member[k] = member[k + 1];
					member[k + 1] = stmp;
				}
				else if (member[k].count == member[k + 1].count)
				{
					if (member[k].word < member[k + 1].word){
						stmp = member[k];
						member[k] = member[k + 1];
						member[k + 1] = stmp;
					}
				}
			}
		}
	}

	static void print(Count *member, int n){
		printf("<%s>: %d\n", member[n].word, member[n].count);
	}
};
int main(int argc, char *argv[])
{
	Count wordss[200], stmp;
	int lines = 0, words = 0, characters = 0, j, k;
	char filename[160] = "";
	FILE *fp = NULL;
	ifstream inf;
	inf.open(argv[1]);
	//inf.open("E:/0905-software/out.txt");
	string sline;//每一行
	string str;

	while (getline(inf, sline))
	{
		//cout << "Comein" << endl;
		characters += Count::j_cha(sline) + 1;
		istringstream stream(sline);
		while (stream >> str)
		{
			//cout << str.c_str() << endl;
			words += Count::j_wod(str, wordss);
			if (error != 0){
				break;
			}
		}
		if (Count::j_cha(sline)>0)
			lines++;
		if (error != 0){
			break;
		}
	}

	//没有单词记录
	if (i == 0)
	{
		cout << "没有单词记录" << endl;
	}
	if (error == 2)
	{
		cout << "某些单词过长" << endl << "所在行数：" << lines << endl;

	}
	else{
		cout << endl << "characters: " << characters - 1 << endl;
		cout << "words: " << words << endl;
		cout << "lines: " << lines << endl;
		//使用率排序 
		Count::sort(wordss);
		//输出排序后的所有已记录单词 
		i = (i < 10) ? i : 10;
		for (k = 0; k<i; k++)
		{
			Count::print(wordss, k);
		}
	}
	system("pause");
	return 0;
}
