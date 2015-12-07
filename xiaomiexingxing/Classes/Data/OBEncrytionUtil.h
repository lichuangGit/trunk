//
//  OBEncrytionUtil.h
//  AirCommander
//
//  Created by lichuang 15/4/17.
//
//

#ifndef __OBEncrytionUtil_h
#define __OBEncrytionUtil_h

#include "cocos2d.h"

#define USERDEFAULT				UserDefault::getInstance()
#define SaveStringToXML			UserEncrytionUtil::setStringForKey
#define SaveIntegerToXML		UserEncrytionUtil::setIntegerForKey
#define SaveFloatToXML			UserEncrytionUtil::setFolatForKey
#define SaveDoubleToXML			UserEncrytionUtil::setDoubleForKey
#define SaveBooleanToXML		UserEncrytionUtil::setBooleanForKey
#define LoadStringFormXML		UserEncrytionUtil::getStringForKey
#define LoadIntergerFormXML		UserEncrytionUtil::getIntegerForKey
#define LoadFloatFormXML		UserEncrytionUtil::getFloatForKey
#define LoadDoubleFormXML		UserEncrytionUtil::getDoubleForKey
#define LoadBooleanFormXML		UserEncrytionUtil::getBooleanForKey

USING_NS_CC;

class EncrytionUtil
{
public:
	static int Encryt(std::string& stream, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		return Encryt(stream, 0,  stream.length()-1, secret);
	}
    
	static int Decrpt(std::string& stream, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		return Decrpt(stream, 0, stream.length()-1, secret);
	}
    
	static int Encryt(std::string& stream, int begin, int end, const char* secret)
	{
		return XORM(stream, begin, end, secret);
	}
    
	static int Decrpt(std::string& stream, int begin, int end, const char* secret)
	{
		return XORM(stream, begin, end, secret);
	}
	
private:
	static int XORM(std::string& stream, int begin, int end, const char* secret)
	{
        if (begin<0 || end>=stream.length() || begin>end || strlen(secret) == 0)
        {
            return -1;
        }
        
        int keyLength = strlen(secret);
        int j(0);
        for (int i=begin; i<=end; i++)
        {
            if (j>=keyLength)
            {
                j = 0;
            } 
            stream[i] = stream[i] ^ secret[j];
            if(stream[i] == '\0')
            {
                stream[i] = secret[j];
            }
            j++;
        }

		return 0;
	}
};

class UserEncrytionUtil
{
public:
    static void setStringForKey(const char* key, const char* value,const char* secret = "Cocos2dxReallyHelplichuang")
    {
            std::string keyString = key;
            EncrytionUtil::Encryt(keyString,secret);
            
            std::string valueString = value;
            EncrytionUtil::Encryt(valueString,secret);
            
			USERDEFAULT->setStringForKey(key, valueString);
			USERDEFAULT->flush();
    }
    
    static void setIntegerForKey(const char* key, long value,const char* secret = "Cocos2dxReallyHelplichuang")
    {
        char valueString[64] = {0};
        sprintf(valueString, "%ld",value);
        setStringForKey(key,valueString,secret);
    }
    
	static void setFolatForKey(const char* key, float value, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		char valueString[64] = { 0 };
		sprintf(valueString, "%f", value);
		setStringForKey(key, valueString, secret);
	}

	static void setDoubleForKey(const char* key, double value, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		char valueString[64] = { 0 };
		sprintf(valueString, "%lf", value);
		setStringForKey(key, valueString, secret);
	}

	static void setBooleanForKey(const char* key, bool value, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		if (value)
			setStringForKey(key, "true", secret);
		else
			setStringForKey(key, "false", secret);
	}

    static std::string getStringForKey(const char* key, const char* secret = "Cocos2dxReallyHelplichuang")
    {
		std::string valueString = USERDEFAULT->getStringForKey(key);
		EncrytionUtil::Decrpt(valueString, secret);
		return valueString;
    }

	static std::string getStringForKey(const char* key, const std::string & defaultValue, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		std::string valueString = USERDEFAULT->getStringForKey(key,defaultValue);
		if (valueString != defaultValue)
			EncrytionUtil::Decrpt(valueString, secret);
		return valueString;
	}
    
    static int getIntegerForKey(const char* key,const char* secret = "Cocos2dxReallyHelplichuang")
    {
        return  atoi(getStringForKey(key,secret).c_str());
    }

	static int getIntegerForKey(const char* key, int defaultValue, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		char valueString[20] = { 0 };
		sprintf(valueString, "%d", defaultValue);

		return  atoi(getStringForKey(key, valueString, secret).c_str());
	}

	static float getFloatForKey(const char* key, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		return Value(getStringForKey(key, secret)).asFloat();
	}

	static float getFloatForKey(const char* key, float defaultValue, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		char valueString[20] = { 0 };
		sprintf(valueString, "%f", defaultValue);
		return Value(getStringForKey(key, valueString, secret)).asFloat();
	}

	static double getDoubleForKey(const char* key, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		return Value(getStringForKey(key, secret)).asDouble();
	}

	static double getDoubleForKey(const char* key, double defaultValue, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		char valueString[20] = { 0 };
		sprintf(valueString, "%lf", defaultValue);
		return Value(getStringForKey(key, valueString, secret)).asDouble();
	}

	static bool getBooleanForKey(const char* key, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		return getStringForKey(key, secret).c_str()=="false"? false:true;
	}

	static bool getBooleanForKey(const char* key, bool defaultVale, const char* secret = "Cocos2dxReallyHelplichuang")
	{
		std::string str;
		if (defaultVale)
			str = getStringForKey(key, "true", secret);
		else
			str = getStringForKey(key, "false", secret);

		if (str == "false")
			return false;
		else
			return true;
	}
};


#endif
