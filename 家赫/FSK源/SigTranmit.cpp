#include "framework.h"
#include "pch.h"
#include "FSK.h"
#include "SigTranmit.h"
#include <random>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


SigTranmit::SigTranmit()
{
	myID = 1111;
	myIntensity = 1;
	fs = 8000.0;
	fc1 = 1000.0;
	fc2 = 2000.0;
	lFc = 400;
	bFc1 = 600;
	bFc2 = 1400;
	bFc3 = 1600;
	bFc4 = 2400;
}


SigTranmit::~SigTranmit()
{

}

//
void SigTranmit::Basesignal(int myID)
{
	int b[4];
	int d[4][4];
	int cnt = 0;//计数使用，用来给16位二进制数计数
	b[0] = myID / 1000;//学号第一位
	b[1] = (myID % 1000) / 100;//学号的第二位
	b[2] = (myID % 100) / 10;//学号的第三位
	b[3] = myID - b[0] * 1000 - b[1] * 100 - b[2] * 10;//学号的最后一位
	for(int i = 0; i < 4; i++)
	{
		switch (b[i])//转换为二进制
		{
		case 0:d[i][0] = 0; d[i][1] = 0; d[i][2] = 0; d[i][3] = 0; break;
		case 1:d[i][0] = 0; d[i][1] = 0; d[i][2] = 0; d[i][3] = 1; break;
		case 2:d[i][0] = 0; d[i][1] = 0; d[i][2] = 1; d[i][3] = 0; break;
		case 3:d[i][0] = 0; d[i][1] = 0; d[i][2] = 1; d[i][3] = 1; break;
		case 4:d[i][0] = 0; d[i][1] = 1; d[i][2] = 0; d[i][3] = 0; break;
		case 5:d[i][0] = 0; d[i][1] = 1; d[i][2] = 0; d[i][3] = 1; break;
		case 6:d[i][0] = 0; d[i][1] = 1; d[i][2] = 1; d[i][3] = 0; break;
		case 7:d[i][0] = 0; d[i][1] = 1; d[i][2] = 1; d[i][3] = 1; break;
		case 8:d[i][0] = 1; d[i][1] = 0; d[i][2] = 0; d[i][3] = 0; break;
		case 9:d[i][0] = 1; d[i][1] = 0; d[i][2] = 0; d[i][3] = 1; break;
		}
		for (int j = 0; j < 4; j++)
		{
			S0[cnt] = d[i][j];//将四行四列的值按行依次取出存储在16位的数组中
			cnt++;
		}
	}
	for (int j = 0; j < 16; j++)			//Sal[16*M]为采样序列M=40   输入信号的码元是200Hz,采样频率是8000Hz
	{
		for (int k = 0; k < M; k++)
		{
			Sal[k + j * M] = (float)S0[j];
			Sa[k + j * M] = (float)S0[j];
		}
	}

}

//第二路信号为第一路互补
void SigTranmit::Convert(void)
{
	for (int i = 0; i < 16 * M; i++)
	{
		if (Sa[i] > 0)Sa2[i] = 0;
		else Sa2[i] = 1;
	}
}

//公式幅频特性
void SigTranmit::Dft(float x[], int m)
{
	for (int i = 0; i < m; i++)
	{
		AR[i] = 0.0;
		AI[i] = 0.0;
		for (int j = 0; j < m; j++)
		{
			AR[i] = AR[i] + x[j] * (float)cos(-2.0 * PI * i * j / m);
			AI[i] = AI[i] + x[j] * (float)sin(-2.0 * PI * i * j / m);
		}
		A[i] = (float)(sqrt(pow(AR[i], 2) + pow(AI[i], 2)));
	}
}


void SigTranmit::Idft(float hR[], float hI[])
{
	int i, j;
	float real = 0.0;
	float image = 0.0;
	float H2r[N];
	float H2i[N];
	for (i = 0; i < N; i++)
	{
		real = 0.0;
		image = 0.0;
		for (j = 0; j < N; j++)
		{
			real = real + hR[j] * (float)cos(2 * PI * i * j / N) - hI[j] * (float)sin(2 * PI * i * j / N);
			image = image + hR[j] * (float)sin(2 * PI * i * j / N) + hI[j] * (float)cos(2 * PI * i * j / N);
		}
		H2r[i] = (float)real / N;
		H2i[i] = (float)image / N;
	}
	for (i = 0; i < N; i++)
	{
		H2[i] = H2r[i];
	}
}


