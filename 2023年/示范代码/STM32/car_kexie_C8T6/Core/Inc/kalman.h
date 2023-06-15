/*
 * kalman.h
 *
 *  Created on: 2023年3月30日
 *      Author: liuxc
 */

#ifndef INC_KALMAN_H_
#define INC_KALMAN_H_


#include "main.h"

typedef struct
{
    float Last_P;//上次估算协方差 不可以为0 ! ! ! ! !
    float Now_P;//当前估算协方差
    float out;//卡尔曼滤波器输出
    float Kg;//卡尔曼增益
    float Q;//过程噪声协方差
    float R;//观测噪声协方差
}Kalman;

void Kalman_Init(Kalman * kfp,double Q,double R);

float KalmanFilter(Kalman *kfp,float input);
float UserKalFil(Kalman *kfp,float input,float Pf);

extern Kalman kfp;


#endif /* INC_KALMAN_H_ */
