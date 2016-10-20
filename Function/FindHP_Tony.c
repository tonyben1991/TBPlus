/*******************************************************************************
            > 文件: FindHP_Tony
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
    Numeric maxIndex;           //
Begin
    NumericArrayInsert(IndexArr, 0, 0);
    for i = CurrentBar - EndBarIndex to CurrentBar - BeginBarIndex
    {
        if (Max(Open[i], Close[i]) >= Max(Open[i - 1], Close[i - 1]) && Max(Open[i], Close[i]) >= Max(Open[i - 2], Close[i - 2])
            && Max(Open[i], Close[i]) >= Max(Open[i + 1], Close[i + 1]) && Max(Open[i], Close[i]) >= Max(Open[i + 2], Close[i + 2]))
        {
            NumericArrayInsert(IndexArr, GetNumericArraySize(IndexArr) - 1, CurrentBar - i);
        }
    }

    maxIndex = IndexArr[0];
    for i = 1 to GetNumericArraySize(IndexArr) - 2
    {
        if (Max(Open[CurrentBar - IndexArr[i]], Close[CurrentBar - IndexArr[i]]) > Max(Open[CurrentBar - maxIndex], Close[CurrentBar - maxIndex]))
        {
            maxIndex = IndexArr[i];
        }
    }

    return maxIndex; //返回最高顶部的Bar序号
End
