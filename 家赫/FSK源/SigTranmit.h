#if !defined(AFX_SIGTRANMIT_H)
#define AFX_SIGTRANMIT_H

#if _MSC_VER > 1600
#pragma once
#endif // _MSC_VER > 1600
#include <math.h>
#define M 40
#define N 127
#define PI 3.1415926
#define Stride 0.005
#define FILTER_SAMPLE	1
#define FILTER_WIN	2
#define WIN_JXC	0
#define WIN_HNC	1
#define WIN_HMC	2
#define WIN_BLKMC	3
class SigTranmit
{
private:
	float myIntensity;        //噪声强度
	int myID;                 //学号
	int Design;				//设计方法
	int WinFunc;			//窗函数选择
	float fs;                //抽样频率
	float fc1;				//载波频率1
	float fc2;				//载波频率2
	float lFc;				//低通滤波器截止频率
	float bFc1;				//带通滤波器下截止频率
	float bFc2;           //带通滤波器上截止频率
	float bFc3;
	float bFc4;
	float HbR[N];	        //频域实部
	float HbI[N];	       //频域虚部

	int S0[16];			//用来存放在Basesignal函数中对数字信息编码后的信号。
	int S1[16];			//用来存放在Adjust函数中对信号抽样取平均后的信号。
	float Mod[16 * M];	//用来存放生成的载波信号。
	float Sa[16 * M];		//用来存放通过系统中每一个环节后的信号。1
	float Sal[16 * M];	  //用来存放在 Basesignal函数对信号进行采样后的信号。2
	float Sa2[16 * M];    //用来存放通过系统中每一个环节后的信号 FSK两条数据处理线路
	float Sa_Fc1[16 * M]; //用来存放第一条路信号
	float Sa_Fc2[16 * M]; //用来存放第二条路信号
	//float Chann[16 * M];	//用来存放接收端信号
	float Hl[16 * M];        //用来存放生成的低通滤波器的单位取样响应。4
	float H2[N];//存放IDFT后的数据
	float Hb[N];			//存放带通频域数据
	float AR[16 * M];		//用来存放在Dft函数中对传入的数组进行DFT运算后的实部。6
	float AI[16 * M];		//用来存放在Dft函数中对传入的数组进行DFT运算后的虚部。7
	float A[16 * M];		//用来存放在Dft函数中对传入的数组进行DFT运算后的频域幅值。8
	float No[16 * M];		//用来存放生成的噪声9
	float Wn[N];			//存放窗函数
	float Hd[N];			//理想窗
	float Hd2[N];			//理想窗
public:
	SigTranmit();
	virtual ~SigTranmit();
	void SetID(int ID);
	void SetIntensity(float Intensity);
	void SetLFc(float myLFc);
	void SetBFc2(float myBFc2);
	void SetBFc1(float myBFc1);
	void SetBFc3(float myBFc3);
	void SetBFc4(float myBFc4);
	void SetFs(float myFs);
	void SetFc1(float myFc);
	void SetFc2(float myFc);
	void SetDesign(int myDesign);
	void SetWin(int MyWin);
	void Basesignal(int myID);
	void Lpf();
	void Lpf_sample();
	void Lpf_win();
	void modulate(int freq, int flag);
	void Channel(void);
	void Bpf(int choose);
	void Bpf_sample(int choose);
	void Bpf_win(int choose);
	void Demodulate(int freq, int flag);
	void PSKSigRecover(void);
	void FSKSigRecover(void);
	void ASKSigRecover(void);
	void Dft(float x[], int m);
	void Idft(float hR[], float hI[]);
	void Conv(float array1[], float array2[], float* Sa);
	void Convert(void);
	void ASK(int flag);
	void FSK(int flag);
	void PSK(int flag);
	void Noise(double Sq);
	void awgn(float db, int length, float* n);
	void LHDN();
	void BHDN(float f1, float f2);
	void JXC(int n);
	void HNC(int n);
	void HMC(int n);
	void BLKMC(int n);
	int GetmyID(void);
	int GetFs(void);//采样频率
	float GetnLpfc(void);//低通截止频率
	float GetnBpfc1(void);//带通1范围
	float GetnBpfc2(void);
	float GetnBpfc3(void);//带通2范围
	float GetnBpfc4(void);
	float GetFc1(void);//载波1
	float GetFc2(void);//载波2
	float  GetmyIntensity();//噪声
	float* GetSaFc1(void);//载波1
	float* GetSaFc2(void);//载波2
	float* GetSa();
	float* GetA();
	float* GetHl();
	float* GetH2();
	float* GetHb();
	float* GetNo();
	float* GetSal();
	float* GetSa2();
	float findmax(float x[], int m);
	void Draw_graph(float S[], float Fre[]);
	void Draw_graph_filter(float S[], float Fre[]);
	//float* GetChann();
};
#endif 