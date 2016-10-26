/*******************************************************************************
            > 文件: Triangle_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-10-21

            > 函数功能: 识别三角形
*******************************************************************************/

Params
    Numeric Length(100);            //判断周期的长短

Vars
    Numeric Ratio(2);               //控制三角形形态
    NumericArray HighLine;          //趋势线上轨
    NumericArray LowLine;           //趋势线下轨
    StringSeries LastFourPoints;    //记录前一个三角形的四个点
    String FourPoints;              //记录当前三角形的四个点
    Bool Flag(False);               //三角形是否成立的标志

Begin
    Pandora_getHighTrendLine(HighLine, CurrentBar - Length);
    Pandora_getLowTrendLine(LowLine, CurrentBar - Length);

    //Commentary("High Line:" + Text(HighLine[0]) + " " + Text(HighLine[1]));
    //Commentary("Low Line:" + Text(LowLine[0]) + " " + Text(LowLine[1]));

    if (0 != HighLine[0] * HighLine[1] * LowLine[0] * LowLine[1])       //排除没找到趋势线的情况
    {
        if ((HighLine[0] < LowLine[0] && LowLine[0] < HighLine[1] && HighLine[1] < LowLine[1])
        || (LowLine[0] < HighLine[0] && HighLine[0] < LowLine[1] && LowLine[1] < HighLine[1]))  //
        {
            if ((Abs(HighLine[0] - LowLine[0]) < Abs(HighLine[1] - LowLine[1]) * Ratio
                && Abs(HighLine[0] - LowLine[0]) < Min(Abs(LowLine[0] - HighLine[1]), Abs(HighLine[0] - LowLine[1])) * Ratio
                && Min(Abs(LowLine[0] - HighLine[1]), Abs(HighLine[0] - LowLine[1])) < Abs(HighLine[1] - LowLine[1]) * Ratio)
            && (Abs(HighLine[0] - LowLine[0]) > Abs(HighLine[1] - LowLine[1]) / Ratio
                && Abs(HighLine[0] - LowLine[0]) > Min(Abs(LowLine[0] - HighLine[1]), Abs(HighLine[0] - LowLine[1])) / Ratio
                && Min(Abs(LowLine[0] - HighLine[1]), Abs(HighLine[0] - LowLine[1])) > Abs(HighLine[1] - LowLine[1]) / Ratio))
            {
                Flag = True;
            }
        }

        else if (HighLine[1] < LowLine[0] || LowLine[1] < HighLine[0])
        {
            if ((HighLine[1] - HighLine[0] > Min(Abs(HighLine[1] - HighLine[0]), Abs(LowLine[1] - HighLine[0])) / Ratio
                && LowLine[1] - LowLine[0] > Min(Abs(HighLine[1] - HighLine[0]), Abs(LowLine[1] - HighLine[0])) / Ratio)
            && ())
            {
                if ()
                {
                    Flag = True;
                }
            }
        }
        else    //(HighLine[0] < LowLine[0] && LowLine[1] < HighLine[1]) || (LowLine[0] < HighLine[0] && HighLine[1] < LowLine[1])
        {
            if (Min(LowLine[1] - LowLine[0], HighLine[1] - HighLine[0]) > Abs(HighLine[0] - LowLine[0]) / 2
            && Min(LowLine[1] - LowLine[0], HighLine[1] - HighLine[0]) > Abs(HighLine[1] - LowLine[1]) / 2)
            {
                if ()
                {
                    Flag = True;
                }
            }
        }

    }

    FourPoints = (Text(HighLine[0]) + " " + Text(HighLine[1]) + " " + Text(LowLine[0]) + " " + Text(LowLine[1]));
    if (FourPoints == LastFourPoints)
    {
        Flag = False;
    }
    LastFourPoints = FourPoints;

    //Commentary("CurrentBar:" + Text(CurrentBar));

    return Flag;

End
