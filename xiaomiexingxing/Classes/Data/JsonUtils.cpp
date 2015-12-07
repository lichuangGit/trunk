#include "JsonUtils.h"

#define RETURN_IF(cond,p)           if((cond)) return (p)
#define JSON_PATH					"star.json"

static JsonUtils* mUtils = nullptr;

JsonUtils::JsonUtils()
{	
	m_cloKeys.clear();
	for (int i = 0; i < COL_NUM; i++)
	{
		string str = "col";
		str = str + cocos2d::String::createWithFormat("%d", i)->getCString();
		m_cloKeys.push_back(str);
	}
	setSavePath(JSON_PATH);
}

void JsonUtils::clearFile()
{
	FILE *fp = fopen(m_jsonPath.c_str(), "w");
	if (fp)
	{		
		fwrite("", 1, 1, fp);
	}
	m_buffer = "";
	fclose(fp);
}

JsonUtils::~JsonUtils(void)
{
	CC_SAFE_DELETE(mUtils);
}

JsonUtils* JsonUtils::getInstance()
{
	if (NULL == mUtils)
	{
		mUtils = new JsonUtils();
	}

	return mUtils;
}

const std::string JsonUtils::getStringFromeFile(const std::string &fileName)
{
	const std::string mstr = cocos2d::FileUtils::getInstance()->getStringFromFile(fileName);

	return mstr;
}

const std::string JsonUtils::getStringFromeJson(const std::string jsonStr, const std::string key)
{
	rapidjson::Document _mDoc;

	std::string mstr = jsonStr;

	RETURN_IF(NULL == mstr.c_str() || !mstr.compare(""), "");
	
	_mDoc.Parse<rapidjson::kParseDefaultFlags>(mstr.c_str());
	
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject() || !_mDoc.HasMember(key.c_str()), "");
	
	const rapidjson::Value &pArr = _mDoc[key.c_str()];
	
	RETURN_IF(!pArr.IsString(), "");
	
	const std::string mm = pArr.GetString();
	
	return mm;
}

const std::string JsonUtils::getStringFromeJson(const std::string jsonStr, const std::string key1, const std::string key2)
{
	rapidjson::Document _mDoc;

	std::string mstr = jsonStr;

	RETURN_IF(NULL == mstr.c_str() || !mstr.compare(""), "");

	_mDoc.Parse<rapidjson::kParseDefaultFlags>(mstr.c_str());

	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject() || !_mDoc.HasMember(key1.c_str()), "");

	const rapidjson::Value &pArr = _mDoc[key1.c_str()];

	RETURN_IF(!pArr.IsObject(), "");

	const rapidjson::Value &p = pArr[key2.c_str()];

	RETURN_IF(!p.IsString(), "");

	const std::string vvv = p.GetString();

	return vvv;

}

int JsonUtils::getIntFromeJson(const std::string jsonStr, const std::string key)
{
	rapidjson::Document _mDoc;

	std::string mstr = jsonStr;

	RETURN_IF(NULL == mstr.c_str() || !mstr.compare(""), NULL);

	_mDoc.Parse<rapidjson::kParseDefaultFlags>(mstr.c_str());

	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject() || !_mDoc.HasMember(key.c_str()), NULL);

	const rapidjson::Value &pArr = _mDoc[key.c_str()];

	RETURN_IF(!pArr.IsInt(), NULL);

	int mm = pArr.GetInt();

	return mm;
}

int JsonUtils::getIntFromeJson(const std::string jsonStr, const std::string key1, const std::string key2)
{
	std::string str = "{ \"row0col0\" :  \"2\"}";
	//log("%s\n", str.c_str());
	rapidjson::Document d;
	d.Parse<0>(str.c_str());
	if (d.HasParseError())  //打印解析错误
	{
		log("GetParseError %s\n", d.GetParseError());
	}

	if (d.IsObject() && d.HasMember("row0col0")) {

		log("%s\n", d["row0col0"].GetString());//打印获取hello的值
	}
	rapidjson::Document _mDoc;

	std::string mstr = jsonStr;

	//log("%s",mstr.c_str());

	RETURN_IF(NULL == mstr.c_str() || !mstr.compare(""), NULL);

	_mDoc.Parse<rapidjson::kParseDefaultFlags>(mstr.c_str());
	//log("%s",_mDoc.GetParseError());
	RETURN_IF(_mDoc.HasParseError(), NULL);

	RETURN_IF(!_mDoc.IsObject(), NULL);

	RETURN_IF(!_mDoc.HasMember(key1.c_str()), NULL);

	const rapidjson::Value &pArr = _mDoc[key1.c_str()];

	RETURN_IF(!pArr.IsArray(), NULL);

	for (int i = 0; i < pArr.Capacity(); i++)
	{
		const rapidjson::Value &p = pArr[i];
		if (p.HasMember(key2.c_str()))
		{
			//RETURN_IF(!p.IsInt(), -1);
			//log("%d",p.GetType());
			p.GetString();
		}
	}
		
	return -1;
}

unsigned JsonUtils::getSizeFromeJsonArr(const std::string jsonArr)
{
	rapidjson::Document _mDoc;

	std::string mstr = jsonArr;

	RETURN_IF(NULL == mstr.c_str() || !mstr.compare(""), NULL);

	_mDoc.Parse<rapidjson::kParseDefaultFlags>(mstr.c_str());

	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject(), NULL);

	const rapidjson::Value &mValue = _mDoc;

	RETURN_IF(!mValue.IsArray(), NULL);

	unsigned count = 0;

	unsigned mm = mValue.Capacity();

	return mm;
}

void JsonUtils::setSavePath(const string &path)
{
	m_jsonPath = FileUtils::getInstance()->getWritablePath().append(path.c_str());
}

string JsonUtils::getSavePath()
{
	return m_jsonPath;
}

bool JsonUtils::setIntArrayToJson(const std::string &key, const vector<int> &value)
{
	if (key.empty() || value.size() != COL_NUM)
	{
		return false;
	}

	rapidjson::Document document;
	document.SetObject();

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value objectROOT(rapidjson::kArrayType);
	//log("key = %s, value = %d", key.c_str(), value.size());
	
	rapidjson::Value object(rapidjson::kObjectType);

	for (int i = 0; i < COL_NUM; i++)
	{		
		//log("%s : %d",m_cloKeys.at(i).c_str(), value.at(i));
		object.AddMember(m_cloKeys.at(i).c_str(), const_cast<char *>(cocos2d::CCString::createWithFormat("%d",value.at(i))->getCString()), allocator);
	}

	objectROOT.PushBack(object,allocator);

	document.AddMember(key.c_str(), objectROOT, allocator);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	//log("%s", buffer.GetString());
	m_buffer = m_buffer + StringUtils::format("%s", buffer.GetString()) + "\n";

	if (m_buffer.empty())
	{
		return false;
	}

	return true;
}

bool JsonUtils::setIntToJson(const std::string &key, int value)
{
	rapidjson::Document document;
	document.SetObject();

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember(key.c_str(), value, allocator);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	//log("%s", buffer.GetString());
	m_buffer = m_buffer + StringUtils::format("%s\r", buffer.GetString());

	if (m_buffer.empty())
	{
		return false;
	}

	return true;
}

void JsonUtils::saveData()
{
	FILE *fp = fopen(m_jsonPath.c_str(), "w");

	if (fp)
	{
		fwrite(m_buffer.c_str(), 1, m_buffer.size(), fp);
	}

	fclose(fp);
}
