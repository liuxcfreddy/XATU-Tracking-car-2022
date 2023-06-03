#include "Kalman.h"


/*
 * @detection:
		 * Q值为过程噪声，越小系统越容易收敛，我们对模型预测的值信任度越高；
		 * 但是太小则容易发散，如果Q为零，那么我们只相信预测值；
		 * Q值越大我们对于预测的信任度就越低，而对测量值的信任度就变高；
		 * 如果Q值无穷大，那么我们只信任测量值；
		 *
		 * R值为测量噪声，太小太大都不一定合适。
		 * R太大，卡尔曼滤波响应会变慢，因为它对新测量的值的信任度降低；
		 * 越小系统收敛越快，但过小则容易出现震荡；
		 * R值的改变主要是影响卡尔曼的收敛速度。
		 *
		 * 调节方法：
		 * 测试时可以先将Q从小往大调整，将R从大往小调整；先固定一个值去调整另外一个值，看收敛速度与波形输出。
		 * 系统中还有一个关键值P，它是误差协方差初始值，表示我们对当前预测状态的信任度，它越小说明我们越相信当前预测状态；
		 * 它的值决定了初始收敛速度，一般开始设一个较小的值以便于获取较快的收敛速度。
		 * 随着卡尔曼滤波的迭代，P的值会不断的改变，当系统进入稳态之后P值会收敛成一个最小的估计方差矩阵，这个时候的卡尔曼增益也是最优的，所以这个值只是影响初始收敛速度。

 */
void Kalman_Init(Kalman * kfp,double Q,double R)
{
	kfp->Last_P = 1;
	kfp->Now_P = 0;
	kfp->out = 0;
	kfp->Kg = 0;
	kfp->Q = Q;
	kfp->R = R;
}


/**
 *卡尔曼滤波器
 *@param 	Kalman *kfp 卡尔曼结构体参数
 *   			float input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
float KalmanFilter(Kalman *kfp,float input)
{
   //预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
   kfp->Now_P = kfp->Last_P + kfp->Q;
   //卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
   kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);
   //更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
   kfp->out = kfp->out + kfp->Kg * (input -kfp->out);//因为这一次的预测值就是上一次的输出值
   //更新协方差方程: 本次的系统协方差付给 kfp->LastP 威下一次运算准备。
   kfp->Last_P = (1-kfp->Kg) * kfp->Now_P;
   return kfp->out;
}

/*
 * P为比例缩放系数
 *
 */
float UserKalFil(Kalman *kfp,float input,float Pf)
{
	return (KalmanFilter(kfp,input/Pf));

}
