#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "Const.h"
#include <string>
#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
using namespace rapidjson;

class JsonUtils
{
public:
	static JsonUtils* getInstance();

	const std::string getStringFromeFile(const std::string &fileName);
	
	const std::string getStringFromeJson(const std::string jsonStr, const std::string key);
	
	const std::string getStringFromeJson(const std::string jsonStr, const std::string key1, const std::string key2);
	
	int getIntFromeJson(const std::string jsonStr, const std::string key);
	
	int getIntFromeJson(const std::string jsonStr, const std::string key1, const std::string key2);
	
	unsigned getSizeFromeJsonArr(const std::string jsonArr);
	
	/*
		key ��
		value ÿһ�е�����
	*/
	bool setIntArrayToJson(const std::string &key, const vector<int> &value);

	bool setIntToJson(const std::string &key, int value);

	JsonUtils();
	
	/*
		������ã������޷����浽����
	*/
	void saveData();

	void clearFile();

	string getSavePath();
		
private:		
	~JsonUtils(void);
	void setSavePath(const string &path);

	std::string m_buffer;
	vector<string> m_cloKeys;
	string m_jsonPath;
};


#endif

