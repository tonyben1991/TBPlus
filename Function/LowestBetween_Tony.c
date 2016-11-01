/*******************************************************************************
            > 文件: LowestBetween_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-10-26

            > 函数功能:
*******************************************************************************/

Params
    Numeric BeginPoint;
    Numeric EndPoint;

Vars
    Numeric i;
    Numeric LowestIndex;

Begin
    LowestIndex = CurrentBar - EndPoint;
    for i = (CurrentBar - EndPoint + 1) to (CurrentBar - BeginPoint)
    {
        if (Min(Open[i], Close[i]) < Min(Open[LowestIndex], Close[LowestIndex]))
        {
            LowestIndex = i;
        }
    }

    return CurrentBar - LowestIndex;

End
