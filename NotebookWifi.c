#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFSIZE 1024

void wi_fi_setting(void);

void main(void)
{
	int select = 0;
	
	system("title 노트북 Wi-fi Hotspot화 프로그램 - 제작.By osm1892");
	
	do{
		puts("1.....와이파이 설정");
		puts("2.....와이파이 켜기");
		puts("3.....와이파이 끄기");
		puts("4.....와이파이 제거");
		puts("0.....프로그램 종료");
		printf("번호 입력 : ");
		scanf("%d",&select);
		getchar();
		switch(select)
		{
			case 1:
				wi_fi_setting();
				getchar();
				break;
			case 2:
				system("netsh wlan start hostednetwork");
				getchar();
				break;
			case 3:
				system("netsh wlan stop hostednetwork");
				getchar();
				break;
			case 4:
				system("netsh wlan set hostednetwork mode=disallow");
				getchar();
				break;
			case 0:
				break;
			default:
				printf("잘못 입력하셨습니다.");
				getchar();
				break;
		}
		system("cls");
	}while(select);
}

void wi_fi_setting(void)
{
	char buffer[2][MAX_BUFSIZE] = {0}, retval[200] = {0}; // I thought this 200 size is enough.
	int i = 0, length = 0, Exit = 0;
	
	system("cls");
	while (!Exit)
	{
		Exit = 1;
		printf("와이파이 네트워크의 이름을 설정해주세요 (최대 16글자 영어, 숫자만 가능)\n: ");
		gets(buffer[0]);
		getchar();
		length = strlen(buffer[0]);
		if (length <= 0 || 16 < length)
		{
			puts("글 길이가 맞지 않습니다. 다시 설정해주세요.");
			getchar();
			Exit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[0][i]) && !isdigit(buffer[0][i]))
			{
				puts("네트워크 이름이 잘못되었습니다.");
				getchar();
				Exit = 0;
				break;
			}
		}
	}
	Exit = 0;
	
	while (!Exit)
	{
		Exit = 1;
		printf("와이파이 비밀번호를 설정해주세요 (최소 8글자/최대 63글자 영어,숫자만 가능)\n :");
		gets(buffer[1]);
		getchar();
		length = strlen(buffer[1]);
		if(length < 8 || length > 63)
		{
			puts("글 길이가 맞지 않습니다. 다시 설정해주세요.");
			getchar();
			Exit = 0;
			continue;
		}
		for(i = 0; i < length; i++)
		{
			if (!isalpha(buffer[1][i]) && !isdigit(buffer[1][i]))
			{
				puts("비밀번호가 잘못되었습니다.");
				getchar();
				Exit = 0;
				break;
			}
		}
	}
	
	system("net start Wlansvc");
	system("net start SharedAccess");
	sprintf(retval, "%s%s%s%s%s%s", "netsh wlan set hostednetwork mode=allow \"ssid=",buffer[0],"\" \"key=",buffer[1],"\" keyUsage=persistent", NULL); 
	system(retval);
}
// This code was updated by osm1892