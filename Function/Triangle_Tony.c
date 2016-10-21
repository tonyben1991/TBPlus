/*******************************************************************************
            > 文件: Triangle_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:

            > 函数功能: 识别三角形
*******************************************************************************/

Params
    Numeric BeginBarIndex;     //
    Numeric EndBarIndex;

Vars
    Numeric HighestBarIndex;        //最该点索引
    Numeric SecHighestBarIndex;     //次高点索引
    Numeric LowestBarIndex;         //最低点索引
    Numeric SecLowestBarIndex;      //次低点索引
    NumericSeries Flag(0);          //前一个三角形的起点,用来过滤同一个三角形

Begin
    HighestBarIndex = InvalidNumeric;
    SecHighestBarIndex = InvalidNumeric;
    LowestBarIndex = InvalidNumeric;
    SecLowestBarIndex = InvalidNumeric;

    HighestBarIndex = FindHP_Tony(BeginBarIndex, EndBarIndex);
    LowestBarIndex = FindLP_Tony(BeginBarIndex, EndBarIndex);

    if (0 == HighestBarIndex || 0 == LowestBarIndex)
    {
        return False;
    }

    if (HighestBarIndex < LowestBarIndex)
    {
        SecHighestBarIndex = FindHP_Tony(LowestBarIndex + 1, EndBarIndex); //在最高点之后找一个最高点,也就是次高点
        SecLowestBarIndex = FindLP_Tony(SecHighestBarIndex + 1, EndBarIndex);   //在最低点之后找一个最低点,也就是次低点
    }
    else
    {
        SecLowestBarIndex = FindLP_Tony(HighestBarIndex + 1, EndBarIndex);   //在最低点之后找一个最低点,也就是次低点
        SecHighestBarIndex = FindHP_Tony(SecLowestBarIndex + 1, EndBarIndex); //在最高点之后找一个最高点,也就是次高点
    }

    if (0 == SecHighestBarIndex || 0 == SecLowestBarIndex)
    {
        return False;
    }

    Flag = HighestBarIndex + SecHighestBarIndex + LowestBarIndex + SecLowestBarIndex;
    if (Flag[1] == Flag)
    {
        return False;
    }

    if (Max(Close[CurrentBar - SecHighestBarIndex], Open[CurrentBar - SecHighestBarIndex])
      > Min(Close[CurrentBar - SecLowestBarIndex], Open[CurrentBar - SecLowestBarIndex]))     //如果次高点大于次低点
    {
        return True;
    }

    return False;

End
