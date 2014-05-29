#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define MAX_BUFSIZE 1024

char *concatstr(char *,...);
void wi_fi_setting(void);

void main(void)
{
	int select;

	system("title 노트북 Wi-fi Hotspot화 프로그램 - 제작.By 카가미네");

	do{
		puts("1.....와이파이 설정");
		puts("2.....와이파이 켜기");
		puts("3.....와이파이 끄기");
		puts("4.....와이파이 제거");
		puts("0.....프로그램 종료");
		printf("번호 입력 : ");
		scanf_s("%d",&select);
		fflush(stdin);
		switch(select)
		{
		case 1:
			wi_fi_setting();
			_getch();
			break;
		case 2:
			system("netsh wlan start hostednetwork");
			_getch();
			break;
		case 3:
			system("netsh wlan stop hostednetwork");
			_getch();
			break;
		case 4:
			system("netsh wlan set hostednetwork mode=disallow");
			_getch();
			break;
		case 0:		break;
		default:
			printf("잘못 입력하셨습니다.");
			_getch();
			break;
		}
		system("cls");
	}while(select);
}

char *concatstr(char *origin,...)
{
	va_list ap;
	char *retval,*tmp;
	long len = 0;

	_crt_va_start(ap,origin);
	len += strlen(origin);

	while((tmp=_crt_va_arg(ap,char *))!=NULL)
	{
		len += strlen(tmp);
	}
	retval = (char *)calloc(len+1,sizeof(char));

	_crt_va_end(ap);
	_crt_va_start(ap,origin);
	strcat(retval,origin);

	while((tmp=_crt_va_arg(ap,char *))!=NULL)
	{
		strcat(retval,tmp);
	}
	_crt_va_end(ap);
	return retval;
}

void wi_fi_setting(void)
{
	char buffer[2][MAX_BUFSIZE] = {0}, *retval;
	int i , length;

	system("cls");
wi_fi_name:
	printf("와이파이 네트워크의 이름을 설정해주세요 (최대 16글자 영어,숫자만 가능)\n :");
	gets(buffer[0]);
	fflush(stdin);
	length = strlen(buffer[0]);
	if((length<=0) || (length>16)){
		puts("글 길이가 맞지 않습니다. 다시 설정해주세요.");
		_getch();
		goto wi_fi_name;
	}
	for(i = 0;i<length;i++){
		if((isalpha(buffer[0][i])!=0) || (isdigit(buffer[0][i])!=0));
		else{puts("네트워크 이름이 잘못되었습니다.");	_getch();	goto wi_fi_name;}
	}
wi_fi_pass:
	printf("와이파이 비밀번호를 설정해주세요 (최소 8글자/최대 63글자 영어,숫자만 가능)\n :");
	gets(buffer[1]);
	fflush(stdin);
	length = strlen(buffer[1]);
	if((length<8) || (length>63)){
		puts("글 길이가 맞지 않습니다. 다시 설정해주세요.");
		_getch();
		goto wi_fi_pass;
	}
	for(i = 0;i<length;i++){
		if((isalpha(buffer[1][i])!=0) || (isdigit(buffer[1][i])!=0));
		else{puts("비밀번호가 잘못되었습니다.");	_getch();	goto wi_fi_pass;}
	}
	system("net start Wlansvc");
	system("net start SharedAccess");
	retval = concatstr("netsh wlan set hostednetwork mode=allow \"ssid=",buffer[0],"\" \"key=",buffer[1],"\" keyUsage=persistent",NULL);
	system(retval);
	free(retval);
}