void SigTranmit::Lpf()
{
	if (Design == FILTER_SAMPLE)
	{
		Lpf_sample();
	}
	else if (Design == FILTER_WIN)
	{
		Lpf_win();
	}
}


void SigTranmit::Lpf_sample()//低通滤波器，频率采样法
{
	int i;                                      //频率采样法N=127
	float temp = N;
	float HbR[N];	//频域实部
	float HbI[N];	//频域虚部
	for (i = 0; i < (temp + 1) / 2; i++)
	{
		if (fs * i / N >= 0 && fs * i / N < lFc)
		{
			Hb[i] = 1.0; Hb[N - i - 1] = 1.0;
		}
		else
		{
			Hb[i] = 0.0; Hb[N - i - 1] = 0.0;
		}
	}
	for (i = 0; i < N / 2; i++)//使得频率曲线平滑
	{
		if (Hb[i] == 1 && Hb[i + 1] == 0)
		{
			Hb[i + 1] = 0.5; Hb[N - i - 1] = 0.5;
		}
		else if (Hb[i] == 0 && Hb[i + 1] == 1)
		{
			Hb[i] = 0.5; Hb[N - i] = 0.5;
		}
	}
	for (i = 0; i < N; i++)
	{
		HbR[i] = Hb[i] * (float)cos((temp - 1) / temp * PI * i);
		HbI[i] = Hb[i] * (float)sin(-(temp - 1) / temp * PI * i);
	}
	Idft(HbR, HbI);
	for (i = 0; i < N; i++)
	{
		Hl[i] = H2[i];
	}
}


void SigTranmit::Lpf_win()
{
	int i;
	switch (WinFunc)
	{
	case 0: JXC(N); break;
	case 1: HNC(N); break;
	case 2: HMC(N); break;
	case 3: BLKMC(N); break;
	}
	LHDN();
	for (i = 0; i < N; i++)
	{
		Hl[i] = Hd[i] * Wn[i];						//加窗
	}
	Dft(Hl, N);
	for (i = 0; i < N; i++)
	{
		Hb[i] = A[i];
	}
}


void SigTranmit::Conv(float array1[], float array2[], float *Sa)
{
	int i, j, length = 16 * M + N;
	float b1[16 * M + N];
	for (i = 0; i < length; i++)
	{
		b1[i] = 0.0;
		for (j = 0; j < N; j++)
		{
			if (((i - j) < 0) || ((i - j) > 16 * M))
				b1[i] += 0.0;
			else
				b1[i] += array2[j] * array1[i - j];
		}
	}
	for (i = 0; i < 16 * M; i++)//这里卷积后长度应该为16*M+N-1，但这里为了后续方便调用，取中间长度为16*M的序列
		Sa[i] = b1[i + (N - 1) / 2];
}


void SigTranmit::modulate(int freq, int flag)
{
	for (int i = 0; i < 16 * M; i++)
	{
		if (flag == 1)
			Sa[i] = (float)(Sa[i] * cos(2 * PI * freq * i / fs));
		else if(flag==2)
			Sa2[i] = (float)(Sa2[i] * cos(2 * PI * freq * i / fs));
	}
}


void SigTranmit::Channel(void)
{
	Noise(myIntensity);
	for (int i = 0; i < 16 * M; i++)
	{
		Sa[i] = Sa[i] + No[i];
	}
}

void SigTranmit::ASK(int flag)
{
	for (int i = 0; i < 16 * M; i++)
	{
		Sa[i] = Sa[i];
	}
}
void SigTranmit::FSK(int flag)
{
	for (int i = 0; i < 16 * M; i++)
	{
		Sa[i] = Sa[i] + Sa2[i];
	}
}

void SigTranmit::PSK(int flag)
{
	for (int i = 0; i < 16 * M; i++)
	{
		Sa[i] = Sa[i]- Sa2[i];
	}
}

