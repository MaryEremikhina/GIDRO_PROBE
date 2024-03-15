#ifndef ___WIFI_H___
#define ___WIFI_H___

class WIFI
{
	public:
        WIFI();
        WIFI(String ssid, String pswd);
        WIFI(bool mode);
        WIFI(String ssid, String pswd, bool mode);
        ~WIFI();
        void setup();
        void stop();
        void set_ssid(String ssid);
        void set_pswd(String pswd);
		void set_mode(bool mode);
        bool get_mode();
        bool check_connection();
	private:
		String _ssid;
        String _pswd;
        bool _mode;
};

#endif