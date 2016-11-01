/*******************************************************************************
            > 文件: GetLine_K_B_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-10-21

            > 函数功能: 计算直线的斜率和纵截距
*******************************************************************************/

Params
    Numeric BeginPoint;
    Numeric EndPoint;
    Numeric proportionYX;

Vars
    Numeric k;
    Numeric b;

Begin
    k = (Min(o[CurrentBar - TrendLine[i * 2 + 1]], c[CurrentBar - TrendLine[i * 2 + 1]]) - Min(o[CurrentBar - TrendLine[i * 2]], c[CurrentBar - TrendLine[i * 2]])) / proportionYX / (TrendLine[i * 2 + 1] - TrendLine[i * 2]); //k = (y2 - y1) / (x2 - x1)
    b = Min(o[CurrentBar - TrendLine[i * 2]], c[CurrentBar - TrendLine[i * 2]]) / proportionYX - TrendLine[i * 2] * k;

    TrendLine[2] = k;
    TrendLine[3] = b;

    return True;

End
