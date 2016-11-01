/*******************************************************************************
            > 文件:TriangleTest_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-10-26

            > 策略原理:
                1.三角形形态识别函数测试
            > 测试品种:
                1.通用
            > 适用周期:
                1.通用
            > 参数列表:
                1.
*******************************************************************************/

Params
    Numeric Length(100);        //判断周期长短

Vars
    NumericArray HighLine[4];
    NumericArray LowLine[4];
    Numeric k_H;
    Numeric k_L;
    Numeric b_H;
    Numeric b_L;
    StringSeries FourPoints;
    StringSeries LastFourPoints;

Begin
    if (Triangle_Tony(Length, HighLine, LowLine))
    {
        k_H = (Max(Open[CurrentBar - HighLine[1]], Close[CurrentBar - HighLine[1]])
                - Max(Open[CurrentBar - HighLine[0]], Close[CurrentBar - HighLine[0]]))
            / (HighLine[1] - HighLine[0]);
        b_H = Max(Open[CurrentBar - HighLine[1]], Close[CurrentBar - HighLine[1]]) - HighLine[0] * k_H;  //b = y1 - k * x1

        k_L = (Min(Open[CurrentBar - LowLine[1]], Close[CurrentBar - LowLine[1]])
                - Min(Open[CurrentBar - LowLine[0]], Close[CurrentBar - LowLine[0]]))
            / (LowLine[1] - LowLine[0]);
        b_L = Min(Open[CurrentBar - LowLine[1]], Close[CurrentBar - LowLine[1]]) - LowLine[0] * k_L;

        FourPoints = (Text(HighLine[0]) + " " + Text(HighLine[1]) + " " + Text(LowLine[0]) + " " + Text(LowLine[1]));
        if (FourPoints != LastFourPoints)
        {
            PlotBool("T", True);
        }
        LastFourPoints = FourPoints;

    }

End
