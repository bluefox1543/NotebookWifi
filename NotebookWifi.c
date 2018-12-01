#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFSIZE 1024

#ifdef _WIN32
#define CLEAR system("cls")
#else
#define CLEAR system("clear")
#endif

int IsNetConnected(void);
void WiFiSetting(void);

int main(void)
{
	int select = 0;

#ifdef _WIN32
	system("title ?명듃遺?Wi-fi Hotspot???꾨줈洹몃옩 - ?쒖옉.By 移댁뭅誘몃꽕. 湲곗뿬?? osm1892");
#endif

#if defined _WIN32 || defined __linux
	while (!select)
	{
		puts("?꾩옱??Vista ?댁긽???덈룄???먮뒗 Debian 怨꾩뿴??由щ늼??OS瑜?吏?먰빀?덈떎.");

#if defined _WIN32
		printf("?덈룄??OS??寃껋쑝濡??뺤씤?⑸땲?? Vista/7/8/10 踰꾩쟾??留욎뒿?덇퉴? (y/n) : ");
		scanf("%c", &select);
		getchar();

		switch (select)
		{
		case 'y':
		case 'Y':
			CLEAR;
			break;
		case 'n':
		case 'N':
			puts("?꾨줈洹몃옩??醫낅즺?⑸땲??);
			return 0;
		default:
			CLEAR;
			select = 0;
			break;
		}
	}

	do {
		puts
		(
			"1.....??댄뙆???ㅼ젙\n"
			"2.....??댄뙆??耳쒓린\n"
			"3.....??댄뙆???꾧린\n"
			"4.....??댄뙆???쒓굅\n"
			"0.....?꾨줈洹몃옩 醫낅즺"
		);
		printf("踰덊샇 ?낅젰 : ");
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
				printf("?섎せ ?낅젰?섏뀲?듬땲??");
				getchar();
				break;
		}
		CLEAR;

#elif defined __linux
		fputs("Debian 怨꾩뿴??由щ늼??踰꾩쟾???ъ슜?섍퀬 怨꾩떗?덇퉴? (y/n) : ", stdout);
		scanf("%d", &select);
		getchar();

		do {
			puts
			(
				"1.....??댄뙆???ㅼ젙\n"
				"2.....??댄뙆??耳쒓린\n"
				"3.....??댄뙆???꾧린\n"
				"4.....??댄뙆???쒓굅\n"
				"0.....?꾨줈洹몃옩 醫낅즺"
			);
			printf("踰덊샇 ?낅젰 : ");
			scanf("%d", &select);
			getchar();
			switch (select)
			{
			case 1:
				WiFiSetting();
				getchar();
				break;
			case 2:
				system("service hostapd start");
				system("service dnsmasq start");
				getchar();
				break;
			case 3:
				system("service hostapd stop");
				system("service dnsmasq stop");
				getchar();
				break;
			case 4:
				system("sudo echo '0' > /proc/sys/net/ipv4/ip_forward");
				system("sudo rm /etc/sysconfig/iptables");
				system("sudo mv /etc/sysconfig/iptables.original /etc/sysconfig/iptables");
				getchar();
				break;
			case 0:
				return 0;
			default:
				printf("?섎せ ?낅젰?섏뀲?듬땲??");
				getchar();
				break;
			}
	} while (select);
#endif
#else
	puts("二꾩넚?⑸땲?? 吏?먰븯吏 ?딅뒗 OS?낅땲?? ?꾨줈洹몃옩??醫낅즺?⑸땲??");
	getchar();
	return 0;
#endif
}

void WiFiSetting(void)
{
#if defined _WIN32
	char buffer[MAX_BUFSIZE] = { 0 }, retval[200] = { 0 }; // I thought this 200 size is enough.
	int i = 0, length = 0, isExit = 0;

	system("cls");
	while (!isExit)
	{
		isExit = 1;
		printf("??댄뙆???ㅽ듃?뚰겕???대쫫???ㅼ젙?댁＜?몄슂 (理쒕? 16湲???곸뼱, ?レ옄留?媛??\n: ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer);
		if (length <= 0 || 16 < length)
		{
			puts("SSID??湲몄씠媛 留욎? ?딆뒿?덈떎.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("?ㅽ듃?뚰겕 ?대쫫???섎せ?섏뿀?듬땲??");
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
		printf("??댄뙆??鍮꾨?踰덊샇瑜??ㅼ젙?댁＜?몄슂 (理쒖냼 8湲??理쒕? 63湲???곸뼱,?レ옄留?媛??\n : ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer);
		if (length < 8 || length > 63)
		{
			puts("鍮꾨?踰덊샇??湲몄씠媛 留욎? ?딆뒿?덈떎.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("?섎せ???뺤떇??鍮꾨?踰덊샇?낅땲??");
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

#elif defined __linux
	char buffer[MAX_BUFSIZE] = { 0 };
	int isInstalled = 0, isExit = 0, length = 0, i = 0;
	FILE *hostapd = popen("apt version hostapd", "r");
	FILE *dnsmasq = popen("apt version dnsmasq", "r");
	FILE *wireless_tools = popen("apt version wireless-tools", "r");
	FILE *iw = popen("apt version iw", "r");
	FILE *wvdial = popen("apt version wvdial", "r");
	FILE *conf1 = fopen("conf1", "w");
	FILE *conf2 = fopen("conf2", "w");

	// hostapd???ㅼ튂 ?щ?瑜??먮떒?⑸땲??
	fgets(buffer, sizeof(buffer), hostapd);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 1;
	}
	pclose(hostapd);

	// dnsmasq???ㅼ튂 ?щ?瑜??먮떒?⑸땲??
	fgets(buffer, sizeof(buffer), dnsmasq);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 2;
	}
	pclose(dnsmasq);

	// wireless-tools???ㅼ튂 ?щ?瑜??먮떒?⑸땲??
	fgets(buffer, sizeof(buffer), wireless_tools);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 4;
	}
	pclose(wireless_tools);

	// iw???ㅼ튂 ?щ?瑜??먮떒?⑸땲??
	fgets(buffer, sizeof(buffer), iw);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 8;
	}
	pclose(iw);

	// wvdial???ㅼ튂 ?щ?瑜??먮떒?⑸땲??
	fgets(buffer, sizeof(buffer), wvdial);
	if (strlen(buffer) > 2)
	{
		isInstalled |= 16;
	}

	if (isInstalled != 31)
	{
		if (IsNetConnected() == 0)
		{
			puts("援ъ꽦?붿냼瑜??ㅼ튂?댁빞 ?섏?留? ?ㅽ듃?뚰겕???곌껐???섏뼱?덉? ?딆뒿?덈떎. ?꾨줈洹몃옩??醫낅즺?⑸땲??");
			exit(0);
		}
		else
		{
			puts("援ъ꽦?붿냼瑜??ㅼ튂?⑸땲??");
			if (isInstalled & 1 == 0)
				system("sudo apt install hostapd -y");
			if (isInstalled & 2 == 0)
				system("sudo apt install dnsmasq -y");
			if (isInstalled & 4 == 0)
				system("sudo apt install wireless-tools -y"); // 湲곕낯?ㅼ튂 ?섏뼱?덉쓣 ???덉쓬.
			if (isInstalled & 8 == 0)
				system("sudo apt install iw -y"); // 湲곕낯?ㅼ튂 ?섏뼱?덉쓣 ???덉쓬.
			if (isInstalled & 16 == 0)
				system("sudo apt install wvdial -y");
		}
		puts("援ъ꽦?붿냼 ?ㅼ튂媛 ?꾨즺?섏뿀?듬땲??");
	}

	puts("?ㅼ젙???쒖옉?⑸땲??");

	fputs
	(
		"log-facility=/var/log/dnsmasq.log\n"
		"#address=/#/10.0.0.1\n"
		"#address=/google.com/10.0.0.1\n"
		"interface=wlan0\n"
		"dhcp-range=10.0.0.10,10.0.0.250,12h\n"
		"dhcp-option=3,10.0.0.1\n"
		"dhcp-option=6,10.0.0.1\n"
		"#no-resolv\n"
		"log-queries\n", conf1
	);
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

	fputs
	(
		"interface=wlan0\n"
		"driver=nl80211\n"
		"channel=1\n\n"
		"ssid=", conf2
	);

	while (!isExit)
	{
		isExit = 1;
		printf("??댄뙆???ㅽ듃?뚰겕???대쫫???ㅼ젙?댁＜?몄슂 (理쒕? 16湲???곸뼱, ?レ옄留?媛??\n: ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer[0]);
		if (length <= 0 || 16 < length)
		{
			puts("SSID??湲몄씠媛 留욎? ?딆뒿?덈떎.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("?ㅽ듃?뚰겕 ?대쫫???섎せ?섏뿀?듬땲??");
				getchar();
				isExit = 0;
				break;
			}
		}
	}
	fputs(buffer, conf2);
	fputs
	(
		"\nwpa=2\n"
		"wpa_passphrase=", conf2
	);
	while (!isExit)
	{
		isExit = 1;
		printf("??댄뙆??鍮꾨?踰덊샇瑜??ㅼ젙?댁＜?몄슂 (理쒖냼 8湲??理쒕? 63湲???곸뼱,?レ옄留?媛??\n : ");
		fgets(buffer, sizeof(buffer), stdin);
		getchar();
		length = strlen(buffer);
		if (length < 8 || length > 63)
		{
			puts("鍮꾨?踰덊샇??湲몄씠媛 留욎? ?딆뒿?덈떎.");
			getchar();
			isExit = 0;
			continue;
		}
		for (i = 0; i < length; i++)
		{
			if (!isalpha(buffer[i]) && !isdigit(buffer[i]))
			{
				puts("?섎せ???뺤떇??鍮꾨?踰덊샇?낅땲??");
				getchar();
				isExit = 0;
				break;
			}
		}
	}
	fputs
	(
		"\nwpa_key_mgmt=WPA-PSK\n"
		"wpa_pairwise=CCMP\n"
		"# Change the broadcasted/multicasted keys after this many seconds.\n"
		"wpa_group_rekey=600\n" // ??蹂寃?二쇨린瑜??덈Т 湲멸쾶 ?ㅼ젙?섎㈃ 蹂댁븞??臾몄젣媛 諛쒖깮 ?????덉뒿?덈떎.
		"# Change the master key after this many seconds. Master key is used as a basis\n"
		"wpa_gmk_rekey=86400\n", conf2 // 留덉갔媛吏濡? ??二쇨린瑜??덈Т 湲멸쾶 ?ㅼ젙?섏떆硫?蹂댁븞??臾몄젣媛 諛쒖깮?????덉뒿?덈떎. ?섏?留??덈Т 吏㏐쾶 ?ㅼ젙 ??寃쎌슦, ?딄?????쓣 ???덉뒿?덈떎.
	);
	fclose(conf2);
	system("sudo rm /etc/hostapd/hostapd.conf");
	system("sudo mv ./conf2 /etc/hostapd/hostapd.conf");
	system("sudo service hostapd start");
	return;
#endif
}

int IsNetConnected(void) // ?ㅽ듃?뚰겕 ?곌껐 ?щ?瑜??뺤씤?⑸땲??
{
#ifdef _WIN32
	if (system("ping www.google.com -t 2 > null") == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
#else
	if (system("ping www.google.com -c 2 > /dev/null") == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
#endif
}
// This code was updated by osm1892