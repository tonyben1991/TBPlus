/*******************************************************************************
            > 文件: Triangle_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-10-21

            > 函数功能: 识别三角形
*******************************************************************************/

Params
    Numeric Length(100);            //判断周期的长短
    NumericArrayRef HighLine;       //趋势线上轨
    NumericArrayRef LowLine;        //趋势线下轨

Vars
    Numeric Ratio(2);               //控制三角形形态
    Bool Flag(False);               //三角形是否成立的标志

Begin
    HighTrendLine_Tony(HighLine, CurrentBar - Length);
    LowTrendLine_Tony(LowLine, CurrentBar - Length);

    //Commentary("High Line:" + Text(HighLine[0]) + " " + Text(HighLine[1]));
    //Commentary("Low Line:" + Text(LowLine[0]) + " " + Text(LowLine[1]));

    if (0 != HighLine[0] * HighLine[1] * LowLine[0] * LowLine[1])       //排除没找到趋势线的情况
    {
        /**********************************************************************/
        if (HighLine[0] < LowLine[0] && LowLine[0] < HighLine[1] && HighLine[1] < LowLine[1])
        {
            if (LowLine[0] - HighLine[0] < (LowLine[1] - LowLine[0]) * Ratio       //(HighLine[1] - LowLine[0]) * Ratio
            && HighLine[1] - LowLine[0] < (LowLine[1] - HighLine[1]) * Ratio)
            {
                Flag = True;
            }
        }
        if (LowLine[0] < HighLine[0] && HighLine[0] < LowLine[1] && LowLine[1] < HighLine[1])
        {
            if (HighLine[0] - LowLine[0] < (HighLine[1] - HighLine[0]) * Ratio       //(LowLine[1] - HighLine[0]) * Ratio
            && LowLine[1] - HighLine[1] < (LowLine[1] - HighLine[1]) * Ratio)
            {
                Flag = True;
            }
        }
        /**********************************************************************/

        /**********************************************************************/
        if (HighLine[0] < LowLine[0] && LowLine[1] < HighLine[1])
        {
            if (LowLine[1] - LowLine[0] > (LowLine[0] - HighLine[0]) / Ratio
            && LowLine[1] - LowLine[0] > (HighLine[1] - LowLine[1]) / Ratio)
            {
                if (High[CurrentBar - HighestBetween_Tony(LowLine[0], LowLine[1])] > High[CurrentBar - HighLine[1]])
                {
                    HighLine[0] = HighestBetween_Tony(LowLine[0], LowLine[1]);
                }
            }
        }
        if (LowLine[0] < HighLine[0] && HighLine[1] < LowLine[1])
        {
            if (HighLine[1] - HighLine[0] > (HighLine[0] - LowLine[0]) / Ratio
            && HighLine[1] - HighLine[0] > (LowLine[1] - HighLine[1]) / Ratio)
            {
                if (Low[CurrentBar - LowestBetween_Tony(HighLine[0], HighLine[1])] < Low[CurrentBar - LowLine[1]])
                {
                    LowLine[0] = LowestBetween_Tony(HighLine[0], HighLine[1]);
                }
            }
        }
        /**********************************************************************/

        /**********************************************************************/
        if (HighLine[1] < LowLine[0])
        {
            if (HighLine[1] - HighLine[0] > (LowLine[0] - HighLine[1]) / Ratio
            && LowLine[1] - LowLine[0] > (LowLine[0] - HighLine[1]) / Ratio)
            {
                if (Low[CurrentBar - LowestBetween_Tony(HighLine[0], HighLine[1])] < Low[CurrentBar - LowLine[0]])
                {
                    Flag = True;
                }
            }
        }
        if (LowLine[1] < HighLine[0])
        {
            if (LowLine[1] - LowLine[0] > (HighLine[0] - LowLine[1]) / Ratio
            && HighLine[1] - HighLine[0] > (HighLine[0] - LowLine[1]) / Ratio)
            {
                if (High[CurrentBar - HighestBetween_Tony(LowLine[0], LowLine[1])] > High[CurrentBar - HighLine[0]])
                {
                    Flag = True;
                }
            }
        }
        /**********************************************************************/
    }

    //Commentary("CurrentBar:" + Text(CurrentBar));

    return Flag;

End
