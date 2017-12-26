//�����(width*height)����Ԫ
//�м��1/2*(width*height)����Ԫ
//�����1����Ԫ
//һ��3/2(width*height)+1����Ԫ
//һ��(1 / 2)*width*height*width*height+(1 / 2)*width*height��Ȩֵ
#include <cstring>
#include <ctime>
#include <cstdlib>

#ifndef MAX_BOARD
#define MAX_BOARD 100
#endif // !MAX_BOARD


extern int width, height;//����ȫ�ֱ�������
extern int board[MAX_BOARD][MAX_BOARD];//����ȫ�ֱ�������״̬

//��Ԫ����[width*height]+(1/2)*width*height+1
int *neure= new int[(3/2)*width*height+1];
//Ȩֵ����[width*height][(1/2)*width*height]+(1/2)*width*height
int *weight = new int[(1 / 2)*width*height*width*height + (1 / 2)*width*height];


//��������¿�ʹ�����·�ʽ����������
////��Ԫ����[width*height]+(1/2)*width*height+1
//int *neure = new int[(int)((3.0 / 2)*MAX_BOARD*MAX_BOARD + 1)];
////Ȩֵ����[width*height][(1/2)*width*height]+(1/2)*width*height
//int *weight = new int[(int)((1.0 / 2)*MAX_BOARD*MAX_BOARD*MAX_BOARD*MAX_BOARD + (1.0 / 2)*MAX_BOARD*MAX_BOARD)];


void init_ANN(){//��ʼ��ANN���������Ȩֵ��������Ԫ��ֵ���м估�����Ԫ��0

	//��ʼ��ǰwidth*height����ԪֵΪ����״̬
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			neure[i*height + j] = board[i][j];
		}
	}

	memset(&(neure[width*height]), 0, sizeof(int)*((int)((1.0 / 2)*width*height + 1)));
	srand((unsigned)time(NULL));
	for (int i = 0; i < (int)((1.0 / 2)*width*height*width*height + (1.0 / 2)*width*height); i++){
		weight[i] = rand();
	}
}

void Update_ANN(){//����Ȩֵ�����м䣬�����Ԫֵ
	//���Ϻ���=��Ȩ���g(x)=sum(wi*ai)
	//�����=���Ժ���f(x)=x
	for (int i = 0; i < (int)((1.0 / 2)*width*height); i++){//�����м����Ԫֵ
		//neure[width*height+i]=sum(wi*ai)
		for (int j = 0; j < width*height; j++){
			//ÿһ��������ԪJ*���ϵ��м���ԪI��Ȩ��
			neure[width*height + i] += neure[j] * weight[(int)(j*(1.0 / 2)*width*height + i)];
		}
	}
	for (int i = 0; i <= (int)((1.0 / 2)*width*height); i++){//�����������Ԫֵ
		//neure[(3/2)*width*height]=sum(wi*ai)
		neure[(int)((3.0 / 2)*width*height)] += neure[width*height + i] * weight[(int)((1.0 / 2)*width*height*width*height + i)];
	}
}