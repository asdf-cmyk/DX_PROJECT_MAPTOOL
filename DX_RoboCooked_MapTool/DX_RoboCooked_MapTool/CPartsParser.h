#pragma once
#define TOKEN_COUNT 200  // ��ū�� �ִ� ����

enum MY_TOKEN_TYPE { TOKEN_STRING = 0, TOKEN_NUMBER };

struct MY_TOKEN
{
	MY_TOKEN_TYPE type;
	union {             // �� ���� �� �� ������ ������ ���̹Ƿ� ����ü
		char* string;
		double number;
	};
	bool isArray;  
};

struct JSON
{
	MY_TOKEN tokens[TOKEN_COUNT];
};

class CParts;
class CPartsParser
{
private:
	map<string, CParts> m_mapPartsData;
public:
	CPartsParser();
	~CPartsParser();

	char* ReadFile(char* fileName, int* readSize);
	void ParseJSON(char* doc, int size, JSON* json);
	void SavePartsData(JSON json);
	void FreeJSON(JSON* json);
	void EliminateChar(char* str, char c);
};

