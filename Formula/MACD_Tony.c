/****************************************************************************************
            > 文件: MACD_Tony     指数平滑异同平均线
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-09-28-09.10

            > 策略原理:
               	1. DIF、DEA均为正，DIF向上突破DEA，买入信号参考。
                2. DIF、DEA均为负，DIF向下跌破DEA，卖出信号参考。
                3. DIF线与K线发生背离，行情可能出现反转信号。
                4. DIF、DEA的值从正数变成负数，或者从负数变成正数并不是交易信号，因为它们落后于市场。
                5. 当价格出现新高,但是DEA没能突破前高时,离场
            > 测试品种:
                1. 螺纹钢指数
            > 适用周期:
                1. 1h
            > 参数列表:
                1. 12 26 9 6 2
****************************************************************************************/

Params
    Numeric ShortLength(12);
    Numeric LongtLength(26);
    Numeric MACDLength(9);
    Numeric TrailLength(6);
    Numeric Filter(2);          //过滤值,当MACD过小时,价格波动,不进行买入的判断
    Numeric OffsetRatio(0);     //判断条件的偏移率 100 -> 100%
Vars
    NumericSeries DIF;      //MACDLine
    NumericSeries DEA;      //SignalLine
    NumericSeries MACD;     //DIF - DEA
    BoolSeries AfterSell(False);
    BoolSeries AfterBuyToCover(False);

Begin
    if (!CallAuctionFilter)
    {
        return;
    }

	Commentary("Bar:" + Text(CurrentBar));

    DIF = XAverage(Close, ShortLength) - XAverage(Close, LongtLength) ;
    DEA = XAverage(DIF, MACDLength);
    MACD = (DIF - DEA);

    PlotNumeric("DIF", DIF);
    PlotNumeric("DEA", DEA);

    if (MACD >= 0)
    {
        PlotNumeric("MACD", MACD, 0, Red);
    }
    else
    {
        PlotNumeric("MACD", MACD, 0, Green);
    }
    PlotNumeric("零线", 0);




    if (ABS(MACD) > Filter) //当MACD过小时,价格波动,不进行买入的判断
    {
        if (0 == MarketPosition)
        {
            if (!AfterSell && (DIF > 0 && DEA > 0) && MACD > 0)
            {
                Buy(0, High);
                AfterSell = False;
                AfterBuyToCover = False;
            }

            if (!AfterBuyToCover && (DIF < 0 && DEA < 0) && MACD < 0)
            {
                SellShort(0, Low);
                AfterSell = False;
                AfterBuyToCover = False;
            }

        }
    }




    if (1 == MarketPosition)
    {
        if (High > EntryPrice + 350)
        {
            Sell(0, Low);
            Commentary("止盈");
            PlotBool("T", False);
        }
        if (Low < EntryPrice - 200)
        {
            Sell(0, Low);
            AfterSell = True;
            Commentary("止损");
        }
        if (BarsSinceEntry > ShortLength
            && High > High[CurrentBar - FindTop_Tony(High, BarsSinceEntry + ShortLength)]
            && DEA[CurrentBar - FindTop_Tony(DEA, BarsSinceEntry + ShortLength)] > DEA)
        {
            Sell(0, Low);
            AfterSell = True;
            Commentary("背离");
        }
        if (DIF < 0 && DEA < 0)
        {
            Sell(0, Low);
            AfterSell = True;
        }
    }

    if (-1 == MarketPosition)
    {
        if (Low < EntryPrice - 350)
        {
            BuyToCover(0, High);
            Commentary("止盈");
            PlotBool("T", False);
        }
        if (High > EntryPrice + 200)
        {
            BuyToCover(0, High);
            AfterBuyToCover = True;
            Commentary("止损");
        }
        if (BarsSinceEntry > LongtLength
            && Low < Low[CurrentBar - FindBottom_Tony(Low, BarsSinceEntry)]
            && Low[CurrentBar - FindBottom_Tony(DEA, BarsSinceEntry)] < DEA)
        {
            BuyToCover(0, High);
            AfterBuyToCover = True;
        }
        if (DIF > 0 && DEA > 0)
        {
            BuyToCover(0, High);
            AfterBuyToCover = True;
        }
    }

End
