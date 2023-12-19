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
	float myIntensity;        //����ǿ��
	int myID;                 //ѧ��
	int Design;				//��Ʒ���
	int WinFunc;			//������ѡ��
	float fs;                //����Ƶ��
	float fc1;				//�ز�Ƶ��1
	float fc2;				//�ز�Ƶ��2
	float lFc;				//��ͨ�˲�����ֹƵ��
	float bFc1;				//��ͨ�˲����½�ֹƵ��
	float bFc2;           //��ͨ�˲����Ͻ�ֹƵ��
	float bFc3;
	float bFc4;
	float HbR[N];	        //Ƶ��ʵ��
	float HbI[N];	       //Ƶ���鲿

	int S0[16];			//���������Basesignal�����ж�������Ϣ�������źš�
	int S1[16];			//���������Adjust�����ж��źų���ȡƽ������źš�
	float Mod[16 * M];	//����������ɵ��ز��źš�
	float Sa[16 * M];		//�������ͨ��ϵͳ��ÿһ�����ں���źš�1
	float Sal[16 * M];	  //��������� Basesignal�������źŽ��в�������źš�2
	float Sa2[16 * M];    //�������ͨ��ϵͳ��ÿһ�����ں���ź� FSK�������ݴ�����·
	float Sa_Fc1[16 * M]; //������ŵ�һ��·�ź�
	float Sa_Fc2[16 * M]; //������ŵڶ���·�ź�
	//float Chann[16 * M];	//������Ž��ն��ź�
	float Hl[16 * M];        //����������ɵĵ�ͨ�˲����ĵ�λȡ����Ӧ��4
	float H2[N];//���IDFT�������
	float Hb[N];			//��Ŵ�ͨƵ������
	float AR[16 * M];		//���������Dft�����жԴ�����������DFT������ʵ����6
	float AI[16 * M];		//���������Dft�����жԴ�����������DFT�������鲿��7
	float A[16 * M];		//���������Dft�����жԴ�����������DFT������Ƶ���ֵ��8
	float No[16 * M];		//����������ɵ�����9
	float Wn[N];			//��Ŵ�����
	float Hd[N];			//���봰
	float Hd2[N];			//���봰
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
	int GetFs(void);//����Ƶ��
	float GetnLpfc(void);//��ͨ��ֹƵ��
	float GetnBpfc1(void);//��ͨ1��Χ
	float GetnBpfc2(void);
	float GetnBpfc3(void);//��ͨ2��Χ
	float GetnBpfc4(void);
	float GetFc1(void);//�ز�1
	float GetFc2(void);//�ز�2
	float  GetmyIntensity();//����
	float* GetSaFc1(void);//�ز�1
	float* GetSaFc2(void);//�ز�2
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