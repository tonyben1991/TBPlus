/****************************************************************************************
            > 文件: ASI_Tony
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-09-30-14.43

            > 策略原理:
               	1.
            > 测试品种:
                1.
            > 适用周期:
                1. 日线
            > 参数列表:
                1.
****************************************************************************************/

Params


Vars
	Numeric A;
	Numeric B;
	Numeric C;
	Numeric D;
	Numeric R;
	Numeric X;
	NumericSeries SIValue(0);
Begin
	A = Abs(High - Close[1]);
	B = Abs(Low - Close[1]);
	C = Abs(High - Low[1]);
	D = Abs(Close[1] - Open[1]);
	if (A > B && A > C)
	{
		R = A - B * 0.5 + D * 0.25;
	}
	else if ( B > C && B > A)
    {
        R = B - A * 0.5 + D * 0.25;
    }
    else
    {
        R = C + D * 0.25;
    }
	X = (Close -Close[1]) + 0.25*(Close[1] - Open[1]) + 0.5 * (Close - Open);
	If(R != 0)
	{
	    SIValue = 50 * X/R * IIF(A > B, A, B);
	}
	PlotNumeric("ASI",Cum(SIValue));    //求累计值
End
