#ifndef ___DS12B20_H___
#define ___DS12B20_H___

class Temperature
{
	public:
		Temperature();
		Temperature(byte pin);
		~Temperature();
		void init();
		void attach(byte pin);
		void detach();
		void set_average_number(int average_number);
		bool isInited();
		bool isAttached();
		float get_temperature();
		float average();
	private:
		byte _pin;
		bool _attached;
		bool _inited;
		int _average_number;
		byte counter;
};

#endif