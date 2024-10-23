#pragma once
#pragma warning (disable:4786)
#include <string>

#define SIMUCLIENT_API 
//#define _WIN32_WINNT 0x0502
#define USE_GENERIC_BUT_CPU_INTENSIVE_SLEEP 0

// NUTZBARE FUNKTIONEN (offizielle Schnittstelle)
/* 
ʹ�õ�ַ��ͼ�η������������ӣ������ݴ��ڴ�С X �� Y ȷ�����ڵĴ�С��
ʾ��: bInitialisiereGrafik(800,500);
*/
SIMUCLIENT_API bool bInitialisiereGrafik(int iFenstergroesseX, int iFenstergroesseY, const char* adresse = "127.0.0.1", const char* port = "7654");

/**
 * @brief ������ X �� Y ������һ��ʮ��·��
 * @param koordinateX
 * @param koordinateY
 * @return
 */
SIMUCLIENT_API bool bZeichneKreuzung(int koordinateX, int koordinateY);

/* 
����һ����������·���Ľֵ���ָ�����ȡ��ֵ���һϵ�е����ɡ�
������Ҫ 2 ���㣨ֱ�ߣ���������������ǳɶԳ��֣�X/Y����
ʾ��:	
int feld[] = { 100 , 200 , 300 , 400 }; 
int anzahl = 2;
bZeichneStrasse("Hin", "Rueck", 40, anzahl, feld);
*/
SIMUCLIENT_API bool bZeichneStrasse(const std::string& nameHinweg, const std::string& nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);

/*
	��ָ����·������ʾһ��������RelPosition �������·�߳��ȵ�λ�ã�ֵ���� 0 �� 1 ֮�䣩��
	bZeichnePKW("Rennauto", "Rennstrecke" , AbschnittStrecke / WegLaenge, 250, 80);
}
*/
SIMUCLIENT_API bool bZeichnePKW(const std::string& namePKW, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);

/*
	��ָ����·������ʾһ�����г���RelPosition �������·�����ȵ�λ�ã�ֵ���� 0 �� 1 ֮�䣩��

	bZeichneFahrrad("Drahtesel", "Fahrradstrasse" , AbschnittStrecke / WegLaenge, 15);
*/
SIMUCLIENT_API bool bZeichneFahrrad(const std::string& nameFahrrad, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit);

/*
��ͼ�η������Ͽ����Ӳ��رմ���
*/
SIMUCLIENT_API void vBeendeGrafik();

/* ��ָ���ĳ�����ͼ��Ӧ�ó������Ƴ� */
SIMUCLIENT_API bool bLoescheFahrzeug(const std::string& name);

/* ��������ڵı���������ʾȫ��ʱ��
*/
SIMUCLIENT_API void vSetzeZeit(const double globaleZeit);

// Wrapperfunktion fuer Sleep
/*
	����ִ�н��ӳ�ָ���ĺ�������
*/
SIMUCLIENT_API void vSleep(int anzahlMillisekunden);


SIMUCLIENT_API bool bZeichneStrasse(const char* nameHinweg, const char* nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);
SIMUCLIENT_API bool bZeichneStrasse(const std::string& nameHinweg, const char* nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);
SIMUCLIENT_API bool bZeichneStrasse(const char* nameHinweg, const std::string& nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);

SIMUCLIENT_API bool bZeichnePKW(const char*  namePKW, const char* nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);
SIMUCLIENT_API bool bZeichnePKW(const std::string& namePKW, const char* nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);
SIMUCLIENT_API bool bZeichnePKW(const char*  namePKW, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);

SIMUCLIENT_API bool bZeichneFahrrad(const std::string& nameFahrrad, const char* nameWeg, double dRelPosition, double dGeschwindigkeit);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  nameFahrrad, const char* nameWeg, double dRelPosition, double dGeschwindigkeit);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  nameFahrrad, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit);

SIMUCLIENT_API bool bLoescheFahrzeug(const char* name);
