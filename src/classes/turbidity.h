#ifndef ___TURBIDITY_H___
#define ___TURBIDITY_H___

class Turbidity
{
	public:
		Turbidity();
		Turbidity(float xfact);
		Turbidity(byte pin);
		Turbidity(byte pin, float xfact);
		~Turbidity();
		void init();
		void init(float xfact);
		void attach(byte pin);
		void detach();
		void set_xFact(float xfact);
		void set_average_number(int average_number);
		bool isInited();
		bool isAttached();
		int get_rawData();
		float get_turbidity();
		float average();
	private:
		byte _pin;
		bool _attached;
		float _xfact;
		bool _inited;
		int _average_number;
		byte counter;
};

#endif