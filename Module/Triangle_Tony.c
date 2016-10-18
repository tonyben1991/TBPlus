/*******************************************************************************
            > 文件: Triangle_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间:

            > 模块功能: 识别三角形
*******************************************************************************/

Params
    Numeric Length(50);     判断周期

Vars
    Numeric HighestBarIndex;        //最该点索引
    Numeric SecHighestBarIndex;     //次高点索引
    Numeric LowestBarIndex;         //最低点索引
    Numeric SecLowestBarIndex;      //次低点索引
    NumericSeries Flag(0);          //前一个三角形的起点,用来过滤同一个三角形
    Bool Condition1(False);
    Bool Condition2(False);

Begin
    Commentary("Bar " + Text(CurrentBar));

    HighestBarIndex = InvalidNumeric;
    SecHighestBarIndex = InvalidNumeric;
    LowestBarIndex = InvalidNumeric;
    SecLowestBarIndex = InvalidNumeric;

    HighestBarIndex = FindHP_Tony(Length);
    SecHighestBarIndex = FindHP_Tony(CurrentBar - HighestBarIndex - 1); //在最高点之后找一个最高点,也就是次高点

    LowestBarIndex = FindLP_Tony(Length);
    SecLowestBarIndex = FindLP_Tony(CurrentBar - LowestBarIndex - 1);   //在最低点之后找一个最低点,也就是次低点


    Flag = Min(HighestBarIndex, LowestBarIndex);
    if (Flag[1] == Flag)
    {
        return;
    }

    Condition1 = HighestBarIndex < LowestBarIndex
                && LowestBarIndex < SecHighestBarIndex
                && SecHighestBarIndex < SecLowestBarIndex;
    Condition2 = LowestBarIndex < HighestBarIndex
                && HighestBarIndex < SecLowestBarIndex
                && SecLowestBarIndex < SecHighestBarIndex;

    if (Condition1 || Condition2)
    {
        if (Max(Close[CurrentBar - SecHighestBarIndex],
                Open[CurrentBar - SecHighestBarIndex])
          > Min(Close[CurrentBar - SecLowestBarIndex],
                Open[CurrentBar - SecHighestBarIndex]))
        {
            Commentary(Text(HighestBarIndex) + " " + Text(SecHighestBarIndex));
            Commentary(Text(LowestBarIndex) + " " + Text(SecLowestBarIndex));
            PlotBool("H", False);
        }
    }

End
