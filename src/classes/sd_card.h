#ifndef ___SD_CARD_H___
#define ___SD_CARD_H___

class Sd_card
{
	public:
		Sd_card();
		Sd_card(String file_name);
		Sd_card(byte pin);
		Sd_card(byte pin, String file_name);
		~Sd_card();
		void init();
		void init(byte pin);
		void init(String file_name);
		void init(byte pin, String file_name);
		void attach(byte pin);
		void detach();
		void set_file_name(String file_name);
		bool isInited();
		bool isAttached();
        void saveDataFrame(envSensorData df);
        void sendDataFrame();
	private:
		byte _pin;
        String _file_name;
		bool _attached;
		bool _inited;
};

#endif