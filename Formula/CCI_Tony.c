/*******************************************************************************
            > 文件: CCI_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-10-09-09.40

            > 策略原理:
               	1.
            > 测试品种:
                1.
            > 适用周期:
                1.
            > 参数列表:
                1.
*******************************************************************************/

Params
    Numeric Length(14);
    Numeric AvgLength(9);

Vars
    NumericSeries TempValue;
    Numeric Mean(0);
    Numeric AvgDev(0);
    Numeric i;
    NumericSeries CCI(0);
    Numeric AvgCCI;

Begin
    TempValue = High + Low + Close;
    Mean = Average(TempValue, Length);
    for i = 0 to Length - 1
    {
        AvgDev = AvgDev + Abs(TempValue[i] - Mean);
    }
    AvgDev = AvgDev / Length;

    if (0 == AvgDev)
    {
        CCI = 0;
    }
    else
    {
        CCI = (TempValue - Mean) / (0.015 * AvgDev);
    }
    AvgCCI = Average(CCI, AvgLength);
    PlotNumeric("CCI", CCI);
    PlotNumeric("AvgCCI", AvgCCI);

End
