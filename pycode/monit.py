import re

r = '(\\<div class="input"\\>[\\s]*\\<div class="prompt input_prompt"\\>[^<]*</div>[\\s]*\\<div class="inner_cell"\\>[\\s]*\\<div class="input_area"\\>[\\s]<div class=" highlight hl-ipython3">[\\s\\S]+?)<div class="output_wrapper">'
    
rr = '(<div class="prompt output_prompt">[\s\S]+?</div>)'

with open('D:\\code\\UIUC_code\\pycode\\answer.html',encoding='utf-8') as f:
    s = f.read()

l = re.findall(r,s)
for i in l:
    s = s.replace(i,'')

l = re.findall(rr,s)
for i in l:
    s = s.replace(i,'')

with open('D:\\code\\UIUC_code\\pycode\\fix_answer.html','w',encoding='utf-8') as f:

    f.write(s)