#include<stdio.h>
#include<math.h>

int main(){
	int n,i;
	printf("���������ݸ���:\n");
	scanf("%d",&n);
	float a[n],sum1=0,average,sum2=0,uA,ins,k,uB,uC;
	printf("����������(�޵�λ):\n");
	for(i=0;i<n;i++){
		scanf("%f",&a[i]);
		sum1=sum1+a[i];
	}
	average=sum1/n;
	if(n>1){
		for(i=0;i<n;i++)
			sum2=sum2+(a[i]-average)*(a[i]-average);
		uA=sqrt(sum2/(n*(n-1)));
	}
	else uA=0;
	printf("��������������(�޵�λ):\n");
	scanf("%f",&ins);
	printf("��������������(С����ʽ,����3=1.7320508):\n");
	scanf("%f",&k);
	uB=ins/k;
	uC=sqrt(uA*uA+uB*uB);
	printf("ƽ��ֵΪ%f\n",average);
	printf("A�಻ȷ����Ϊ%f\n",uA);
	printf("B�಻ȷ����Ϊ%f\n",uB);
	printf("C�಻ȷ����Ϊ%f\n",uC);
	printf("��׼��Բ�ȷ����Ϊ%%%f\n",uC/average*100);
	return(0);
}
