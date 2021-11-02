#include <stdio.h>
//#include <curl/curl.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/locale/encoding.hpp>

#define BUFFER_SIZE            1024

using namespace std;


std::string GetCertInfoAsString(X509 *cert);

X509* openPemFile(char* filename)
{

    X509* cert = X509_new();
    BIO* bio_cert = BIO_new_file(filename, "rb");
    PEM_read_bio_X509(bio_cert, &cert, NULL, NULL);
    return cert;
}

std::string GetCertInfoAsString(X509 *pX509Cert)
{
    std::ostringstream ostr;
    std::string certInfoStr = "";
    char buffer[BUFFER_SIZE] = {0,};

    if(NULL != pX509Cert)
    {
        X509_NAME_oneline(X509_get_subject_name(pX509Cert), buffer, BUFFER_SIZE);
        std::string subject = boost::algorithm::replace_all_copy(std::string(buffer), "/", " ");
        ostr << "Subject: " << subject;

        memset((void*)buffer, 0, BUFFER_SIZE);

        X509_NAME_oneline(X509_get_issuer_name(pX509Cert), buffer, BUFFER_SIZE);
        std::string issuer = boost::algorithm::replace_all_copy(std::string(buffer), "/", " ");
        ostr << "\nIssuer: " << issuer;
        memset((void*)buffer, 0, BUFFER_SIZE);

        ostr << "\nType: " << X509_certificate_type(pX509Cert, X509_get_pubkey(pX509Cert));
        ostr << " Serial No.: " << ASN1_INTEGER_get(X509_get_serialNumber(pX509Cert));
        ostr << " Not Before: " << X509_get_notBefore(pX509Cert)->data;
        ostr << " Not After: " << X509_get_notAfter(pX509Cert)->data;
        ostr << " Signature Type: " << X509_get_signature_type(pX509Cert);

        certInfoStr = ostr.str();
	      printf("%s", certInfoStr.c_str());
    }

    return certInfoStr;
}

int main(void)
{

 X509* mycert = openPemFile("cacert.pem");

 std::string certInfo = GetCertInfoAsString(mycert);

//  CURL *curl;
//  CURLcode res;
//  FILE *headerfile;
//  const char *pPassphrase = NULL;

//  static const char *pCertFile = "testcert.pem";
//  static const char *pCACertFile = "cacert.pem";
//  static const char *pHeaderFile = "dumpit";

//  const char *pKeyName;
//  const char *pKeyType;

//  const char *pEngine;

//#ifdef USE_ENGINE
//  pKeyName  = "rsa_test";
//  pKeyType  = "ENG";
//  pEngine   = "chil";            /* for nChiper HSM... */
//#else
//  pKeyName  = "testkey.pem";
//  pKeyType  = "PEM";
//  pEngine   = NULL;
//#endif

//  headerfile = fopen(pHeaderFile, "wb");

//  curl_global_init(CURL_GLOBAL_DEFAULT);

//  curl = curl_easy_init();
//  if(curl) {

//  /* what call to write: */
//    curl_easy_setopt(curl, CURLOPT_URL, "https://servernameurl");
//    curl_easy_setopt(curl, CURLOPT_HEADERDATA, headerfile);

//    do { /* dummy loop, just to break out from */
//      if(pEngine) {
//        /* use crypto engine */
//        if(curl_easy_setopt(curl, CURLOPT_SSLENGINE, pEngine) != CURLE_OK) {
//          /* load the crypto engine */
//          fprintf(stderr, "can't set crypto engine\n");
//          break;
//        }
//        if(curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 1L) != CURLE_OK) {
//          /* set the crypto engine as default */
//          /* only needed for the first time you load
//             a engine in a curl object... */
//          fprintf(stderr, "can't set crypto engine as default\n");
//          break;
//        }
//      }
//      /* cert is stored PEM coded in file... */
//      /* since PEM is default, we needn't set it for PEM */
//      curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");

//      /* set the cert for client authentication */
//      curl_easy_setopt(curl, CURLOPT_SSLCERT, pCertFile);

//      /* sorry, for engine we must set the passphrase
//         (if the key has one...) */
//      if(pPassphrase)
//        curl_easy_setopt(curl, CURLOPT_KEYPASSWD, pPassphrase);

//      /* if we use a key stored in a crypto engine,
//         we must set the key type to "ENG" */
//      curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, pKeyType);

//      /* set the private key (file or ID in engine) */
//      curl_easy_setopt(curl, CURLOPT_SSLKEY, pKeyName);

//      /* set the file with the certs vaildating the server */
//      curl_easy_setopt(curl, CURLOPT_CAINFO, pCACertFile);

//      /* disconnect if we can't validate server's cert */
//      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

//      /* Perform the request, res will get the return code */
//      res = curl_easy_perform(curl);
//      /* Check for errors */
//      if(res != CURLE_OK)
//        fprintf(stderr, "curl_easy_perform() failed: %s\n",
//                curl_easy_strerror(res));

//      /* we are done... */
//    } while(0);
//    /* always cleanup */
//    curl_easy_cleanup(curl);
//  }

//  curl_global_cleanup();

  return 0;
}
