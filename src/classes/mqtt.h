#ifndef ___MQTT_H___
#define ___MQTT_H___

class MQTT // в иерархии от класса WIFI ???
{
	public:
		MQTT();
        MQTT(char* host, int port);
        MQTT(bool mode);
        MQTT(char* host, int port, bool mode);
		~MQTT();
        void set_host(char* host);
        void set_port(int port);
        void set_mode(bool mode);
        bool get_mode();

        void set_startStatus(bool startStatus);
        bool get_startStatus();
        void set_divingTime(uint32_t divingTime);
        uint32_t get_divingTime();
        void set_swimmingTime(uint32_t swimmingTime);
        uint32_t get_swimmingTime();
        void set_floatingTime(uint32_t floatingTime);
        uint32_t get_floatingTime();
        void set_targetDepth(float targetDepth);
        float get_targetDepth();
        void set_floatingDepth(float targetDepth);
        float get_floatingDepth();

        bool check_connection();
        bool connect();
        void tick();
        void routine();
        void reconnect();
        void log(String msg);
        void send_sensorData(String msg);

        void start_handler();
        void reboot_handler();
        void resetMQTT_handler();
        void resetWIFI_handler();
        void set_divingTime_handler(String msg);
        void set_swimmingTime_handler(String msg);
        void set_floatingTime_handler(String msg);
        void set_targetDepth_handler(String msg);
        void set_servo_handler(String msg);
	private:
		char* _host;
        int _port;
        bool _mode;
        bool _startStatus;

        uint32_t _divingTime;
        uint32_t _swimmingTime;
        uint32_t _floatingTime;
        float _targetDepth;
        float _floatingDepth;

        void callback(char* topic, byte* message, unsigned int length);
};

#endif