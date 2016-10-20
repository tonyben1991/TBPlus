//------------------------------------------------------------------------
// 潘多拉测试 Pandora_main_test
// 版本 20160804
// 测试品种 通用
// 周期 通用(默认15分钟周期)
// 作者 西门吹雪(QQ:149561420)
//------------------------------------------------------------------------

Params

Vars
    NumericArray arr_high;                      //高点的索引组成的数组
    NumericArray arr_low;                       //低点的索引组成的数组
    NumericSeries trend_line_up1;               //趋势线上轨“点1”
    NumericSeries trend_line_up2;               //趋势线上轨“点2”
    NumericSeries trend_line_down1;             //趋势线下轨“点1”
    NumericSeries trend_line_down2;             //趋势线下轨“点2”

Begin
    Pandora_getHighTrendLine(arr_high, CurrentBar - 200);
    trend_line_up1 = arr_high[0];
    trend_line_up2 = arr_high[1];
    Commentary("trend_line_up1:" + Text(trend_line_up1));
    Commentary("trend_line_up2:" + Text(trend_line_up2));

    Pandora_getLowTrendLine(arr_low, CurrentBar - 200);
    trend_line_down1 = arr_low[0];
    trend_line_down2 = arr_low[1];
    Commentary("trend_line_down1:" + Text(trend_line_down1));
    Commentary("trend_line_down2:" + Text(trend_line_down2));

    Commentary("CurrentBar:" + Text(CurrentBar));
End