#include "System.h"
/*
    测试独立模式
        扫描                        1
        规则触发 (软件触发)          1 
        注入触发 (软件触发)          1
        规则间断                    0
        注入间断                    0
        自动注入                    0
        连续转换                    1
        看门狗                      0
        内部温度                    0
        DMA                        0
*/
NVIC_InitTypeDef ADC_NVIC_InitStructure = {
    .NVIC_IRQChannel = ADC1_2_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 5,
    .NVIC_IRQChannelCmd = DISABLE};
ADC_Base_InitTypeDef ADC_Base_InitStructure = {
    .RCC_PCLK2_Divx = RCC_PCLK2_Div6,
    .ADC_DiscModeNumber = 1,
    .ADC_DataAlign = ADC_DataAlign_Right,
    .ADC_Mode = ADC_Mode_Independent,
    .ADC_JAuto = DISABLE,
    .ADC_ContinuousConvMode = ENABLE,
    .ADC_ScanConvMode = ENABLE};
vector<ADC_Channel_ConInfo> ADC_RegularChannellist = {
    {ADC_Channel_10,
     1,
     ADC_SampleTime_1Cycles5},
    {ADC_Channel_11,
     2,
     ADC_SampleTime_1Cycles5},
    {ADC_Channel_12,
     3,
     ADC_SampleTime_1Cycles5}};
vector<ADC_Channel_ConInfo> ADC_InjectedChannellist = {
    {ADC_Channel_13,
     1,
     ADC_SampleTime_1Cycles5}};
ADC_Channel_InitTypeDef ADC_RegularChannel_InitStructure = {
    .ADC_Channellist = ADC_RegularChannellist,
    .ADC_ExternalTrigConv = ADC_ExternalTrigConv_None,
    .ADC_DiscMode = DISABLE,
    .ADC_ExternalTrig = DISABLE};
ADC_Channel_InitTypeDef ADC_InjectedChannel_InitStructure = {
    .ADC_Channellist = ADC_InjectedChannellist,
    .ADC_ExternalTrigConv = ADC_ExternalTrigInjecConv_None, //如果用软件开启则直接使用none
    .ADC_DiscMode = DISABLE,
    .ADC_ExternalTrig = DISABLE};
ADC_Param ADCx_Param = {
    .ADCx = ADC1,
    .ADC_Base_InitStructure = ADC_Base_InitStructure,
    .ADC_RegularChannel_InitStructure = ADC_RegularChannel_InitStructure,
    .ADC_InjectedChannel_InitStructure = ADC_InjectedChannel_InitStructure,
    .ADC_NVIC_InitStructure = ADC_NVIC_InitStructure,
    .ADC_IT_Selection = ADC_IT_EOC,
    .ADC_IT_State = ENABLE,
    .ADC_DMA_State = DISABLE};
ADC ADC_Test = ADC(ADCx_Param);
void Setup();
void Test();
void End();
int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    system_init();
    ADC_Test.Init();
}
void Test()
{
    
}
void End()
{
}