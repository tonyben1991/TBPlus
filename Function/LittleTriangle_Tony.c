/*******************************************************************************
            > 文件: LittTriangle_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-10-21

            > 函数功能: 识别三角形
*******************************************************************************/

Params
    Numeric Length;            //判断周期的长短
    NumericArrayRef HighLine;       //趋势线上轨
    NumericArrayRef LowLine;        //趋势线下轨

Vars
    Numeric Ratio(2);               //控制三角形形态
    Numeric RatioH(4);
    Bool Flag(False);               //三角形是否成立的标志

Begin
    HighTrendLine_Tony(HighLine, CurrentBar - Length);
    LowTrendLine_Tony(LowLine, CurrentBar - Length);

    if (0 != HighLine[0] * HighLine[1] * LowLine[0] * LowLine[1])       //排除没找到趋势线的情况
    {
        /**********************************************************************/
        if (HighLine[0] < LowLine[0] && LowLine[0] < HighLine[1] && HighLine[1] < LowLine[1])
        {
            if (((LowLine[0] - HighLine[0]) / (LowLine[1] - LowLine[0])) < Ratio && ((HighLine[1] - LowLine[0]) / (LowLine[1] - HighLine[1])) < Ratio
            && (((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2]) - HighLine[0]) / ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2])- LowLine[1])) < RatioH)
            {
                Flag = True;
            }
        }
        else if (LowLine[0] < HighLine[0] && HighLine[0] < LowLine[1] && LowLine[1] < HighLine[1])
        {
            if (((HighLine[0] - LowLine[0]) / (HighLine[1] - HighLine[0])) < Ratio && ((LowLine[1] - HighLine[0]) / (HighLine[1] - LowLine[1])) < Ratio
            && (((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2]) - LowLine[0]) / ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2])- HighLine[1])) < RatioH)
            {
                Flag = True;
            }
        }
        /**********************************************************************/
    }

    return Flag;

End