//float inten
void SigTranmit::Noise(double Sq)
{
	//awgn(inten, 16 * M, No);
	int  k;
	const float mean = 0.0;//均值
	const float stddev = 0.1;//标准差
	default_random_engine generator;
	normal_distribution<float> dist(mean, stddev);
	for (k = 0; k < 16 * M; k++)
	{
		No[k] = sqrt((1 / Sq)) * dist(generator);
	}
	Dft(No, 16 * M);
}


void SigTranmit::awgn(float db, int length, float* n)
{


	float  pdf[10000] = { 0 };
	//int interleaver[16 * M];
	//int flag[16 * M];
	//for (int i = 0; i < 16 * M; i++)
	//	flag[i] = 0;
	//srand((unsigned int)time(0));
	//for (int i = 0; i < 16 * M; i++)
	//{
	//	int tmp = rand() % (16 * M);
	//	while (flag[tmp] == 1)
	//	{
	//		tmp = rand() % (16 * M);
	//	}
	//	interleaver[i] = tmp;
	//	flag[tmp] = 1;
	//}
	//float* amp;
	//float  delta = 0, amplitude = 0, sum = 0, temp1 = 0, temp2 = 0;
	//int* num;
	//int counter, counter1, counter2, counter3;
	//int half_length;
	//delta = 1 / (2 * pow(10, 0.1 * db));                     // 计算噪声功率
	//counter = 0;                                            // 通过概率密度计算幅度集合和对应的概率密度
	//while (sum < (0.5 / Stride))
	//{
	//	pdf[counter] = 1 / sqrt(2 * PI * delta) * exp(-0.5 * pow(amplitude, 2) / delta);
	//	sum += pdf[counter];
	//	amplitude += Stride;
	//	counter++;
	//}                                                      // 最后得到的counter是幅度集合的长度
	//num = (int*)calloc(counter, sizeof(int));              // num每个幅度在序列中出现的次数,幅度放在amp中
	//amp = (float*)calloc(counter, sizeof(float));
	//amplitude = 0;
	//sum = 0;
	//temp1 = length * Stride;
	//temp2 = 0;
	//for (counter1 = 0; counter1 < counter; counter1++)
	//{
	//	temp2 = temp1 * pdf[counter1];
	//	if ((int)(temp2 + 0.5) > (int)temp2)
	//		*(num + counter1) = (int)(temp2 + 1);
	//	else
	//		*(num + counter1) = (int)temp2;
	//	sum += *(num + counter1);
	//	*(amp + counter1) = amplitude;
	//	amplitude += Stride;
	//}
	//temp1 = 0;
	//half_length = length >> 1;
	//if (sum < half_length)                                     // 使num的和恰好是length的一半
	//{
	//	temp1 = half_length - sum;
	//	for (counter1 = 0; counter1 < temp1; counter1++)
	//		(*(num + counter - 1 - counter1))++;
	//}
	//else if (sum > half_length)
	//{
	//	temp1 = sum - half_length;
	//	*num -= temp1;
	//}
	//counter3 = 0;
	//for (counter1 = 0; counter1 < counter; counter1++)             // 往*n里填入幅度值
	//{
	//	for (counter2 = 0; counter2 < *(num + counter1); counter2++)
	//	{
	//		*(n + counter3) = *(amp + counter1);
	//		*(n + length - 1 - counter3) = -*(amp + counter1);
	//		counter3++;
	//	}
	//}
	//for (counter1 = 0; counter1 < length; counter1++)
	//{
	//	temp1 = *(n + counter1);
	//	*(n + counter1) = *(n + interleaver[counter1]);
	//	*(n + interleaver[counter1]) = temp1;
	//	for (counter2 = 0; counter2 < length - counter1 - 1; counter2++)
	//		if (interleaver[counter1 + counter2 + 1] == counter1)
	//			interleaver[counter1 + counter2 + 1] = interleaver[counter1];
	//}

}



//低通理想窗
void SigTranmit::LHDN()
{
	int i;
	float a = (N - 1) / 2;
	for (i = 0; i < N; i++)
	{
		if (i == a) Hd[i] = (float)2 * lFc / fs;
		else Hd[i] = (float)sin((2 * PI * lFc / fs) * (i - a)) / (float)(PI * (i - a));
	}
}



