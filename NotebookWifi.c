#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFSIZE 1024

int IsNetConnected(void);

#if defined _WIN32
#define OS 1

void WiFiSetting(void);

int main(void)
{
	int select = 0;

	system("title 노트북 Wi-fi Hotspot화 프로그램 - 제작.By 카카미네. 기여자: osm1892");

	while (!select)
	{
		puts("현재는 Vista 이상의 윈도우 또는 Debian 계열의 리눅스 OS를 지원합니다.");
		printf("윈도우 OS인 것으로 확인됩니다. Vista/7/8/10 버전이 맞습니까? (y/n) : ");
		scanf("%c", &select);
		getchar();

		switch (select)
		{
		case 'y':
		case 'Y':
			system("cls");
			break;
		case 'n':
		case 'N':
			puts("프로그램을 종료합니다");
			return 0;
		default:
			system("cls");
			select = 0;
			break;
		}
	}

	do {
		puts("1.....와이파이 설정");
		puts("2.....와이파이 켜기");
		puts("3.....와이파이 끄기");
		puts("4.....와이파이 제거");
		puts("0.....프로그램 종료");
		printf("번호 입력 : ");
		scanf("%d", &select);
		getchar();
		switch (select)
		{
		case 1:
			WiFiSetting();
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
			return 0;
		default:
			printf("잘못 입력하셨습니다.");
			getchar();
			break;
		}
		system("cls");
	} while (select);
}

