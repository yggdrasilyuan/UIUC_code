## indicators
我们从行业层面的量价数据入手，根据量价因子的本质含义对其进行归类，将量价因子分为动量、交易波动、换手率、多空对比、量价背离、量幅同向六大类。我们对这六大类中的量价因子进行单因子测试，最终得到了 11 个较为有效、逻辑性强的
月频行业因子。
### 动量因子
动量因子是一种基于历史价格走势的投资策略，它认为资产的过去表现对未来表现有预测作用。投资者利用动量因子来确定哪些资产可能会在未来继续表现优异，从而实现投资收益。
#### 二阶动量
动量是价格的一阶函数，我们用最新一期动量减去过去的动量 ，可得动量间的差值，即价格的二阶函数 。 二阶动量 可以理解为 动量的改善情况 我们对过去一段时间window 的二阶动量进行了指数加权移动平均，因子公式：
$$EWMA(\frac{Close_{t}-mean(Close_{t-window_{1:t}})}{mean(Close_{t-window_{1:t}})}-delay(\frac{Close_{t}-mean(Close_{t-window1:t})}{mean(Close_{t-window1:t})},window2),window)$$
#### 动量期限差
长期动量越高体现了较好的动量持续性与筹码量的堆砌，而短期动量越高通常代表着较为拥挤的赛道。 动量期限差，即长期动量减去短期动量 。该因子值越高可以理解为在长期向上趋势明显的行业中剔除了近日较为拥挤的行业。因子公式为
$$\frac{Close_{t}-Close_{t-window1}}{Close_{t-window_{1}}}-\frac{Close_{t}-Close_{t-window_{2}}}{Close_{t-window2}}$$,window1>window2

### 交易波动因子
本节我们只考虑交易量数据，分别介绍成交金额波动因子和成交量波动因子。我们用交易量的标准差反映近期行业的成交波动情况，波动越小说明市场情绪越稳定。
#### 成交金额波动
我们用过去一段时间的成交金额标准差来衡量行业交易情况的稳定程度，并取相反数，波动率最小组为因子值最大组，波动率最大组为因子值最小组。
$$-STD(Amount)$$
#### 成交量波动
成交量波动即过去一段时间成交量标准差的相反数，同样的波动率最小组为因子值最大组，波动率最大组为因子值最小组 ，这个因子代表着做多市场情绪稳定的行业
$$-STD(Volume)$$

### 换手率因子
在只考虑行业换手率数据的情况下单一期限的换手率均值在行业上的区分度并不明显，因此我们尝试了用长期换手率与短期换手 率相除，得到换手率短期相对于长期的变化情况
#### 换手率变化
我们用长期换手率均值除以短期换手率均值，因子值越大，说明短期换手率相对于长期较低，市场预期较为一致 ；因子值越小说明短期相对于长期换手更加活跃市场分歧较大：
$$\frac{Mean(turnover_{t-window_{1:t}})}{Mean(turnover_{t-window_{2:t}})},window1>window2$$

### 多空对比因子
把行业指数每日收盘价与最低价的差值看作是多头力量、每日最高价与收盘价的差值看作是空头力量，那么最高价与最低价之间 就是多空力量制衡的值域 。 我们根据指数日频的价格信息构建多空对比因子。
#### 多空对比总量
我们计算过去一段时间内每日多空力量对比即多头力量与空头力量的比值并求和。多空对比总量越大，说明这段时间内多头力量相对于空头力量更强势多空对比总量越小，说明这段时间内空头力量较多头力量更加强势 。这里我们取因子值的相反数，也就是做多过去空头力量较强的行业，这本质上是一个反转因子。
$$-\sum^{i=t}_{i=t-window}\frac{Close_{i}-Low_{i}}{Hight_{i}-Close_{i}}$$
#### 多空对比变化
首先计算多空力量对比。分子我们用多头力量与空头力量相减，即(𝐶𝑙𝑜𝑠𝑒−𝐿𝑜𝑤)−(𝐻𝑖𝑔ℎ−𝐶𝑙𝑜𝑠𝑒)，分母为最高价减去最低价 也就是日内价格区间的极值。再将所得多空力量对比乘上当日行业成交量，可得当日多空力量对比的金额绝对值。我们用长期每日多空力量对比的指数加权平均值，减去短期每日多空力量对比的指数加权平均值，可以得到近期多空力量对比相对于长期多空力量对比均值的变化。因子值越大，说明近期多头相对于空头力量减弱；因子值越小，说明近期多空对比度相对于长期加大
$$EWMA(Volume*\frac{(Close-Low)-(High-Close)}{High-Low},window_{1})-EWNA(Volume*\frac{(Close-Low)-(High-Close)}{High-Low},window_{2})window_1>window_2$$

