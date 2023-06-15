
#include "pid.h"
 
/**
 * @name 	fuzzy
 * @brief 	pid模糊控制调节函数
 * @note 	在实践中建议通过一定的方法获取自适应参数，设为默认值，可以减少收敛时间
 *			或者配合EEPROM等外设自动更新值，由此即可达到类似于机器学习效果，小车越跑，跟的越准。根据数据不断自我迭代。
 * */ 
PID fuzzy(float e,float ec)
{
 
     float etemp,ectemp;
     float eLefttemp,ecLefttemp;
     float eRighttemp ,ecRighttemp;
 
     int eLeftIndex,ecLeftIndex;
     int eRightIndex,ecRightIndex;
     PID      fuzzy_PID;
     etemp = e > 3.0 ? 0.0 : (e < - 3.0 ? 0.0 : (e >= 0.0 ? (e >= 2.0 ? 2.5: (e >= 1.0 ? 1.5 : 0.5)) : (e >= -1.0 ? -0.5 : (e >= -2.0 ? -1.5 : (e >= -3.0 ? -2.5 : 0.0) ))));
 
     eLeftIndex = (int)e;
     eRightIndex = eLeftIndex;
     eLeftIndex = (int)((etemp-0.5) + 3);        //[-3,3] -> [0,6]
     eRightIndex = (int)((etemp+0.5) + 3);
 
     eLefttemp =etemp == 0.0 ? 0.0:((etemp+0.5)-e);
     eRighttemp=etemp == 0.0 ? 0.0:( e-(etemp-0.5));
 
     ectemp = ec > 3.0 ? 0.0 : (ec < - 3.0 ? 0.0 : (ec >= 0.0 ? (ec >= 2.0 ? 2.5: (ec >= 1.0 ? 1.5 : 0.5)) : (ec >= -1.0 ? -0.5 : (ec >= -2.0 ? -1.5 : (ec >= -3.0 ? -2.5 : 0.0) ))));
 
     ecLeftIndex = (int)((ectemp-0.5) + 3);        //[-3,3] -> [0,6]
     ecRightIndex = (int)((ectemp+0.5) + 3);
 
     ecLefttemp =ectemp == 0.0 ? 0.0:((ectemp+0.5)-ec);
     ecRighttemp=ectemp == 0.0 ? 0.0:( ec-(ectemp-0.5));
 
/*************************************反模糊*************************************/
 
 
	fuzzy_PID.Kp = (eLefttemp * ecLefttemp *  fuzzyRuleKp[ecLeftIndex][eLeftIndex]                    
					+ eLefttemp * ecRighttemp * fuzzyRuleKp[ecRightIndex][eLeftIndex]
					+ eRighttemp * ecLefttemp * fuzzyRuleKp[ecLeftIndex][eRightIndex]
					+ eRighttemp * ecRighttemp * fuzzyRuleKp[ecRightIndex][eRightIndex]);
 
	fuzzy_PID.Ki =   (eLefttemp * ecLefttemp * fuzzyRuleKi[ecLeftIndex][eLeftIndex]
					+ eLefttemp * ecRighttemp * fuzzyRuleKi[ecRightIndex][eLeftIndex]
					+ eRighttemp * ecLefttemp * fuzzyRuleKi[ecLeftIndex][eRightIndex]
					+ eRighttemp * ecRighttemp * fuzzyRuleKi[ecRightIndex][eRightIndex]);
 
	fuzzy_PID.Kd = (eLefttemp * ecLefttemp *    fuzzyRuleKd[ecLeftIndex][eLeftIndex]
					+ eLefttemp * ecRighttemp * fuzzyRuleKd[ecRightIndex][eLeftIndex]
					+ eRighttemp * ecLefttemp * fuzzyRuleKd[ecLeftIndex][eRightIndex]
					+ eRighttemp * ecRighttemp * fuzzyRuleKd[ecRightIndex][eRightIndex]);
return fuzzy_PID;
 
}
/**
 * @name speed_pid
 * @brief tar 目标值
 * @brief cur 实际值（当前量）
 * @note 当前控制方法为位置式控制函数
*/
float speed_pid(float tar,float cur)
{           
	static PID pid= {0, 0, 0};      //赋予初值kp，ki，kd
	static int sumE = 0;                   //累加偏差
	static int lastE = 0;
 
	PID OUT = {0, 0, 0};
	float e = -1,ec = -2.6;

	e = tar - cur;             //目标值 - 实际值
	ec = e - lastE;            //误差变化率
	sumE += e;
	lastE = e;
	OUT = fuzzy(e, ec);      //模糊控制调整  kp，ki，kd
 
	return (pid.Kp+OUT.Kp)*e + (pid.Kd+OUT.Kd)*ec + (pid.Ki+OUT.Ki)*sumE;
}
