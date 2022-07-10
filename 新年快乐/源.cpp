#include "head.h"

int main()
{
	//窗口初始化一个
	HWND hwnd = initgraph(1200, 600);
	SetWindowTextA(hwnd, "新年快乐");



	srand((unsigned)time(0));//搞个随机种子
	//music
	mciSendString(L"open yh.mp3 alias music", 0, 0, 0);//open bgm
	mciSendString(L"r music", 0, 0, 0); // 播放

	//saySomething();

	//getch();

	DWORD t1 = timeGetTime();//for heart to prepare
	DWORD* pmem = GetImageBuffer();
	DWORD st1 = timeGetTime();

	//init
	for (int i = 0; i < NUM; i++)
		Init(i);

	//load
	Load();
	starTime();
	//主程序开始调用
	BeginBatchDraw();
	while (1)
	{
		for (int i = 0; i < N; i++) {
			putpixel((int)star[i].x, star[i].y, star[i].color);
		}

		for (int clr = 0; clr < 1000; clr++)
		{
			for (int j = 0; j < 2; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 600;
				if (py1 < 790)
					pmem[py1 * 1200 + px1] = pmem[py1 * 1200 + px1 + 1] = BLACK;
			}
		}
		ChoiseRelu(t1);
		Shoot();
		ShowFire(pmem);
		Style(st1);
		FlushBatchDraw();
	}


	return 0;
}

void Init(int i)
{
	int r[NUM] = { 120,120,155,123,130,147,138,138,130,135,140,132,155 };
	int x[NUM] = { 120,120,110,117,110,93,102,102,110,105,100,108,110 };
	int y[NUM] = { 120,120,85,118,120,103,105,110,110,120,120,104,85 };
	fire[i].width = 1000;
	fire[i].height = 240;
	fire[i].cen_x = x[i];
	fire[i].cen_y = y[i];
	fire[i].maxr = r[i];
	fire[i].show = false;
	fire[i].dt = 5;
	fire[i].t1 = timeGetTime();//时间获取速度
	fire[i].r = 0;

	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;
	jet[i].shoot = false;//unmovable
}

void Load()
{
	IMAGE flowerImg, fimg;
	loadimage(&flowerImg, L"flower.jpg", 3120, 240);//绽开花程序
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&flowerImg);  //这个函数用于设定当前的绘图设备。
		getimage(&fimg, i * 240, 0, 240, 240);// 这个函数用于从当前绘图设备中获取图像。
		/*// 从当前绘图设备获取图像
void getimage(
	IMAGE* pDstImg,		// 保存图像的 IMAGE 对象指针
	int srcX,			// 要获取图像区域左上角 x 坐标
	int srcY,			// 要获取图像区域的左上角 y 坐标
	int srcWidth,		// 要获取图像区域的宽度
	int srcHeight		// 要获取图像区域的高度
);*/
		SetWorkingImage(&fimg);
		for (int m = 0; m < 240; m++)
		{
			for (int n = 0; n < 240; n++)
				fire[i].xy[m][n] = getpixel(m, n);//用于获取点的颜色
		}
	}
	IMAGE shootImg;
	loadimage(&shootImg, L"shoot.jpg", 200, 50);//发射图片
	for (int i = 0; i < NUM; i++)
	{
		int n = rand() % 5;
		SetWorkingImage(&shootImg);
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);
}

void ChoiseRelu(DWORD& t1)
{
	//flushmessage(EM_MOUSE);


	DWORD t2 = timeGetTime();
	if (t2 - t1 > 100)
	{
		int n = rand() % NUM;
		if (jet[n].shoot == false && fire[n].show == false)
		{
			jet[n].x = rand() % 1180;
			jet[n].y = rand() % 100 + 600;
			jet[n].hx = jet[n].x;
			jet[n].hy = rand() % 400;
			jet[n].height = jet[n].y - jet[n].hy;
			jet[n].shoot = true;
			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);
		}
		t1 = t2;
	}
}
void Shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = timeGetTime();
		if (jet[i].t2 - jet[i].t1 > jet[i].dt && jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			if (jet[i].y >= jet[i].hy)
			{
				jet[i].y -= 5;
				jet[i].n++;
			}
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			//越高越慢
			if (jet[i].y - jet[i].hy * 4 < jet[i].height)
				jet[i].dt = rand() % 4 + 10;
			//登顶
			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				fire[i].x = jet[i].x;
				fire[i].y = jet[i].hy;
				fire[i].show = true;
				jet[i].shoot = false;
			}
			jet[i].t1 = jet[i].t2;
		}
	}
}

void ShowFire(DWORD* pmem)
{
	//dt 
	int  drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 65, 65 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();

		if (fire[i].t2 - fire[i].t1 > fire[i].dt && fire[i].show == true)
		{
			if (fire[i].r < fire[i].maxr)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}

			if (fire[i].r >= fire[i].maxr - 1)
			{
				fire[i].draw = false;
				Init(i);
			}
			fire[i].t1 = fire[i].t2;
		}

		//
		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a));

				if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;   //blue
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;   //green
					int r = fire[i].xy[x1][y1] >> 16;   //red

					int xx = (int)(fire[i].x + fire[i].r * cos(a));
					int yy = (int)(fire[i].y - fire[i].r * sin(a));


					if (r > 0x20 && g > 0x20 && b > 0x20 && xx < 1200 && xx>0 && yy > 0 && yy < 600)
					{
						pmem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
					}

				}
			}
			fire[i].draw = false;
		}
	}
}


void Style(DWORD& st1)
{
	//DWORD st2 = timeGetTime();
	//if (st2 - st1 > 5000)  //18s

	ExMessage msg;
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			int count = rand() % NUM;
			jet[count].x = msg.x;
			jet[count].y = msg.y;
			jet[count].hx = jet[count].x;
			jet[count].hy = msg.y;

			jet[count].height = jet[count].y - jet[count].hy;
			jet[count].shoot = true;
			jet[count].dt = 0;
			putimage(jet[count].x, jet[count].y, &jet[count].img[jet[count].n], SRCINVERT);

			fire[count].x = jet[count].x + 10;
			fire[count].y = jet[count].hy;
			fire[count].show = false;
			fire[count].r = 0;
		}
		else if (msg.message == WM_MOUSEMOVE) {
			int count = rand() % NUM;
			if (msg.x % 3 == 0 || msg.y % 3 == 0) {
				jet[count].x = msg.x;
				jet[count].y = msg.y;
				jet[count].hx = jet[count].x;
				jet[count].hy = msg.y / 2;

				jet[count].height = jet[count].y - jet[count].hy;
				jet[count].shoot = true;
				jet[count].dt = 0;
				putimage(jet[count].x, jet[count].y, &jet[count].img[jet[count].n], SRCINVERT);

				fire[count].x = jet[count].x + 10;
				fire[count].y = jet[count].hy;
				fire[count].show = false;
				fire[count].r = 0;
			}
		}
	}
}
void starTime() {
	for (int i = 0; i < N; i++) {
		star[i].x = rand() % 1200 + 1;
		star[i].y = rand() % 600 + 1;
		star[i].color = (int)((255 * 600 - star[i].y * 255) / 6.0 + 0.5);
		star[i].color = RGB(star[i].color, star[i].color, star[i].color);
	}

	for (int i = 0; i < N; i++) {
		Sleep(13);
		putpixel((int)star[i].x, star[i].y, star[i].color);
	}
}