### 量价背离因子
量价背离，是一种技术分析指标，用于衡量股票或其他金融资产的价格与成交量之间的背离程度。它可以帮助投资者识别市场中的趋势反转信号，从而在交易中获取潜在的盈利机会。即过去一段时间内成交量上升、价格下降，或成交量下降，价格上升。量价背离程度越高，超额收益增加的概率越大。
#### 量价排序协方差
我们把量价背离定义为过去一段时间内收盘价与成交量排序的协方差的相反数。
我们也可以把用于计算协方差的价格替换为开盘价或最高价 ，二者因子值最大组行业组合的超额收益走势都呈明显向上趋势。
$$-rank\{covariance[rank(Close),rank(Volume),window]\}$$
#### 量价相关系数
这里把量价背离定义为过去一段时间内成交量与收盘价相关系数的相反数
$$-correlation(Close,Volume,window)$$
#### 一阶量价背离
成交量的一阶变化是今日成交量相对于昨日成交量的变化 ，价格的一阶变化是涨跌幅。一阶量价背离，即成交量和价格各自一阶变化的背离程度。 因子值越大，说明成交量增加速度加快、涨跌幅下降或成交量减少速度加快，涨跌幅提升。
$$-correlation[Rank(\frac{Volume_{i}}{Volume_{i-1}}-1),Rank(\frac{Close_{i}}{Open_{i}}-1),window]$$

### 量幅同向因子
量幅同向因子，即成交量变化的幅度和价格变化幅度同向变化。因子值越大，说明成交量扩大速度加快、最高价与最低价距离拓宽，或成交量减少速度加快，最高价与最低价距离缩小。
$$correlation[Rank(\frac{Volume_{i}}{Volume_{i-1}}-1),Rank(\frac{High_{i}}{Low_{i}}-1),window]$$

## indicators
Starting from the industry-level volume and price data, we categorized the volume and price factors into six categories: momentum, trading volatility, turnover rate, long-short comparison, volume divergence, and volume and amplitude convergence. We conducted single-factor tests on the quantitative factors in these six categories, and finally obtained 11 more effective and logical
Monthly frequency industry factors.
### Momentum Factor
A momentum factor is an investment strategy based on historical price movements, which assumes that an asset's past performance is predictive of future performance. Investors use momentum factors to determine which assets are likely to continue to outperform in the future and thus realize investment returns.
#### second-order momentum
Momentum is a first-order function of price. We subtract past momentum from the latest period of momentum to obtain the difference between momentum, which is a second-order function of price. Second-order momentum can be interpreted as the improvement in momentum We performed an exponentially weighted moving average of the second-order momentum of the window over the past period, with the factor formula
$$EWMA(\frac{Close_{t}-mean(Close_{t-window_{1:t}})}{mean(Close_{t-window_{1:t}})}-delay(\frac{Close_{t}-mean(Close_{t-window1:t}) }{mean(Close_{t-window1:t})},window2),window)$$
#### Momentum term difference
Higher long-term momentum reflects better momentum persistence and stacking of chip volume, while higher short-term momentum usually represents a more crowded circuit. Momentum duration difference, i.e. long-term momentum minus short-term momentum. A higher value of this factor can be interpreted as the removal of the more crowded sectors in recent days from those with a clear long-term upward trend. The factor formula is
$$\frac{Close_{t}-Close_{t-window1}}{Close_{t-window_{1}}}-\\frac{Close_{t}-Close_{t-window_{2}}}{Close_{t-window2}}$$,window1> window2

