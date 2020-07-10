#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_BUFSIZE 1024

void wi_fi_setting(void);

void main(void)
{
	int select = 0;

	_wsetlocale(LC_ALL, L"korean");
	
	_wsystem(L"title 노트북 Wi-fi Hotspot화 프로그램 - 제작.By osm1892");
	
	do{
		_putws(L"1.....와이파이 설정");
		_putws(L"2.....와이파이 켜기");
		_putws(L"3.....와이파이 끄기");
		_putws(L"4.....와이파이 제거");
		_putws(L"0.....프로그램 종료");
		wprintf(L"번호 입력 : ");
		wscanf(L"%d",&select);
		getwchar();
		switch(select)
		{
			case 1:
				wi_fi_setting();
				getwchar();
				break;
			case 2:
				_wsystem(L"netsh wlan start hostednetwork");
				getwchar();
				break;
			case 3:
				_wsystem(L"netsh wlan stop hostednetwork");
				getwchar();
				break;
			case 4:
				_wsystem(L"netsh wlan set hostednetwork mode=disallow");
				getwchar();
				break;
			case 0:
				break;
			default:
				wprintf(L"잘못 입력하셨습니다.");
				getwchar();
				break;
		}
		_wsystem(L"cls");
	} while(select);
}

void wi_fi_setting(void)
{
	wchar_t buffer[2][MAX_BUFSIZE] = {0}, retval[200] = {0}; // I thought this 200 size is enough.
	int i = 0, length = 0, _exit = 0;
	
	_wsystem(L"cls");
	while (!_exit)
	{
		_exit = 1;
		wprintf(L"와이파이 네트워크의 이름을 설정해주세요 (최대 16글자 영어, 숫자만 가능)\n: ");
		fgetws(buffer[0], sizeof(buffer[0]), stdin);
		getwchar();
		length = wcslen(buffer[0]);
		if (length <= 0 || 16 < length)
		{
			_putws(L"글 길이가 맞지 않습니다. 다시 설정해주세요.");
			getwchar();
			_exit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[0][i]) && !isdigit(buffer[0][i]))
			{
				_putws(L"네트워크 이름이 잘못되었습니다.");
				getwchar();
				_exit = 0;
				break;
			}
		}
	}
	_exit = 0;
	
	while (!_exit)
	{
		_exit = 1;
		wprintf(L"와이파이 비밀번호를 설정해주세요 (최소 8글자/최대 63글자 영어,숫자만 가능)\n :");
		fgetws(buffer[1], sizeof(buffer[1]), stdin);
		getwchar();
		length = wcslen(buffer[1]);
		if(length < 8 || length > 63)
		{
			_putws(L"글 길이가 맞지 않습니다. 다시 설정해주세요.");
			getwchar();
			_exit = 0;
			continue;
		}
		for(i = 0; i < length; i++)
		{
			if (!isalpha(buffer[1][i]) && !isdigit(buffer[1][i]))
			{
				_putws(L"비밀번호가 잘못되었습니다.");
				getwchar();
				_exit = 0;
				break;
			}
		}
	}
	
	_wsystem(L"net start Wlansvc");
	_wsystem(L"net start SharedAccess");
	swprintf(retval, L"%s%s%s%s%s%s", L"netsh wlan set hostednetwork mode=allow \"ssid=", buffer[0], L"\" \"key=", buffer[1], L"\" keyUsage=persistent", NULL); 
	_wsystem(retval);
}
// This code was updated by osm1892