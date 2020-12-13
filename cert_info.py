import ssl, socket
from OpenSSL import crypto # pip install pyopenssl

import sys



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
cert_array = crypto.load_certificate(crypto.FILETYPE_PEM, cert)
subject = dict(x[0] for x in cert['subject'])
issued_to = subject['commonName']
subject_altname = cert['subjectAltName']


name = sys.argv[1]
if cert.has_key("subjectAltName"):
        for typ, val in cert["subjectAltName"]:
            if typ == "DNS" and val == name:
                return True


print("+++++++++==============")
print(subject_altname)

print(issued_to)
issuer = dict(x[0] for x in cert['issuer'])
issued_by = issuer['commonName']

print(issued_by)