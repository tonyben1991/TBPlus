/*******************************************************************************
            > 文件: Triangle_Tony
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
    Numeric RatioH(4);              //控制突破点
    Numeric Filter(1);              //控制回调比例
    Numeric TempHigh;
    Numeric TempLow;
    Numeric TempIndex;
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

        /**********************************************************************/
        else if (HighLine[0] < LowLine[0] && LowLine[1] < HighLine[1])
        {
            TempIndex = HighestBetween_Tony(LowLine[0], LowLine[1]);
            TempHigh = HighLine[2] * TempIndex + HighLine[3];
            TempLow = LowLine[2] * TempIndex + LowLine[3];
            if (((TempHigh- Max(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex])) / (TempHigh - TempLow)) * 100 < Filter
            && ((LowLine[0] - HighLine[0]) / (HighLine[1] - LowLine[0])) < Ratio
            && (((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2]) - HighLine[0]) / ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2])- HighLine[1])) < RatioH)
            {
                Flag = True;
            }
            else if (Max(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex]) > Max(Open[CurrentBar - HighLine[1]], Close[CurrentBar - HighLine[1]]))
            {
                Flag = LittTriangle_Tony(CurrentBar - LowLine[0], HighLine, LowLine);
            }
        }
        else if (LowLine[0] < HighLine[0] && HighLine[1] < LowLine[1])
        {
            TempIndex = LowestBetween_Tony(HighLine[0], HighLine[1]);
            TempHigh = HighLine[2] * TempIndex + HighLine[3];
            TempLow = LowLine[2] * TempIndex + LowLine[3];
            if ((Min(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex]) - TempLow) / (TempHigh - TempLow) * 100 < Filter
            && ((HighLine[0] - LowLine[0]) / (LowLine[1] - HighLine[0])) < Ratio
            && ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2]) - LowLine[0]) / ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2])- LowLine[1]) < RatioH)
            {
                Flag = True;
            }
            else if (Min(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex]) < Min(Open[CurrentBar - LowLine[1]], Close[CurrentBar - LowLine[1]]))
            {
                Flag = LittTriangle_Tony(CurrentBar - HighLine[0], HighLine, LowLine);
            }
        }
        /**********************************************************************/

        /**********************************************************************/
        else if (HighLine[1] < LowLine[0])
        {
            TempIndex = LowestBetween_Tony(HighLine[0], HighLine[1]);
            TempHigh = HighLine[2] * TempIndex + HighLine[3];
            TempLow = LowLine[2] * TempIndex + LowLine[3];
            if ((Min(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex]) - TempLow) / (TempHigh - TempLow) * 100 < Filter
            && ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2]) - HighLine[0]) / ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2])- LowLine[1]) < RatioH)
            {
                Flag = True;
            }
            else if (Min(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex]) < Min(Open[CurrentBar - LowLine[0]], Close[CurrentBar - LowLine[0]]))
            {
                Flag = LittTriangle_Tony(CurrentBar - TempIndex, HighLine, LowLine);
            }
            else
            {
                Flag = LittTriangle_Tony(CurrentBar - HighLine[1], HighLine, LowLine);
            }
        }
        else    //if (LowLine[1] < HighLine[0])
        {
            TempIndex = HighestBetween_Tony(LowLine[0], LowLine[1]);
            TempHigh = HighLine[2] * TempIndex + HighLine[3];
            TempLow = LowLine[2] * TempIndex + LowLine[3];
            if ((TempHigh - Max(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex])) / (TempHigh - TempLow) * 100 < Filter
            && ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2]) - LowLine[0]) / ((LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2])- HighLine[1]) < RatioH)
            {
                Flag = True;
            }
            else if (Max(Open[CurrentBar - TempIndex], Close[CurrentBar - TempIndex]) > Max(Open[CurrentBar - HighLine[0]], Close[CurrentBar - HighLine[0]]))
            {
                Flag = LittTriangle_Tony(CurrentBar - TempIndex, HighLine, LowLine);
            }
            else
            {
                Flag = LittTriangle_Tony(CurrentBar - LowLine[1], HighLine, LowLine);
            }
        }
        /**********************************************************************/
    }

    //Commentary("High Line:" + Text(HighLine[0]) + " " + Text(HighLine[1]));
    //Commentary("Low Line:" + Text(LowLine[0]) + " " + Text(LowLine[1]));
    //Commentary("CurrentBar:" + Text(CurrentBar));

    return Flag;

End
