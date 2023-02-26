---
title: Value and Momentum Everywhere
authors:
  - name: First Author
    email: youremail@illinois.edu
    department: Financial Engineering
    affiliation: University of Illinois
  - name: Second Author (optional, continue for third, fourth, etc)
    email: youremail@illinois.edu
    department: Financial Engineering
    affiliation: University of Illinois
abstract: |
  Enter the text of your abstract here. Consider your précis from the summary
  and add 1-3 sentences about your conclusions.  6-10 sentences.
keywords:
  - trading strategies
  - quantitative analysis
  - machine learning
  - these are optional and can be removed
nocite: |
  @PetersonReplication, @jabref, @Rmarkdown, @Peterson2015, @jupyterbook, @jupytext
bibliography: references.bib
bibtex_bibfiles: references.bib
bibtex_default_style: 'alpha'
copyright: Copyright CC-BY ©2023 
output: rticles::arxiv_article 
sphinx:
  config:
    bibtex_reference_style: author_year
    bibtex_bibfiles: "your_reference_file.bib"
jupyter:
  jupytext:
    cell_metadata_filter: -all
    formats: ipynb,md
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.3'
      jupytext_version: 1.14.4
  kernelspec:
    display_name: Python 3 (ipykernel)
    language: python
    name: python3
---

# Introduction

<!-- This is a template for Research Replication projects following the process -->
<!-- outlined in @PetersonReplication.  This template was originally created using Rmarkdown [@Rmarkdown]. -->
<!-- The sample bibliography file was generated via @jabref . The additional sections -->
<!-- in this template will be inserted as comments, and will not be included in the -->
<!-- compiled output. This version of the template has been converted to a Jupyter Notebooks with @jupyterbook and @jupytext -->
<!-- note that I (still) feel that RMarkdown with python code blocks is easier to work in and produces more professional output. --> 

{cite}`jupyterbook`

{cite}`jupytext`



# Paper Summary

<!-- Start with a single paragraph in précis form. -->
<!-- See @PetersonReplication p. 1-2 for details. -->
<!-- Complete this section with paragraphs describing each major point in the paper. -->
<!-- The entire summary will be 4-10 paragraphs. -->


# Hypothesis Overview

<!-- Formally detail the paper's key hypotheses. -->
<!-- See @PetersonReplication p. 2 for details. -->


# Literature Review

<!-- Write your literature review. See @PetersonReplication p. 2-4 for details. This -->
<!-- section must include paragraphs at least for the 3-5 key references for the -->
<!-- paper to be replicated, similar work, implementation references, more recent -->
<!-- references where available, and any references with attempt to refute the -->
<!-- hypotheses of the replicated work.  A full literature review may contain 20-50 -->
<!-- references.  Not all will be covered in the same level of detail.  Important -->
<!-- references probably warrant an entire paragraph, but similar work can probably -->
<!-- be covered together in 1-2 paragraphs for multiple related works. -->
## prior works
Prior to "Value and Momentum Everywhere", there had been a significant amount of research on both value and momentum investing strategies in individual markets, primarily the US stock market. This research had generally shown that both value and momentum strategies could generate excess returns, but there was some debate over which strategy was more effective and whether the two strategies were complementary or in conflict. The "Value and Momentum Everywhere" paper built upon this prior research by examining the performance of value and momentum strategies across a range of asset classes and geographic regions, providing a more comprehensive analysis of these strategies' effectiveness.

Jegadeesh, N., & Titman, S. (1993). Returns to buying winners and selling losers: Implications for stock market efficiency. The Journal of finance, 48(1), 65-91.
The thesis of this paper is that momentum trading generates significant abnormal returns in the US stock market, challenging the efficient market hypothesis. The main findings of the paper are that a simple momentum trading strategy generates abnormal returns that cannot be explained by traditional risk factors and are likely due to behavioral biases or other market frictions. The paper is relevant to "Value and Momentum Everywhere" as it provides empirical evidence for the existence of momentum effects in financial markets and highlights the potential benefits of combining momentum and value strategies. However, it also suggests that momentum strategies come with higher risk and can experience periods of underperformance.

Hong, H.G., & Stein, J.C. (1997). A Unified Theory of Underreaction, Momentum Trading and Overreaction in Asset Markets. Capital Markets: Asset Pricing & Valuation.
The thesis of this paper is that both momentum and contrarian strategies in financial markets can be explained by a combination of behavioral biases, market frictions, and risk considerations. The main findings of the paper are that investors tend to underreact to new information, leading to momentum in stock prices, but then overreact in the subsequent period, creating a reversal in stock prices. The paper is relevant to current research in the field of behavioral finance and has influenced the development of quantitative investment strategies that seek to exploit market inefficiencie

