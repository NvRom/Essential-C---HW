/*
@author NvRom 
		2016.5.14 in USTC
题目见《Essential C++中文版》 侯捷译P97
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
	//文件无法打开
	if (!inFile || !outFile){
		std::cout<<"无法打开目标文件，请检查文件是否存在或是损坏"<<std::endl;
		return -1;
	}
	//初始化setOfWordExclusion的值,默认从小到大的顺序排列
	const std::string wordExclusion[6] = {"the","an","or","a","and","but"};
	std::set<std::string>setOfWordExclusion;
	setOfWordExclusion.insert(wordExclusion , wordExclusion + 6);
	//从文件中读入数据添加到map中
	std::string strWord;
	std::map<std::string , int>mapWord;
	while (inFile >> strWord){
		if (setOfWordExclusion.count(strWord)){
			continue;
		}
		mapWord[strWord]++;
	}
	//写入数据和展示
	std::map<std::string , int>::iterator it = mapWord.begin();
	for (;it != mapWord.end();it++){
		std::cout<<it->first<<std::setw(16)<<"\t"<<it->second<<std::endl;
		outFile<< it->first <<std::setw(16)<<"\t["<<it->second<<"]"<<std::endl;
	}
	outFile<<std::endl;
	system("pause");
	return 0;
}