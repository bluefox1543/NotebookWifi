#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define MAX_BUFSIZE 1024

char *concatstr(char *,...);
void wi_fi_setting(void);

void main(void)
{
	int select;

	system("title ��Ʈ�� Wi-fi Hotspotȭ ���α׷� - ����.By ī���̳�");

	do{
		puts("1.....�������� ����");
		puts("2.....�������� �ѱ�");
		puts("3.....�������� ����");
		puts("4.....�������� ����");
		puts("0.....���α׷� ����");
		printf("��ȣ �Է� : ");
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
			printf("�߸� �Է��ϼ̽��ϴ�.");
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
	printf("�������� ��Ʈ��ũ�� �̸��� �������ּ��� (�ִ� 16���� ����,���ڸ� ����)\n :");
	gets(buffer[0]);
	fflush(stdin);
	length = strlen(buffer[0]);
	if((length<=0) || (length>16)){
		puts("�� ���̰� ���� �ʽ��ϴ�. �ٽ� �������ּ���.");
		_getch();
		goto wi_fi_name;
	}
	for(i = 0;i<length;i++){
		if((isalpha(buffer[0][i])!=0) || (isdigit(buffer[0][i])!=0));
		else{puts("��Ʈ��ũ �̸��� �߸��Ǿ����ϴ�.");	_getch();	goto wi_fi_name;}
	}
wi_fi_pass:
	printf("�������� ��й�ȣ�� �������ּ��� (�ּ� 8����/�ִ� 63���� ����,���ڸ� ����)\n :");
	gets(buffer[1]);
	fflush(stdin);
	length = strlen(buffer[1]);
	if((length<8) || (length>63)){
		puts("�� ���̰� ���� �ʽ��ϴ�. �ٽ� �������ּ���.");
		_getch();
		goto wi_fi_pass;
	}
	for(i = 0;i<length;i++){
		if((isalpha(buffer[1][i])!=0) || (isdigit(buffer[1][i])!=0));
		else{puts("��й�ȣ�� �߸��Ǿ����ϴ�.");	_getch();	goto wi_fi_pass;}
	}
	system("net start Wlansvc");
	system("net start SharedAccess");
	retval = concatstr("netsh wlan set hostednetwork mode=allow \"ssid=",buffer[0],"\" \"key=",buffer[1],"\" keyUsage=persistent",NULL);
	system(retval);
	free(retval);
}