Barberis, N., Shleifer, A.V., & Vishny, R.W. (1997). A Model of Investor Sentiment. Behavioral & Experimental Finance.
The thesis of the paper is that investor sentiment, or the tendency for investors to be overly optimistic or pessimistic about the prospects of the stock market, can explain many of the anomalies in financial markets.The main points of the paper include the development of a theoretical model that incorporates investor sentiment, the examination of how sentiment affects stock prices, and the analysis of how sentiment can help explain a range of market anomalies, including the value and momentum effects.The paper is relevant to "Value and Momentum Everywhere" as it provides a theoretical explanation for the existence of these market anomalies based on investor sentiment. It also suggests that sentiment can help to explain the performance of these strategies over time and highlights the importance of considering behavioral factors in financial market analysis.

Fama, E.F., & French, K.R. (1993). Common risk factors in the returns on stocks and bonds. Journal of Financial Economics, 33, 3-56.
The thesis of the paper is that the returns on stocks and bonds can be explained by a small number of common risk factors, including the market risk, size, and value factors.The main points of the paper include the development of a three-factor model that explains the variation in stock returns based on market risk, size, and book-to-market ratios, the examination of how this model can be used to explain a range of market anomalies, including the value and momentum effects, and the analysis of how the model can be used to construct portfolios with higher expected returns.The paper is relevant to the main paper as it provides a theoretical foundation for understanding the value and momentum effects in financial markets. 

Fama, E.F., & French, K.R. (1996). Multifactor Explanations of Asset Pricing Anomalies. Journal of Finance, 51, 55-84.
The thesis of the paper is that many of the previously identified market anomalies, including the value and momentum effects, can be explained by a small number of fundamental factors, such as company size and book-to-market ratio.The main findings of the paper include the identification of several factors that explain the cross-sectional variation in stock returns, the demonstration that many of the previously identified anomalies disappear once these factors are accounted for, and the suggestion that the value and momentum effects may be subsumed by a multifactor model.As it provides an alternative explanation for the existence of these market anomalies, based on fundamental factors rather than behavioral biases.

Hong, H.G., Lim, T., & Stein, J.C. (1998). Bad News Travels Slowly: Size, Analyst Coverage and the Profitability of Momentum Strategies. Capital Markets: Market Efficiency.
The paper provides that momentum strategies are more profitable for smaller firms with less analyst coverage because bad news travels more slowly for these firms, allowing momentum to persist for longer periods.The main points of the paper include the analysis of how firm size and analyst coverage affect momentum profitability, the identification of a link between momentum profits and the speed of information diffusion, and the examination of the role of market frictions in sustaining momentum profits.The paper is relevant to the topic paper as it provides a potential explanation for why momentum strategies are more profitable for certain types of stocks, particularly those with less analyst coverage. 

Johnson, T.C. (2001). Rational Momentum Effects. Journal of Financial Abstracts eJournal.
The thesis of the paper is that momentum in stock prices can be rational and explained by time-varying expected returns based on changes in risk and investor preferences.The main points of the paper include the examination of the underlying factors that drive momentum in financial markets, the analysis of how rational momentum differs from behavioral momentum, and the exploration of how rational momentum can be used to construct profitable investment strategies.The paper is relevant as it provides an alternative explanation for the existence of momentum effects in financial markets that is based on rational economic theory. It also suggests that momentum strategies can be rational and profitable, rather than simply being the result of behavioral biases or market frictions. 

Bondt, W.D., & Thaler, R.H. (1985). Does the Stock Market Overreact. Journal of Finance, 40, 793-805.
The thesis of the paper is that the stock market tends to overreact to news and events, leading to periods of over- and under-performance that can be exploited by contrarian investment strategies.The main points of the paper include the examination of the performance of past stock market winners and losers, the identification of a reversal effect in stock prices, and the analysis of how this effect can be used to generate abnormal returns.The paper is relevant as it highlights the importance of contrarian investment strategies, which seek to buy underperforming stocks and sell outperforming ones. It also suggests that market inefficiencies can persist over time, and that these inefficiencies can be exploited using both value and momentum strategies.

Lo, A.W., & Mackinlay, A. (1989). When are Contrarian Profits Due to Stock Market Overreaction? Behavioral & Experimental Finance eJournal.
The thesis of the paper is that contrarian profits in financial markets can be due to overreaction by investors to news and events, rather than simply being a result of mean reversion.The main points of the paper include the development of a theoretical model that incorporates investor overreaction, the examination of how this can lead to contrarian profits, and the analysis of how market conditions can affect the magnitude and persistence of these profits.The paper is relevant to the topic paper as it provides a potential explanation for the value effect, which is often attributed to mean reversion, and suggests that it may be driven in part by investor overreaction. 

