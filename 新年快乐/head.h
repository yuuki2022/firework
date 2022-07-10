#include <graphics.h> //图形界面
#include <ctime>
#include <cstdlib>
#include <mmsystem.h>
#include <conio.h>
#include <windows.h>

#pragma comment(lib,"winmm.lib")  //有些东西会报错

#define NUM 13
#define PI 3.14

//先把烟花开放的时候弄成结构体
struct Jet
{
	int x, y; //坐标
	int hx, hy;  //最高点
	int height; //???
	bool shoot; //是否发射
	DWORD t1, t2, dt; //速度
	IMAGE img[2];
	byte n : 1;
}jet[NUM];

//搞个烟花结构体
struct Fire //int a;
{
	int r;
	int maxr;
	int x, y; //坐标
	int cen_x, cen_y; //中心点，后面用得上
	int width, height;//img size
	int xy[240][240]; //240*240
	bool show;
	bool draw;
	DWORD t1, t2, dt; //模拟爆炸过程会用到的速度等参数
}fire[NUM];

void Init(int i); //初始化
void Load();  //加载图片音乐
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