### Trading volatility factor
In this section, we only consider the trading volume data and introduce the trading amount volatility factor and volume volatility factor respectively. We use the standard deviation of trading volume to reflect the recent trading volatility of the industry, the smaller the volatility the more stable the market sentiment.
#### Volume Volatility
We use the standard deviation of turnover amount in the past period to measure the stability of the industry trading situation and take the opposite number. The group with the highest volatility is the group with the highest factor value.
$$-STD(Amount)$$
#### Volume Volatility
Volume volatility is the opposite of the standard deviation of volume in the past period, the same volatility of the largest group for the largest group of factors, volatility of the largest group for the largest group of factors, this factor represents the long market sentiment stable industry
$$-STD(Volume)$$

### Changing hands factor
In the case of considering only the industry turnover data the mean value of the turnover rate for a single period is not clearly distinguishable in the industry, so we tried to divide the long-term turnover rate with the short-term turnover rate to get the short-term change in the turnover rate relative to the long-term change
#### Change in turnover rate
We divide the average long-term turnover rate by the average short-term turnover rate. The larger the factor, the lower the short-term turnover rate relative to the long-term, the more consistent the market expectation; the smaller the factor, the more active the short-term turnover relative to the long-term market divergence:
$$\frac{Mean(turnover_{t-window_{1:t}})}{Mean(turnover_{t-window_{2:t}})},window1>window2$$

### Long-short comparison factor
If we consider the difference between the daily closing price and the lowest price of the industry index as the long force and the difference between the daily highest price and the closing price as the short force, then the range between the highest price and the lowest price is the value of the long/short force balance. We construct the long-short comparison factor based on the daily frequency price information of the index.
#### Total Long-Short Contrast
We calculate the daily long/short power comparison over time, i.e. the ratio of long to short power, and sum it up. The larger the total long/short comparison, the stronger the long power is compared to the short power during the period. The smaller the total long/short comparison, the stronger the short power is compared to the long power during the period. Here we take the opposite of the factor value, which is to go long the sectors where short forces were stronger in the past, which is essentially a reversal factor.
$$-\sum^{i=t}_{i=t-window}\frac{Close_{i}-Low_{i}}{Hight_{i}-Close_{i}}$$
#### Long-short contrast change
First calculate the long-short power contrast. For the numerator we subtract the long power from the short power, i.e. (𝐶𝑙𝑜𝑠𝑒 - 𝐿𝑜𝑤) -(𝐻𝑖𝑔ℎ-𝐶𝑙𝑜𝑠𝑒) and the denominator is the highest price minus the the minimum price which is the extreme value of the intra-day price range. The resulting long-short power comparison is then multiplied by the industry volume for the day to obtain the absolute value of the amount of the long-short power comparison for the day. We subtract the exponentially weighted average of the long-term daily long-short power comparison from the exponentially weighted average of the short-term daily long-short power comparison to obtain the change in the recent long-short power comparison relative to the long-term long-short power comparison average. The larger the factor value, the weaker the recent long relative to short strength; the smaller the factor value, the greater the recent long-short contrast relative to the long-term
$$EWMA(Volume*\frac{(Close-Low)-(High-Close)}{High-Low},window_{1})-EWNA(Volume*\frac{(Close-Low)-(High-Close)}{High-Low},window_{ 2}),window_1>window_2$$

