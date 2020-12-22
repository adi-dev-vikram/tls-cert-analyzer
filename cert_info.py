#!/usr/bin/env python3

import ssl, socket
import sys
import os



hostname = 'google.com'
ctx = ssl.create_default_context()
with ctx.wrap_socket(socket.socket(), server_hostname=hostname) as s:
    print(s.cipher())
    print(ssl._DEFAULT_CIPHERS)
    s.connect((hostname, 443))
    cert = s.getpeercert()
    if cert is None:
        print("Cert error")

print(cert)

subject = dict(x[0] for x in cert['subject'])
issued_to = subject['commonName']
subject_altname = cert['subjectAltName']


name = sys.argv[1]
name_dns_map={}

print("List of DNS names:")
if "subjectAltName" in cert.keys():
  for typ, val in cert["subjectAltName"]:
    print(typ + ":" + val)
    name_dns_map[typ]=val


print("Cert is Issued to:")

print(issued_to)
issuer = dict(x[0] for x in cert['issuer'])
issued_by = issuer['commonName']

print("Cert is issued by:")

print(issued_by)
