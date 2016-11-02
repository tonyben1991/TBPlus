/*******************************************************************************
            > 文件: LowestBefore_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:2016-11-02

            > 函数功能:
*******************************************************************************/

Params
    Numeric FirstPoint;

Vars
    Numeric LowestIndex;
    Numeric i(1);

Begin
    LowestIndex = FirstPoint;
    while (CurrentBar - FirstPoint + i - 4 > 0)
    {
        if (Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i + 1], Close[CurrentBar - FirstPoint + i + 1])
        && Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i + 2], Close[CurrentBar - FirstPoint + i + 2])
        && Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i + 3], Close[CurrentBar - FirstPoint + i + 3])
        && Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i + 4], Close[CurrentBar - FirstPoint + i + 4])
        && Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i - 1], Close[CurrentBar - FirstPoint + i - 1])
        && Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i - 2], Close[CurrentBar - FirstPoint + i - 2])
        && Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i - 3], Close[CurrentBar - FirstPoint + i - 3])
        && Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - FirstPoint + i - 4], Close[CurrentBar - FirstPoint + i - 4]))
        {
            if (Min(Open[CurrentBar - FirstPoint + i], Close[CurrentBar - FirstPoint + i]) < Min(Open[CurrentBar - LowestIndex], Close[CurrentBar - LowestIndex]))
            {
                LowestIndex = FirstPoint - i;
            }
            else
            {
                break;
            }
        }
        i = i + 1;
    }

    return LowestIndex;

End