### Volume Divergence Factor
Volume Divergence, a technical analysis indicator, is used to measure the degree of divergence between the price and volume of a stock or other financial asset. It can help investors identify trend reversal signals in the market and thus capture potential profit opportunities in trading. That is, a period of time in the past when volume was up and price was down, or volume was down and price was up. The higher the degree of volume divergence, the greater the probability of increased excess returns.
#### Volume Price Sorting Covariance
We define volume divergence as the opposite of the covariance of the closing price and volume ranking over the past period.
We can also replace the price used to calculate the covariance with the opening price or the highest price , both of which have a significant upward trend in the excess return trend of the industry portfolio in the largest group of factor values.
$$-rank\{covariance[rank(Close),rank(Volume),window]\}$$
#### Volume and price correlation coefficients
Here, volume divergence is defined as the opposite of the correlation coefficient between volume and closing price over the past period
$$-correlation(Close,Volume,window)$$
#### First Order Volume Divergence
The first-order change in volume is the change in today's volume relative to yesterday's volume , and the first-order change in price is the increase or decrease. First-order volume divergence is the degree of divergence between the respective first-order changes in volume and price. The larger the factor value, the faster the volume increases and the rate of increase/decrease decreases or the faster the volume decreases and the rate of increase/decrease increases.
$$-correlation[Rank(\frac{Volume_{i}}{Volume_{i-1}}-1),Rank(\frac{Close_{i}}{Open_{i}}-1),window]$$

### Volume isotropy factor
Volume and amplitude isotropic factor, i.e., the magnitude of volume change and price change in the same direction. The higher the value of the factor, the faster the volume expansion and the widening of the distance between the highest and lowest prices, or the faster the volume decrease and the narrowing of the distance between the highest and lowest prices.
$$correlation[Rank(\frac{Volume_{i}}{Volume_{i-1}}-1),Rank(\frac{High_{i}}{Low_{i}}-1),window]$$


For the above categories of factors we will make a summary

|big category factor|factor name|calculation formula|
|--|--|--|
|momentum|second-order momentum|$EWMA(\frac{Close_{t}-mean(Close_{t-window_{1:t}})}{mean(Close_{t-window_{1:t}})}-delay(\frac{Close_{t}-mean(Close_{t- window1:t})}{mean(Close_{t-window1:t})},window2),window)$|
|momentum|momentum term difference|$\frac{Close_{t}-Close_{t-window1}}{Close_{t-window_{1}}}-\frac{Close_{t}-Close_{t-window_{2}}}{Close_{t-window2}}$. window1>window2|
|Volatility|Volume Fluctuation|$-STD(Amount)$|
|volatility|volume fluctuation|$-STD(Volume)$|
|Volatility|Volume Change|$-STD(Volume)$|| \frac{Mean(turnover_{t-window_{1:t}})}{Mean(turnover_{t-window_{2:t}})}$,window1>window2|
|Multiple comparison|Multiple comparison total|$-\sum^{i=t}_{i=t-window}\frac{Close_{i}-Low_{i}}{Hight_{i}-Close_{i}}$|
|Multiple comparison|Multiple comparison change|$EWMA(Volume*\frac{(Close-Low)-(High-Close)}{High-Low},window_{1})-EWNA(Volume*\frac{(Close-Low)-(High-Close)}{High- Low},window_{2})$,$window_1>window_2$|
|volume-price divergence|volume-price divergence covariance(close)|$-rank\{covariance[rank(Close),rank(Volume),window]\}$|
|volume-price divergence|volume-price correlation(close)|$-correlation(Close,Volume,window)$|
|volume divergence|first-order volume divergence|$-correlation[Rank(\frac{Volume_{i}}{Volume_{i-1}}-1),Rank(\frac{Close_{i}}{Open_{i}}-1),window]$|
|volume-amplitude isotropy|volume-amplitude isotropy|$correlation[Rank(\frac{Volume_{i}}{Volume_{i-1}}-1),Rank(\frac{High_{i}}{Low_{i}}-1),window]$|

Since the specific window parameters were not given in the study. Therefore, the common window periods of 5, 10, 20, 60, 120, and 180 were used to construct the factors again, and a total of 192 factors were generated.

