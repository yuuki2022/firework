#include <graphics.h> //ͼ�ν���
#include <ctime>
#include <cstdlib>
#include <mmsystem.h>
#include <conio.h>
#include <windows.h>

#pragma comment(lib,"winmm.lib")  //��Щ�����ᱨ��

#define NUM 13
#define PI 3.14

//�Ȱ��̻����ŵ�ʱ��Ū�ɽṹ��
struct Jet
{
	int x, y; //����
	int hx, hy;  //��ߵ�
	int height; //???
	bool shoot; //�Ƿ���
	DWORD t1, t2, dt; //�ٶ�
	IMAGE img[2];
	byte n : 1;
}jet[NUM];

//����̻��ṹ��
struct Fire //int a;
{
	int r;
	int maxr;
	int x, y; //����
	int cen_x, cen_y; //���ĵ㣬�����õ���
	int width, height;//img size
	int xy[240][240]; //240*240
	bool show;
	bool draw;
	DWORD t1, t2, dt; //ģ�ⱬը���̻��õ����ٶȵȲ���
}fire[NUM];

void Init(int i); //��ʼ��
void Load();  //����ͼƬ����
void ChoiseRelu(DWORD& t1);
void Shoot();
void ShowFire(DWORD* pmem);
void Style(DWORD& st1);
//void saySomething();
const int N = 800;
struct STAR
{
	int 	x;
	int		y;
	int		color;
}star[N];

void starTime();
#pragma once
