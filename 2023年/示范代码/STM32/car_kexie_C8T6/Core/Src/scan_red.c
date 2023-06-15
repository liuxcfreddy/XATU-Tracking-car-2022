#include "scan_red.h"
#include "math.h"



/*
 *偏移距离坐标换算，返回值单位为 毫米 mm
 */

float Coordinate_Conversion(int16_t input)
{
    return (0.6001*input+0.5743);
}
 /*
  *@brif:交叉负反馈 
  *@prgam:wheelbase  轴距(单位：mm)
  *@prgam:Dist_sensor2axis 感应器距轴心距离(单位：mm)
  *@prgam:L2R_Difference 偏移距离 (单位：mm)
    *@prgam:    mode  =
                    1：输出需要的偏差比例 
                    0：输出偏移的弧度角
    *@retive: 需要的弧度角
  */
float Cross_negative_feedback(float wheelbase,float Dist_sensor2axis, float Difference,int mode)
{
    float rad,//偏移弧度
    Leading_quantity;//超调量
    rad = atan(Difference/Dist_sensor2axis);
    if(mode)
    {
        Leading_quantity = (rad/3.14);//除以Π（派），分配电机功率比例的弧度比例
    }
    else 
    {
        Leading_quantity = rad;
    }
    return Leading_quantity;
}
