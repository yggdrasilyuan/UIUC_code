from bs4 import BeautifulSoup
import xlwt
import requests
import random
from time import sleep
import numpy as np
head = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5)\
            AppleWebKit/537.36 (KHTML, like Gecko) Cafari/537.36'}
# head = { \
#         'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.117 Safari/537.36' \
#         }  # 防止HTTP403错误
article_titles = []
article_links = []
user_agent_list = [
  'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_5) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.1.1 Safari/605.1.15',
  'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:77.0) Gecko/20100101 Firefox/77.0',
  'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
  'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:77.0) Gecko/20100101 Firefox/77.0',
  'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
]


def parseInfoAndLink(index,sheet:xlwt.Worksheet,nameList,linkList, soup:BeautifulSoup,end):
    articles = soup.find_all(class_="gs_r gs_or gs_scl")
    cnt = index
    # print(soup.prettify())
    for article in articles:
        article_info = article.h3.string
        if article_info is None:
            try:
                article_info = article.h3.a.string
            except AttributeError as e:
                try:
                    article_info = article.find(id="WICzJFpit-MJ").string ##corner case orz
                except AttributeError as e:
                    article_info = "ERROR"
                finally:
                    pass
            finally:
                pass
        print(str(cnt) +'-'+ article_info) 
        article_links = article.find_all('a')
        link = "NONE"
        for article_link in article_links:
            span = 0
            find = 0
            span = article_link.find_all(name='span')
            if len(span) > 0:
                for tag in span:
                    if tag.string == "[PDF]":
                        find = 1
                        link = article_link["href"]
                        break
            if find:
                break
        # print(link)
        linkList.append(link)
        nameList.append(str(cnt)+'-' + article_info)
        cnt += 1
        sheet.write(cnt,0,str(cnt)+'-' + article_info)
        if cnt == end:
            return

if __name__ == '__main__':
    ## config here

    proxy='127.0.0.1'
    proxies={
    'http':'http://'+proxy+':1087',
    'https':'http://'+proxy+':1087'
    }

    html_addr = "https://scholar.google.com/scholar" 
    html_attri = "&hl=zh-CN&as_sdt=2005&sciodt=0,5&as_ylo=2021&cites=12110830951022031701&scipsc="
    start = 525
    end = 790
    html_str_prefix = html_addr + "?start="; 
    
    ## config end

    ## google scholar encode with index 0 
    rowCnt = 0
    myxls = xlwt.Workbook()
    sheet1 = myxls.add_sheet(u'信息', True)
    #column = ['序号', '文章题目','文章链接','期刊', '作者链接', '摘要']
    column = ['引文编号-引文名','作者','论文出处（论文、书籍、ArXiv\博士论文...）','CCF-A类','IEEE/ACM trans']
    for i in range(0, len(column)):
        sheet1.write(rowCnt, i, column[i])
    rowCnt += 1
    now = start
    print("\n"+"检索中……")
    nameList = []
    linkList = []
    while(now <= end):
        print("getting now at:"+str(now))
        html_url = html_str_prefix + str(now-1) + html_attri 
        user_agent = random.choice(user_agent_list)
        headers = {'User-Agent': user_agent}
        #r = requests.get(html_url, headers=head,proxies = proxies)
        r = requests.get(html_url, headers=head)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        soup = BeautifulSoup(r.text, "html.parser")
        parseInfoAndLink(now,sheet1,nameList,linkList,soup,end)
        now += 10  
        sleep(5)         #sleep for 5 second
    myxls.save("result.xls")
    print("\n"+"检索完成")

    nameListarr=np.array(nameList)
    np.save('nameListarr.npy',nameListarr)
    linkListarr=np.array(linkList)
    np.save('linkListarr.npy',linkListarr)

