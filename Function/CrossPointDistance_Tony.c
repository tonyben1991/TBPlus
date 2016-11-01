/*******************************************************************************
            > 文件: CrossPointDistance_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-10-31

            > 函数功能:
*******************************************************************************/

Params
    NumericArrayRef HighLine;
    NumericArrayRef LowLine;

Vars
    Numeric CrossPointIndex;
    Numeric Height;
    Bool Flag(False);

Begin
    CrossPointIndex = (LowLine[3] - HighLine[3]) / (HighLine[2] - LowLine[2]);
    Height = CrossPointIndex - Min(HighLine[0], LowLine[0]);
    if ((CrossPointIndex - Max(HighLine[1], LowLine[1])) > Height / 4)
    {
        Flag = True;
    }

    return Flag;

End