//带通理想窗
void SigTranmit::BHDN(float f1, float f2)
{
	int i;
	float a = (N - 1) / 2;
	for (i = 0; i < N; i++)
	{
		if (i == a) Hd[i] = (float)2 * f2 / fs - 2 * f1 / fs;
		else Hd[i] = (float)sin((2 * PI * f2 / fs) * (i - a)) / (float)(PI * (i - a)) - (float)sin((2 * PI * f1 / fs) * (i - a)) / (float)(PI * (i - a));
	}
}


//各个窗函数
void SigTranmit::JXC(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (i < N) Wn[i] = 1.0;
		else Wn[i] = 0.0;
	}
}

void SigTranmit::HNC(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (i < N) Wn[i] = float(0.5 * (1.0 - cos(2.0 * PI * i / (N - 1))));
		else Wn[i] = 0.0;
	}
}

void SigTranmit::HMC(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (i < N) Wn[i] = float(0.54 - 0.46 * cos(2.0 * PI * i / (N - 1)));
		else Wn[i] = 0.0;
	}
}

void SigTranmit::BLKMC(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (i < N) Wn[i] = float(0.42 - 0.5 * cos(2.0 * PI * i / (N - 1)) + 0.08 * cos(4.0 * PI * i / (N - 1)));
		else Wn[i] = 0.0;
	}
}



void SigTranmit::Bpf(int choose)
{
	if (Design == FILTER_SAMPLE)
	{
		Bpf_sample(choose);
	}
	else if (Design == FILTER_WIN)
	{
		Bpf_win(choose);
	}
}


void SigTranmit::Bpf_sample(int choose)
{
	float f1, f2;
	int i;                                  //频率采样法
	float temp = N;
	float HbR[N];	//频域实部
	float HbI[N];	//频域虚部
	switch (choose)
	{
	case 1: 
		{f1 = bFc1;f2 = bFc2;}break;
	case 2: 
		{f1 = bFc3;f2 = bFc4;}break;
	default:
		break;
	}
	for (i = 0; i < (temp + 1) / 2; i++)
	{
		if (fs * i / N > f1 && fs * i / N < f2)
		{
			Hb[i] = 1.0; Hb[N - i - 1] = 1.0;
		}
		else
		{
			Hb[i] = 0.0; Hb[N - i - 1] = 0.0;
		}
	}
	for (i = 0; i < N / 2; i++)
	{
		if (Hb[i] == 1 && Hb[i + 1] == 0)
		{
			Hb[i + 1] = 0.5; Hb[N - i - 1] = 0.5;
		}
		else if (Hb[i] == 0 && Hb[i + 1] == 1)
		{
			Hb[i] = 0.5; Hb[N - i] = 0.5;
		}
	}
	for (i = 0; i < N; i++)
	{
		HbR[i] = Hb[i] * (float)cos((temp - 1) / temp * PI * i);
		HbI[i] = Hb[i] * (float)sin(-(temp - 1) / temp * PI * i);
	}
	Idft(HbR, HbI);
}


void SigTranmit::Bpf_win(int choose)
{
	int i;
	float f1, f2;
	switch (choose)
	{
	case 1:
	{f1 = bFc1; f2 = bFc2; }break;
	case 2:
	{f1 = bFc3; f2 = bFc4; }break;
	default:
		break;
	}
	switch (WinFunc)
	{
	case 0: JXC(N); break;
	case 1: HNC(N); break;
	case 2: HMC(N); break;
	case 3: BLKMC(N); break;
	}
	BHDN(f1,f2);
	for (i = 0; i < N; i++)
	{
		H2[i] = Hd[i] * Wn[i];
	}
	Dft(H2, N);
	for (i = 0; i < N; i++)
	{
		Hb[i] = A[i];
	}
}


void SigTranmit::Demodulate(int freq, int flag)
{
	for (int i = 0; i < 16 * M; i++)
	{
		if (flag == 1) Sa_Fc1[i] = (float)(Sa_Fc1[i] * cos(2 * PI * freq * i / fs));
		else if (flag == 2) Sa_Fc2[i] = (float)(Sa_Fc2[i] * cos(2 * PI * freq * i / fs));
		
	}
}

