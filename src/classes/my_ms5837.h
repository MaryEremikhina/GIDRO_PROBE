#ifndef ___MY_MS5837_H___
#define ___MY_MS5837_H___

class My_ms5837
{
	public:
		My_ms5837();
		My_ms5837(String model);
		My_ms5837(int xfact);
		My_ms5837(String model, int xfact);
		~My_ms5837();
		void init();
		void init(String model);
		void init(int xfact);
		void init(String model, int xfact);
		void set_model(String model);
		void set_xFact(int xfact);
		void set_average_number(int average_number);
		bool isInited();
        void update();
		float get_pressure();
        float get_temperature();
        float get_depth();
        float get_altitude();
		float average();
		float average_temp();
		float average_pressure();
		float average_depth();
		float average_altitude();
	private:
		String _model;
		int _xfact;
		bool _inited;
		int _average_number;
		byte counter_pressure;
		byte counter_temp;
		byte counter_depth;
		byte counter_altitude;
};

#endif