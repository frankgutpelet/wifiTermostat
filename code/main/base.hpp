#include <ESP8266WebServer.h>
#include <Arduino.h>
#pragma once
class base
{
	public:
		base (ESP8266WebServer* server);

		void Render (void);
		void GetAjaxValues (void);
		void SetCallback_submit(void (*callback)(void)) {this->Submit_UserCallback = callback;}
		void Set_version (String value);
		String Get_version ();
		void Set_allow (String value);
		String Get_allow ();
		void Set_outSetTempMax (String value);
		String Get_outSetTempMax ();
		void Set_outCalibrate (String value);
		String Get_outCalibrate ();
		void Set_outTreshold (String value);
		String Get_outTreshold ();
		void Set_temp (String value);
		String Get_temp ();
		void Set_setTempMax (String value);
		String Get_setTempMax ();
		void Set_treshold (String value);
		String Get_treshold ();
		void Set_calibrate (String value);
		String Get_calibrate ();
		void Set_setTempMin (String value);
		String Get_setTempMin ();
		void Set_status (String value);
		String Get_status ();
		void Set_outSetTempMin (String value);
		String Get_outSetTempMin ();
		void Set_headline (String value);
		String Get_headline ();
	private:
		void Submit_Callback(void);
		void (*Submit_UserCallback)(void) = NULL;
		ESP8266WebServer* server;

		String version;
		String allow;
		String outSetTempMax;
		String outCalibrate;
		String outTreshold;
		String temp;
		String setTempMax;
		String treshold;
		String calibrate;
		String setTempMin;
		String status;
		String outSetTempMin;
		String headline;
};