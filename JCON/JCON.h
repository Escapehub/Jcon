/*
    +-----------------------------
    |
    |   @file JCON.h
    |
    |   
    |
    |
    |
    |
    |
    |
*/
#pragma once

#include <iostream>
#include <windows.h>
#include <variant>
#include <map>
#include <vector>
#include <any>


#ifndef JCON

struct JValue;

enum VariantType
{
    TYPE_INT        = 0,
    TYPE_FLOAT      = 1,
    TYPE_DOUBLE     = 2,
    TYPE_BOOL       = 3,
    TYPE_WCHAR      = 4,
    TYPE_CHAR       = 5,
    TYPE_LPCSTR     = 6,
    TYPE_LPCWSTR    = 7,
    TYPE_LPSTR      = 8,
    TYPE_LPWSTR     = 9,
    TYPE_JLIST      = 10,
    TYPE_JOBJECT    = 11
};

typedef struct JList
{
    std::vector<JValue> vValue;
};

typedef struct JObject
{
    std::map<LPCSTR, JValue> mValue;
};

typedef std::variant<int, float, double, bool, WCHAR, CHAR, LPCSTR, LPCWSTR, LPSTR, LPWSTR, JList, JObject> JVariant;

struct JValue
{
    VariantType type;
    JVariant var;
};

class Jcon
{
private:
    std::map<LPCSTR, JVariant> mValue;

public:
	Jcon() {}
	virtual ~Jcon() {}

    void set(LPCSTR key, JVariant value)
    {
        //JValue val;
        //val.type = (VariantType)value.index();
        //val.var = value;
        this->mValue[key] = value;
    }

	void stringify()
	{
        std::string output;
        INT i = 0;
        output += "{";
        for (const auto v : this->mValue) 
        {
            switch (v.second.index())
            {
            case TYPE_INT:
                    output += formatString("\"%s\":%d", v.first, std::get<int>(v.second));
                break;

            case TYPE_LPCSTR:
                    output += formatString("\"%s\":%s", v.first, std::get<LPCSTR>(v.second));
                break;

            case TYPE_FLOAT:
                    output += formatString("\"%s\":%f", v.first, std::get<float>(v.second));
                break;

            case TYPE_DOUBLE:
                    output += formatString("\"%s\":%lf", v.first, std::get<double>(v.second));
                break;
            }
            output += (mValue.size() - 1) == i ? "" : ",";
            i++;
        }
        output += "}";
        printf(output.c_str());
	}

    template<typename ... Args> 
    std::string formatString(const std::string& format, Args ... args)
    {
        int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
        if (size <= 0) { throw std::runtime_error("Error during formatting."); }
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); 
    }
};

#endif // !JCON