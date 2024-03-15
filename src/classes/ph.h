#ifndef ___PH_H___
#define ___PH_H___

class PH
{
	public:
		PH();
		PH(float vcc, int adc_max, float xfact);
		PH(byte pin);
		PH(byte pin, float vcc, int adc_max, float xfact);
		~PH();
		void init();
		void init(float vcc, int adc_max, float xfact);
		void attach(byte pin);
		void detach();
		void set_vcc(float vcc);
		void set_adcMax(int adc_max);
		void set_xFact(float xfact);
		void set_average_number(int average_number);
		bool isInited();
		bool isAttached();
		int get_rawData();
		float get_ph();
		float average();
	private:
		byte _pin;
		bool _attached;
		float _vcc;
		float _xfact;
		int _adc_max;
		bool _inited;
		int _average_number;
		byte counter;
};

#endif