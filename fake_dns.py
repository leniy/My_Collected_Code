# -*- coding: utf-8 -*-
"""
Created on Tue Nov 20 09:06:42 2012

@author: Leniy

#伪造dns请求
"""

#!/usr/bin/python

import sys
import libnet
from libnet.constants import * 

l = libnet.context(
                  RAW4,                        # The injection type
                    'eth0'                       # Device name
                      )

dst_ip = l.name2addr4(
                  '10.0.0.197', # Let's get the network byte ordered representation of this IP
                    DONT_RESOLVE
                      )

src_ip = l.name2addr4(
                  '10.0.0.31', # Let's get the network byte ordered representation of this IP
                    DONT_RESOLVE
                      )
#query
import struct
query=struct.pack('b3sb4sb3sbbbbb',3,'www',4,'sina',3,'com',0,0,1,0,1)

dns_tag = l.build_dnsv4(
                        h_len=12,
                        id=2,
                        flags=256,
                        num_q=1,
                        num_anws_rr=0,
                        num_auth_rr=0,
                        num_addi_rr=0,
                        payload=query,
                        )


udp_tag = l.build_udp(
                   dp=53,                      # destination port
                   sum=0,
                   len=38,
                         ) 


# Now onto the IPv4 header
#ipv4_tag = l.autobuild_ipv4(
ipv4_tag = l.build_ipv4(
#                   len=IPV4_H + UDP_H + 12,         # IPV4 packet length
                      prot=IPPROTO_UDP,           # Protocol type
                         dst=dst_ip,
                         src=src_ip,
                            )
#send packet
l.write()