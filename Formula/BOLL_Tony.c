/****************************************************************************************
            > 文件:
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-09-30-14.56

            > 策略原理:
               	1.
            > 测试品种:
                1.
            > 适用周期:
                1.
            > 参数列表:
                1.
****************************************************************************************/

Params
	Numeric Length(20);
	Numeric Offset(2);

Vars
	Numeric UpLine;		    //上轨
	Numeric DownLine;		//下轨
	NumericSeries MidLine;	//中间线
	Numeric Band;           //宽度

Begin
	MidLine = AverageFC(Close,Length);
	Band = StandardDev(Close,Length,2);
	UpLine = MidLine + Offset * Band;
	DownLine = MidLine - Offset * Band;
	PlotNumeric("UpLine",UpLine);
	PlotNumeric("DownLine",DownLine);
	PlotNumeric("MidLine",MidLine);

End
