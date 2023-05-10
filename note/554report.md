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

