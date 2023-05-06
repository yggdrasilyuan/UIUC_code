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
As we know the params like $\mu^S=\mu^M=0$
We can use the equations to eval the params
