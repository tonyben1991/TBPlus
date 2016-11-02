/*******************************************************************************
            > 文件: HighestBetween_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-10-26

            > 函数功能: 获取区间内最高点的索引
*******************************************************************************/

Params
    Numeric BeginPoint;
    Numeric EndPoint;

Vars
    Numeric i;
    Numeric HighestIndex;

Begin
    HighestIndex = CurrentBar - EndPoint;
    for i = (CurrentBar - EndPoint + 1) to (CurrentBar - BeginPoint)
    {
        if (Max(Open[i], Close[i]) > Max(Open[HighestIndex], Close[HighestIndex]))
        {
            HighestIndex = i;
        }
    }

    return CurrentBar - HighestIndex;

End
