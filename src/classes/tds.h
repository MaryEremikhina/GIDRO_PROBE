#ifndef ___TDS_H___
#define ___TDS_H___

class TDS
{
	public:
		TDS();
		TDS(float vcc, int adc_max);
		TDS(byte pin);
		TDS(byte pin, float vcc, int adc_max);
		~TDS();
		void init();
		void init(float vcc, int adc_max);
		void attach(byte pin);
		void detach();
		void set_vcc(float vcc);
		void set_adcMax(int adc_max);
		void set_average_number(int average_number);
		bool isInited();
		bool isAttached();
		int get_rawData();
        float get_conductivity();
        float get_normConductivity();
        float get_EC();
        float get_TDS();
		float average_normConductivity();
		float average_EC();
		float average_TDS();
		float average();

	private:
		byte _pin;
		bool _attached;
		float _vcc;
		int _adc_max;
		bool _inited;
		int _average_number;
		byte counter_normConductivity;
		byte counter_EC;
		byte counter_TDS;
};

#endif