void WiFiSetting(void)
{
	char buffer[MAX_BUFSIZE] = { 0 }, retval[200] = { 0 }; // I thought this 200 size is enough.
	int i = 0, length = 0, isExit = 0;

	system("cls");
	while (!isExit)
	{
		isExit = 1;
		printf("와이파이 네트워크의 이름을 설정해주세요 (최대 16글자 영어, 숫자만 가능)\n: ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer);
		if (length <= 0 || 16 < length)
		{
			puts("SSID의 길이가 맞지 않습니다.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("네트워크 이름이 잘못되었습니다.");
				getchar();
				isExit = 0;
				break;
			}
		}
	}
	isExit = 0;

	while (!isExit)
	{
		isExit = 1;
		printf("와이파이 비밀번호를 설정해주세요 (최소 8글자/최대 63글자 영어,숫자만 가능)\n : ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer);
		if (length < 8 || length > 63)
		{
			puts("비밀번호의 길이가 맞지 않습니다.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("잘못된 형식의 비밀번호입니다.");
				getchar();
				isExit = 0;
				break;
			}
		}
	}

	system("net start Wlansvc");
	system("net start SharedAccess");
	sprintf(retval, "%s%s%s%s%s%s", "netsh wlan set hostednetwork mode=allow \"ssid=", buffer[0], "\" \"key=", buffer[1], "\" keyUsage=persistent", NULL);
	system(retval);
}

#elif defined __linux__
#define OS 2

void WiFiSetting(void);

int main(void)
{
	int select = 0;

	while (!select)
	{
		puts("현재는 Vista 이상의 윈도우 또는 Debian 계열의 리눅스 OS를 지원합니다.");
		printf("Debian, Ubuntu, 또는 Mint OS가 맞습니까? (y/n) : ");
		scanf("%c", &select);
		getchar();

		switch (select)
		{
		case 'y':
		case 'Y':
			system("clear");
			break;
		case 'n':
		case 'N':
			puts("프로그램을 종료합니다.");
			return 0;
		default:
			system("clear");
			select = 0;
			break;
		}
	}

	puts("1.....와이파이 설정");
	puts("2.....와이파이 켜기");
	puts("3.....와이파이 끄기");
	puts("4.....와이파이 제거");
	puts("0.....프로그램 종료");
	printf("번호 입력 : ");
	scanf("%d", &select);
	getchar();
	switch (select)
	{
	case 1:
		WiFiSetting();
		break;
	case 2:
		system("service hostapd start");
		system("service dnsmasq start");
		break;
	case 3:
		system("service hostapd stop");
		system("service dnsmasq stop");
		break;
	case 4:
		system("sudo apt remove dnsmasq -y");
		system("sudo apt remove hostapd -y");
		system("sudo apt remove wvdial -y");
		system("sudo echo '0' > /proc/sys/net/ipv4/ip_forward");
		system("sudo rm /etc/sysconfig/iptables");
		system("sudo mv /etc/sysconfig/iptables.original /etc/sysconfig/iptables");
	case 0:
		return 0;
	default:
		puts("잘못 입력하셨습니다.");
		getchar();
		break;
	}
}

void WiFiSetting(void)
{
	char buffer[MAX_BUFSIZE] = { 0 };
	int isInstalled = 0, isExit = 0, length = 0, i = 0;
	FILE *hostapd = popen("apt version hostapd", "r");
	FILE *dnsmasq = popen("apt version dnsmasq", "r");
	FILE *wireless_tools = popen("apt version wireless-tools", "r");
	FILE *iw = popen("apt version iw", "r");
	FILE *wvdial = popen("apt version wvdial", "r");
	FILE *conf1 = fopen("conf1", "w");
	FILE *conf2 = fopen("conf2", "w");

	// hostapd의 설치 여부를 판단합니다.
	fgets(buffer, sizeof(buffer), hostapd);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 1;
	}
	pclose(hostapd);

	// dnsmasq의 설치 여부를 판단합니다.
	fgets(buffer, sizeof(buffer), dnsmasq);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 2;
	}
	pclose(dnsmasq);

	// wireless-tools의 설치 여부를 판단합니다.
	fgets(buffer, sizeof(buffer), wireless_tools);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 4;
	}
	pclose(wireless_tools);

	// iw의 설치 여부를 판단합니다.
	fgets(buffer, sizeof(buffer), iw);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 8;
	}
	pclose(iw);

	// wvdial의 설치 여부를 판단합니다.
	fgets(buffer, sizeof(buffer), wvdial);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 16;
	}

	if (isInstalled != 31)
	{
		if (IsNetConnected() == 0)
		{
			puts("구성요소를 설치해야 하지만, 네트워크에 연결이 되어있지 않습니다. 프로그램을 종료합니다.");
			exit(0);
		}
		else
		{
			puts("구성요소를 설치합니다.");
			if (isInstalled & 1 == 0)
				system("sudo apt install hostapd -y");
			if (isInstalled & 2 == 0)
				system("sudo apt install dnsmasq -y");
			if (isInstalled & 4 == 0)
				system("sudo apt install wireless-tools -y"); // 기본설치 되어있을 수 있음.
			if (isInstalled & 8 == 0)
				system("sudo apt install iw -y"); // 기본설치 되어있을 수 있음.
			if (isInstalled & 16 == 0)
				system("sudo apt install wvdial -y");
		}
		puts("구성요소 설치가 완료되었습니다.");
	}

	puts("설정을 시작합니다.");

	fputs("log-facility=/var/log/dnsmasq.log\n", conf1);
	fputs("#address=/#/10.0.0.1\n", conf1);
	fputs("#address=/google.com/10.0.0.1\n", conf1);
	fputs("interface=wlan0\n", conf1);
	fputs("dhcp-range=10.0.0.10,10.0.0.250,12h\n", conf1);
	fputs("dhcp-option=3,10.0.0.1\n", conf1);
	fputs("dhcp-option=6,10.0.0.1\n", conf1);
	fputs("#no-resolv\n", conf1);
	fputs("log-queries\n", conf1);
	fclose(conf1);
	system("sudo rm /etc/dnsmasq.conf");
	system("sudo mv ./conf1 /etc/dnsmasq.conf");

	system("sudo service dnsmasq start");

	system("sudo ifconfig wlan0 up");
	system("sudo ifconfig wlan0 10.0.0.1/24");

	system("sudo cp /etc/sysconfig/iptables /etc/sysconfig/iptables.original");

	system("sudo iptables -t nat -F");
	system("sudo iptables -F");
	system("sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE");
	system("sudo iptables -A FORWARD -i wlan0 -o eth0 -j ACCEPT");
	system("sudo echo '1' > /proc/sys/net/ipv4/ip_forward");
	system("sudo service iptables save");


	fputs("interface=wlan0\n", conf2);
	fputs("driver=nl80211\n", conf2);
	fputs("channel=1\n\n", conf2);
	fputs("ssid=", conf2);
	while (!isExit)
	{
		isExit = 1;
		printf("와이파이 네트워크의 이름을 설정해주세요 (최대 16글자 영어, 숫자만 가능)\n: ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer[0]);
		if (length <= 0 || 16 < length)
		{
			puts("SSID의 길이가 맞지 않습니다.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("네트워크 이름이 잘못되었습니다.");
				getchar();
				isExit = 0;
				break;
			}
		}
	}
	fputs(buffer, conf2);
	fputs("\nwpa=2\n", conf2);
	fputs("wpa_passphrase=", conf2);
	while (!isExit)
	{
		isExit = 1;
		printf("와이파이 비밀번호를 설정해주세요 (최소 8글자/최대 63글자 영어,숫자만 가능)\n : ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer);
		if (length < 8 || length > 63)
		{
			puts("비밀번호의 길이가 맞지 않습니다.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("잘못된 형식의 비밀번호입니다.");
				getchar();
				isExit = 0;
				break;
			}
		}
	}
	fputs("\nwpa_key_mgmt=WPA-PSK\n", conf2);
	fputs("wpa_pairwise=CCMP\n", conf2);
	fputs("# Change the broadcasted/multicasted keys after this many seconds.\n", conf2);
	fputs("wpa_group_rekey=600\n", conf2); // 이 변경 주기를 너무 길게 설정하면 보안에 문제가 발생 할 수 있습니다.
	fputs("# Change the master key after this many seconds. Master key is used as a basis\n", conf2);
	fputs("wpa_gmk_rekey=86400\n", conf2); // 마찬가지로, 이 주기를 너무 길게 설정하시면 보안에 문제가 발생할 수 있습니다. 하지만 너무 짧게 설정 할 경우, 끊김이 잦을 수 있습니다.
	fclose(conf2);
	system("sudo rm /etc/hostapd/hostapd.conf");
	system("sudo mv ./conf2 /etc/hostapd/hostapd.conf");
	system("sudo service hostapd start");
	return;
}
#else
#define OS 0

int main(void)
{
	puts("죄송합니다. 지원하지 않는 OS로 확인됩니다. 프로그램을 종료합니다.");
	getchar();
	return 0;
}

#endif

int IsNetConnected(void) // 네트워크 연결 여부를 확인합니다.
{
	if (OS == 1) // 윈도우용
	{
		if (system("ping www.google.com -t 2 > null") == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else // 리눅스 외 여러 OS에서 사용되는 방식
	{
		if (system("ping www.google.com -c 2 > /dev/null") == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
// This code was updated by osm1892