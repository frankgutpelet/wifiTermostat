#include "base.hpp"
#include <ArduinoJson.h>

StaticJsonDocument < 600 > base_doc;
const char base_text[] = "﻿<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n\
<html xmlns=\"http://www.w3.org/1999/xhtml\">\n\
\n\
<head>\n\
	<link rel=\"stylesheet\" style=\"text/css\">\n\
<meta content=\"de\" http-equiv=\"Content-Language\" />\n\
<meta content=\"text/html; charset=utf-8\" http-equiv=\"Content-Type\" />\n\
<title>Embedded Template</title>\n\
<style type=\"text/css\">\n\
\n\
	html {\n\
	  background: linear-gradient(to bottom right, navy, black);\n\
		background-repeat: no-repeat;\n\
		min-height: 100%;\n\
	}\n\
	.button {\n\
	  display: inline-block;\n\
	  padding: 15px 20px;\n\
	  font-size: 20px;\n\
	  cursor: pointer;\n\
	  text-align: center;\n\
	  text-decoration: none;\n\
	  outline: none;\n\
	  color: #fff;\n\
	  background-color: silver;\n\
	  border: none;\n\
	  border-radius: 10px;\n\
	  box-shadow: 0 9px black;\n\
	}\n\
	.auto-style-headline {\n\
    text-transform: uppercase;\n\
    font-family: verdana;\n\
    font-size: 3em;\n\
    font-weight: 700;\n\
    color: #f5f5f5;\n\
    text-shadow: 1px 1px 1px #919191,\n\
        1px 1px 1px #919191,\n\
        1px 2px 1px #919191,\n\
        1px 3px 1px #919191,\n\
        1px 4px 1px #919191,\n\
        1px 5px 1px #919191,\n\
\n\
    1px 18px 6px rgba(16,16,16,0.4),\n\
    1px 22px 10px rgba(16,16,16,0.2),\n\
    1px 25px 35px rgba(16,16,16,0.2);\n\
}\n\
.auto-style3 {\n\
	color: #EEEEEE;\n\
}\n\
.auto-style4 {\n\
	color: #008000;\n\
}\n\
.auto-style5 {\n\
	color: #A70D2A;\n\
}\n\
</style>\n\
\n\
<body>\n\
	<p class=\"auto-style-headline\" id=\"headline\" >Kühlschran Lüftung</p>\n\
	<p class=\"auto-style4\" id=\"version\">unknown</p>\n\
	<table class=\"auto-style3\">\n\
		<tr>\n\
			<td><strong class=\"auto-style4\">Schwellwert unterschreiten: </strong></td>\n\
			<td><strong id=\"setTempMin\"></strong><strong>°C</strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong class=\"auto-style4\">Schwellwert überschreiten: </strong></td>\n\
			<td><strong id=\"setTempMax\"></strong><strong>°C</strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong>Temperatur: </strong></td>\n\
			<td><strong id=\"temp\"></strong><strong>°C</strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong>Status: </strong></td>\n\
			<td><strong id=\"status\"></strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong>Treshold: </strong></td>\n\
			<td><strong id=\"treshold\"></strong><strong>K</strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong>Calibrate: </strong></td>\n\
			<td><strong id=\"calibrate\"></strong><strong>K</strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong class=\"auto-style4\">Schwellwert unterschreiten (mit Freigabe): </strong></td>\n\
			<td><input type=\"text\" id=\"outSetTempMin\" onchange=\"updateDynamicVariable1()\" /></strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong class=\"auto-style4\">Schwellwert überschreiten (mit Freigabe): </strong></td>\n\
			<td><input type=\"text\" id=\"outSetTempMax\" onchange=\"updateDynamicVariable2()\" /></strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong>Treshold (°C): </strong></td>\n\
			<td><input type=\"text\" id=\"outTreshold\" onchange=\"updateDynamicVariable3()\" /></strong></td>\n\
		</tr>\n\
		<tr>\n\
			<td><strong>calibrate (°C): </strong></td>\n\
			<td><input type=\"text\" id=\"outCalibrate\" onchange=\"updateDynamicVariable4()\" /></strong></td>\n\
		</tr>\n\
		<tr></tr>\n\
		<tr>\n\
			<td>\n\
				<form action=\"submit\" method=\"post\">\n\
					<button class=\"button\" id=\"submitBtn\" type=\"submit\" name=\"action\" value=\"\">übernehmen</button>\n\
				</form>\n\
			</td>\n\
		</tr>\n\
\n\
	</table>\n\
</body>\n\
</html>\n\
\n\
<script>\n\
	var values =\n\
	{\n\
		\"setTempMin\" : \"dynamic\",   \n\
		\"setTempMax\" : \"dynamic\",   \n\
		\"outSetTempMin\" : \"dynamic\",\n\
		\"outSetTempMax\" : \"dynamic\",\n\
		\"outTreshold\" : \"dynamic\",  \n\
		\"outCalibrate\" : \"dynamic\", \n\
		\"temp\" : \"dynamic\",         \n\
		\"status\" : \"dynamic\",       \n\
		\"allow\" : \"dynamic\",        \n\
		\"headline\" : \"dynamic\",     \n\
		\"version\" : \"dynamic\",      \n\
		\"treshold\" : \"dynamic\",     \n\
		\"calibrate\" : \"dynamic\",    \n\
	}\n\
	document.title = values.headline\n\
	document.getElementById(\"setTempMin\").innerHTML = values.setTempMin\n\
	document.getElementById(\"setTempMax\").innerHTML = values.setTempMax\n\
	document.getElementById(\"temp\").innerHTML = values.temp\n\
	interval = setInterval(updateValues, 1000)\n\
\n\
	function updateDynamicVariable1()\n\
	{\n\
		values.outSetTempMin = document.getElementById(\"outSetTempMin\").value\n\
		document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
	}\n\
	function updateDynamicVariable2()\n\
	{\n\
		values.outSetTempMax = document.getElementById(\"outSetTempMax\").value\n\
		document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
	}\n\
	function updateDynamicVariable3()\n\
	{\n\
		values.outTreshold = document.getElementById(\"outTreshold\").value\n\
		document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
	}\n\
	function updateDynamicVariable4()\n\
	{\n\
		values.outCalibrate = document.getElementById(\"outCalibrate\").value\n\
		document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
	}\n\
\n\
	function updateValues()\n\
	{\n\
		var xhttp = new XMLHttpRequest();\n\
		xhttp.onreadystatechange = function(){\n\
			pairs = this.responseText.split(\";\");\n\
			for(let i = 0; i < pairs.length; i++)\n\
			{\n\
				pair = pairs[i].split(':');\n\
				if (2 > pair.length) {\n\
					continue;\n\
				}\n\
				values[pair[0]] = pair[1];\n\
				try {\n\
					document.getElementById(pair[0]).innerHTML = pair[1]\n\
				}\n\
				catch (e) {\n\
					console.error(`Unable to set Value for ${pair[0]}: ${pair[1]}\n$`);\n\
				}\n\
			}\n\
		}\n\
		xhttp.open(\"GET\", \"getValues\", true);\n\
		xhttp.send();\n\
	}\n\
\n\
</script>\n\
";

base::base(ESP8266WebServer* server)
{
	this->server = server;
	this->server->on("/submit", std::bind( & base::Submit_Callback, this));
	this->server->on("/getValues", std::bind( & base::GetAjaxValues, this));
}
void base::Submit_Callback(void)
{
	String jsonstring = this->server->arg("action");
	DeserializationError error = deserializeJson(base_doc, jsonstring);
	Serial.println(jsonstring);
	JsonObject obj = base_doc.as < JsonObject > ();

	if (error)
	{
	Serial.print(F("deserializeJson() failed: "));
	Serial.println(error.f_str());
	}
	else
	{
		this->version = obj["version"].as < String > ();
		this->allow = obj["allow"].as < String > ();
		this->outSetTempMax = obj["outSetTempMax"].as < String > ();
		this->outCalibrate = obj["outCalibrate"].as < String > ();
		this->outTreshold = obj["outTreshold"].as < String > ();
		this->temp = obj["temp"].as < String > ();
		this->setTempMax = obj["setTempMax"].as < String > ();
		this->treshold = obj["treshold"].as < String > ();
		this->calibrate = obj["calibrate"].as < String > ();
		this->setTempMin = obj["setTempMin"].as < String > ();
		this->status = obj["status"].as < String > ();
		this->outSetTempMin = obj["outSetTempMin"].as < String > ();
		this->headline = obj["headline"].as < String > ();

	}
	if (NULL != this->Submit_UserCallback)
	{
		this->Submit_UserCallback();
	}
}

void base::Set_version (String value)
{
	this->version = value;
}

String base::Get_version ( void )
{
	return this->version;
}
void base::Set_allow (String value)
{
	this->allow = value;
}

String base::Get_allow ( void )
{
	return this->allow;
}
void base::Set_outSetTempMax (String value)
{
	this->outSetTempMax = value;
}

String base::Get_outSetTempMax ( void )
{
	return this->outSetTempMax;
}
void base::Set_outCalibrate (String value)
{
	this->outCalibrate = value;
}

String base::Get_outCalibrate ( void )
{
	return this->outCalibrate;
}
void base::Set_outTreshold (String value)
{
	this->outTreshold = value;
}

String base::Get_outTreshold ( void )
{
	return this->outTreshold;
}
void base::Set_temp (String value)
{
	this->temp = value;
}

String base::Get_temp ( void )
{
	return this->temp;
}
void base::Set_setTempMax (String value)
{
	this->setTempMax = value;
}

String base::Get_setTempMax ( void )
{
	return this->setTempMax;
}
void base::Set_treshold (String value)
{
	this->treshold = value;
}

String base::Get_treshold ( void )
{
	return this->treshold;
}
void base::Set_calibrate (String value)
{
	this->calibrate = value;
}

String base::Get_calibrate ( void )
{
	return this->calibrate;
}
void base::Set_setTempMin (String value)
{
	this->setTempMin = value;
}

String base::Get_setTempMin ( void )
{
	return this->setTempMin;
}
void base::Set_status (String value)
{
	this->status = value;
}

String base::Get_status ( void )
{
	return this->status;
}
void base::Set_outSetTempMin (String value)
{
	this->outSetTempMin = value;
}

String base::Get_outSetTempMin ( void )
{
	return this->outSetTempMin;
}
void base::Set_headline (String value)
{
	this->headline = value;
}

String base::Get_headline ( void )
{
	return this->headline;
}
void base::Render( void )
{
	this->server->send( 200, "text/html", base_text);
}
void base::GetAjaxValues( void )
{
	String message = "version:" + this->version + ";allow:" + this->allow + ";outSetTempMax:" + this->outSetTempMax + ";outCalibrate:" + this->outCalibrate + ";outTreshold:" + this->outTreshold + ";temp:" + this->temp + ";setTempMax:" + this->setTempMax + ";treshold:" + this->treshold + ";calibrate:" + this->calibrate + ";setTempMin:" + this->setTempMin + ";status:" + this->status + ";outSetTempMin:" + this->outSetTempMin + ";headline:" + this->headline;
	this->server->send(200, "text/plain", message);
}
