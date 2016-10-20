/*******************************************************************************
            > 文件: FindLP_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:

            > 函数功能:
*******************************************************************************/

Params
    Numeric BeginBarIndex;     //
    Numeric EndBarIndex;

Vars
    Numeric i;                  //循环计数
    NumericArray IndexArr;      //保存满足条件的Bar距离当前Bar的距离
    Numeric minIndex;           //保存最的最低底部的Bar距离当前Bar的距离

Begin
    NumericArrayInsert(IndexArr, 0, 0);
    for i = CurrentBar - EndBarIndex to CurrentBar - BeginBarIndex
    {
        if (Min(Open[i], Close[i]) <= Min(Open[i - 1], Close[i - 1]) && Min(Open[i], Close[i]) <= Min(Open[i - 2], Close[i - 2])
            && Min(Open[i], Close[i]) <= Min(Open[i + 1], Close[i + 1]) && Min(Open[i], Close[i]) <= Min(Open[i + 2], Close[i + 2]))
        {
            NumericArrayInsert(IndexArr, GetNumericArraySize(IndexArr) - 1, CurrentBar - i);
        }
    }

    minIndex = IndexArr[0];
    for i = 1 to GetNumericArraySize(IndexArr) - 2
    {
        if (Min(Open[CurrentBar - IndexArr[i]], Close[CurrentBar - IndexArr[i]]) < Min(Open[CurrentBar - minIndex], Close[CurrentBar - minIndex]))
        {
            minIndex = IndexArr[i];
        }
    }

    return minIndex; //返回最低底部的Bar序号
End
