#ifndef ___LOGGING_H___
#define ___LOGGING_H___

class Logging
{
	public:
		Logging();
		Logging(String file_name);
		Logging(byte pin);
		Logging(byte pin, String file_name);
		~Logging();
		void init();
		void init(byte pin);
        void init(String file_name);
        void init(byte pin, String file_name);
		void attach(byte pin);
		void detach();
		void set_file_name(String file_name);
		bool isInited();
		bool isAttached();
        void log(String text);
	private:
		byte _pin;
        String _file_name;
		bool _attached;
		bool _inited;
};

#endif