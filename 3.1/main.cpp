/*
@author NvRom 
		2016.5.14 in USTC
题目见《Essential C++中文版》 侯捷译P97
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
	//文件无法打开
	if (!inFile || !outFileMap || !outFileVec){
		std::cout<<"无法打开目标文件，请检查文件是否存在或是损坏"<<std::endl;
		return -1;
	}
	//初始化setOfWordExclusion的值,默认从小到大的顺序排列
	const std::string wordExclusion[6] = {"the","an","or","a","and","but"};
	std::set<std::string>setOfWordExclusion;
	setOfWordExclusion.insert(wordExclusion , wordExclusion + 6);
	//从文件中读入数据添加到map以及vector中
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
	//对vector进行排序
	sort(vectorWord.begin(),vectorWord.end(),lessThan());
	//写入数据和展示
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