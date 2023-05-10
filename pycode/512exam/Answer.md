#### I pledge that I have not received assistance from anyone in preparing this exam. 
#### Zeyuan Pan


## Question 1

### Answer
According to the question, we can know that: $f=f(\rho_t), \rho_t=\rho(\sigma_t^M,\sigma_t^S), \sigma_t^S=\sigma_t^S(\sigma_t^I,\sigma_t^M)$

So we can also learn that $df=\frac{\partial f}{\partial t}*dt+\frac{\partial f}{\partial \sigma^I}*d\sigma^I+\frac{1}{2}*\frac{\partial^2 f}{\partial\sigma^2}(d\sigma_t^I)^2*\frac{\partial f}{\partial \sigma^M}d\sigma^M+\frac{\partial^2 f}{2 \partial\sigma^{M^2}}d\sigma^{M^2}+\rho\frac{\partial^2 f}{\partial \sigma^2\sigma^M}d\sigma^2d\sigma^M$

Since the two factors are independent, so their correlation is 0 which $\rho=0$

$$\therefore df=\frac{\partial f}{\partial t}*dt+\frac{\partial f}{\partial \sigma^I}*K^I(\bar{\sigma^I}-\sigma_t^I)dt+b^I\sigma_t^IdW3_t+\frac{1}{2}*b^{I^2}\sigma_t^{I^2}\frac{\partial^2 f}{\partial\sigma^2}dW3_t^2+\frac{\partial f}{\partial \sigma^M}K^M(\bar{\sigma^M}-\sigma_t^M)dt+b^M\sigma_t^MdW4_t+\frac{1}{2}b^{M^2}\sigma^{M^2}_t\frac{\partial^2 f}{\partial\sigma^{M^2}}dW4^2_t$$

And based on stochastic calculus, we can know that:
$$E(dW3_t)=E(dW4_t)=0,E(dW3_t^2)=E(dW4_t^2)=dt$$

Under the risk neutral condition:
$$E(df)=2fdt$$

So we get our answer:
$$\therefore rf=\frac{\partial f}{\partial t}+K^I(\bar{\sigma^I}-\sigma_t^I)\frac{\partial f}{\partial \sigma^2}+\frac{1}{2}b^{I^2}\sigma_t^{I^2}\frac{\partial^2 f}{\partial {\sigma_t^I}^2}+K^M(\bar{\sigma^M}-\sigma_t^M)+\frac{1}{2}b^{M^2}\sigma_t^{M^2}\frac{\partial^2 f}{\partial \sigma_t^{M^2}}$$

## Question 2 
### Question 2.1
As we know the params like $\mu^S=\mu^M=0, K^I=K^M=2$ and so on. Given these conditions I can use the previous $dS^M$ and $dS_{t=0}$ to calculate the new values of $S^M$ and $S_{t=\Delta t}$, which means we can also use these params to update $\sigma^I_t, \sigma^M_t$

There are following equations are used to update values:
$$V_t^S=\sigma^I_t*dW1_t+\sigma _t^M*dW2_t,\ V_t^M=\sigma_t^M*dW2_t\\
\\ d\sigma^I_t=2*(0.25-\sigma^I_t)dt+0.5*\sigma^I_tdW3_t\\
\\ d\sigma^M_t=2*(0.25-\sigma^M_t)dt+0.5*\sigma^M_tdW4_t\\
\\ \sigma^I_{t+1}=\sigma^I_t+d\sigma^I_t,\ \sigma^M_{t+1}=\sigma^M_t+d\sigma^M_t$$

### Question 2.2
So using python we can calculate the results of these three parts and I picked first ten of the array to show my result and each of them are reserved four decimal places:
part A Answer: [ 0.0176 -0.0111 -0.0356 -0.0077 -0.0311 -0.0229 -0.0258  0.0101  0.02  0.0267]
part B Answer: [0.5156 0.4679 0.4567 0.4599 0.5092 0.4892 0.4564 0.4982 0.6012 0.5794]
part C Answer: [0.0027 0.0024 0.0024 0.0022 0.0025 0.0025 0.0023 0.0025 0.0032 0.003 ]

### Question 2.3
And Here are the scatter plots
![answer2.3](./final/1.png)

#### *Q&A:*
- What is the breakeven correlation for the trade?
The breakeven correlation for the trade is the return which is equal to 0. And get the average of true correlation and realized sample correlation is shown below. And I choose the true correlation value as breakeven correlation which is 0.5041475659362336. 
- If you do the trade for a notional amount of $10 million, how much do you make or lose if correlation is 0.10 higher/lower than the breakeven value?
If trade 0.1 higher than breakeven value, you can make 398074.0502668916 profit
if lower 0.1 than breakeven value it will lose 682074.9049327854


### Question 3
Here are the plots of the time series realizations
![answer3](./final/2.png)

#### *Q&A:*
- How well does the model capture the empirical facts alluded to in the Bloomberg article?

According to the model and the Bloomberg article, it appears that the model captures the empirical facts to a certain degree. The primary finding in the article is that the VIX decreases while realized correlation remains high. The second main finding highlights their similar trends. The two-factor stochastic volatility model can partly explain these observations, with $σ_t^M$ representing the VIX mentioned in the Bloomberg article.

Based on the model, $σ_t^s= \sqrt{((σ_t^I)^2+(β*σ_t^M)^2)}$ and $ρ_t=β*σ_t^M/σ_t^s$. This implies that the correlation between the two is influenced not only by $σ_t^M$, but also by $σ_t^s$ and $β$. This relationship could result in lower VIX values accompanied by high correlation. Based on these observations, we can infer that the model exhibits directional correlation. Nevertheless, it allows for higher profits in up markets compared to down markets. It is not possible to determine whether higher correlation is observed when market volatility increases, as the VIX in this model is influenced by various factors.


### Question 4
#### *Q&A:*
- Using your findings from Question 2, and the column showing the realized vols over the subsequent 60 trading days to 8/26/20, estimate how much money you would have made/lost if the notional value of the market vol swap was $10 million

As the index vol swap means that start at 08/26/2020,I will pay the rate at 22.8% and get a rate at 20.1%. The net payment of mine would be 22.8-20.1=2.7%. By selling individual volatility swaps on the index components, each with equal proportions summing to one, the following results are observed on August 26, 2020: A payment rate of 25.83% is required, corresponding to the simple average of the 60-day historical volatility for the component sector ETFs. Meanwhile, a received rate of 27.4% is calculated, based on the simple average of the implied volatility for the component sector ETFs as of May 26, 2020. This leads to a net payment of -1.57%.Taking both trades into account, the total payment comes to 1.13%. Consequently, a loss of $113000

- What do your results imply about the observations in the Bloomberg column from May 26?

The realized correlation between May 26 and August 26 is lower than the obserbations in the Bloomberg column.
