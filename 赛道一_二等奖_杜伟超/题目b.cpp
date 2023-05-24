#include<stdio.h>
#include<math.h>

int main(){
	int n,i;
	printf("请输入数据个数:\n");
	scanf("%d",&n);
	float a[n],sum1=0,average,sum2=0,uA,ins,k,uB,uC;
	printf("请输入数据(无单位):\n");
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
	printf("请输入允许误差极限(无单位):\n");
	scanf("%f",&ins);
	printf("请输入置信因子(小数形式,根号3=1.7320508):\n");
	scanf("%f",&k);
	uB=ins/k;
	uC=sqrt(uA*uA+uB*uB);
	printf("平均值为%f\n",average);
	printf("A类不确定度为%f\n",uA);
	printf("B类不确定度为%f\n",uB);
	printf("C类不确定度为%f\n",uC);
	printf("标准相对不确定度为%%%f\n",uC/average*100);
	return(0);
}
