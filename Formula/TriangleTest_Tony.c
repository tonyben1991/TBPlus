Params
    Numeric Length(200);        //判断周期长短
    Numeric Ratio(2);           //控制三角形形态
Vars
    NumericArray HighLine;
    NumericArray LowLine;
    StringSeries LastFourPoint;     //记录前一个三角形的四个点

Begin
    Pandora_getHighTrendLine(HighLine, CurrentBar - Length);
    Pandora_getLowTrendLine(LowLine, CurrentBar - Length);

    Commentary("High Line:" + Text(HighLine[0]) + " " + Text(HighLine[1]));
    Commentary("Low Line:" + Text(LowLine[0]) + " " + Text(LowLine[1]));

    if (0 != HighLine[0] * HighLine[1] * LowLine[0] * LowLine[1])       //排除没找到去实现的的情况
    {
        //if ((HighLine[0] < LowLine[0] && LowLine[0] < HighLine[1] && HighLine[1] < LowLine[1]) || (LowLine[0] < HighLine[0] && HighLine[0] < LowLine[1] && LowLine[1] < HighLine[1]))
        {
            if (Abs(HighLine[0] - LowLine[0]) < Abs(HighLine[1] - LowLine[1]) * Ratio)
            {
                LastFourPoint = Text(HighLine[0]) + Text(HighLine[1]) + Text(LowLine[0]) + Text(LowLine[1]);
                if (LastFourPoint[1] != LastFourPoint)
                {
                    PlotBool("T", True);
                }
            }
        }
    }

End
