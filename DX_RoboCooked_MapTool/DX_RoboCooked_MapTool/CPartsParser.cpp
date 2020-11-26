#include "stdafx.h"
#include "CPartsParser.h"
#include "CParts.h"

CPartsParser::CPartsParser()
{
}


CPartsParser::~CPartsParser()
{
}

char* CPartsParser::ReadFile(char* fileName, int* readSize)
{
	FILE *fp = fopen(fileName, "rb");
	if (fp == NULL)
		return NULL;

	int size;
	char *buffer;

	// ���� ũ�� ���ϱ�
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ���� ũ�� + NULL ������ŭ �޸𸮸� �Ҵ��ϰ� 0���� �ʱ�ȭ
	buffer = (char*)malloc(size + 1);
	memset(buffer, 0, size + 1);

	// ���� ���� �б�
	if (fread(buffer, size, 1, fp) < 1)
	{
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}

	*readSize = size;	// ���� ũ�⸦ �Ѱ���
	fclose(fp);

	return buffer;
}

void CPartsParser::ParseJSON(char* doc, int size, JSON* json)
{
	int tokenIndex = 0;    // ��ū �ε���
	int pos = 0;           // ���� �˻� ��ġ�� �����ϴ� ����

	EliminateChar(doc, '\r');
	EliminateChar(doc, '\n');
	EliminateChar(doc, ' ');

	if (doc[pos] != '[')   // ������ ������ [ ���� �˻�
		return;

	pos++;					// ���� ���ڷ�

	if (doc[pos] != '{')	// ���� ���ڰ� { ���� �˻�
		return;

	while (pos < size)       // ���� ũ�⸸ŭ �ݺ�
	{
		switch (doc[pos])    // ������ ������ ���� �б�
		{
		case '"':            // ���ڰ� "�̸� ���ڿ�
		{
			// ���ڿ��� ���� ��ġ�� ����. �� ���� "�� �����ϱ� ���� + 1
			char *begin = doc + pos + 1;

			// ���ڿ��� �� ��ġ�� ����. ���� "�� ��ġ
			char *end = strchr(begin, '"');
			if (end == NULL)    // "�� ������ �߸��� �����̹Ƿ� �ݺ��� ����
				break;

			int stringLength = end - begin;    // ���ڿ��� ���� ���̴� �� ��ġ - ���� ��ġ

			// ��ū �迭�� ���ڿ� ����, ��ū ������ ���ڿ�
			json->tokens[tokenIndex].type = (MY_TOKEN_TYPE)TOKEN_STRING;
			// ���ڿ� ���� + NULL ������ŭ �޸� �Ҵ�
			json->tokens[tokenIndex].string = (char*)malloc(stringLength + 1);
			// �Ҵ��� �޸𸮸� 0���� �ʱ�ȭ
			memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

			// �������� ���ڿ��� ��ū�� ����
			// ���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ�� ����
			memcpy(json->tokens[tokenIndex].string, begin, stringLength);

			tokenIndex++; // ��ū �ε��� ����

			pos = pos + stringLength + 1;    // ���� ��ġ + ���ڿ� ���� + " (+1)
		}
		break;

		case '0': case '1': case '2': case '3': case '4': case '5':    // ���ڰ� �����̸�
		case '6': case '7': case '8': case '9': case '-':              // -�� ������ ��
		{
			// ���ڿ��� ���� ��ġ�� ����
			char *begin = doc + pos;
			char *end;
			char *buffer;

			// ���ڿ��� �� ��ġ�� ����. ,�� �����ų�
			end = strchr(doc + pos, ',');
			if (end == NULL)
			{
				// } �� ������ ���ڿ��� ����
				end = strchr(doc + pos, '}');
				if (end == NULL)    // }�� ������ �߸��� �����̹Ƿ�
					break;          // �ݺ��� ����
			}

			int stringLength = end - begin;    // ���ڿ��� ���� ���̴� �� ��ġ - ���� ��ġ
			buffer = (char*)malloc(stringLength + 1);
			memset(buffer, 0, stringLength + 1);	// �Ҵ��� �޸𸮸� 0���� �ʱ�ȭ

			// �������� ���ڿ��� ���ۿ� ����
			// ���ڿ� ���� ��ġ���� ���ڿ� ���̸�ŭ�� ����
			memcpy(buffer, begin, stringLength);

			// ��ū ������ ����
			json->tokens[tokenIndex].type = TOKEN_NUMBER;
			// ���ڿ��� ���ڷ� ��ȯ�Ͽ� ��ū�� ����
			json->tokens[tokenIndex].number = atof(buffer);

			free(buffer);
			tokenIndex++;

			pos = pos + stringLength + 1;    // ���� ��ġ + ���ڿ� ���� + , �Ǵ� } (+1)
		}
		break;
		}
		pos++; // ���� ���ڷ�
	}
}

void CPartsParser::SavePartsData(JSON json)
{
	for(int i = 0; i < 20; i++)
	{
		CParts parts("");
		
		parts.SetPartsID(json.tokens[1 + (i * 11 + i)].string);
		parts.SetSize(D3DXVECTOR3(json.tokens[3 + (i * 11 + i)].number
			,json.tokens[5 + (i * 11 + i)].number
			,json.tokens[7 + (i * 11 + i)].number));
		parts.SetWeight(json.tokens[9 + (i * 11 + i)].number);
		parts.SetFormula(json.tokens[11 + (i * 11 + i)].string);
		m_mapPartsData.insert(std::make_pair(json.tokens[1 + (i * 11 + i)].string, parts));
	}
}

void CPartsParser::FreeJSON(JSON* json)
{
	for (int i = 0; i < TOKEN_COUNT; i++)
	{
		if (json->tokens[i].type == (MY_TOKEN_TYPE)TOKEN_STRING)
			free(json->tokens[i].string);
	}
}

void CPartsParser::EliminateChar(char* str, char c)
{
	for (; *str != '\0'; str++)	//���� ���ڸ� ���� ������ �ݺ�
	{
		if (*str == c)			//ch�� ���� ������ ��
		{
			strcpy(str, str + 1);
			str--;
		}
	}
}