/* soapClient.cpp
   Generated by gSOAP 2.8.30 for webapi.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.30 2017-04-11 06:54:20 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_api__trans(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *msg, char **rtn)
{	struct api__trans soap_tmp_api__trans;
	struct api__transResponse *soap_tmp_api__transResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/myweb.cgi";
	soap_tmp_api__trans.msg = msg;
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_api__trans(soap, &soap_tmp_api__trans);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_api__trans(soap, &soap_tmp_api__trans, "api:trans", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_api__trans(soap, &soap_tmp_api__trans, "api:trans", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!rtn)
		return soap_closesock(soap);
	*rtn = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_api__transResponse = soap_get_api__transResponse(soap, NULL, "", NULL);
	if (!soap_tmp_api__transResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (rtn && soap_tmp_api__transResponse->rtn)
		*rtn = *soap_tmp_api__transResponse->rtn;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_api__get_server_status(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *cmd, char *&status)
{	struct api__get_server_status soap_tmp_api__get_server_status;
	struct api__get_server_statusResponse *soap_tmp_api__get_server_statusResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/myweb.cgi";
	soap_tmp_api__get_server_status.cmd = cmd;
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_api__get_server_status(soap, &soap_tmp_api__get_server_status);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_api__get_server_status(soap, &soap_tmp_api__get_server_status, "api:get-server-status", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_api__get_server_status(soap, &soap_tmp_api__get_server_status, "api:get-server-status", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	status = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_api__get_server_statusResponse = soap_get_api__get_server_statusResponse(soap, NULL, "", NULL);
	if (!soap_tmp_api__get_server_statusResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	status = soap_tmp_api__get_server_statusResponse->status;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_api__login_by_key(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *usr, char *psw, struct ArrayOfEmp2 &ccc)
{	struct api__login_by_key soap_tmp_api__login_by_key;
	struct api__login_by_keyResponse *soap_tmp_api__login_by_keyResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/myweb.cgi";
	soap_tmp_api__login_by_key.usr = usr;
	soap_tmp_api__login_by_key.psw = psw;
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_api__login_by_key(soap, &soap_tmp_api__login_by_key);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_api__login_by_key(soap, &soap_tmp_api__login_by_key, "api:login-by-key", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_api__login_by_key(soap, &soap_tmp_api__login_by_key, "api:login-by-key", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ccc)
		return soap_closesock(soap);
	soap_default_ArrayOfEmp2(soap, &ccc);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_api__login_by_keyResponse = soap_get_api__login_by_keyResponse(soap, NULL, "", NULL);
	if (!soap_tmp_api__login_by_keyResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	ccc = soap_tmp_api__login_by_keyResponse->ccc;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */