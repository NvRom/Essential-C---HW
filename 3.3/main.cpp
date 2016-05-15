/*
@author NvRom
	2016.5.15 in USTC
*/
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

typedef std::vector<std::string> vString;

//文件每一行第一个为姓氏名，后面为孩子名
int main(){
	std::map<std::string , vString> familyMap;
	std::string familyStr;
	//打开输入输出文件
	std::ifstream inFile("family.txt");
	std::ofstream outFile("outFamily.txt");

	if (!inFile || !outFile){
		std::cout<<"无法打开目标文件，请检查文件是否存在"<<std::endl;
	}
	//处理每一行的family name以及children name,这些都包含在familyStr中
	//利用substr(firstPos , length)来划分新字符串
	while(getline(inFile , familyStr)){
		//
		std::string familyName;
		std::string childrenName;
		std::vector<std::string>children;
		//pos:当前的' '的位置
		//prevPos:' '前一个单词首字母所在位置
		std::string::size_type pos = 0 , prevPos = 0;
		//find_first_of:从pos开始找特定字符或字符串，返回其地址；若没找到返回string::npos
		while ((pos = familyStr.find_first_of(' ' , pos)) != std::string::npos){
			std::string::size_type length = pos - prevPos;
			//prevPos没有被重新赋值时，表示读到的是第一个单词
			if (!prevPos){
				familyName = familyStr.substr(prevPos , length);
				outFile<<"family name:"<< familyName<<"\t"<<"childred name:"<<"\t";
				prevPos = ++ pos;
			}else{
				childrenName = familyStr.substr(prevPos , length);
				children.push_back(childrenName);
				outFile<<childrenName<<"; ";
				prevPos = ++ pos;
			}
		}
		//处理最后一个单词，此时pos为string::npos
		//当这一行只有一个单词时，表示其没有后代
		if (prevPos < familyStr.size()){
			if (prevPos)
			{
				childrenName = familyStr.substr(prevPos , pos - prevPos);
				children.push_back(childrenName);
				outFile<<childrenName<<"; ";
			}else
			{
				familyName = familyStr.substr(prevPos , pos - prevPos);
				outFile<<"family name:"<< familyName;
			}
		}
		outFile<<"\n";
		/*
		写入map中，当familyMap[familyName] = children不存在familName时，
		往map中自动添加key值，然后再添加value值
		*/
		if (familyMap.count(familyName)){
			std::cout<<"已经存在family name"<<familyName<<std::endl;
		}else
		{
			familyMap[familyName] = children;
		}
	}
	outFile<<std::endl;
	//查询map中key值
	std::string sqlStr;
	while (std::cin>>sqlStr){
		if (sqlStr == "q" || sqlStr == "Q"){
			break;
		}
		//利用map中find函数查找
		std::map<std::string , vString>::iterator mit = familyMap.find(sqlStr);
		if (mit != familyMap.end()){
			std::cout<<"family name 为:"<<sqlStr<<",他共有"<<mit->second.size()<<"个孩子，分别为：\t";
			std::vector<std::string>::iterator ivec = mit->second.begin();
			for (;ivec < mit->second.end();ivec ++){
				std::cout<<*ivec<<"  ";
			}
		}else{
			std::cout<<"找不到该family name";
		}
		std::cout<<std::endl;
	}
	return 0;
}