/*******************************************************************************
            > 文件: FindBottom_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-09-28-09.10

            > 函数功能: 查找最低底部的Index
*******************************************************************************/

Params
    NumericSeries myValue;  //传入的数值
    Numeric Length;         //传入的周期

Vars
    Numeric i;                  //循环计数
    NumericArray IndexArr;      //保存满足条件的Bar距离当前Bar的距离
    Numeric minIndex;           //保存最的最低底部的Bar距离当前Bar的距离

Begin
    NumericArrayInsert(IndexArr, 0, 0);
    for i = 2 to Length
    {
        if (myValue[i] < myValue[i - 1] && myValue[i] < myValue[i - 2]
            && myValue[i] < myValue[i + 1] && myValue[i] < myValue[i + 2])
        {
            NumericArrayInsert(IndexArr, GetNumericArraySize(IndexArr) - 1, i);
        }
    }

    minIndex = IndexArr[0];
    for i = 1 to GetNumericArraySize(IndexArr) - 2
    {
        if (myValue[IndexArr[i]] < myValue[minIndex])
        {
            minIndex = IndexArr[i];
        }
    }

    return CurrentBar - minIndex; //返回最低底部的Bar序号
End
