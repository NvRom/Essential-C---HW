/*
@author NvRom 
		2016.5.14 in USTC
��Ŀ����Essential C++���İ桷 �����P97
*/

#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
//
int main(){
	std::ifstream inFile("RennyGleeson_2012U.txt");
	std::ofstream outFile("Out_RennyGleeson_2012U.txt");
	//�ļ��޷���
	if (!inFile || !outFile){
		std::cout<<"�޷���Ŀ���ļ��������ļ��Ƿ���ڻ�����"<<std::endl;
		return -1;
	}
	//��ʼ��setOfWordExclusion��ֵ,Ĭ�ϴ�С�����˳������
	const std::string wordExclusion[6] = {"the","an","or","a","and","but"};
	std::set<std::string>setOfWordExclusion;
	setOfWordExclusion.insert(wordExclusion , wordExclusion + 6);
	//���ļ��ж���������ӵ�map��
	std::string strWord;
	std::map<std::string , int>mapWord;
	while (inFile >> strWord){
		if (setOfWordExclusion.count(strWord)){
			continue;
		}
		mapWord[strWord]++;
	}
	//д�����ݺ�չʾ
	std::map<std::string , int>::iterator it = mapWord.begin();
	for (;it != mapWord.end();it++){
		std::cout<<it->first<<std::setw(16)<<"\t"<<it->second<<std::endl;
		outFile<< it->first <<std::setw(16)<<"\t["<<it->second<<"]"<<std::endl;
	}
	outFile<<std::endl;
	system("pause");
	return 0;
}