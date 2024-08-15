/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.0
 * @日  期  2022-12-29
 * @内  容  VIN输入电压检测
 *
 ******************************************************************************
 * @说  明
 *
 * 1.使用ADC1对VIN输入电压采样，查询方式
 * 2.输入电压检测功能，可实现对电池电量的评估
 *
 ******************************************************************************
 */

#include "bsp_vin.h"

float vol_scale;

/**
 * @brief	读取一次参考电压值
 * @retval 参考电压值
 */
float VOL_Get(void)
{
    uint16_t vrefint;

    HAL_ADC_Start(&hadc1);
    // 等待转换结束
    HAL_ADC_PollForConversion(&hadc1, 10);
    vrefint = HAL_ADC_GetValue(&hadc1);

    return vrefint;
}

/**
 * @brief  获得电压模数转换比例
 * @retval 比例值
 */
float VOL_ScaleSet(void)
{
    uint32_t temp = 0;

    for (uint8_t i = 0; i < 200; i++)
    {
        temp += VOL_Get();
    }

    vol_scale = 200 * 1.2f / temp;

    return vol_scale;
}

/**
 * @brief  VIN 获得输入电压
 * @retval 电压值，扩大100倍。例如7.2V输出为720。
 */
float VIN_GetVal(void)
{
    uint16_t temp;
    float vin;

    HAL_ADC_Start(&hadc3);

    // 等待转换结束
    HAL_ADC_PollForConversion(&hadc3, 10);

    temp = HAL_ADC_GetValue(&hadc3);
    //(22K Ω + 200K Ω) / 22K Ω = 10.090909090909090909090909090909
    vin = temp * vol_scale * 10.091f;

    return vin;
}
