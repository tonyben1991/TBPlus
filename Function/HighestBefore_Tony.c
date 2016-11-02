/*******************************************************************************
            > 文件: HighestBefore_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-11-02

            > 函数功能:
*******************************************************************************/

Params
    Numeric FirstPoint;

Vars
    Numeric HighestIndex;
    Numeric i(1);

Begin
    HighestIndex = FirstPoint;
    while (CurrentBar - FirstPoint + i - 4 > 0)
    {
        if (Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i + 1], Close[CurrentBar - FirstPoint + i + 1])
        && Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i + 2], Close[CurrentBar - FirstPoint + i + 2])
        && Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i + 3], Close[CurrentBar - FirstPoint + i + 3])
        && Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i + 4], Close[CurrentBar - FirstPoint + i + 4])
        && Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i - 1], Close[CurrentBar - FirstPoint + i - 1])
        && Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i - 2], Close[CurrentBar - FirstPoint + i - 2])
        && Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i - 3], Close[CurrentBar - FirstPoint + i - 3])
        && Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - FirstPoint + i - 4], Close[CurrentBar - FirstPoint + i - 4]))
        {
            if (Max(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) > Max(Open[CurrentBar - HighestIndex], Close[CurrentBar - HighestIndex]))
            {
                HighestIndex = FirstPoint - i;
            }
            else
            {
                break;
            }
        }
        i = i + 1;
    }

    return HighestIndex;

End
