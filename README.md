# tls-cert-analyzer
client side and server side scripts to analyse the tls connection parameters and certs
*.) The python script helps in extracting useful info from a pem format ssl certificate 
For example: CN Name, Subject Alt Name, cipher suite used in TLS Handshake etc.

The script can help in monitoring https configuration and tls cert configurations. And it can inform about incorrect configuration based on cert parameters and required communication modes for example : (IP, FQDN, Hostname fields and SAN field)

About X.509
X.509 is a specification for digital certificates published by the ITU-T. It specifies information and attributes required for the identification of a server or system, and is used for secure management and distribution of digitally signed certificates across secure Internet networks. OpenSSL most commonly uses X.509 certificates.


To get cert info from cmdline:
openssl s_client -showcerts -connect url:443

openssl x509 -in HTTPSRSAServerCertificate.crt -noout -text

Changes will be added to make sure that SNI extension is able to help client to distinguish the hostname with which it wantes to do HTTPS based communication.
SNI related work:-
You can enable SNI in s_client with the -servername switch:

openssl s_client -servername abc.com -connect abc.com:443

