//�����(width*height)����Ԫ
//�м��1/2*(width*height)����Ԫ
//�����1����Ԫ
//һ��3/2(width*height)+1����Ԫ
//һ��(1 / 2)*width*height*width*height+(1 / 2)*width*height��Ȩֵ
#ifndef MAX_BOARD
#define MAX_BOARD 100
#endif // !MAX_BOARD
#define debug 1

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;
int width, height;//����ȫ�ֱ�������
int board[MAX_BOARD][MAX_BOARD];//����ȫ�ֱ�������״̬

//��Ԫ����[width*height]+(1/2)*width*height+1
int *neure = new int[(int)((3.0/ 2)*MAX_BOARD*MAX_BOARD + 1)];
//Ȩֵ����[width*height][(1/2)*width*height]+(1/2)*width*height
int *weight = new int[(int)((1.0/ 2)*MAX_BOARD*MAX_BOARD*MAX_BOARD*MAX_BOARD + (1.0/ 2)*MAX_BOARD*MAX_BOARD)];

void init_ANN();
void Update_ANN();

int main(){
	cin >> width >> height;

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			cin >> board[j][i];
		}
	}
	init_ANN();
	Update_ANN();
	
	cout << "��Ԫֵ��" << endl;
	for (int i = 0; i <(int)((1.0/ 2)*width*height); i++){//�����������Ԫֵ
		//neure[(3/2)*width*height]=sum(wi*ai)
		cout << neure[width*height + i] << " ";
		cout << endl;
	}
	cout << neure[(int)((3.0/ 2)*width*height)]<<endl;

	cout << "Ȩֵ��" << endl;
	for (int i = 0; i < width*height; i++){
		for (int j = 0; j < (int)((1.0/ 2)*width*height); j++){
			cout<<weight[(int)(i*(1.0/ 2)*width*height + j)]<<" ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i <= int((1.0/ 2)*width*height); i++){
		cout << weight[(int)((1.0/ 2)*width*height*width*height + i)] << " ";
	}
	cout << endl;
}

//
////��Ԫ����[width*height]+(1/2)*width*height+1
//int *neure = new int[(3 / 2)*width*height + 1];
////Ȩֵ����[width*height][(1/2)*width*height]+(1/2)*width*height
//int *weight = new int[(1 / 2)*width*height*width*height + (1 / 2)*width*height];

void init_ANN(){//��ʼ��

	//��ʼ��ǰwidth*height����ԪֵΪ����״̬
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			neure[i*height + j] = board[i][j];
		}
	}

	memset(&(neure[width*height]), 0, sizeof(int)*((int)((1.0/ 2)*width*height + 1)));
	srand((unsigned)time(NULL));
	for (int i = 0; i < (int)((1.0/ 2)*width*height*width*height + (1.0/ 2)*width*height); i++){
		weight[i] = rand();
	}
}

void Update_ANN(){
	//���Ϻ���=��Ȩ���g(x)=sum(wi*ai)
	//�����=���Ժ���f(x)=x
	for (int i = 0; i < (int)((1.0/ 2)*width*height); i++){//�����м����Ԫֵ
		//neure[width*height+i]=sum(wi*ai)
		for (int j = 0; j < width*height; j++){
			//ÿһ��������ԪJ*���ϵ��м���ԪI��Ȩ��
			neure[width*height + i] += neure[j] * weight[(int)(j*(1.0/ 2)*width*height + i)];
		}
	}
	for (int i = 0; i <= (int)((1.0/ 2)*width*height); i++){//�����������Ԫֵ
		//neure[(3/2)*width*height]=sum(wi*ai)
		neure[(int)((3.0/ 2)*width*height)] += neure[width*height + i] * weight[(int)((1.0/ 2)*width*height*width*height + i)];
	}
}