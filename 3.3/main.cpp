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

//�ļ�ÿһ�е�һ��Ϊ������������Ϊ������
int main(){
	std::map<std::string , vString> familyMap;
	std::string familyStr;
	//����������ļ�
	std::ifstream inFile("family.txt");
	std::ofstream outFile("outFamily.txt");

	if (!inFile || !outFile){
		std::cout<<"�޷���Ŀ���ļ��������ļ��Ƿ����"<<std::endl;
	}
	//����ÿһ�е�family name�Լ�children name,��Щ��������familyStr��
	//����substr(firstPos , length)���������ַ���
	while(getline(inFile , familyStr)){
		//
		std::string familyName;
		std::string childrenName;
		std::vector<std::string>children;
		//pos:��ǰ��' '��λ��
		//prevPos:' 'ǰһ����������ĸ����λ��
		std::string::size_type pos = 0 , prevPos = 0;
		//find_first_of:��pos��ʼ���ض��ַ����ַ������������ַ����û�ҵ�����string::npos
		while ((pos = familyStr.find_first_of(' ' , pos)) != std::string::npos){
			std::string::size_type length = pos - prevPos;
			//prevPosû�б����¸�ֵʱ����ʾ�������ǵ�һ������
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
		//�������һ�����ʣ���ʱposΪstring::npos
		//����һ��ֻ��һ������ʱ����ʾ��û�к��
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
		д��map�У���familyMap[familyName] = children������familNameʱ��
		��map���Զ����keyֵ��Ȼ�������valueֵ
		*/
		if (familyMap.count(familyName)){
			std::cout<<"�Ѿ�����family name"<<familyName<<std::endl;
		}else
		{
			familyMap[familyName] = children;
		}
	}
	outFile<<std::endl;
	//��ѯmap��keyֵ
	std::string sqlStr;
	while (std::cin>>sqlStr){
		if (sqlStr == "q" || sqlStr == "Q"){
			break;
		}
		//����map��find��������
		std::map<std::string , vString>::iterator mit = familyMap.find(sqlStr);
		if (mit != familyMap.end()){
			std::cout<<"family name Ϊ:"<<sqlStr<<",������"<<mit->second.size()<<"�����ӣ��ֱ�Ϊ��\t";
			std::vector<std::string>::iterator ivec = mit->second.begin();
			for (;ivec < mit->second.end();ivec ++){
				std::cout<<*ivec<<"  ";
			}
		}else{
			std::cout<<"�Ҳ�����family name";
		}
		std::cout<<std::endl;
	}
	return 0;
}