## Metrics
我们使用的Metrics 包括了年化收益率，累计收益率，波动率，夏普，最大回撤，索提诺比率，calmar这些指标，下面我将详细描述这些指标的含义
- 年化收益率，定义是指把当前收益率(日收益率、周收益率、月收益率)换算成年收益率来计算的，它是一种理论收益率，并不是真正的已取得的收益率。
年化收益率 =  ((单位净值(现在) / 单位净值(成立日)) ^ (1 / 存续年数) - 1) * 100%
- 累计收益率，是指基金从成立开始至今天的累计收益比率，衡量基金成立以来的累计收益情况。
累计收益率 = (单位净值(现在) / 单位净值(成立日) - 1) * 100%
- 波动率，是金融资产价格的波动程度，是对资产收益率不确定性的衡量，用于反映金融资产的风险水平。但由于波动率具多样性，本文中所用波动率特指历史波动率，是指投资回报率在过去一段时间内所表现出的波动率，它由标的资产市场价格过去一段时间的历史数据（即St的时间序列资料）反映。
- 夏普比率，定义是投资收益与无风险收益之差的期望值，再除以投资标准差（即其波动性）。它代表投资者额外承受的每一单位风险所获得的额外收益。
夏普比率 = 超额收益/标准差(风险)
- 最大回撤，指在选定周期内任一历史时点往后推，产品净值走到最低点时的收益率回撤幅度的最大值，用来描述买入产品后可能出现的最糟糕的情况。最大回撤是一个重要的风险指标，对于对冲基金和数量化策略交易，该指标比波动率还重要。
- 索提诺比率，是一种衡量投资组合相对表现的方法。与夏普比率有相似之处，但索提诺比率运用下偏标准差而不是总标准差，以区别不利和有利的波动。和夏普比率类似，这一比率越高，表明基金承担相同单位下行风险能获得更高的超额回报率。索提诺比率可以看做是夏普比率在衡量对冲基金/私募基金时的一种修正方式。
- calmar 描述的是收益和最大回撤之间的关系。计算方式为年化收益率与历史最大回撤之间的比率。Calmar比率数值越大，基金的业绩表现越好。反之，基金的业绩表现越差。
卡玛比率 = 超额收益/最大回撤(风险)

The Metrics we use include annualized return, cumulative return, volatility, Sharpe, maximum retracement, Sortino ratio, and calmar, and I will describe the meaning of these indicators in detail below
- Annualized rate of return, defined as the current rate of return (daily, weekly, monthly) converted into an annualized rate of return, is a theoretical rate of return, not a true achieved rate of return.
Annualized yield = ((Net unit value (now) / Net unit value (inception date)) ^ (1 / number of years of existence) - 1) * 100%
- Cumulative return, which is the ratio of the fund's cumulative return from inception to today, measures the fund's cumulative return since inception.
Cumulative Return = (Net Unit Value (Now) / Net Unit Value (Inception Date) - 1) * 100%
- Volatility, which is the degree of volatility in the price of a financial asset, is a measure of the uncertainty of asset returns and is used to reflect the level of risk of a financial asset. However, due to the diversity of volatility, volatility used in this article refers to historical volatility, which refers to the volatility of investment returns over time, as reflected by historical data (i.e. time series information of St) of the underlying asset market price over time.
- Sharpe ratio, defined as the expected value of the difference between investment return and risk-free return, divided by the standard deviation of the investment (i.e. its volatility). It represents the additional return per unit of risk taken by the investor.
Sharpe ratio = excess return/standard deviation (risk)
- Maximum retracement, the maximum value of the return retracement when the net value of the product goes to its lowest point at any historical point backward in the selected period, is used to describe the worst-case scenario that can occur after buying the product. Maximum retracement is an important risk metric that is more important than volatility for hedge funds and quantitative strategy trading.
- The Sortino ratio, a measure of relative portfolio performance. There are similarities to the Sharpe ratio, but the Sortino ratio applies the lower bias standard deviation rather than the total standard deviation to distinguish between unfavorable and favorable volatility. Similar to the Sharpe ratio, a higher ratio indicates that a fund can achieve a higher excess return for the same unit of downside risk. The Sortino ratio can be seen as a modification of the Sharpe ratio when measuring hedge funds/private equity funds.
- The calmar describes the relationship between returns and maximum retracements. It is calculated as the ratio between the annualized return and the historical maximum retracement. the higher the value of the calmar ratio, the better the fund's performance. Conversely, the worse the fund's performance.
Calmar Ratio = Excess Return/Maximum Retracement (Risk)

这些指标的实现过程主要依赖了hugo toolkit提供的backtest工具，其中的