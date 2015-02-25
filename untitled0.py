# -*- coding: utf-8 -*-
"""
Created on Mon Nov 05 11:23:08 2012

@author: Leniy
"""

import urllib2

#访问的目标网站
leniy_request='http://leniy.info/liuyan'
req = urllib2.Request(leniy_request)

#设置访问的参数
leniy_referer='http://leniy.info/'
leniy_ua='Mozilla/5.0 (Windows NT 6.1; rv:16.0) Gecko/20100101 Firefox/16.0'

req.add_header('Referer', leniy_referer)
req.add_header('User-Agent', leniy_ua)

#开始获取数据
page = urllib2.urlopen(req,timeout=10)
data = page.read()

#后期处理
print data