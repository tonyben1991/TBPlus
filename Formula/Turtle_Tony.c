/****************************************************************************************
            > 文件: Turtle_Tony  海龟交易系统
            > 作者: Tony Ben
            > 电子邮箱: tonyben1991@outlook.com
            > 创建时间: 2016-09-27 09:38

            > 策略原理:
                1. 根据一段时间的ATR计算系数N,由当前可用资金和N,计算出每单数量
                2. 分别绘制出长短两个不同周期的唐奇安通道,当价格突破上轨时做多,
                价格突破下轨时做空(长短两个系统分别操作).
                3. 根据跟踪周期的最高价和最低价确定离场突破价格.在有多仓的情况下,
                如果价格突破最低离场价格,进行平仓.
                4. 如果开盘时有多单且价格涨幅超过N/2,进行加仓.当最高价涨幅超过N/2,
                以N/2的价格步进持续加仓.
                5.当价格下跌超过2N时,平仓离场.
                6. 有空单的情况下,依照3~5相对应的方法进行操作.
            > 测试品种:
                1. 螺纹钢指数
            > 适用周期:
                1. 15分钟
            > 参数列表:
                1. 1 12 20 66 6
****************************************************************************************/

Params
    Numeric RiskRatio(1);               //风险率(1-100),也就是资金使用率
    Numeric ATRLen(20);                 //平均真实波动周期
    Numeric ShortLen(20);               //短周期
    Numeric LongLen(56);                //长周期
    Numeric TrailLen(10);               //跟踪周期

Vars
    NumericSeries ATR;                  //平均真实波动
    Numeric N;                          //N值
    Numeric MinPoint;                   //最小变动量
    Numeric TotalEquity;                //可用资金
    Numeric TradeUnits;                 // 交易单位
    Numeric SDonchianH;                 //短周期唐奇安通道上轨
    Numeric SDonchianL;                 //短周期唐奇安通道下轨
    Numeric LDonchianH;                 //长周期唐奇安通道上轨
    Numeric LdonchianL;                 //长周期唐奇安通道下轨
    Numeric LowestExitPrice;            //最低离市价格
    Numeric HighestExitPrice;           //最高离市价格
    Numeric myEntryPrice;               // 开仓价格
    Numeric PreEntryPrice;              // 前一次开仓的价格
    Numeric myExitPrice;                // 平仓价格
    Bool TradeThisBar(False);           // 当前Bar是否有过交易


Begin
    //开始运行,初始化
    if (0 == BarStatus)
    {
        PreEntryPrice = 0;
    }

    if (!CallAuctionFilter)
    {
        return;
    }

    MinPoint = MinMove * PriceScale;
    ATR = Average(TrueRange, ATRLen);
    N = ATR[1];
    TotalEquity = Portfolio_CurrentCapital();   //获得当前的可用资金，已考虑交易费用
    TradeUnits = IntPart((TotalEquity * RiskRatio / 100) / (N * ContractUnit() * BigPointValue()));
                                                           /*当前商品每张合约包含的基本单位数量*//*当前商品一个整数点的价值*/

    SDonchianH = Highest(High[1], ShortLen);    //短周期唐奇安通道上轨
    SDonchianL = Lowest(Low[1], ShortLen);      //短周期唐奇安通道下轨

    LDonchianH = Highest(High[1], LongLen);     //长周期唐奇安通道上轨
    LdonchianL = Lowest(Low[1], LongLen);       //长周期唐奇安通道下轨

    HighestExitPrice = Highest(High[1], TrailLen);
    LowestExitPrice = Lowest(Low[1], TrailLen);

    //短周期突破开场
    if (0 == MarketPosition)
    {
        //做多
        if (High > SDonchianH && TradeUnits >= 1)
        {
            myEntryPrice = Max(Open, Min(High, SDonchianH + MinPoint));
            PreEntryPrice = myEntryPrice;
            Buy(TradeUnits, myEntryPrice);
            TradeThisBar = True;
        }

        //做空
        if (Low < SDonchianL && TradeUnits >= 1)
        {
            myEntryPrice = Min(Open, Max(Low, SDonchianL - MinPoint));
            PreEntryPrice = myEntryPrice;
            SellShort(TradeUnits, myEntryPrice);
            TradeThisBar = True;
        }
    }

    //长周期突破开仓
    if (0 == MarketPosition)
    {
        //做多
        if (High > LDonchianH && TradeUnits >= 1)
        {
            myEntryPrice = Max(Open, Min(High, LDonchianH + MinPoint));
            PreEntryPrice = myEntryPrice;
            Buy(TradeUnits, myEntryPrice);
            TradeThisBar = True;
        }

        //做空
        if (Low < LDonchianL && TradeUnits >= 1)
        {
            myEntryPrice = Min(Open, Max(Low, LDonchianl - MinPoint));
            PreEntryPrice = myEntryPrice;
            SellShort(TradeUnits, myEntryPrice);
            TradeThisBar = True;
        }
    }


    //平仓
    //有多仓的情况
    if (1 == MarketPosition)
    {
        if (Low < LowestExitPrice)      //止损
        {
            myExitPrice = Min(Open, Max(Low, LowestExitPrice - MinPoint));
            Sell(0, myExitPrice);       //平掉所有持仓
        }
        //
        else
        {
            if (0 != PreEntryPrice && TradeUnits >= 1)     //判断是否已经进场
            {
                if (Open >= PreEntryPrice + N * 0.5)        //判断是否增仓
                {
                    myEntryPrice  = Open;
                    PreEntryPrice = myEntryPrice;
                    Buy(TradeUnits, myEntryPrice);
                    TradeThisBar = True;
                }
                while (High >= PreEntryPrice + N * 0.5)     //以最高价为标准,判断增仓次数
                {
                     myEntryPrice = myEntryPrice + N * 0.5;
                     PreEntryPrice = myEntryPrice;
                     Buy(TradeUnits, myEntryPrice);
                     TradeThisBar = True;
                }
            }

            //止损
            if (Low <= PreEntryPrice - N * 2 && False == TradeThisBar/*加仓Bar不止损*/)
            {
                myExitPrice = PreEntryPrice - N * 2;
                Sell(0, myExitPrice);
            }
        }
    }
    //有空仓的情况
    else if(-1 == MarketPosition)
    {
        if (High > HighestExitPrice)    //止损
        {
            myExitPrice = Max(Open, Min(High, myExitPrice + MinPoint));
            BuyToCover(0, myExitPrice);
        }
        //
        else
        {
            if (0 != PreEntryPrice && TradeUnits >= 1) //判断是否已经进场
            {
                if (Open <= PreEntryPrice - N * 0.5)    //判断是否增仓
                {
                    myEntryPrice = PreEntryPrice - N * 0.5;
                    PreEntryPrice = myEntryPrice;
                    SellShort(TradeUnits, myEntryPrice);
                    TradeThisBar = True;
                }
                while (Low <= PreEntryPrice - N * 2 && False == TradeThisBar)   //以最低价判断增仓次数
                {
                    myEntryPrice = PreEntryPrice - N * 0.5;
                    PreEntryPrice = myEntryPrice;
                    SellShort(TradeUnits, myEntryPrice);
                    TradeThisBar = True;
                }
            }

            if (High >= PreEntryPrice + N * 2 && False == TradeThisBar)  //加仓Bar不止损
            {
                myExitPrice = PreEntryPrice + N * 2;
                BuyToCover(0, myExitPrice);
            }
        }

    }

End
