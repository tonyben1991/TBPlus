/*******************************************************************************
            > 文件: RSI_Tony 相对强强弱指标
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-10-08-09.15

            > 策略原理:
               	1.
            > 测试品种:
                1.
            > 适用周期:
                1.
            > 参数列表:
                1.
*******************************************************************************/

Params
	Numeric Length(14) ;
	Numeric OverSold(30) ;
	Numeric OverBought(70) ;

Vars
	NumericSeries A(0);
	NumericSeries B(0);
    Numeric RS;
	Numeric RSI;

Begin
    A = Average(Max(0, Close - Close[1]), Length);        	//周期内上涨收市价的平均值
    B = Average(Max(0, -1 * (Close - Close[1])), Length);	//周期内下跌收市价的平均值
    RS = A / B;
    RSI = 100 - (100 / (1 + RS));
    PlotNumeric("RSI", RSI);
    PlotNumeric("超买",OverBought);
    PlotNumeric("超卖",OverSold);

End