Berk, J.B., Green, R., & Naik, V. (1998). Optimal Investment, Growth Options, and Security Returns. NBER Working Paper Series.
The thesis of the paper is that the value of a firm's growth options can affect the expected returns of its stock and other securities.The main points of the paper include the development of a theoretical model that incorporates growth options, the analysis of how the value of these options affects the firm's investment decisions and stock returns, and the examination of how these effects can be incorporated into investment strategies.Overall, the paper highlights the importance of considering a range of factors, including growth options, when developing investment strategies based on value and momentum signals.


Asness, C. S. (1995). The power of past stock returns to explain future stock returns. Available at SSRN 2865769.
The thesis of the paper is that past stock returns have predictive power for future stock returns, even after controlling for other factors like book-to-market ratios and dividend yields.The main findings of the paper are that a simple momentum trading strategy based on past stock returns generates significant abnormal returns, and that these returns cannot be explained by traditional risk factors. The paper also suggests that momentum strategies are more effective for small stocks and during periods of market turbulence.The paper is relevant to "Value and Momentum Everywhere" as it provides empirical evidence for the existence of momentum effects in financial markets. It also highlights the potential benefits of combining momentum and value strategies, as momentum strategies can be more effective for small stocks and during periods of market turbulence, while value strategies can help to mitigate the risks associated with momentum investing.

## derivative works
"Value and Momentum Everywhere" has inspired numerous derivative works, including papers that refine the original momentum and value strategies, explore their performance across different countries and asset classes, and examine the role of other factors like liquidity, volatility, and investor sentiment. Some of these works have also sought to combine momentum and value strategies with other factors, such as quality and low volatility, to create more robust investment strategies. Overall, these derivative works have helped to advance our understanding of the factors that drive asset returns and have contributed to the development of more sophisticated investment strategies.

Zaremba, A., & Shemer, J. (2017). Trend Is Your Friend: Momentum Investing.


# Replication

<!-- Now we move on to the actual replication.  The sections included here are all -->
<!-- necessary, but the may not be sufficient.  Add additional sections and sub-sections -->
<!-- as required to describe your work and make your analytical case. -->

## Data

<!-- Describe the approach that the replication is taking to Data. -->
<!-- See @PetersonReplication p. 4-5 for details. -->
<!-- Describe both the data used in the original paper, and the data you are using -->
<!-- for replication.  For your replicated data, include detailed descriptions of -->
<!-- obtaining, parsing, and cleaning the data to prepare it for use.  Describe data -->
<!-- quality issues. -->


## Replication of Key Analytical Techniques

<!-- Model the Key Analytical Techniques from the paper to be replicated. -->
<!-- See @PetersonReplication p. 5-6 for details. -->
<!-- This section will vary significantly based on the paper being replicated. -->
<!-- Describe your process as you work, documenting the steps you are taking, -->
<!-- referencing any libraries, websites, or third party code that you use as part of -->
<!-- your replication, and the decree to which your replication agrees or disagrees -->
<!-- with the source material. Be sure to include summary statistics used in the -->
<!-- original paper, as well as any additional summary statistics that you feel are -->
<!-- relevant for checking the quality of your replication. -->

### Technique 1

### Technique 2

### Technique 3


## Hypothesis Tests

<!-- After replicating the initial work, it is time to evaluate the hypotheses of -->
<!-- the replicated work. Those hypotheses were identified above, before you started -->
<!-- replication. Describe, in detail, the statistical tests you perform to refute or -->
<!-- validate the hypotheses in the replicated work.  This should go beyond any explicit -->
<!-- tests performed in the original paper. -->


## Extended Analysis

<!-- Extend the analysis with more (recent) data or additional asset classes, and/or -->
<!-- replicate similar or extended techniques and compare them to the original paper's methods. -->
<!-- See @PetersonReplication p. 6-7 for details. -->


## Overfitting

<!-- Analyze the likelihood that the original paper is overfit.  Include data -->
<!-- considerations, experiment design, model assumptions, parameterization, and -->
<!-- biases, out of sample results, etc.  Assess how changes to these affects -->
<!-- results, and produce an opinion on whether and how the original work is overfit, -->
<!-- as well as what might be doable to reduce the degree of overfitting, and whether -->
<!-- the main results would hold if the level of overfitting were reduced. -->


# Future Work

<!-- What additional work on this topic should be performed in the future, if this -->
<!-- project were to be picked up again or continued? -->


# Conclusions

<!-- Summarize the project and describe your conclusions.  This sections can -->
<!-- range from 1-2 paragraphs to 1-2 pages. -->

\newpage 

![CC-BY](cc_by_88x31.png)

# References

```{bibliography}

```


