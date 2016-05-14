/*
@author NvRom 
		2016.5.14 in USTC
��Ŀ����Essential C++���İ桷 �����P97
*/

#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

//function object
class lessThan{
public:
	bool operator()(const std::string &str1 , const std::string &str2){
		return str1.size() < str2.size();
	}
};

//
int main(){
	std::ifstream inFile("RennyGleeson_2012U.txt");
	std::ofstream outFileMap("Map_RennyGleeson_2012U.txt");
	std::ofstream outFileVec("Vec_RennyGleeson_2012U.txt");
	//�ļ��޷���
	if (!inFile || !outFileMap || !outFileVec){
		std::cout<<"�޷���Ŀ���ļ��������ļ��Ƿ���ڻ�����"<<std::endl;
		return -1;
	}
	//��ʼ��setOfWordExclusion��ֵ,Ĭ�ϴ�С�����˳������
	const std::string wordExclusion[6] = {"the","an","or","a","and","but"};
	std::set<std::string>setOfWordExclusion;
	setOfWordExclusion.insert(wordExclusion , wordExclusion + 6);
	//���ļ��ж���������ӵ�map�Լ�vector��
	std::string strWord;
	std::map<std::string , int>mapWord;
	std::vector<std::string>vectorWord;
	while (inFile >> strWord){
		if (setOfWordExclusion.count(strWord)){
			continue;
		}
		mapWord[strWord]++;
		vectorWord.push_back(strWord);
	}
	//��vector��������
	sort(vectorWord.begin(),vectorWord.end(),lessThan());
	//д�����ݺ�չʾ
	std::map<std::string , int>::iterator it = mapWord.begin();
	for (;it != mapWord.end();it++){
		std::cout<<std::setiosflags(std::ios::left)<<std::setw(16)<<it->first<<"\t"<<it->second<<std::endl;
		outFileMap<<std::setiosflags(std::ios::left)<<std::setw(16)<<it->first <<"\t["<<it->second<<"]"<<std::endl;
	}
	outFileMap<<std::endl;
	std::vector<std::string>::iterator vit = vectorWord.begin();
	for (;vit != vectorWord.end();vit++){
		outFileVec<<*vit<<" ";
	}
	outFileVec<<std::endl;
	system("pause");
	return 0;
}