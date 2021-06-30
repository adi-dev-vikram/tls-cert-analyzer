# tls-cert-analyzer
client side and server side scripts to analyse the tls connection parameters and certs
*.) The python script helps in extracting useful info from a pem format ssl certificate 
For example: CN Name, Subject Alt Name, cipher suite used in TLS Handshake etc.

The script can help in monitoring https configuration and tls cert configurations. And it can inform about incorrect configuration based on cert parameters and required communication modes for example : (IP, FQDN, Hostname fields and SAN field)

To get cert info from cmdline:
openssl s_client -showcerts -connect url:443

openssl x509 -in HTTPSRSAServerCertificate.crt -noout -text