void SigTranmit::ASKSigRecover(void)
{
	int count = 0;
	for (int i = 0; i < 16; i++)
	{
		count = 0;
		for (int j = 0; j < M; j++)
		{
			if (Sa_Fc1[j + M * i] >= 0.5)
			{
				count++;
			}
			else count = count;
		}
		for (int k = 0; k < M; k++)
		{
			if (count >= 5)
			{
				Sa[k + M * i] = 1;
			}
			else Sa[k + M * i] = 0;
		}
	}
}
void SigTranmit::PSKSigRecover(void)
{
	float average_fc1 = 0.0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < M; j++)
		{
			average_fc1 += Sa_Fc1[j + M * i];
		}
		average_fc1 /= M;
		for (int k = 0; k < M; k++)
		{
			if (average_fc1 >= 0)
			{
				Sa[k + i * M] = 1;
			}
			else Sa[k + i * M] = 0;
		}
	}
}
void SigTranmit::FSKSigRecover(void)
{
	float average_fc1 = 0.0, average_fc2 = 0.0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < M; j++)
		{
			average_fc1 += Sa_Fc1[j + M * i];
			average_fc2 += Sa_Fc2[j + M * i];
		}
		average_fc1 /= M;
		average_fc2 /= M;
		for (int k = 0; k < M; k++)
		{
			if (average_fc1 > average_fc2)
			{
				Sa[k + i * M] = 1;
			}
			else Sa[k + i * M] = 0;
		}
	}
}


void SigTranmit::SetID(int ID)
{
	myID = ID;
}


void SigTranmit::SetIntensity(float Intensity)
{
	myIntensity = Intensity;
}


void SigTranmit::SetLFc(float myLFc)
{
	lFc = myLFc;
}


void SigTranmit::SetBFc1(float myBFc1)
{
	bFc1 = myBFc1;
}


void SigTranmit::SetBFc2(float myBFc2)
{
	bFc2 = myBFc2;
}


void SigTranmit::SetBFc3(float myBFc3)
{
	bFc3 = myBFc3;
}


void SigTranmit::SetBFc4(float myBFc4)
{
	bFc4 = myBFc4;
}


void SigTranmit::SetFs(float myFs)
{
	fs = myFs;
}


void SigTranmit::SetFc1(float myFc)
{
	fc1 = myFc;
}


void SigTranmit::SetFc2(float myFc)
{
	fc2 = myFc;
}


void SigTranmit::SetDesign(int myDesign)
{
	Design = myDesign;
}


void SigTranmit::SetWin(int MyWin)
{
	WinFunc = MyWin;
}


int SigTranmit::GetmyID(void)
{
	return myID;
}


int SigTranmit::GetFs(void)
{
	return fs;
}


float SigTranmit::GetnLpfc(void)
{
	return lFc;
}


float SigTranmit::GetnBpfc1(void)
{
	return bFc1;
}


float SigTranmit::GetnBpfc2(void)
{
	return bFc2;
}


float SigTranmit::GetnBpfc3(void)
{
	return bFc3;
}


float SigTranmit::GetnBpfc4(void)
{
	return bFc4;
}


float SigTranmit::GetFc1(void)
{
	return fc1;
}


float SigTranmit::GetFc2(void)
{
	return fc2;
}


float SigTranmit::GetmyIntensity()
{
	return myIntensity;
}


float* SigTranmit::GetSa()
{
	return Sa;
}


float* SigTranmit::GetA()
{
	return A;
}


float* SigTranmit::GetHl()
{
	return Hl;
}


float* SigTranmit::GetH2()
{
	return H2;
}


float* SigTranmit::GetHb()
{
	return Hb;
}


float* SigTranmit::GetNo()
{
	return No;
}


float* SigTranmit::GetSal()
{
	return Sal;
}


float* SigTranmit::GetSa2()
{
	return Sa2;
}

float* SigTranmit::GetSaFc1(void)//载波1
{
	return Sa_Fc1;
}


float* SigTranmit::GetSaFc2(void)//载波2
{
	return Sa_Fc2;
}
//float* SigTranmit::GetChann()
//{
//	
//}

