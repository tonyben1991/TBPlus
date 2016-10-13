/*******************************************************************************
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-09-28-09.10

            > 函数功能: 查找最高顶点Index
*******************************************************************************/

Params
    NumericSeries myValue;  //出入的数值
    Numeric Length;         //传入的周期

Vars
    Numeric i;                  //循环计数
    NumericArray IndexArr;      //保存满足条件的Bar距离当前Bar的距离
    Numeric maxIndex;           //
Begin
    NumericArrayInsert(IndexArr, 0, 0);
    for i = 2 to Length
    {
        if (myValue[i] > myValue[i - 1] && myValue[i] > myValue[i - 2]
            && myValue[i] > myValue[i + 1] && myValue[i] > myValue[i + 2])
        {
            NumericArrayInsert(IndexArr, GetNumericArraySize(IndexArr) - 1, i);
        }
    }

    maxIndex = IndexArr[0];
    for i = 1 to GetNumericArraySize(IndexArr) - 2
    {
        if (myValue[IndexArr[i]] > myValue[maxIndex])
        {
            maxIndex = IndexArr[i];
        }
    }

    return CurrentBar - maxIndex; //返回最高顶部的Bar序号
End
